#include "err_error.h"

#include <sstream>
#include <iomanip>

Cog::Error::Error::Error(
	ErrorCode::Enum errorCode, ErrorLevel::Enum errorLevel,
	const std::string& stage, const std::string& filename,
	const std::string& reason, const Cog::Error::Location& errorLocation)
	: Code(errorCode), Level(errorLevel), Stage(stage),
	Filename(filename), Reason(reason), ErrorLocation(errorLocation)
{
	return;
}

std::string FormatError(const Cog::Error::Error& error)
{
	std::stringstream ss;

	ss << Cog::Error::ErrorLevel::ToString(error.Level)
		<< " " << std::setfill('0') << std::setw(4) << error.Code
		<< ": " << error.Reason << " [" << error.Stage << "]";

	return ss.str();
}

std::string FormatLineError(const Cog::Error::Error& error)
{
	std::stringstream ss;

	ss << error.Filename << "(" << error.ErrorLocation.first_line << "," <<
		error.ErrorLocation.first_col << "): " <<
		Cog::Error::ErrorLevel::ToString(error.Level) << " " <<
		std::setfill('0') << std::setw(4) << error.Code << ": " <<
		error.Reason << " [" << error.Stage << "]";

	return ss.str();
}

Cog::Error::Error::operator std::string() const
{
	switch(Level)
	{
	case ErrorLevel::CriticalError:
		return FormatError(*this);

	case ErrorLevel::Error:
	case ErrorLevel::Warning:
		return FormatLineError(*this);
	}

	return std::string();
}
