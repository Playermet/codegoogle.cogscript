#include "s3_code_visitor.h"
#include "s3_expression_visitor.h"

using namespace Cog::AST;
using Cog::Stages::Stage3::CodeVisitor;

CodeVisitor::CodeVisitor(Cog::AST::Factory& factory, Cog::Symbols::SymbolTable& symbolTable,
	const std::unordered_map<std::string, Cog::VirtualMachine::Value>& constantTable,
	Cog::Error::Report& report)
	: AST::Visitor("Stage3::CodeVisitor", report), Factory(factory), SymbolTable(symbolTable),
	ConstantTable(constantTable)
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
	ExpressionVisitor v(Factory, SymbolTable, ConstantTable, ErrorReport);
	s.Expression->Accept(v);
	s.Expression = v.GetSubstitution();
}

void CodeVisitor::VisitBreakStatement(BreakStatement& s)
{
	return;
}

void CodeVisitor::VisitReturnStatement(ReturnStatement& s)
{
	return;
}

void CodeVisitor::VisitCallStatement(CallStatement& s)
{
	return;
}

void CodeVisitor::VisitIfStatement(IfStatement& s)
{
	ExpressionVisitor v(Factory, SymbolTable, ConstantTable, ErrorReport);
	s.Condition->Accept(v);
	s.Condition = v.GetSubstitution();

	s.Code->Accept(*this);
}

void CodeVisitor::VisitIfElseStatement(IfElseStatement& s)
{
	ExpressionVisitor v(Factory, SymbolTable, ConstantTable, ErrorReport);
	s.Condition->Accept(v);
	s.Condition = v.GetSubstitution();

	s.Code->Accept(*this);
	s.ElseCode->Accept(*this);
}

void CodeVisitor::VisitWhileStatement(WhileStatement& s)
{
	ExpressionVisitor v(Factory, SymbolTable, ConstantTable, ErrorReport);
	s.Condition->Accept(v);
	s.Condition = v.GetSubstitution();

	s.Code->Accept(*this);
}

void CodeVisitor::VisitDoStatement(DoStatement& s)
{
	ExpressionVisitor v(Factory, SymbolTable, ConstantTable, ErrorReport);
	s.Condition->Accept(v);
	s.Condition = v.GetSubstitution();

	s.Code->Accept(*this);
}

void CodeVisitor::VisitForStatement(ForStatement& s)
{
	ExpressionVisitor v(Factory, SymbolTable, ConstantTable, ErrorReport);

	s.Condition->Accept(v);
	s.Incrementer->Accept(v);
	s.Initializer->Accept(v);

	s.Code->Accept(*this);
}

void CodeVisitor::VisitLabeledStatement(LabeledStatement& s)
{
	s.Code->Accept(*this);
}
