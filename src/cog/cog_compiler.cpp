#include "cog_compiler.h"
#include "ast_factory.h"
#include "cog_stages.h"
#include "ir_codeprinter.h"
#include <iostream>

Cog::Compiler::Compiler(Verbs::VerbTable& verbTable)
	: VerbTable(verbTable)
{
	// The constant and message tables must associate string message names with
	// numeric values.
	// Populate these tables:
#define MSGDEF(x, y) ConstantTable.insert(std::make_pair(x, y)); MessageTable.insert(std::make_pair(x, y))
	MSGDEF("activate", Cog::MessageId::Activated);
	MSGDEF("activated", Cog::MessageId::Activated);
	MSGDEF("aievent", Cog::MessageId::AiEvent);
	MSGDEF("arrived", Cog::MessageId::Arrived);
	MSGDEF("autoselect", Cog::MessageId::Autoselect);
	MSGDEF("blocked", Cog::MessageId::Blocked);
	MSGDEF("changed", Cog::MessageId::Changed);
	MSGDEF("created", Cog::MessageId::Created);
	MSGDEF("crossed", Cog::MessageId::Crossed);
	MSGDEF("damaged", Cog::MessageId::Damaged);
	MSGDEF("deactivated", Cog::MessageId::Deactivated);
	MSGDEF("deselected", Cog::MessageId::Deselected);
	MSGDEF("entered", Cog::MessageId::Entered);
	MSGDEF("exited", Cog::MessageId::Exited);
	MSGDEF("fire", Cog::MessageId::Fire);
	MSGDEF("global0", Cog::MessageId::Global0);
	MSGDEF("join", Cog::MessageId::Join);
	MSGDEF("killed", Cog::MessageId::Killed);
	MSGDEF("leave", Cog::MessageId::Leave);
	MSGDEF("loading", Cog::MessageId::Loading);
	MSGDEF("newplayer", Cog::MessageId::NewPlayer);
	MSGDEF("pulse", Cog::MessageId::Pulse);
	MSGDEF("removed", Cog::MessageId::Removed);
	MSGDEF("respawn", Cog::MessageId::Respawn);
	MSGDEF("selected", Cog::MessageId::Selected);
	MSGDEF("shutdown", Cog::MessageId::Shutdown);
	MSGDEF("sighted", Cog::MessageId::Sighted);
	MSGDEF("skill", Cog::MessageId::Skill);
	MSGDEF("splash", Cog::MessageId::Splash);
	MSGDEF("startup", Cog::MessageId::Startup);
	MSGDEF("taken", Cog::MessageId::Taken);
	MSGDEF("timer", Cog::MessageId::Timer);
	MSGDEF("touched", Cog::MessageId::Touched);
	MSGDEF("trigger", Cog::MessageId::Trigger);
	MSGDEF("user0", Cog::MessageId::User0);
	MSGDEF("user1", Cog::MessageId::User1);
	MSGDEF("user2", Cog::MessageId::User2);
	MSGDEF("user3", Cog::MessageId::User3);
	MSGDEF("user4", Cog::MessageId::User4);
	MSGDEF("user5", Cog::MessageId::User5);
	MSGDEF("user6", Cog::MessageId::User6);
	MSGDEF("user7", Cog::MessageId::User7);
#undef MSGDEF
}

void Cog::Compiler::Compile(Cog::Script& output, const std::string& filename, std::istream& fileStream, Error::Report& errorReport)
{
	Cog::AST::Factory astFactory(filename);

	AST::TranslationUnit* ast = Stages::Stage1::GenerateAST(filename, fileStream, errorReport, astFactory);

	if(errorReport.GetErrorCount() > 0)
	{
		return;
	}

	Stages::Stage2::SemanticAnalysis(ast, output.SymbolTable, ConstantTable, VerbTable, errorReport);

	if(errorReport.GetErrorCount() > 0)
	{
		return;
	}

	Stages::Stage3::ConstantFolding(astFactory, ast, output.SymbolTable, ConstantTable, errorReport);

	if(errorReport.GetErrorCount() > 0)
	{
		return;
	}

	IR::CodePrinter printer(output.Code, output.SymbolTable, MessageTable, VerbTable, output.JumpTable);

	Stages::Stage4::CodeGeneration(ast, printer, errorReport);
}
