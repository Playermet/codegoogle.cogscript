#include "cog_instance.h"

Cog::Instance::Instance(const Cog::Script& Script)
	: Script(Script)
{
	Heap.resize(Script.SymbolTable.Size());

	auto it = Script.SymbolTable.Begin();
	auto jt = Heap.begin();

	for( ; it != Script.SymbolTable.End() && jt != Heap.end(); ++it, ++jt)
	{
		(*jt) = it->DefaultValue;
	}
}

Cog::Instance::Instance(const Cog::Script& Script, const std::vector<VirtualMachine::Value>& values)
	: Script(Script)
{
	Heap.resize(Script.SymbolTable.Size());

	auto it = Script.SymbolTable.Begin();
	auto jt = Heap.begin();
	auto kt = values.begin();

	for( ; it != Script.SymbolTable.End() && jt != Heap.end(); ++it, ++jt)
	{
		if(kt != values.end() && !it->Local)
		{
			(*jt) = *kt;
			++kt;
		}
		else
		{
			(*jt) = it->DefaultValue;
		}
	}

	return;
}
