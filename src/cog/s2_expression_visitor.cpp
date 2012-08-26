#include "s2_expression_visitor.h"
#include "s2_lval_visitor.h"
#include "err_helper.h"
#include <algorithm>

using namespace Cog::AST;
using Cog::Stages::Stage2::ExpressionVisitor;

ExpressionVisitor::ExpressionVisitor(Cog::Symbols::SymbolTable& symbolTable,
	const std::unordered_map<std::string, Cog::VirtualMachine::Value>& constantTable,
	Cog::Verbs::VerbTable& verbTable, Cog::Error::Report& report)
	: AST::Visitor("Stage2::ExpressionVisitor", report), SymbolTable(symbolTable),
	ConstantTable(constantTable), VerbTable(verbTable),	ExpressionType(VirtualMachine::Type::Void)
{
	return;
}

void ExpressionVisitor::VisitStringLiteralExpression(StringLiteralExpression& e)
{
	ExpressionType = VirtualMachine::Type::String;
}

void ExpressionVisitor::VisitIntegerLiteralExpression(IntegerLiteralExpression& e)
{
	ExpressionType = VirtualMachine::Type::Integer;
}

void ExpressionVisitor::VisitFloatLiteralExpression(FloatLiteralExpression& e)
{
	ExpressionType = VirtualMachine::Type::Float;
}

void ExpressionVisitor::VisitVectorLiteralExpression(VectorLiteralExpression& e)
{
	ExpressionType = VirtualMachine::Type::Vector;
}

void ExpressionVisitor::VisitIdentifierExpression(IdentifierExpression& e)
{
	// Convert identifier to lowercase for processing.
	std::transform(e.Identifier.begin(), e.Identifier.end(), e.Identifier.begin(), tolower);

	// Check constant table.
	auto it = ConstantTable.find(e.Identifier);
	if(it != ConstantTable.end())
	{
		// Identifier represents a constant.
		ExpressionType = it->second.GetType();
	}
	else
	{
		// Identifier does not represent a constant.

		// Actual type is not known, but the result must be
		// an actual value. Fake the result.
		ExpressionType = VirtualMachine::Type::Integer;

		if(!SymbolTable.IsSymbolDefined(e.Identifier))
		{
			Error::Helper::UndefinedSymbol(ErrorReport, VisitorName, e.Identifier, *e.Filename, e.Location);
			SymbolTable.AddSymbol(e.Identifier);
		}
	}
}

void ExpressionVisitor::VisitSubscriptExpression(SubscriptExpression& e)
{
	// Convert base identifier to lowercase for processing.
	std::transform(e.Base.begin(), e.Base.end(), e.Base.begin(), tolower);

	if(!SymbolTable.IsSymbolDefined(e.Base))
	{
		Error::Helper::UndefinedArrayBase(ErrorReport, VisitorName, e.Base, *e.Filename, e.Location);
	}

	ExpressionVisitor subscript(SymbolTable, ConstantTable, VerbTable, ErrorReport);
	e.Index->Accept(subscript);

	if(subscript.ExpressionType == VirtualMachine::Type::Void)
	{
		Error::Helper::IllegalVoidResult(ErrorReport, VisitorName, *e.Index->Filename, e.Index->Location);
	}

	// Actual type is not known, but the result must be
	// an actual value. Fake the result.
	ExpressionType = VirtualMachine::Type::Integer;
}

void ExpressionVisitor::VisitMethodCallExpression(MethodCallExpression& e)
{
	// Convert verb name to lowercase for processing.
	std::transform(e.Base.begin(), e.Base.end(), e.Base.begin(), tolower);

	if(!VerbTable.IsVerbDefined(e.Base))
	{
		Error::Helper::UnknownVerb(ErrorReport, VisitorName, e.Base, *e.Filename, e.Location);
		ExpressionType = VirtualMachine::Type::Integer;
	}
	else
	{
		auto id = VerbTable.GetVerb(e.Base);
		size_t pcount = VerbTable.ParameterCount(id);
		ExpressionType = VerbTable.ReturnType(id);

		if(pcount != e.Arguments->size())
		{
			Error::Helper::InvalidArgumentCount(ErrorReport, VisitorName, e.Base, pcount,
				e.Arguments->size(), *e.Filename, e.Location);
		}
		else
		{
			for(auto it = e.Arguments->begin(); it != e.Arguments->end(); ++it)
			{
				ExpressionVisitor arg(SymbolTable, ConstantTable, VerbTable, ErrorReport);
				(*it)->Accept(arg);

				if(arg.ExpressionType == VirtualMachine::Type::Void)
				{
					Error::Helper::IllegalVoidResult(ErrorReport, VisitorName, *(*it)->Filename, (*it)->Location);
				}
			}
		}
	}

	return;
}

void ExpressionVisitor::VisitUnaryExpression(UnaryExpression& e)
{
	ExpressionVisitor v(SymbolTable, ConstantTable, VerbTable, ErrorReport);
	e.Base->Accept(v);

	if(v.ExpressionType == VirtualMachine::Type::Void)
	{
		Error::Helper::IllegalVoidResult(ErrorReport, VisitorName, *e.Base->Filename, e.Base->Location);
		v.ExpressionType = VirtualMachine::Type::Integer;
	}

	switch(e.Operator)
	{
	case UnaryOperator::Plus:
	case UnaryOperator::Minus:
		ExpressionType = v.ExpressionType;
		return;

	case UnaryOperator::Not:
		if(v.ExpressionType != VirtualMachine::Type::Boolean)
		{
			Error::Helper::ResultNotBoolean(ErrorReport, VisitorName, *e.Filename, e.Location);
		}
		
		ExpressionType = VirtualMachine::Type::Boolean;
		return;
	}
}

void ExpressionVisitor::VisitInfixExpression(InfixExpression& e)
{
	ExpressionVisitor left(SymbolTable, ConstantTable, VerbTable, ErrorReport);
	e.Left->Accept(left);

	ExpressionVisitor right(SymbolTable, ConstantTable, VerbTable, ErrorReport);
	e.Right->Accept(right);

	// Left and right must both have values.
	if(left.ExpressionType == VirtualMachine::Type::Void)
	{
		Error::Helper::IllegalVoidResult(ErrorReport, VisitorName, *e.Left->Filename, e.Left->Location);
		left.ExpressionType = VirtualMachine::Type::Integer;
	}

	if(right.ExpressionType == VirtualMachine::Type::Void)
	{
		Error::Helper::IllegalVoidResult(ErrorReport, VisitorName, *e.Right->Filename, e.Right->Location);
		right.ExpressionType = VirtualMachine::Type::Integer;
	}

	switch(e.Operator)
	{
	case InfixOperator::Addition:
	case InfixOperator::Subtraction:
	case InfixOperator::Multiplication:
	case InfixOperator::Division:
	case InfixOperator::Modulo:
		// Result must have a numeric type.
		// Fake the result.
		ExpressionType = VirtualMachine::Type::Integer;
		break;

	case InfixOperator::Greater:
	case InfixOperator::GreaterEqual:
	case InfixOperator::Less:
	case InfixOperator::LessEqual:
	case InfixOperator::Equal:
	case InfixOperator::NotEqual:
		// Result must have a boolean type.
		ExpressionType = VirtualMachine::Type::Boolean;
		break;

	case InfixOperator::And:
	case InfixOperator::Or:
	case InfixOperator::Xor:
		// Result must have an integer type.
		ExpressionType = VirtualMachine::Type::Integer;
		break;

	case InfixOperator::LogicalAnd:
	case InfixOperator::LogicalOr:
		// Inputs must have boolean types.
		if(left.ExpressionType != VirtualMachine::Type::Boolean)
		{
			Error::Helper::ResultNotBoolean(ErrorReport, VisitorName, *e.Left->Filename, e.Left->Location);
		}

		if(right.ExpressionType != VirtualMachine::Type::Boolean)
		{
			Error::Helper::ResultNotBoolean(ErrorReport, VisitorName, *e.Right->Filename, e.Right->Location);
		}

		// Result must have a boolean type.
		ExpressionType = VirtualMachine::Type::Boolean;
		break;
	}

	return;
}

void ExpressionVisitor::VisitAssignmentExpression(AssignmentExpression& e)
{
	LValueVisitor target(SymbolTable, ConstantTable, VerbTable, ErrorReport);
	e.Target->Accept(target);

	ExpressionVisitor value(SymbolTable, ConstantTable, VerbTable, ErrorReport);
	e.Value->Accept(value);

	if(value.ExpressionType == VirtualMachine::Type::Void)
	{
		Error::Helper::IllegalVoidResult(ErrorReport, VisitorName, *e.Value->Filename, e.Value->Location);
	}

	ExpressionType = value.ExpressionType;
}

void ExpressionVisitor::VisitCommaExpression(CommaExpression& e)
{
	ExpressionVisitor left(SymbolTable, ConstantTable, VerbTable, ErrorReport);
	e.Left->Accept(left);

	ExpressionVisitor right(SymbolTable, ConstantTable, VerbTable, ErrorReport);
	e.Right->Accept(right);

	ExpressionType = right.ExpressionType;
}

void ExpressionVisitor::VisitForOptionalExpression(ForOptionalExpression& e)
{
	ExpressionType = VirtualMachine::Type::Boolean;
}

void ExpressionVisitor::VisitForExpression(ForExpression& e)
{
	e.Condition->Accept(*this);
	return;
}
