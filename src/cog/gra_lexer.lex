%option reentrant
%option never-interactive
%option bison-bridge
%option bison-locations
%option yylineno
%option noyywrap
%option case-insensitive
%option prefix="gra_"
%option stack

%{
	#include "gra_context.h"
	#include "err_code.h"
	#include "err_location.h"
	#include "err_report.h"
	#include "gra_parser.hpp"
	#include "err_helper.h"

	#include <string.h>
	#include <stdlib.h>
	#include <sstream>
	#include <iostream>

	// Resolve warnings in Visual C++:
	#ifdef _MSC_VER
	#define isatty _isatty
	#define fileno _fileno
	#define strdup _strdup

	#pragma warning(disable: 4267)
	#pragma warning(disable: 4244)
	#pragma warning(disable: 4996)
	#endif

	#define YY_EXTRA_TYPE Cog::Grammar::Context*
	#define YY_USER_ACTION									\
	{														\
		if(yylloc->first_line != yylineno) yycolumn = 1;	\
		yylloc->first_line = yylloc->last_line = yylineno;	\
		yylloc->first_column = yycolumn;					\
		yylloc->last_column = yycolumn + yyleng - 1;		\
		yycolumn += yyleng;									\
	}

	#define YY_INPUT(buf, result, max_size)					\
	{														\
		buf[0] = yyextra->GetNext();						\
		if(buf[0] == '\0') result = YY_NULL;				\
		else result = 1;									\
	}

	int parse_hex_int(char*);

%}

D			[0-9]
L			[_a-zA-Z]
H			[a-fA-F0-9]
E			[Ee][+-]?{D}+

%x CODE_SECTION
%x SYMBOL_FIELD
%x SYMBOL_SECTION
%x SYMBOL_DEF
%x SYMBOL_DEF_ASSIGN
%x SYMBOL_EXT_SECTION
%x LINE_COMMENT
%x STRING

%%

<LINE_COMMENT>\n			{ yy_pop_state(yyextra->GetScanner()); yycolumn = 1; }
<LINE_COMMENT>.				/* eat non-terminal input */

<SYMBOL_FIELD>{
	[+-]?0x{H}+				{
								yy_pop_state(yyextra->GetScanner());
								yylval->integer = parse_hex_int(yytext);
								return INTEGER_LITERAL;
							}

	[+-]?{D}+				{
								yy_pop_state(yyextra->GetScanner());
								yylval->integer = atoi(yytext);
								return INTEGER_LITERAL;
							}

	[+-]?{D}+{E}			{
								yy_pop_state(yyextra->GetScanner());
								yylval->floating = static_cast<float>(atof(yytext));
								return FLOAT_LITERAL;
							}

	[+-]?{D}*"."{D}+({E})?	{
								yy_pop_state(yyextra->GetScanner());
								yylval->floating = static_cast<float>(atof(yytext));
								return FLOAT_LITERAL;
							}

	[+-]?{D}+"."{D}*({E})?	{
								yy_pop_state(yyextra->GetScanner());
								yylval->floating = static_cast<float>(atof(yytext));
								return FLOAT_LITERAL;
							}

	[^[:space:]^=]+			{
								yy_pop_state(yyextra->GetScanner());
								yylval->string = strdup(yytext);
								return STRING_FRAGMENT;
							}

	[[:space:]]				/* Ignore other whitespace */
}

<SYMBOL_SECTION,SYMBOL_DEF,SYMBOL_DEF_ASSIGN,SYMBOL_EXT_SECTION>{
	"#"|"//"				{
								yy_pop_state(yyextra->GetScanner());
								yy_push_state(SYMBOL_SECTION, yyextra->GetScanner());
								yy_push_state(LINE_COMMENT, yyextra->GetScanner());
								return ENDLINE;
							}

	"end"					{ yy_pop_state(yyextra->GetScanner()); return END; }

	"="						{
								yy_pop_state(yyextra->GetScanner());
								yy_push_state(SYMBOL_EXT_SECTION, yyextra->GetScanner());
								yy_push_state(SYMBOL_FIELD, yyextra->GetScanner());
								return '=';
							}

	"\n"					{
								yy_pop_state(yyextra->GetScanner());
								yy_push_state(SYMBOL_SECTION, yyextra->GetScanner());
								return ENDLINE;
							}

	[[:space:]]				/* Ignore other whitespace */
}

<SYMBOL_EXT_SECTION>{
	{L}({L}|{D})*			{ yylval->string = strdup(yytext); return IDENTIFIER; }
	","						/* Ignore commas */
}

<SYMBOL_DEF_ASSIGN>{L}({L}|{D})*	{
								yy_pop_state(yyextra->GetScanner());
								yy_push_state(SYMBOL_EXT_SECTION, yyextra->GetScanner());
								yylval->string = strdup(yytext);
								return IDENTIFIER;
							}

<SYMBOL_DEF>{L}({L}|{D})*	{
								yy_pop_state(yyextra->GetScanner());
								yy_push_state(SYMBOL_DEF_ASSIGN, yyextra->GetScanner());
								yylval->string = strdup(yytext);
								return IDENTIFIER;
							}

<SYMBOL_SECTION>{L}({L}|{D})*	{
									yy_pop_state(yyextra->GetScanner());
									yy_push_state(SYMBOL_DEF, yyextra->GetScanner());
									yylval->string = strdup(yytext);
									return IDENTIFIER;
								}

<STRING>{
	<<EOF>>					{
								Cog::Error::Helper::EofInStringLiteral(yyextra->GetErrorReport(),
									yyextra->GetFilename(), Cog::Error::Location(yylloc->first_line,
										yylloc->first_column, yylloc->last_line, yylloc->last_column));
							}

	\"						{
								yy_pop_state(yyextra->GetScanner());
								yylval->string = strdup(yyextra->TokenBuffer.c_str());
								return STRING_LITERAL;
							}

	\n						{
								Cog::Error::Helper::UnescapedNewlineInString(yyextra->GetErrorReport(),
									yyextra->GetFilename(), Cog::Error::Location(yylloc->first_line,
										yylloc->first_column, yylloc->last_line, yylloc->last_column));
							}

	\\\n					/* Consume escaped newlines */

	\\["\\]					{ yyextra->TokenBuffer.push_back(yytext[1]); }

	\\n						{ yyextra->TokenBuffer.push_back('\n'); }

	\\.						{
								Cog::Error::Helper::UnknownEscapeSequence(yyextra->GetErrorReport(), yytext,
									yyextra->GetFilename(), Cog::Error::Location(yylloc->first_line,
										yylloc->first_column, yylloc->last_line, yylloc->last_column));
							}

	.						{ yyextra->TokenBuffer.append(yytext); }
}

<CODE_SECTION>{
	"#"						{ yy_push_state(LINE_COMMENT, yyextra->GetScanner()); }
	"//"					{ yy_push_state(LINE_COMMENT, yyextra->GetScanner()); }
	"end"					{ yy_pop_state(yyextra->GetScanner()); return END; }

	\"						{ yy_push_state(STRING, yyextra->GetScanner()); yyextra->TokenBuffer.clear(); }

	"break"					{ return BREAK; }
	"call"					{ return CALL; }
	"do"					{ return DO; }
	"else"					{ return ELSE; }
	"for"					{ return FOR; }
	"if"					{ return IF; }
	"return"				{ return RETURN; }
	"stop"					{ return RETURN; }
	"while"					{ return WHILE; }

	{L}({L}|{D})*			{ yylval->string = strdup(yytext); return IDENTIFIER; }

	0x{H}+					{ yylval->integer = parse_hex_int(yytext); return INTEGER_LITERAL; }
	{D}+					{ yylval->integer = atoi(yytext); return INTEGER_LITERAL; }

	{D}+{E}					{ yylval->floating = static_cast<float>(atof(yytext)); return FLOAT_LITERAL; }
	{D}*"."{D}+({E})?		{ yylval->floating = static_cast<float>(atof(yytext)); return FLOAT_LITERAL; }
	{D}+"."{D}*({E})?		{ yylval->floating = static_cast<float>(atof(yytext)); return FLOAT_LITERAL; }

	"=="					{ return EQ_OP; }
	"!="					{ return NE_OP; }
	">="					{ return GE_OP; }
	"<="					{ return LE_OP; }

	"&&"					{ return LOGICAL_AND_OP; }
	"||"					{ return LOGICAL_OR_OP; }

	":"						{ return ':'; }
	";"						{ return ';'; }
	","						{ return ','; }

	"\'"					{ return '\''; }

	"+"						{ return '+'; }
	"-"						{ return '-'; }
	"*"						{ return '*'; }
	"/"						{ return '/'; }
	"%"						{ return '%'; }

	"!"						{ return '!'; }

	"&"						{ return '&'; }
	"|"						{ return '|'; }
	"^"						{ return '^'; }

	"="						{ return '='; }

	"{"						{ return '{'; }
	"}"						{ return '}'; }
	"("						{ return '('; }
	")"						{ return ')'; }
	"<"						{ return '<'; }
	">"						{ return '>'; }
	"["						{ return '['; }
	"]"						{ return ']'; }

	[[:space:]]				/* Ignore whitespace */
}

<INITIAL>{
	"#"						{ yy_push_state(LINE_COMMENT, yyextra->GetScanner()); }
	"symbols"				{ yy_push_state(SYMBOL_SECTION, yyextra->GetScanner()); return SYMBOLS; }
	"code"					{ yy_push_state(CODE_SECTION, yyextra->GetScanner()); return CODE; }

	[[:space:]]				/* Ignore whitespace */
}

<INITIAL,SYMBOL_FIELD,SYMBOL_SECTION,SYMBOL_DEF,SYMBOL_DEF_ASSIGN,SYMBOL_EXT_SECTION,CODE_SECTION>.		{
								Cog::Error::Helper::UnrecognizedInput(yyextra->GetErrorReport(), yytext,
									yyextra->GetFilename(), Cog::Error::Location(yylloc->first_line,
										yylloc->first_column, yylloc->last_line, yylloc->last_column));
							}

%%

int parse_hex_int(char* str)
{
	if(str[0] == '\0' || str[1] == '\0') return 0;

	int i = 0;
	while(str[i] != '\0' && isspace(str[i]))
	{
		++i;
	}

	bool is_negative = false;
	if(str[i] == '+')
	{
		++i;
	}
	else if(str[i] == '-')
	{
		is_negative = true;
		++i;
	}

	if(str[i] != '0')
	{
		return 0;
	}

	++i;

	if(str[i] != 'x' && str[i] != 'X')
	{
		return 0;
	}

	++i;

	int retval = 0;
	while(str[i] != '\0')
	{
		retval <<= 4;
		retval += str[i] & 0xF;
		if(str[i] & 0x40)
		{
			retval += 10;
		}

		++i;
	}

	if(is_negative)
	{
		return -retval;
	}
	else
	{
		return retval;
	}
}

void Cog::Grammar::Context::InitScanner()
{
	yylex_init(&scanner);
	yyset_extra(this, scanner);
}

void Cog::Grammar::Context::DestroyScanner()
{
	yylex_destroy(scanner);
}

