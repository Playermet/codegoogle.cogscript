#ifndef _VM_OPCODE_H_INCLUDED_
#define _VM_OPCODE_H_INCLUDED_

namespace Cog
{
	namespace VirtualMachine
	{
		namespace Opcode
		{
			enum Enum : unsigned char
			{
				NOP,			// NOP ; Non-operation

				COPY,			// COPY ; Duplicates value on top of stack
				CONST,			// CONSTV [Value] ; Push constant value

				LOAD,			// LOAD [Address] ; Loads value from address
				LOADI,			// LOADI [Address] ; Adds top value to address and loads
				STORE,			// STORE [Address] ; Stores top value at address
				STOREI,			// STOREI [Address] ; Adds top value to address and stores top value

				JMP,			// JMP [Address] ; Sets PC to address
				JAL,			// JAL [Address] ; Sets PC to address in new stack frame
				BT,				// BT [Address] ; Sets PC to address if top value is true
				BF,				// BF [Address] ; Sets PC to address if top value is false
				CALL,			// CALL [Verb] ; Calls specified verb
				CALLV,			// CALLV [Verb] ; Calls verb and pushes result onto stack
				RET,			// RET ; Returns to previous stack frame

				NEG,			// NEG ; Arithmetic negation
				ADD,			// ADD ; Adds top to second-top
				SUB,			// SUB ; Subtracts top from second-top
				MUL,			// MUL ; Multiplies second-top by top
				DIV,			// DIV ; Divides top from second-top
				MOD,			// MOD ; Second-top mod top
				AND,			// AND ; Second-top and top
				OR,				// OR ; Second-top or top
				XOR,			// XOR ; Second-top xor top

				LNOT,			// LNOT ; Logical negation
				LAND,			// LAND ; Second-top and top
				LOR,			// LOR ; Second-top or top

				CGT,			// CGT ; Second-top > top
				CGEQ,			// CGEQ ; Second-top >= top
				CLT,			// CLT ; Second-top < top
				CLEQ,			// CLEQ ; Second-top <= top
				CEQ,			// CEQ ; Second-top == top
				CNEQ,			// CNEQ ; Second-top != top
			};
		}
	}
}

#endif // _VM_OPCODE_H_INCLUDED_
