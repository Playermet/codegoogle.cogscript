#include "s2_label_visitor.h"
#include "err_helper.h"

#include <algorithm>

using namespace Cog::AST;
using Cog::Stages::Stage2::LabelVisitor;

LabelVisitor::LabelVisitor(std::unordered_set<std::string>& SeenLabels, Cog::Error::Report& report)
	: AST::Visitor("Stage2::LabelVisitor", report), SeenLabels(SeenLabels)
{
	return;
}

void LabelVisitor::VisitCompoundStatement(CompoundStatement& s)
{
	for(auto it = s.Code->begin(); it != s.Code->end(); ++it)
	{
		(*it)->Accept(*this);
	}
}

void LabelVisitor::VisitEmptyStatement(EmptyStatement& s)
{
	return;
}

void LabelVisitor::VisitExpressionStatement(ExpressionStatement& s)
{
	return;
}

void LabelVisitor::VisitBreakStatement(BreakStatement& s)
{
	return;
}

void LabelVisitor::VisitReturnStatement(ReturnStatement& s)
{
	return;
}

void LabelVisitor::VisitCallStatement(CallStatement& s)
{
	return;
}

void LabelVisitor::VisitIfStatement(IfStatement& s)
{
	s.Code->Accept(*this);
}

void LabelVisitor::VisitIfElseStatement(IfElseStatement& s)
{
	s.Code->Accept(*this);
	s.ElseCode->Accept(*this);
}

void LabelVisitor::VisitWhileStatement(WhileStatement& s)
{
	s.Code->Accept(*this);
}

void LabelVisitor::VisitDoStatement(DoStatement& s)
{
	s.Code->Accept(*this);
}

void LabelVisitor::VisitForStatement(ForStatement& s)
{
	s.Code->Accept(*this);
}

void LabelVisitor::VisitLabeledStatement(LabeledStatement& s)
{
	// Convert label name to lowercase for processing
	std::transform(s.Label.begin(), s.Label.end(), s.Label.begin(), tolower);

	if(SeenLabels.find(s.Label) != SeenLabels.end())
	{
		Error::Helper::LabelRedefinition(ErrorReport, VisitorName, s.Label, *s.Filename, s.Location);
	}
	else
	{
		SeenLabels.insert(s.Label);
	}
}
