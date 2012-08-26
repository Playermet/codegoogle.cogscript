#ifndef _CODEGEN_TEST_FIXTURE_H_INCLUDED_
#define _CODEGEN_TEST_FIXTURE_H_INCLUDED_

#include "semantic_test_fixture.h"
#include "cog/cog_messageid.h"
#include "cog/cog_script.h"

class CodegenTestFixture : public SemanticTestFixture
{
private:
	std::unordered_map<std::string, Cog::MessageId::Enum> messageTable;

public:
	Cog::Script Script;

protected:
	CodegenTestFixture(const std::string& basePath);

public:
	void ParseFile(const boost::filesystem::path& path);
};

#define AssertResult(n_errors, n_warnings) { \
	Test_Expect_Eq(Report.GetErrorCount(), n_errors); \
	Test_Expect_Eq(Report.GetWarningCount(), n_warnings); \
	if(Report.GetErrorCount() != n_errors || Report.GetWarningCount() != n_warnings) { \
		PrintErrors(); \
	} \
}

#endif // _CODEGEN_TEST_FIXTURE_H_INCLUDED_
