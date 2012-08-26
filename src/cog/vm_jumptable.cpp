#include "vm_jumptable.h"

Cog::VirtualMachine::JumpTable::JumpTable()
	: table(64, 0)
{
	return;
}
