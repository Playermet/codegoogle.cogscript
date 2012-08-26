#ifndef _VM_VIRTUALMACHINE_H_INCLUDED_
#define _VM_VIRTUALMACHINE_H_INCLUDED_

#include "vm_value.h"
#include "vm_codebuffer.h"
#include "v_table.h"
#include "cog_messageid.h"
#include "cog_instance.h"
#include <vector>
#include <stack>

namespace Cog
{
	namespace VirtualMachine
	{
		class VirtualMachine
		{
		private:
			std::stack<Value> stack;
			const Verbs::VerbTable& verbTable;

			void Execute(std::vector<Value>& heap, const CodeBuffer& code, size_t pc);

		public:
			VirtualMachine(const Verbs::VerbTable& verbTable);

			void Call(Instance& cog, MessageId::Enum message);

			inline void Push(const Value& val)
			{
				stack.push(val);
			}

			inline Value Pop()
			{
				Value val = stack.top();
				stack.pop();
				return val;
			}
		};
	}
}

#endif // _VM_VIRTUALMACHINE_H_INCLUDED_
