#include "semantic_test_fixture.h"
#include "cog/cog_stages.h"
#include <fstream>

using namespace Cog;

SemanticTestFixture::SemanticTestFixture(const std::string& basePath)
	: SyntacticTestFixture(basePath)
{
	return;
}

void SemanticTestFixture::ParseFile(const boost::filesystem::path& path)
{
	std::string fn = (BasePath / path).string();
	std::ifstream cogfile(fn);

	Cog::AST::Factory astFactory(fn);
	
	AST::TranslationUnit* ast = Cog::Stages::Stage1::GenerateAST(fn, cogfile, Report, astFactory);

	if(Report.GetErrorCount() > 0)
	{
		return;
	}

	Stages::Stage2::SemanticAnalysis(ast, Script.SymbolTable, ConstantTable, VerbTable, Report);
}
