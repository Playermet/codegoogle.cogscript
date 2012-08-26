#ifndef _S4_LVAL_EXPRESSION_VISITOR_H_INCLUDED_
#define _S4_LVAL_EXPRESSION_VISITOR_H_INCLUDED_

#include "ast_visitor.h"
#include "ir_printer.h"

namespace Cog
{
	namespace Stages
	{
		namespace Stage4
		{
			class LValueExpressionVisitor : public AST::Visitor
			{
			protected:
				IR::Printer& Printer;

			public:
				LValueExpressionVisitor(IR::Printer& printer, Error::Report& report);

			private:
				AVPROTO(IdentifierExpression);
				AVPROTO(SubscriptExpression);
			};
		}
	}
}

#endif // _S4_LVAL_EXPRESSION_VISITOR_H_INCLUDED_
