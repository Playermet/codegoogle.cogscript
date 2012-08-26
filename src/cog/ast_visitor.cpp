#include "ast_visitor.h"
#include "err_helper.h"

Cog::AST::Visitor::Visitor(const std::string& name, Error::Report& report)
	: VisitorName(name), ErrorReport(report)
{
	return;
}

Cog::AST::Visitor::~Visitor()
{
	return;
}

void Cog::AST::Visitor::DefaultAction(const std::string& action, Node& n)
{
	Error::Helper::FeatureNotImplemented(ErrorReport, VisitorName, action);
}

ASTCLASS_ALL(AVDEFAULTACTION)
