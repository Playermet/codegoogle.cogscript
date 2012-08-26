#ifndef _ERR_ERROR_H_INCLUDED_
#define _ERR_ERROR_H_INCLUDED_

#include "err_code.h"
#include "err_level.h"
#include "err_location.h"

#include <string>
#include <iosfwd>

namespace Cog
{
	namespace Error
	{
		class Error
		{
		public:
			const ErrorCode::Enum Code;
			const ErrorLevel::Enum Level;
			const std::string Stage;
			const std::string Filename;
			const std::string Reason;
			const Error::Location ErrorLocation;

			Error(ErrorCode::Enum errorCode, ErrorLevel::Enum errorLevel,
				const std::string& stage, const std::string& filename,
				const std::string& reason, const Error::Location& errorLocation);

			operator std::string() const;
		};
	}
}

#endif // _ERR_ERROR_H_INCLUDED_
