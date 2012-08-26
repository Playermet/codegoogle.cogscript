#ifndef _S2_EXPRESSION_VISITOR_H_INCLUDED_
#define _S2_EXPRESSION_VISITOR_H_INCLUDED_

#include "ast_visitor.h"
#include "sym_table.h"
#include "v_table.h"

namespace Cog
{
	namespace Stages
	{
		namespace Stage2
		{
			class ExpressionVisitor : public AST::Visitor
			{
			protected:
				Symbols::SymbolTable& SymbolTable;
				const std::unordered_map<std::string, VirtualMachine::Value>& ConstantTable;
				Verbs::VerbTable& VerbTable;

			public:
				VirtualMachine::Type::Enum ExpressionType;

				ExpressionVisitor(Symbols::SymbolTable& st, const std::unordered_map<std::string, VirtualMachine::Value>& ct,
					Verbs::VerbTable& vt, Error::Report& report);

			private:
				ASTCLASS_EXPRESSION(AVPROTO);
			};
		}
	}
}

#endif // _S2_EXPRESSION_VISITOR_H_INCLUDED_
