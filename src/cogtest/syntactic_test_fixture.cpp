#include "syntactic_test_fixture.h"
#include "cog/cog_stages.h"
#include <fstream>

SyntacticTestFixture::SyntacticTestFixture(const std::string& basePath)
	: BasePath(basePath)
{
	return;
}

void SyntacticTestFixture::ParseFile(const boost::filesystem::path& path)
{
	std::string fn = (BasePath / path).string();
	std::ifstream cogfile(fn);

	Cog::AST::Factory astFactory(fn);
	Cog::Stages::Stage1::GenerateAST(fn, cogfile, Report, astFactory);
}

void SyntacticTestFixture::PrintErrors() const
{
	for(auto it = Report.ErrorBegin(); it != Report.ErrorEnd(); ++it)
	{
		NullUnit::Test_Reporter->CaseExpectationFail(
			NullUnit::Test_Suite_Name,
			NullUnit::Test_Case_Name,
			static_cast<std::string>(*it),
			it->Filename, it->ErrorLocation.first_line);
	}
}
