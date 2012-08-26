#ifndef _S4_EXPRESSION_VISITOR_H_INCLUDED_
#define _S4_EXPRESSION_VISITOR_H_INCLUDED_

#include "ast_visitor.h"
#include "ir_printer.h"

namespace Cog
{
	namespace Stages
	{
		namespace Stage4
		{
			class ExpressionVisitor : public AST::Visitor
			{
			protected:
				IR::Printer& Printer;

			public:
				ExpressionVisitor(IR::Printer& printer, Error::Report& report);

			private:
				ASTCLASS_FINAL_EXPRESSION(AVPROTO);
			};
		}
	}
}

#endif // _S4_EXPRESSION_VISITOR_H_INCLUDED_
