#ifndef _S4_CODE_VISITOR_H_INCLUDED_
#define _S4_CODE_VISITOR_H_INCLUDED_

#include "ast_visitor.h"
#include "ir_printer.h"

namespace Cog
{
	namespace Stages
	{
		namespace Stage4
		{
			class CodeVisitor : public AST::Visitor
			{
			protected:
				IR::Printer& Printer;
				int& nextLabelNumber;

				const std::string BreakLabel;

				std::string GenerateLabel(const std::string& prefix);

			public:
				CodeVisitor(int& nextLabelNumber, IR::Printer& printer, Error::Report& report, const std::string breakLabel = "");

			private:
				ASTCLASS_STATEMENT(AVPROTO);
			};
		}
	}
}

#endif // _S4_CODE_VISITOR_H_INCLUDED_
