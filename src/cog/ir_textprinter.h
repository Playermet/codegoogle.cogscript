#ifndef _IR_TEXTPRINTER_H_INCLUDED_
#define _IR_TEXTPRINTER_H_INCLUDED_

#include "ir_printer.h"
#include "sym_table.h"
#include "v_table.h"

#include <iostream>

namespace Cog
{
	namespace IR
	{
		class TextPrinter : public Printer
		{
		private:
			std::ostream& stream;
			const Symbols::SymbolTable& SymbolTable;
			const Verbs::VerbTable& VerbTable;

			void writeValue(const VirtualMachine::Value& value);

		public:
			TextPrinter(std::ostream& os, const Symbols::SymbolTable& symbolTable, const Verbs::VerbTable& verbTable);

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

#endif // _IR_TEXTPRINTER_H_INCLUDED_
