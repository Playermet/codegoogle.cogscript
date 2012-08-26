#ifndef _SEMANTIC_TEST_FIXTURE_H_INCLUDED_
#define _SEMANTIC_TEST_FIXTURE_H_INCLUDED_

#include "syntactic_test_fixture.h"
#include "cog/sym_table.h"
#include "cog/v_table.h"

#include <string>
#include <unordered_map>

class SemanticTestFixture : public SyntacticTestFixture
{
public:
	std::unordered_map<std::string, Cog::VirtualMachine::Value> ConstantTable;
	Cog::Verbs::VerbTable VerbTable;

protected:
	SemanticTestFixture(const std::string& basePath);

public:
	virtual void ParseFile(const boost::filesystem::path& path);
};

#endif // _SEMANTIC_TEST_FIXTURE_H_INCLUDED_
