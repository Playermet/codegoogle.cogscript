#include "err_storedreport.h"

#include <iomanip>
#include <iostream>

Cog::Error::StoredReport::StoredReport()
	: errorCount(0), warningCount(0)
{
	return;
}

void Cog::Error::StoredReport::AddError(
	ErrorCode::Enum errorCode, const std::string& stage,
	const std::string& filename, const std::string& reason,
	const Cog::Error::Location& errorLocation)
{
	container.push_back(
		Error(errorCode, ErrorLevel::Error, stage, filename, reason, errorLocation));
	++errorCount;
}

void Cog::Error::StoredReport::AddWarning(
	ErrorCode::Enum errorCode, const std::string& stage,
	const std::string& filename, const std::string& reason,
	const Cog::Error::Location& errorLocation)
{
	container.push_back(
		Error(errorCode, ErrorLevel::Warning, stage, filename, reason, errorLocation));
	++warningCount;
}

void Cog::Error::StoredReport::AddCriticalError(
	ErrorCode::Enum errorCode, const std::string& stage, const std::string& reason)
{
	container.push_back(
		Error(errorCode, ErrorLevel::CriticalError, stage, "", reason, Cog::Error::Location()));
	++errorCount;
}

unsigned int Cog::Error::StoredReport::GetErrorCount()
{
	return errorCount;
}

unsigned int Cog::Error::StoredReport::GetWarningCount()
{
	return warningCount;
}

std::vector<Cog::Error::Error>::const_iterator Cog::Error::StoredReport::ErrorBegin() const
{
	return container.begin();
}

std::vector<Cog::Error::Error>::const_iterator Cog::Error::StoredReport::ErrorEnd() const
{
	return container.end();
}

void Cog::Error::StoredReport::Repeat(Report& report) const
{
	for(auto it = container.begin(); it != container.end(); ++it)
	{
		switch(it->Level)
		{
		case ErrorLevel::CriticalError:
			report.AddCriticalError(it->Code, it->Stage, it->Reason);
			break;

		case ErrorLevel::Error:
			report.AddError(it->Code, it->Stage, it->Filename, it->Reason, it->ErrorLocation);
			break;

		case ErrorLevel::Warning:
			report.AddWarning(it->Code, it->Stage, it->Filename, it->Reason, it->ErrorLocation);
			break;
		}
	}

	return;
}
