#include "v_verb.h"

Cog::Verbs::BaseVerb::BaseVerb(VirtualMachine::Type::Enum returnType, size_t parameterCount)
	: parameterCount(parameterCount), returnType(returnType)
{
	return;
}

Cog::Verbs::BaseVerb::~BaseVerb()
{
	return;
}

