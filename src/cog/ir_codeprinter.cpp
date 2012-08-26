#include "ir_codeprinter.h"
#include "vm_opcode.h"

using Cog::IR::CodePrinter;

Cog::IR::CodePrinter::CodePrinter(VirtualMachine::CodeBuffer& codeBuffer,
	const Symbols::SymbolTable& symbolTable,
	const std::unordered_map<std::string, MessageId::Enum>& messageTable,
	const Verbs::VerbTable& verbTable, VirtualMachine::JumpTable& jumpTable)
	: codeBuffer(codeBuffer), stream(codeBuffer), SymbolTable(symbolTable), VerbTable(verbTable),
	MessageTable(messageTable), JumpTable(jumpTable)
{
	return;
}

void CodePrinter::Backpatch()
{
	for(auto it = labelmap.begin(); it != labelmap.end(); ++it)
	{
		auto jt = MessageTable.find(it->first);
		if(jt != MessageTable.end())
		{
			MessageId::Enum id = static_cast<MessageId::Enum>(static_cast<int>(jt->second));
			JumpTable.SetTarget(id, it->second);
		}
	}

	for(auto it = backpatchmap.begin(); it != backpatchmap.end(); ++it)
	{
		auto jt = labelmap.find(it->first);
		if(jt != labelmap.end())
		{
			codeBuffer.Write<size_t>(jt->second, it->second);
		}
		else
		{
			// Missing labels already reported by semantic analysis.
			// Default to zero.
			codeBuffer.Write<size_t>(0, it->second);
		}
	}
}

void CodePrinter::Comment(const std::string&)
{
	return;
}

void CodePrinter::Label(const std::string& name)
{
	labelmap.insert(std::make_pair(name, stream.Tell()));
}

void CodePrinter::Nop()
{
	stream.Write(VirtualMachine::Opcode::NOP);
}

void CodePrinter::Copy()
{
	stream.Write(VirtualMachine::Opcode::COPY);
}

void CodePrinter::Const(const Cog::VirtualMachine::Value& value)
{
	stream.Write(VirtualMachine::Opcode::CONST);
	stream.Write(value);
}

void CodePrinter::Load(const std::string& symbol)
{
	stream.Write(VirtualMachine::Opcode::LOAD);
	stream.Write(SymbolTable.GetSymbolIndex(symbol));
}

void CodePrinter::LoadI(const std::string& symbol)
{
	stream.Write(VirtualMachine::Opcode::LOADI);
	stream.Write(SymbolTable.GetSymbolIndex(symbol));
}

void CodePrinter::Store(const std::string& symbol)
{
	stream.Write(VirtualMachine::Opcode::STORE);
	stream.Write(SymbolTable.GetSymbolIndex(symbol));
}

void CodePrinter::StoreI(const std::string& symbol)
{
	stream.Write(VirtualMachine::Opcode::STOREI);
	stream.Write(SymbolTable.GetSymbolIndex(symbol));
}

void CodePrinter::Jmp(const std::string& label)
{
	stream.Write(VirtualMachine::Opcode::JMP);
	backpatchmap.insert(std::make_pair(label, stream.Tell()));
	stream.Write<size_t>(0);
}

void CodePrinter::Jal(const std::string& label)
{
	stream.Write(VirtualMachine::Opcode::JAL);
	backpatchmap.insert(std::make_pair(label, stream.Tell()));
	stream.Write<size_t>(0);
}

void CodePrinter::Bt(const std::string& label)
{
	stream.Write(VirtualMachine::Opcode::BT);
	backpatchmap.insert(std::make_pair(label, stream.Tell()));
	stream.Write<size_t>(0);
}

void CodePrinter::Bf(const std::string& label)
{
	stream.Write(VirtualMachine::Opcode::BF);
	backpatchmap.insert(std::make_pair(label, stream.Tell()));
	stream.Write<size_t>(0);
}

void CodePrinter::Call(const std::string& verb)
{
	stream.Write(VirtualMachine::Opcode::CALL);
	stream.Write(VerbTable.GetVerb(verb));
}

void CodePrinter::CallV(const std::string& verb)
{
	stream.Write(VirtualMachine::Opcode::CALLV);
	stream.Write(VerbTable.GetVerb(verb));
}

void CodePrinter::Ret()
{
	stream.Write(VirtualMachine::Opcode::RET);
}

void CodePrinter::Neg()
{
	stream.Write(VirtualMachine::Opcode::NEG);
}

void CodePrinter::Add()
{
	stream.Write(VirtualMachine::Opcode::ADD);
}

void CodePrinter::Sub()
{
	stream.Write(VirtualMachine::Opcode::SUB);
}

void CodePrinter::Mul()
{
	stream.Write(VirtualMachine::Opcode::MUL);
}

void CodePrinter::Div()
{
	stream.Write(VirtualMachine::Opcode::DIV);
}

void CodePrinter::Mod()
{
	stream.Write(VirtualMachine::Opcode::MOD);
}

void CodePrinter::And()
{
	stream.Write(VirtualMachine::Opcode::AND);
}

void CodePrinter::Or()
{
	stream.Write(VirtualMachine::Opcode::OR);
}

void CodePrinter::Xor()
{
	stream.Write(VirtualMachine::Opcode::XOR);
}

void CodePrinter::LNot()
{
	stream.Write(VirtualMachine::Opcode::LNOT);
}

void CodePrinter::LAnd()
{
	stream.Write(VirtualMachine::Opcode::LAND);
}

void CodePrinter::LOr()
{
	stream.Write(VirtualMachine::Opcode::LOR);
}

void CodePrinter::CGt()
{
	stream.Write(VirtualMachine::Opcode::CGT);
}

void CodePrinter::CGeq()
{
	stream.Write(VirtualMachine::Opcode::CGEQ);
}

void CodePrinter::CLt()
{
	stream.Write(VirtualMachine::Opcode::CLT);
}

void CodePrinter::CLeq()
{
	stream.Write(VirtualMachine::Opcode::CLEQ);
}

void CodePrinter::CEq()
{
	stream.Write(VirtualMachine::Opcode::CEQ);
}

void CodePrinter::CNeq()
{
	stream.Write(VirtualMachine::Opcode::CNEQ);
}
