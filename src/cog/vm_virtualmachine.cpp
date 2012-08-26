#include "vm_virtualmachine.h"
#include "vm_codebufferreadstream.h"
#include "vm_opcode.h"

Cog::VirtualMachine::VirtualMachine::VirtualMachine(const Verbs::VerbTable& verbTable) : verbTable(verbTable)
{
	return;
}

void Cog::VirtualMachine::VirtualMachine::Call(Instance& cog, MessageId::Enum message)
{
	// Execute from the given message.
	size_t startupAddr = cog.Script.JumpTable.GetTarget(message);
	Execute(cog.Heap, cog.Script.Code, startupAddr);
}

void Cog::VirtualMachine::VirtualMachine::Execute(std::vector<Value>& heap, const CodeBuffer& code, size_t pc)
{
	CodeBufferReadStream stream(code);
	stream.Seek(pc);

	while(true)
	{
		Opcode::Enum op = stream.Read<Opcode::Enum>();

		switch(op)
		{
		case Opcode::NOP:
			break;

		case Opcode::COPY:
			{
				Value v = stack.top();
				Push(v);
			}
			break;

		case Opcode::CONST:
			{
				Value v = stream.Read<Value>();
				Push(v);
			}
			break;

		case Opcode::LOAD:
			{
				size_t addr = stream.Read<size_t>();
				Push(heap[addr]);
			}
			break;

		case Opcode::LOADI:
			{
				size_t addr = stream.Read<size_t>();
				int offset = static_cast<int>(Pop());
				Push(heap[addr + offset]);
			}
			break;

		case Opcode::STORE:
			{
				size_t addr = stream.Read<size_t>();
				heap[addr] = Pop();
			}
			break;

		case Opcode::STOREI:
			{
				size_t addr = stream.Read<size_t>();
				int offset = static_cast<int>(Pop());
				heap[addr + offset] = Pop();
			}
			break;

		case Opcode::JMP:
			{
				size_t addr = stream.Read<size_t>();
				stream.Seek(addr);
			}
			break;

		case Opcode::JAL:
			{
				size_t addr = stream.Read<size_t>();
				Execute(heap, code, addr);
			}
			break;

		case Opcode::BT:
			{
				size_t addr = stream.Read<size_t>();
				bool condition = static_cast<bool>(Pop());
				if(condition)
				{
					stream.Seek(addr);
				}
			}
			break;

		case Opcode::BF:
			{
				size_t addr = stream.Read<size_t>();
				bool condition = static_cast<bool>(Pop());
				if(!condition)
				{
					stream.Seek(addr);
				}
			}
			break;

		case Opcode::CALL:
			{
				Verbs::VerbId verb = stream.Read<Verbs::VerbId>();
				verbTable.Invoke(verb, stack);
			}
			break;

		case Opcode::CALLV:
			{
				Verbs::VerbId verb = stream.Read<Verbs::VerbId>();
				Push(verbTable.Invoke(verb, stack));
			}
			break;

		case Opcode::RET:
			return;

		case Opcode::NEG:
			{
				Value v = Pop();
				Push(-v);
			}
			break;

		case Opcode::ADD:
			{
				Value right = Pop();
				Value left = Pop();
				Push(left + right);
			}
			break;

		case Opcode::SUB:
			{
				Value right = Pop();
				Value left = Pop();
				Push(left - right);
			}
			break;

		case Opcode::MUL:
			{
				Value right = Pop();
				Value left = Pop();
				Push(left * right);
			}
			break;

		case Opcode::DIV:
			{
				Value right = Pop();
				Value left = Pop();
				Push(left / right);
			}
			break;

		case Opcode::MOD:
			{
				Value right = Pop();
				Value left = Pop();
				Push(left % right);
			}
			break;

		case Opcode::AND:
			{
				Value right = Pop();
				Value left = Pop();
				Push(left & right);
			}
			break;

		case Opcode::OR:
			{
				Value right = Pop();
				Value left = Pop();
				Push(left | right);
			}
			break;

		case Opcode::XOR:
			{
				Value right = Pop();
				Value left = Pop();
				Push(left ^ right);
			}
			break;

		case Opcode::LNOT:
			{
				Value right = Pop();
				Push(!right);
			}
			break;

		case Opcode::LAND:
			{
				Value right = Pop();
				Value left = Pop();
				Push(left && right);
			}
			break;

		case Opcode::LOR:
			{
				Value right = Pop();
				Value left = Pop();
				Push(left || right);
			}
			break;

		case Opcode::CGT:
			{
				Value right = Pop();
				Value left = Pop();
				Push(left > right);
			}
			break;

		case Opcode::CGEQ:
			{
				Value right = Pop();
				Value left = Pop();
				Push(left >= right);
			}
			break;

		case Opcode::CLT:
			{
				Value right = Pop();
				Value left = Pop();
				Push(left < right);
			}
			break;

		case Opcode::CLEQ:
			{
				Value right = Pop();
				Value left = Pop();
				Push(left <= right);
			}
			break;

		case Opcode::CEQ:
			{
				Value right = Pop();
				Value left = Pop();
				Push(left == right);
			}
			break;

		case Opcode::CNEQ:
			{
				Value right = Pop();
				Value left = Pop();
				Push(left != right);
			}
			break;
		}
	}
}
