#ifndef _S3_CODE_VISITOR_H_INCLUDED_
#define _S3_CODE_VISITOR_H_INCLUDED_

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
			class CodeVisitor : public AST::Visitor
			{
			protected:
				AST::Factory& Factory;
				Symbols::SymbolTable& SymbolTable;
				const std::unordered_map<std::string, VirtualMachine::Value>& ConstantTable;

			public:
				CodeVisitor(AST::Factory& factory, Symbols::SymbolTable& symbolTable,
					const std::unordered_map<std::string, VirtualMachine::Value>& constantTable,
					Error::Report& report);

			private:
				ASTCLASS_STATEMENT(AVPROTO);
			};
		}
	}
}

#endif // _S3_CODE_VISITOR_H_INCLUDED_
