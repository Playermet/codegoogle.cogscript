#include "ast_node.h"
#include "ast_factory.h"
#include "err_report.h"
#include <iostream>

#include "gra_context.h"

namespace Cog
{
	namespace Stages
	{
		namespace Stage1
		{
			AST::TranslationUnit* GenerateAST(const std::string& filename, std::istream& inputFilestream,
				Error::Report& errorReport, AST::Factory& astFactory)
			{
				Grammar::Context context(filename, inputFilestream, errorReport, astFactory);
				context.Parse();

				return context.translation_unit;
			}
		}
	}
}
