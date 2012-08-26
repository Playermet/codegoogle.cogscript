#include "sym_symbol.h"

Cog::Symbols::Symbol::Symbol(Type::Enum type, const std::string& name,
	const VirtualMachine::Value& defaultValue, bool local, const std::string& desc,
	int mask, int linkid, bool nolink)
	: Type(type), Name(name), DefaultValue(defaultValue), Local(local),
	Desc(desc), Mask(mask), Linkid(linkid), Nolink(nolink)
{
	return;
}
