#ifndef _VM_JUMPTABLE_H_INCLUDED_
#define _VM_JUMPTABLE_H_INCLUDED_

#include "cog_messageid.h"
#include <vector>

namespace Cog
{
	namespace VirtualMachine
	{
		class JumpTable
		{
		private:
			std::vector<size_t> table;

		public:
			JumpTable();

			inline void SetTarget(MessageId::Enum id, size_t target)
			{
				table[id] = target;
			}

			inline size_t GetTarget(MessageId::Enum id) const
			{
				return table[id];
			}
		};
	}
}

#endif // _VM_JUMPTABLE_H_INCLUDED_
