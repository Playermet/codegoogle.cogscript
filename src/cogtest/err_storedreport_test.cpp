#include <nullunit/nullunit.h>
#include <sstream>

#include "cog/err_storedreport.h"

using namespace Cog::Error;

class StoredReportTestFixture : public NullUnit::Fixture
{
public:
	StoredReport report;
};

BeginSuiteFixture(StoredReportTest, StoredReportTestFixture);

Case(AddError)
{
	Test_Assert_Eq(report.GetWarningCount(), 0);
	Test_Assert_Eq(report.GetErrorCount(), 0);

	report.AddError(ErrorCode::SyntaxError, "Stage 0", "test.w", "Reason",
		Location(15, 16, 10, 11));

	Test_Assert_Eq(report.GetWarningCount(), 0);
	Test_Assert_Eq(report.GetErrorCount(), 1);

	auto it = report.ErrorBegin();
	Test_Assert_Eq(it->Code, ErrorCode::SyntaxError);
	Test_Assert_Eq(it->Level, ErrorLevel::Error);
	Test_Assert_Eq(it->Stage, "Stage 0");
	Test_Assert_Eq(it->Filename, "test.w");
	Test_Assert_Eq(it->Reason, "Reason");

	Location l(15, 16, 10, 11);

	Test_Assert_Eq(it->ErrorLocation.first_line, l.first_line);
	Test_Assert_Eq(it->ErrorLocation.first_col, l.first_col);
	Test_Assert_Eq(it->ErrorLocation.last_line, l.last_line);
	Test_Assert_Eq(it->ErrorLocation.last_col, l.last_col);
}

Case(AddWarning)
{
	Test_Assert_Eq(report.GetErrorCount(), 0);
	Test_Assert_Eq(report.GetWarningCount(), 0);

	report.AddWarning(ErrorCode::SyntaxError, "Stage 0", "test.w", "Reason",
		Location(15, 16, 10, 11));

	Test_Assert_Eq(report.GetErrorCount(), 0);
	Test_Assert_Eq(report.GetWarningCount(), 1);

	auto it = report.ErrorBegin();
	Test_Assert_Eq(it->Code, ErrorCode::SyntaxError);
	Test_Assert_Eq(it->Level, ErrorLevel::Warning);
	Test_Assert_Eq(it->Stage, "Stage 0");
	Test_Assert_Eq(it->Filename, "test.w");
	Test_Assert_Eq(it->Reason, "Reason");

	Location l(15, 16, 10, 11);

	Test_Assert_Eq(it->ErrorLocation.first_line, l.first_line);
	Test_Assert_Eq(it->ErrorLocation.first_col, l.first_col);
	Test_Assert_Eq(it->ErrorLocation.last_line, l.last_line);
	Test_Assert_Eq(it->ErrorLocation.last_col, l.last_col);
}

Case(AddCriticalError)
{
	Test_Assert_Eq(report.GetWarningCount(), 0);
	Test_Assert_Eq(report.GetErrorCount(), 0);

	report.AddCriticalError(ErrorCode::FeatureNotImplemented, "Stage 0", "Reason");

	Test_Assert_Eq(report.GetWarningCount(), 0);
	Test_Assert_Eq(report.GetErrorCount(), 1);

	auto it = report.ErrorBegin();
	Test_Assert_Eq(it->Code, ErrorCode::FeatureNotImplemented);
	Test_Assert_Eq(it->Level, ErrorLevel::CriticalError);
	Test_Assert_Eq(it->Stage, "Stage 0");
	Test_Assert_Eq(it->Reason, "Reason");
}

EndSuite(StoredReportTest);
