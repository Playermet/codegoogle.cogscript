#include "gra_context.h"
#include <iostream>
#include <exception>

Cog::Grammar::Context::Context(const std::string& fn, std::istream& file,
	Error::Report& report, AST::Factory& factory)
	: filename(fn), inputFilestream(file), errorReport(report), astFactory(factory)
{
	InitScanner();
	return;
}

Cog::Grammar::Context::~Context()
{
	DestroyScanner();
	return;
}

char Cog::Grammar::Context::GetNext()
{
	try
	{
		char c = inputFilestream.get();
		if(inputFilestream.good())
		{
			return c;
		}
		else
		{
			return '\0';
		}
	}
	catch(const std::exception&)
	{
		return '\0';
	}
}

int gra_parse(Cog::Grammar::Context*);

void Cog::Grammar::Context::Parse()
{
	gra_parse(this);
}
