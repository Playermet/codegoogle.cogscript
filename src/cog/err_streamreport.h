#ifndef _ERR_STREAMREPORT_H_INCLUDED_
#define _ERR_STREAMREPORT_H_INCLUDED_

#include "err_report.h"

#include <iostream>

namespace Cog
{
	namespace Error
	{
		class StreamReport : public Report
		{
		private:
			unsigned int errorCount, warningCount;
			std::ostream& stream;

			void PrintFormattedError(ErrorCode::Enum errorCode,
				const std::string& errorLevel,
				const std::string& stage,
				const std::string& reason);

			void PrintLineFormattedError(ErrorCode::Enum errorCode,
				const std::string& errorLevel,
				const std::string& stage,
				const std::string& filename,
				const std::string& reason,
				const Error::Location& errorLocation);

		public:
			StreamReport(std::ostream& stream);

			void AddError(ErrorCode::Enum errorCode,
				const std::string& stage,
				const std::string& filename,
				const std::string& reason,
				const Error::Location& errorLocation);

			void AddWarning(ErrorCode::Enum errorCode,
				const std::string& stage,
				const std::string& filename,
				const std::string& reason,
				const Error::Location& errorLocation);

			void AddCriticalError(ErrorCode::Enum errorCode,
				const std::string& stage,
				const std::string& reason);

			unsigned int GetErrorCount();
			unsigned int GetWarningCount();
		};
	}
}

#endif // _ERR_STREAMREPORT_H_INCLUDED_
