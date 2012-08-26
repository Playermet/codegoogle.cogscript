#ifndef _SYNTACTIC_TEST_FIXTURE_H_INCLUDED_
#define _SYNTACTIC_TEST_FIXTURE_H_INCLUDED_

#include <nullunit/nullunit.h>
#include <boost/filesystem/path.hpp>

#include "cog/err_storedreport.h"
#include "cog/gra_context.h"
#include "cog/cog_script.h"

class SyntacticTestFixture : public NullUnit::Fixture
{
public:
	Cog::Script Script;
	Cog::Error::StoredReport Report;
	const boost::filesystem::path BasePath;

protected:
	SyntacticTestFixture(const std::string& basePath);

public:
	virtual void ParseFile(const boost::filesystem::path& path);
	void PrintErrors() const;
};

#define AssertResult(n_errors, n_warnings) { \
	Test_Expect_Eq(Report.GetErrorCount(), n_errors); \
	Test_Expect_Eq(Report.GetWarningCount(), n_warnings); \
	if(Report.GetErrorCount() != n_errors || Report.GetWarningCount() != n_warnings) { \
		PrintErrors(); \
	} \
}

#endif // _SYNTACTIC_TEST_FIXTURE_H_INCLUDED_
