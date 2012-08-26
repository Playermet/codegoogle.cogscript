#include "s2_symbolfield_visitor.h"

using namespace Cog::AST;
using Cog::Stages::Stage2::SymbolFieldVisitor;

SymbolFieldVisitor::SymbolFieldVisitor(Cog::Error::Report& report)
	: AST::Visitor("Stage2::SymbolFieldVisitor", report),
	is_float(false), is_int(false), is_str(false), is_numeric(false)
{
	return;
}

void SymbolFieldVisitor::VisitStringFragmentField(StringFragmentField& v)
{
	is_str = true;
	str_value = v.Value;
}

void SymbolFieldVisitor::VisitIntegerField(IntegerField& v)
{
	is_int = true;
	is_numeric = true;
	int_value = v.Value;
	float_value = static_cast<float>(v.Value);
}

void SymbolFieldVisitor::VisitFloatField(FloatField& v)
{
	is_float = true;
	is_numeric = true;
	float_value = v.Value;
	int_value = static_cast<int>(v.Value);
}

