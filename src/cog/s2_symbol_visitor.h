#ifndef _S2_SYMBOL_VISITOR_H_INCLUDED_
#define _S2_SYMBOL_VISITOR_H_INCLUDED_

#include "ast_visitor.h"
#include "sym_table.h"
#include "sym_type.h"

#include <unordered_set>
#include <string>

namespace Cog
{
	namespace Stages
	{
		namespace Stage2
		{
			class SymbolVisitor : public AST::Visitor
			{
			protected:
				Symbols::SymbolTable& SymbolTable;
				const std::unordered_set<std::string>& SeenLabels;

			public:
				SymbolVisitor(Symbols::SymbolTable& st, const std::unordered_set<std::string>& SeenLabels, Error::Report& report);

			private:
				Symbols::Type::Enum GetType(AST::Symbol& symbol);

				ASTCLASS_SYMBOL(AVPROTO);
			};
		}
	}
}

#endif // _S2_SYMBOL_VISITOR_H_INCLUDED_
