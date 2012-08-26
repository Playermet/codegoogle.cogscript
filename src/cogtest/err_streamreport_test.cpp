#include <nullunit/nullunit.h>
#include <sstream>

#include "cog/err_streamreport.h"

using namespace Cog::Error;

class StreamReportTestFixture : public NullUnit::Fixture
{
public:
	std::ostringstream dummystream;
	StreamReport report;

	StreamReportTestFixture()
		: report(dummystream)
	{
		return;
	}
};

BeginSuiteFixture(StreamReportTest, StreamReportTestFixture);

Case(AddError)
{
	Test_Assert_Eq(report.GetWarningCount(), 0);
	Test_Assert_Eq(report.GetErrorCount(), 0);

	report.AddError(ErrorCode::SyntaxError, "Stage 0", "test.w", "Reason",
		Location(15, 16, 10, 11));

	Test_Assert_Eq(report.GetWarningCount(), 0);
	Test_Assert_Eq(report.GetErrorCount(), 1);
}

Case(AddWarning)
{
	Test_Assert_Eq(report.GetErrorCount(), 0);
	Test_Assert_Eq(report.GetWarningCount(), 0);

	report.AddWarning(ErrorCode::SyntaxError, "Stage 0", "test.w", "Reason",
		Location(15, 16, 10, 11));

	Test_Assert_Eq(report.GetErrorCount(), 0);
	Test_Assert_Eq(report.GetWarningCount(), 1);
}

Case(AddCriticalError)
{
	Test_Assert_Eq(report.GetWarningCount(), 0);
	Test_Assert_Eq(report.GetErrorCount(), 0);

	report.AddCriticalError(ErrorCode::FeatureNotImplemented, "Stage 0", "Reason");

	Test_Assert_Eq(report.GetWarningCount(), 0);
	Test_Assert_Eq(report.GetErrorCount(), 1);
}

EndSuite(StreamReportTest);
