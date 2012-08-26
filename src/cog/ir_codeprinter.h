#ifndef _IR_CODEPRINTER_H_INCLUDED_
#define _IR_CODEPRINTER_H_INCLUDED_

#include "ir_printer.h"
#include "sym_table.h"
#include "v_table.h"
#include "vm_codebuffer.h"
#include "vm_codebufferwritestream.h"
#include "vm_jumptable.h"
#include "cog_messageid.h"

#include <iostream>
#include <unordered_map>

namespace Cog
{
	namespace IR
	{
		class CodePrinter : public Printer
		{
		private:
			VirtualMachine::CodeBuffer& codeBuffer;
			VirtualMachine::CodeBufferWriteStream stream;
			const Symbols::SymbolTable& SymbolTable;
			const Verbs::VerbTable& VerbTable;
			const std::unordered_map<std::string, MessageId::Enum>& MessageTable;
			VirtualMachine::JumpTable& JumpTable;

			std::unordered_map<std::string, size_t> labelmap;
			std::unordered_multimap<std::string, size_t> backpatchmap;

		public:
			CodePrinter(VirtualMachine::CodeBuffer& codeBuffer, const Symbols::SymbolTable& symbolTable,
				const std::unordered_map<std::string, MessageId::Enum>& messageTable, const Verbs::VerbTable& verbTable,
				VirtualMachine::JumpTable& jumpTable);

			void Backpatch();

			void Comment(const std::string& msg);
			void Label(const std::string& name);

			void Nop();

			void Copy();
			void Const(const VirtualMachine::Value& value);

			void Load(const std::string& symbol);
			void LoadI(const std::string& symbol);
			void Store(const std::string& symbol);
			void StoreI(const std::string& symbol);

			void Jmp(const std::string& label);
			void Jal(const std::string& label);
			void Bt(const std::string& label);
			void Bf(const std::string& label);
			void Call(const std::string& verb);
			void CallV(const std::string& verb);
			void Ret();

			void Neg();
			void Add();
			void Sub();
			void Mul();
			void Div();
			void Mod();
			void And();
			void Or();
			void Xor();

			void LNot();
			void LAnd();
			void LOr();

			void CGt();
			void CGeq();
			void CLt();
			void CLeq();
			void CEq();
			void CNeq();
		};
	}
}

#endif // _IR_CODEPRINTER_H_INCLUDED_
