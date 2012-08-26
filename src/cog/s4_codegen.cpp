#include "sym_table.h"
#include "v_table.h"
#include "ir_printer.h"
#include "ast_node.h"
#include "err_report.h"
#include "s4_code_visitor.h"

namespace Cog
{
	namespace Stages
	{
		namespace Stage4
		{
			void CodeGeneration(AST::TranslationUnit* ast, IR::Printer& printer, Error::Report& report)
			{
				printer.Comment("==============================");
				printer.Comment("COG compiler diagnostic output");
				printer.Comment("==============================");

				// Generate 'default' action for unimplemented messages.
				printer.Ret();

				int nextLabelNumber = 1;
				CodeVisitor v(nextLabelNumber, printer, report);

				for(auto it = ast->Code->begin(); it != ast->Code->end(); ++it)
				{
					(*it)->Accept(v);
				}

				// Generate guard return
				if(ast->Code->size() > 0)
				{
					printer.Ret();
				}

				printer.Backpatch();

				return;
			}
		}
	}
}
