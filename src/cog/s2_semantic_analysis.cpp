#include "ast_node.h"
#include "sym_table.h"
#include "v_table.h"
#include "err_report.h"

#include "s2_symbol_visitor.h"
#include "s2_code_visitor.h"
#include "s2_label_visitor.h"

namespace Cog
{
	namespace Stages
	{
		namespace Stage2
		{
			void SemanticAnalysis(AST::TranslationUnit* ast, Symbols::SymbolTable& symbolTable,
				const std::unordered_map<std::string, VirtualMachine::Value>& constantTable,
				Verbs::VerbTable& verbTable, Error::Report& report)
			{
				std::unordered_set<std::string> seenLabels;
				LabelVisitor labelVisitor(seenLabels, report);

				for(auto it = ast->Code->begin(); it != ast->Code->end(); ++it)
				{
					(*it)->Accept(labelVisitor);
				}

				SymbolVisitor symbolVisitor(symbolTable, seenLabels, report);

				for(auto it = ast->Symbols->begin(); it != ast->Symbols->end(); ++it)
				{
					(*it)->Accept(symbolVisitor);
				}

				CodeVisitor codeVisitor(symbolTable, constantTable, verbTable, seenLabels, report);

				for(auto it = ast->Code->begin(); it != ast->Code->end(); ++it)
				{
					(*it)->Accept(codeVisitor);
				}
			}
		}
	}
}
