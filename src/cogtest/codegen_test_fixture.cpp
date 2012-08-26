#include "codegen_test_fixture.h"
#include "cog/cog_stages.h"
#include "cog/ir_codeprinter.h"
#include "cog/vm_jumptable.h"
#include "cog/vm_virtualmachine.h"
#include "cog/cog_script.h"
#include "cog/cog_instance.h"
#include "cog/cog_compiler.h"
#include <fstream>

using namespace Cog;

CodegenTestFixture::CodegenTestFixture(const std::string& basePath)
	: SemanticTestFixture(basePath)
{
	#define MSG(x, y) messageTable.insert(std::make_pair(x, y))
		MSG("activate", Cog::MessageId::Activated);
		MSG("activated", Cog::MessageId::Activated);
		MSG("aievent", Cog::MessageId::AiEvent);
		MSG("arrived", Cog::MessageId::Arrived);
		MSG("autoselect", Cog::MessageId::Autoselect);
		MSG("blocked", Cog::MessageId::Blocked);
		MSG("changed", Cog::MessageId::Changed);
		MSG("created", Cog::MessageId::Created);
		MSG("crossed", Cog::MessageId::Crossed);
		MSG("damaged", Cog::MessageId::Damaged);
		MSG("deactivated", Cog::MessageId::Deactivated);
		MSG("deselected", Cog::MessageId::Deselected);
		MSG("entered", Cog::MessageId::Entered);
		MSG("exited", Cog::MessageId::Exited);
		MSG("fire", Cog::MessageId::Fire);
		MSG("global0", Cog::MessageId::Global0);
		MSG("join", Cog::MessageId::Join);
		MSG("killed", Cog::MessageId::Killed);
		MSG("leave", Cog::MessageId::Leave);
		MSG("loading", Cog::MessageId::Loading);
		MSG("newplayer", Cog::MessageId::NewPlayer);
		MSG("pulse", Cog::MessageId::Pulse);
		MSG("removed", Cog::MessageId::Removed);
		MSG("respawn", Cog::MessageId::Respawn);
		MSG("selected", Cog::MessageId::Selected);
		MSG("shutdown", Cog::MessageId::Shutdown);
		MSG("sighted", Cog::MessageId::Sighted);
		MSG("skill", Cog::MessageId::Skill);
		MSG("splash", Cog::MessageId::Splash);
		MSG("startup", Cog::MessageId::Startup);
		MSG("taken", Cog::MessageId::Taken);
		MSG("timer", Cog::MessageId::Timer);
		MSG("touched", Cog::MessageId::Touched);
		MSG("trigger", Cog::MessageId::Trigger);
		MSG("user0", Cog::MessageId::User0);
		MSG("user1", Cog::MessageId::User1);
		MSG("user2", Cog::MessageId::User2);
		MSG("user3", Cog::MessageId::User3);
		MSG("user4", Cog::MessageId::User4);
		MSG("user5", Cog::MessageId::User5);
		MSG("user6", Cog::MessageId::User6);
		MSG("user7", Cog::MessageId::User7);
	#undef MSG

	return;
}

void CodegenTestFixture::ParseFile(const boost::filesystem::path& path)
{
	std::string fn = (BasePath / path).string();
	std::ifstream cogfile(fn);

	Cog::Compiler compiler(VerbTable);
	
	compiler.Compile(Script, fn, cogfile, Report);

	if(Report.GetErrorCount() > 0)
	{
		return;
	}

	// Build instance
	auto inst = Cog::Instance(Script);

	Cog::VirtualMachine::VirtualMachine vm(VerbTable);
	vm.Call(inst, MessageId::Startup);
}
