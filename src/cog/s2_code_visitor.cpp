#include "s2_code_visitor.h"
#include "s2_expression_visitor.h"
#include "err_helper.h"

#include <algorithm>

using namespace Cog::AST;
using Cog::Stages::Stage2::CodeVisitor;

CodeVisitor::CodeVisitor(Cog::Symbols::SymbolTable& symbolTable,
	const std::unordered_map<std::string, Cog::VirtualMachine::Value>& constantTable,
	Cog::Verbs::VerbTable& verbTable, const std::unordered_set<std::string>& SeenLabels,
	Cog::Error::Report& report, bool inside_loop, bool inside_block)
	: AST::Visitor("Stage2::CodeVisitor", report), SymbolTable(symbolTable),
	ConstantTable(constantTable), VerbTable(verbTable),
	SeenLabels(SeenLabels), inside_loop(inside_loop), inside_block(inside_block)
{
	return;
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
	ExpressionVisitor v(SymbolTable, ConstantTable, VerbTable, ErrorReport);
	s.Expression->Accept(v);
}

void CodeVisitor::VisitBreakStatement(BreakStatement& s)
{
	if(!inside_loop)
	{
		Error::Helper::BreakOutsideLoop(ErrorReport, VisitorName, *s.Filename, s.Location);
	}
}

void CodeVisitor::VisitReturnStatement(ReturnStatement& s)
{
	return;
}

void CodeVisitor::VisitCallStatement(CallStatement& s)
{
	// Convert label name to lowercase for processing
	std::transform(s.Label.begin(), s.Label.end(), s.Label.begin(), tolower);

	if(SeenLabels.find(s.Label) == SeenLabels.end())
	{
		Error::Helper::CallToUnusedLabel(ErrorReport, VisitorName,
			s.Label, *s.Filename, s.Location);
	}
}

void CodeVisitor::VisitIfStatement(IfStatement& s)
{
	ExpressionVisitor cond(SymbolTable, ConstantTable, VerbTable, ErrorReport);
	s.Condition->Accept(cond);

	if(cond.ExpressionType != VirtualMachine::Type::Boolean)
	{
		Error::Helper::ResultNotBoolean(ErrorReport, VisitorName, *s.Condition->Filename, s.Condition->Location);
	}

	CodeVisitor v(SymbolTable, ConstantTable, VerbTable, SeenLabels, ErrorReport, inside_loop, true);
	s.Code->Accept(v);
}

void CodeVisitor::VisitIfElseStatement(IfElseStatement& s)
{
	ExpressionVisitor cond(SymbolTable, ConstantTable, VerbTable, ErrorReport);
	s.Condition->Accept(cond);

	if(cond.ExpressionType != VirtualMachine::Type::Boolean)
	{
		Error::Helper::ResultNotBoolean(ErrorReport, VisitorName, *s.Condition->Filename, s.Condition->Location);
	}

	CodeVisitor first(SymbolTable, ConstantTable, VerbTable, SeenLabels, ErrorReport, inside_loop, true);
	s.Code->Accept(first);

	CodeVisitor second(SymbolTable, ConstantTable, VerbTable, SeenLabels, ErrorReport, inside_loop, true);
	s.ElseCode->Accept(second);
}

void CodeVisitor::VisitWhileStatement(WhileStatement& s)
{
	ExpressionVisitor cond(SymbolTable, ConstantTable, VerbTable, ErrorReport);
	s.Condition->Accept(cond);

	if(cond.ExpressionType != VirtualMachine::Type::Boolean)
	{
		Error::Helper::ResultNotBoolean(ErrorReport, VisitorName, *s.Condition->Filename, s.Condition->Location);
	}

	CodeVisitor v(SymbolTable, ConstantTable, VerbTable, SeenLabels, ErrorReport, true, true);
	s.Code->Accept(v);
}

void CodeVisitor::VisitDoStatement(DoStatement& s)
{
	ExpressionVisitor cond(SymbolTable, ConstantTable, VerbTable, ErrorReport);
	s.Condition->Accept(cond);

	if(cond.ExpressionType != VirtualMachine::Type::Boolean)
	{
		Error::Helper::ResultNotBoolean(ErrorReport, VisitorName, *s.Condition->Filename, s.Condition->Location);
	}

	CodeVisitor v(SymbolTable, ConstantTable, VerbTable, SeenLabels, ErrorReport, true, true);
	s.Code->Accept(v);
}

void CodeVisitor::VisitForStatement(ForStatement& s)
{
	ExpressionVisitor init(SymbolTable, ConstantTable, VerbTable, ErrorReport);
	s.Initializer->Accept(init);

	ExpressionVisitor cond(SymbolTable, ConstantTable, VerbTable, ErrorReport);
	s.Condition->Accept(cond);

	if(cond.ExpressionType != VirtualMachine::Type::Boolean)
	{
		Error::Helper::ResultNotBoolean(ErrorReport, VisitorName, *s.Condition->Filename, s.Condition->Location);
	}

	ExpressionVisitor inc(SymbolTable, ConstantTable, VerbTable, ErrorReport);
	s.Incrementer->Accept(inc);

	CodeVisitor v(SymbolTable, ConstantTable, VerbTable, SeenLabels, ErrorReport, true, true);
	s.Code->Accept(v);
}

void CodeVisitor::VisitLabeledStatement(LabeledStatement& s)
{
	if(inside_block)
	{
		Error::Helper::LabelInsideBlock(ErrorReport, VisitorName, s.Label, *s.Filename, s.Location);
	}

	s.Code->Accept(*this);
}
