#include "s4_code_visitor.h"
#include "s4_expression_visitor.h"
#include "s4_nonval_expression_visitor.h"

#include <boost/format.hpp>

using namespace Cog::AST;
using Cog::Stages::Stage4::CodeVisitor;

CodeVisitor::CodeVisitor(int& nextLabelNumber, Cog::IR::Printer& printer,
	Cog::Error::Report& report, const std::string breakLabel)
	: AST::Visitor("Stage4::CodeVisitor", report), nextLabelNumber(nextLabelNumber),
	Printer(printer), BreakLabel(breakLabel)
{
	return;
}

std::string CodeVisitor::GenerateLabel(const std::string& prefix)
{
	int num = nextLabelNumber++;

	return boost::str(boost::format("%s%03d") % prefix % num);
}

void CodeVisitor::VisitCompoundStatement(CompoundStatement& s)
{
	for(auto it = s.Code->begin(); it != s.Code->end(); ++it)
	{
		(*it)->Accept(*this);
	}
}

void CodeVisitor::VisitEmptyStatement(EmptyStatement& s)
{
	return;
}

void CodeVisitor::VisitExpressionStatement(ExpressionStatement& s)
{
	NonValuedExpressionVisitor v(Printer, ErrorReport);
	s.Expression->Accept(v);
}

void CodeVisitor::VisitBreakStatement(BreakStatement& s)
{
	Printer.Jmp(BreakLabel);
}

void CodeVisitor::VisitReturnStatement(ReturnStatement& s)
{
	Printer.Ret();
}

void CodeVisitor::VisitCallStatement(CallStatement& s)
{
	Printer.Jal(s.Label);
}

void CodeVisitor::VisitIfStatement(IfStatement& s)
{
	std::string endlabel = GenerateLabel("B");

	ExpressionVisitor v(Printer, ErrorReport);
	s.Condition->Accept(v);
	Printer.Bf(endlabel);

	s.Code->Accept(*this);

	Printer.Label(endlabel);
}

void CodeVisitor::VisitIfElseStatement(IfElseStatement& s)
{
	std::string elselabel = GenerateLabel("B");
	std::string endlabel = GenerateLabel("B");

	ExpressionVisitor v(Printer, ErrorReport);
	s.Condition->Accept(v);

	Printer.Bf(elselabel);

	s.Code->Accept(*this);
	Printer.Jmp(endlabel);

	Printer.Label(elselabel);
	s.ElseCode->Accept(*this);

	Printer.Label(endlabel);
}

void CodeVisitor::VisitWhileStatement(WhileStatement& s)
{
	std::string bodybeginlabel = GenerateLabel("L");
	std::string breaklabel = GenerateLabel("L");

	ExpressionVisitor v(Printer, ErrorReport);
	s.Condition->Accept(v);
	Printer.Bf(breaklabel);

	Printer.Label(bodybeginlabel);

	CodeVisitor cv(nextLabelNumber, Printer, ErrorReport, breaklabel);
	s.Code->Accept(cv);

	s.Condition->Accept(v);
	Printer.Bt(bodybeginlabel);

	Printer.Label(breaklabel);
}

void CodeVisitor::VisitDoStatement(DoStatement& s)
{
	std::string bodybeginlabel = GenerateLabel("L");
	std::string breaklabel = GenerateLabel("L");

	Printer.Label(bodybeginlabel);
	CodeVisitor cv(nextLabelNumber, Printer, ErrorReport, breaklabel);
	s.Code->Accept(cv);

	ExpressionVisitor v(Printer, ErrorReport);
	s.Condition->Accept(v);
	Printer.Bt(bodybeginlabel);

	Printer.Label(breaklabel);
}

void CodeVisitor::VisitForStatement(ForStatement& s)
{
	std::string bodybeginlabel = GenerateLabel("L");
	std::string breaklabel = GenerateLabel("L");

	NonValuedExpressionVisitor nv(Printer, ErrorReport);
	ExpressionVisitor v(Printer, ErrorReport);

	s.Initializer->Accept(nv);

	s.Condition->Accept(v);
	Printer.Bf(breaklabel);

	Printer.Label(bodybeginlabel);
	CodeVisitor cv(nextLabelNumber, Printer, ErrorReport, breaklabel);
	s.Code->Accept(cv);

	s.Incrementer->Accept(nv);

	s.Condition->Accept(v);
	Printer.Bt(bodybeginlabel);

	Printer.Label(breaklabel);
}

void CodeVisitor::VisitLabeledStatement(LabeledStatement& s)
{
	Printer.Label(s.Label);
	s.Code->Accept(*this);
}
