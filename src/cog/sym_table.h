#ifndef _SYM_TABLE_H_INCLUDED_
#define _SYM_TABLE_H_INCLUDED_

#include "sym_symbol.h"

#include <vector>
#include <unordered_map>

namespace Cog
{
	namespace Symbols
	{
		class SymbolTable
		{
		private:
			std::vector<Symbol> symbols;
			std::unordered_map<std::string, size_t> symbolMap;
			std::vector<const char*> strings;

		public:
			~SymbolTable();

			void AddSymbol(Type::Enum type, const std::string& name,
				const VirtualMachine::Value& defaultValue,
				bool local, const std::string& desc, int mask, int linkid, bool nolink);
			void AddSymbol(Type::Enum type, const std::string& name,
				bool local, const std::string& desc, int mask, int linkid, bool nolink);
			void AddSymbol(const std::string& name);

			void ReplaceSymbol(Type::Enum type, const std::string& name,
				const VirtualMachine::Value& defaultValue,
				bool local, const std::string& desc, int mask, int linkid, bool nolink);
			void ReplaceSymbol(Type::Enum type, const std::string& name,
				bool local, const std::string& desc, int mask, int linkid, bool nolink);
			void ReplaceSymbol(const std::string& name);

			const Symbol& GetSymbol(size_t index) const;
			const Symbol& GetSymbol(const std::string& name) const;

			bool IsSymbolDefined(size_t index) const;
			bool IsSymbolDefined(const std::string& name) const;

			const char* AddString(const std::string&);

			size_t GetSymbolIndex(const std::string& name) const;

			inline size_t Size() const
			{
				return symbols.size();
			}

			inline std::vector<Symbol>::const_iterator Begin() const
			{
				return symbols.begin();
			}

			inline std::vector<Symbol>::const_iterator End() const
			{
				return symbols.end();
			}
		};
	}
}

#endif // _SYM_TABLE_H_INCLUDED_
