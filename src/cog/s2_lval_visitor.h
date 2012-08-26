#ifndef _S2_LVAL_VISITOR_H_INCLUDED_
#define _S2_LVAL_VISITOR_H_INCLUDED_

#include "ast_visitor.h"
#include "sym_table.h"
#include "v_table.h"

namespace Cog
{
	namespace Stages
	{
		namespace Stage2
		{
			class LValueVisitor : public AST::Visitor
			{
			protected:
				Symbols::SymbolTable& SymbolTable;
				const std::unordered_map<std::string, VirtualMachine::Value>& ConstantTable;
				Verbs::VerbTable& VerbTable;

				void DefaultAction(const std::string& action, AST::Node& n);

			public:
				LValueVisitor(Symbols::SymbolTable& st, const std::unordered_map<std::string, VirtualMachine::Value>& ct,
					Verbs::VerbTable& vt, Error::Report& report);

			private:
				AVPROTO(IdentifierExpression);
				AVPROTO(SubscriptExpression);
			};
		}
	}
}

#endif // _S2_LVAL_VISITOR_H_INCLUDED_
