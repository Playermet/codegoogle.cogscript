#include "s4_nonval_expression_visitor.h"
#include "s4_lval_expression_visitor.h"
#include "s4_expression_visitor.h"

using namespace Cog::AST;
using Cog::Stages::Stage4::NonValuedExpressionVisitor;

NonValuedExpressionVisitor::NonValuedExpressionVisitor(Cog::IR::Printer& printer, Cog::Error::Report& report)
	: AST::Visitor("Stage5::NonValuedExpressionVisitor", report), Printer(printer)
{
	return;
}

void NonValuedExpressionVisitor::VisitIdentifierExpression(IdentifierExpression& e)
{
	return;
}

void NonValuedExpressionVisitor::VisitSubscriptExpression(SubscriptExpression& e)
{
	e.Index->Accept(*this);
	return;
}

void NonValuedExpressionVisitor::VisitMethodCallExpression(MethodCallExpression& e)
{
	ExpressionVisitor v(Printer, ErrorReport);
	for(auto it = e.Arguments->begin(); it != e.Arguments->end(); ++it)
	{
		(*it)->Accept(v);
	}

	Printer.Call(e.Base);
}

void NonValuedExpressionVisitor::VisitUnaryExpression(UnaryExpression& e)
{
	e.Base->Accept(*this);
}

void NonValuedExpressionVisitor::VisitInfixExpression(InfixExpression& e)
{
	e.Left->Accept(*this);
	e.Right->Accept(*this);
}

void NonValuedExpressionVisitor::VisitAssignmentExpression(AssignmentExpression& e)
{
	ExpressionVisitor v(Printer, ErrorReport);
	e.Value->Accept(v);

	LValueExpressionVisitor lv(Printer, ErrorReport);
	e.Target->Accept(lv);
}

void NonValuedExpressionVisitor::VisitCommaExpression(CommaExpression& e)
{
	e.Left->Accept(*this);
	e.Right->Accept(*this);
}

void NonValuedExpressionVisitor::VisitForOptionalExpression(ForOptionalExpression& e)
{
	return;
}

void NonValuedExpressionVisitor::VisitForExpression(ForExpression& e)
{
	e.Condition->Accept(*this);
}

void NonValuedExpressionVisitor::VisitConstantValueExpression(ConstantValueExpression& e)
{
	return;
}
