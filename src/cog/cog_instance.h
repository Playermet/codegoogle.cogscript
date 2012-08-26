#ifndef _COG_INSTANCE_H_INCLUDED_
#define _COG_INSTANCE_H_INCLUDED_

#include "vm_value.h"
#include "cog_script.h"
#include <vector>

namespace Cog
{
	class Script;

	class Instance
	{
	public:
		const Script& Script;
		std::vector<VirtualMachine::Value> Heap;

		Instance(const Cog::Script& Script);
		Instance(const Cog::Script& Script, const std::vector<VirtualMachine::Value>& values);
	};
}

#endif // _COG_INSTANCE_H_INCLUDED_
