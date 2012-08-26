#ifndef _COG_SCRIPT_H_INCLUDED_
#define _COG_SCRIPT_H_INCLUDED_

#include "sym_table.h"
#include "vm_jumptable.h"
#include "vm_codebuffer.h"

namespace Cog
{
	class Script
	{
	public:
		Script();

		Symbols::SymbolTable SymbolTable;
		VirtualMachine::JumpTable JumpTable;
		VirtualMachine::CodeBuffer Code;
	};
}

#endif // _COG_SCRIPT_H_INCLUDED_
