#ifndef _S3_EXPRESSION_VISITOR_H_INCLUDED_
#define _S3_EXPRESSION_VISITOR_H_INCLUDED_

#include "ast_visitor.h"
#include "vm_value.h"
#include "ast_factory.h"
#include "sym_table.h"

#include <string>
#include <unordered_map>

namespace Cog
{
	namespace Stages
	{
		namespace Stage3
		{
			class ExpressionVisitor : public AST::Visitor
			{
			protected:
				AST::Factory& Factory;
				Symbols::SymbolTable& SymbolTable;
				const std::unordered_map<std::string, VirtualMachine::Value>& ConstantTable;

			private:
				bool isConstant;
				VirtualMachine::Value constantValue;
				AST::Expression* visitedExpression;

			public:
				ExpressionVisitor(AST::Factory& factory, Symbols::SymbolTable& symbolTable,
					const std::unordered_map<std::string, VirtualMachine::Value>& constantTable,
					Error::Report& report);

				inline AST::Expression* GetSubstitution() const
				{
					if(isConstant)
					{
						return Factory.MakeConstantValueExpression(constantValue,
							visitedExpression->Filename, visitedExpression->Location);
					}
					else
					{
						return visitedExpression;
					}
				}

				inline VirtualMachine::Value GetConstantValue() const
				{
					return constantValue;
				}

				inline bool IsConstant() const
				{
					return isConstant;
				}

			private:
				ASTCLASS_EXPRESSION(AVPROTO);
			};
		}
	}
}

#endif // _S3_EXPRESSION_VISITOR_H_INCLUDED_
