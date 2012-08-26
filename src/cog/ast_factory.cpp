#include "ast_factory.h"

using namespace Cog::AST;

Factory::Factory(const std::string& filename)
	: current_filename(filename)
{
	return;
}

Factory::~Factory()
{
	// Nodes were created with Arena and placement new.
	// Call destructors on all nodes to free associated members
	for(auto it = nodes.begin(); it != nodes.end(); ++it)
	{
		(*it)->~Node();
	}

	return;
}

StringFragmentField* Factory::MakeStringFragmentField(const char* text, YYLTYPE& yyl)
{
	MAKE(StringFragmentField);
	val->Value = text;
	return val;
}

IntegerField* Factory::MakeIntegerField(int value, YYLTYPE& yyl)
{
	MAKE(IntegerField);
	val->Value = value;
	return val;
}

FloatField* Factory::MakeFloatField(float value, YYLTYPE& yyl)
{
	MAKE(FloatField);
	val->Value = value;
	return val;
}

BareExtension* Factory::MakeBareExtension(const char* name, YYLTYPE& yyl)
{
	MAKE(BareExtension);
	val->Name = name;
	return val;
}

ValuedExtension* Factory::MakeValuedExtension(const char* name, SymbolField* value, YYLTYPE& yyl)
{
	MAKE(ValuedExtension);
	val->Name = name;
	val->Value = value;
	return val;
}

Symbol* Factory::MakeSymbol(const char* type, const char* name, std::vector<SymbolExtension*>* extensions, YYLTYPE& yyl)
{
	MAKE(Symbol);
	val->Type = type;
	val->Name = name;
	val->Extensions = extensions;
	return val;
}

ValuedSymbol* Factory::MakeValuedSymbol(const char* type, const char* name, std::vector<SymbolExtension*>* extensions, SymbolField* value, YYLTYPE& yyl)
{
	MAKE(ValuedSymbol);
	val->Type = type;
	val->Name = name;
	val->Extensions = extensions;
	val->Value = value;
	return val;
}

ConstantValueExpression* Factory::MakeConstantValueExpression(const Cog::VirtualMachine::Value& value, const std::string* filename, const Cog::Error::Location& loc)
{
	MAKE_NOLINES(ConstantValueExpression);
	val->Filename = filename;
	val->Location = loc;
	val->Value = value;
	return val;
}

StringLiteralExpression* Factory::MakeStringLiteralExpression(const char* value, YYLTYPE& yyl)
{
	MAKE(StringLiteralExpression);
	val->Value = value;
	return val;
}

IntegerLiteralExpression* Factory::MakeIntegerLiteralExpression(int value, YYLTYPE& yyl)
{
	MAKE(IntegerLiteralExpression);
	val->Value = value;
	return val;
}

FloatLiteralExpression* Factory::MakeFloatLiteralExpression(float value, YYLTYPE& yyl)
{
	MAKE(FloatLiteralExpression);
	val->Value = value;
	return val;
}

VectorLiteralExpression* Factory::MakeVectorLiteralExpression(float x, float y, float z, YYLTYPE& yyl)
{
	MAKE(VectorLiteralExpression);
	val->X = x;
	val->Y = y;
	val->Z = z;
	return val;
}

IdentifierExpression* Factory::MakeIdentifierExpression(const char* identifier, YYLTYPE& yyl)
{
	MAKE(IdentifierExpression);
	val->Identifier = identifier;
	return val;
}

SubscriptExpression* Factory::MakeSubscriptExpression(const char* base, Expression* index, YYLTYPE& yyl)
{
	MAKE(SubscriptExpression);
	val->Base = base;
	val->Index = index;
	return val;
}

MethodCallExpression* Factory::MakeMethodCallExpression(const char* base, std::vector<Expression*>* arguments, YYLTYPE& yyl)
{
	MAKE(MethodCallExpression);
	val->Base = base;
	val->Arguments = arguments;
	return val;
}

UnaryExpression* Factory::MakeUnaryExpression(Expression* base, UnaryOperator::Enum op, YYLTYPE& yyl)
{
	MAKE(UnaryExpression);
	val->Base = base;
	val->Operator = op;
	return val;
}

InfixExpression* Factory::MakeInfixExpression(Expression* left, Expression* right, InfixOperator::Enum op, YYLTYPE& yyl)
{
	MAKE(InfixExpression);
	val->Left = left;
	val->Right = right;
	val->Operator = op;
	return val;
}

AssignmentExpression* Factory::MakeAssignmentExpression(Expression* target, Expression* value, YYLTYPE& yyl)
{
	MAKE(AssignmentExpression);
	val->Target = target;
	val->Value = value;
	return val;
}

CommaExpression* Factory::MakeCommaExpression(Expression* left, Expression* right, YYLTYPE& yyl)
{
	MAKE(CommaExpression);
	val->Left = left;
	val->Right = right;
	return val;
}

CompoundStatement* Factory::MakeCompoundStatement(std::vector<Statement*>* code, YYLTYPE& yyl)
{
	MAKE(CompoundStatement);
	val->Code = code;
	return val;
}

EmptyStatement* Factory::MakeEmptyStatement(YYLTYPE& yyl)
{
	MAKE(EmptyStatement);
	return val;
}

ExpressionStatement* Factory::MakeExpressionStatement(Expression* expression, YYLTYPE& yyl)
{
	MAKE(ExpressionStatement);
	val->Expression = expression;
	return val;
}

BreakStatement* Factory::MakeBreakStatement(YYLTYPE& yyl)
{
	MAKE(BreakStatement);
	return val;
}

ReturnStatement* Factory::MakeReturnStatement(YYLTYPE& yyl)
{
	MAKE(ReturnStatement);
	return val;
}

CallStatement* Factory::MakeCallStatement(const char* label, YYLTYPE& yyl)
{
	MAKE(CallStatement);
	val->Label = label;
	return val;
}

IfStatement* Factory::MakeIfStatement(Expression* condition, Statement* code, YYLTYPE& yyl)
{
	MAKE(IfStatement);
	val->Condition = condition;
	val->Code = code;
	return val;
}

IfElseStatement* Factory::MakeIfElseStatement(Expression* condition, Statement* code, Statement* elsecode, YYLTYPE& yyl)
{
	MAKE(IfElseStatement);
	val->Condition = condition;
	val->Code = code;
	val->ElseCode = elsecode;
	return val;
}

WhileStatement* Factory::MakeWhileStatement(Expression* condition, Statement* code, YYLTYPE& yyl)
{
	MAKE(WhileStatement);
	val->Condition = condition;
	val->Code = code;
	return val;
}

DoStatement* Factory::MakeDoStatement(Statement* code, Expression* condition, YYLTYPE& yyl)
{
	MAKE(DoStatement);
	val->Code = code;
	val->Condition = condition;
	return val;
}

ForOptionalExpression* Factory::MakeForOptionalExpression(YYLTYPE& yyl)
{
	MAKE(ForOptionalExpression);
	return val;
}

ForExpression* Factory::MakeForExpression(Expression* condition, YYLTYPE& yyl)
{
	MAKE(ForExpression);
	val->Condition = condition;
	return val;
}

ForStatement* Factory::MakeForStatement(ForOptionalExpression* initializer, ForOptionalExpression* condition, ForOptionalExpression* incrementer, Statement* code, YYLTYPE& yyl)
{
	MAKE(ForStatement);
	val->Initializer = initializer;
	val->Condition = condition;
	val->Incrementer = incrementer;
	val->Code = code;
	return val;
}

LabeledStatement* Factory::MakeLabeledStatement(const char* label, Statement* code, YYLTYPE& yyl)
{
	MAKE(LabeledStatement);
	val->Label = label;
	val->Code = code;
	return val;
}

TranslationUnit* Factory::MakeTranslationUnit(std::vector<Symbol*>* symbols, std::vector<Statement*>* code, YYLTYPE& yyl)
{
	MAKE(TranslationUnit);
	val->Symbols = symbols;
	val->Code = code;
	return val;
}
