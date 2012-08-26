#ifndef _ERR_STOREDREPORT_H_INCLUDED_
#define _ERR_STOREDREPORT_H_INCLUDED_

#include "err_report.h"
#include "err_error.h"
#include "err_location.h"

#include <iostream>
#include <vector>

namespace Cog
{
	namespace Error
	{
		class StoredReport : public Report
		{
		private:
			std::vector<Error> container;
			unsigned int errorCount, warningCount;

		public:
			StoredReport();

			void AddError(ErrorCode::Enum errorCode,
				const std::string& stage,
				const std::string& filename,
				const std::string& reason,
				const Location& errorLocation);

			void AddWarning(ErrorCode::Enum errorCode,
				const std::string& stage,
				const std::string& filename,
				const std::string& reason,
				const Location& errorLocation);

			void AddCriticalError(ErrorCode::Enum errorCode,
				const std::string& stage,
				const std::string& reason);

			unsigned int GetErrorCount();
			unsigned int GetWarningCount();

			std::vector<Error>::const_iterator ErrorBegin() const;
			std::vector<Error>::const_iterator ErrorEnd() const;

			void Repeat(Report& report) const;
		};
	}
}

#endif // _ERR_STOREDREPORT_H_INCLUDED_
