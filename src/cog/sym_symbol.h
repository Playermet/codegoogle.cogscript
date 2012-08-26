#ifndef _SYM_SYMBOL_H_INCLUDED_
#define _SYM_SYMBOL_H_INCLUDED_

#include "sym_type.h"
#include "vm_value.h"
#include <string>

namespace Cog
{
	namespace Symbols
	{
		class Symbol
		{
		public:
			const Type::Enum Type;
			const std::string Name;

			const VirtualMachine::Value DefaultValue;

			const bool Local;
			const std::string Desc;
			const int Mask;
			const int Linkid;
			const bool Nolink;

			Symbol(Type::Enum type, const std::string& name, const VirtualMachine::Value& defaultValue,
				bool local, const std::string& desc, int mask, int linkid, bool nolink);
		};
	}
}

#endif // _SYM_SYMBOL_H_INCLUDED_
