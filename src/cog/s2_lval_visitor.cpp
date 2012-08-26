#include "s2_lval_visitor.h"
#include "s2_expression_visitor.h"
#include "err_helper.h"
#include <algorithm>

using namespace Cog::AST;
using Cog::Stages::Stage2::LValueVisitor;

LValueVisitor::LValueVisitor(Cog::Symbols::SymbolTable& symbolTable,
	const std::unordered_map<std::string, Cog::VirtualMachine::Value>& constantTable,
	Cog::Verbs::VerbTable& verbTable, Cog::Error::Report& report)
	: AST::Visitor("Stage2::LValueVisitor", report), SymbolTable(symbolTable),
	ConstantTable(constantTable), VerbTable(verbTable)
{
	return;
}

void LValueVisitor::DefaultAction(const std::string& action, Node& n)
{
	Error::Helper::AssignToRValue(ErrorReport, VisitorName, *n.Filename, n.Location);
}

void LValueVisitor::VisitIdentifierExpression(IdentifierExpression& e)
{
	// Convert identifier to lowercase for processing.
	std::transform(e.Identifier.begin(), e.Identifier.end(), e.Identifier.begin(), tolower);

	if(!SymbolTable.IsSymbolDefined(e.Identifier))
	{
		Error::Helper::UndefinedSymbol(ErrorReport, VisitorName, e.Identifier, *e.Filename, e.Location);
		SymbolTable.AddSymbol(e.Identifier);
	}
}

void LValueVisitor::VisitSubscriptExpression(SubscriptExpression& e)
{
	// Convert base identifier to lowercase for processing.
	std::transform(e.Base.begin(), e.Base.end(), e.Base.begin(), tolower);

	if(!SymbolTable.IsSymbolDefined(e.Base))
	{
		Error::Helper::UndefinedSymbol(ErrorReport, VisitorName, e.Base, *e.Filename, e.Location);
		SymbolTable.AddSymbol(e.Base);
	}

	ExpressionVisitor subscript(SymbolTable, ConstantTable, VerbTable, ErrorReport);
	e.Index->Accept(subscript);

	if(subscript.ExpressionType == VirtualMachine::Type::Void)
	{
		Error::Helper::IllegalVoidResult(ErrorReport, VisitorName, *e.Index->Filename, e.Index->Location);
	}
}
