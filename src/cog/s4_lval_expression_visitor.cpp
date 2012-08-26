#include "s4_lval_expression_visitor.h"
#include "s4_expression_visitor.h"

using namespace Cog::AST;
using Cog::Stages::Stage4::LValueExpressionVisitor;

LValueExpressionVisitor::LValueExpressionVisitor(Cog::IR::Printer& printer, Cog::Error::Report& report)
	: AST::Visitor("Stage5::LValueExpressionVisitor", report), Printer(printer)
{
	return;
}

void LValueExpressionVisitor::VisitIdentifierExpression(IdentifierExpression& e)
{
	Printer.Store(e.Identifier);
}

void LValueExpressionVisitor::VisitSubscriptExpression(SubscriptExpression& e)
{
	ExpressionVisitor v(Printer, ErrorReport);
	e.Index->Accept(v);
	Printer.StoreI(e.Base);
}
