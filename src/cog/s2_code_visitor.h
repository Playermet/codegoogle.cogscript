#ifndef _S2_CODE_VISITOR_H_INCLUDED_
#define _S2_CODE_VISITOR_H_INCLUDED_

#include "ast_visitor.h"
#include "sym_table.h"
#include "v_table.h"

#include <unordered_set>
#include <string>

namespace Cog
{
	namespace Stages
	{
		namespace Stage2
		{
			class CodeVisitor : public AST::Visitor
			{
			protected:
				Symbols::SymbolTable& SymbolTable;
				const std::unordered_map<std::string, VirtualMachine::Value>& ConstantTable;
				Verbs::VerbTable& VerbTable;
				const std::unordered_set<std::string>& SeenLabels;
				const bool inside_loop;
				const bool inside_block;

			public:
				CodeVisitor(Symbols::SymbolTable& st,
					const std::unordered_map<std::string, VirtualMachine::Value>& constantTable,
					Verbs::VerbTable& vt, const std::unordered_set<std::string>& SeenLabels,
					Error::Report& report, bool inside_loop = false, bool inside_block = false);

			private:
				ASTCLASS_STATEMENT(AVPROTO);
			};
		}
	}
}

#endif // _S2_CODE_VISITOR_H_INCLUDED_
