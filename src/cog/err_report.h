#ifndef _ERR_REPORT_H_INCLUDED_
#define _ERR_REPORT_H_INCLUDED_

#include "err_code.h"
#include "err_location.h"

#include <string>

namespace Cog
{
	namespace Error
	{
		class Report
		{
		public:
			virtual ~Report() { }

			virtual void AddError(ErrorCode::Enum errorCode,
				const std::string& stage,
				const std::string& filename,
				const std::string& reason,
				const Error::Location& errorLocation) = 0;

			virtual void AddWarning(ErrorCode::Enum errorCode,
				const std::string& stage,
				const std::string& filename,
				const std::string& reason,
				const Error::Location& errorLocation) = 0;

			virtual void AddCriticalError(ErrorCode::Enum errorCode,
				const std::string& stage,
				const std::string& reason) = 0;

			virtual unsigned int GetErrorCount() = 0;
			virtual unsigned int GetWarningCount() = 0;
		};
	}
}

#endif // _ERR_REPORT_H_INCLUDED_
