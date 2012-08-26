#include "ast_factory.h"
#include "err_report.h"
#include "sym_table.h"
#include <string>
#include <unordered_map>

#include "s3_code_visitor.h"

namespace Cog
{
	namespace Stages
	{
		namespace Stage3
		{
			void ConstantFolding(AST::Factory& factory, AST::TranslationUnit* ast, Symbols::SymbolTable& symbolTable,
				const std::unordered_map<std::string, VirtualMachine::Value>& constantTable, Error::Report& report)
			{
				Stage3::CodeVisitor v(factory, symbolTable, constantTable, report);

				for(auto it = ast->Code->begin(); it != ast->Code->end(); ++it)
				{
					(*it)->Accept(v);
				}
			}
		}
	}
}