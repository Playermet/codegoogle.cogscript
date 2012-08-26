#include "err_streamreport.h"

#include <iomanip>
#include <iostream>

Cog::Error::StreamReport::StreamReport(std::ostream& s)
	: errorCount(0), warningCount(0), stream(s)
{
	return;
}

void Cog::Error::StreamReport::PrintFormattedError(
	ErrorCode::Enum errorCode, const std::string& errorLevel,
	const std::string& stage, const std::string& reason)
{
	stream << errorLevel << " " << std::setfill('0') << std::setw(4) <<
		errorCode << ": " << reason << " [" << stage << "]" << std::endl;
}

void Cog::Error::StreamReport::PrintLineFormattedError(
	ErrorCode::Enum errorCode, const std::string& errorLevel,
	const std::string& stage, const std::string& filename,
	const std::string& reason, const Error::Location& errorLocation)
{
	stream << filename << "(" << errorLocation.first_line << "," <<
		errorLocation.first_col << "): " << errorLevel << " " <<
		std::setfill('0') << std::setw(4) << errorCode << ": " <<
		reason << " [" << stage << "]" << std::endl;
}

void Cog::Error::StreamReport::AddError(
	ErrorCode::Enum errorCode, const std::string& stage,
	const std::string& filename, const std::string& reason,
	const Error::Location& errorLocation)
{
	PrintLineFormattedError(errorCode, "error", stage, filename, reason, errorLocation);
	++errorCount;
}

void Cog::Error::StreamReport::AddWarning(
	ErrorCode::Enum errorCode, const std::string& stage,
	const std::string& filename, const std::string& reason,
	const Error::Location& errorLocation)
{
	PrintLineFormattedError(errorCode, "warning", stage, filename, reason, errorLocation);
	++warningCount;
}

void Cog::Error::StreamReport::AddCriticalError(
	ErrorCode::Enum errorCode, const std::string& stage, const std::string& reason)
{
	PrintFormattedError(errorCode, "critical error", stage, reason);
	++errorCount;
}

unsigned int Cog::Error::StreamReport::GetErrorCount()
{
	return errorCount;
}

unsigned int Cog::Error::StreamReport::GetWarningCount()
{
	return warningCount;
}
