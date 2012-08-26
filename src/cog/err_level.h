#ifndef _ERR_LEVEL_H_INCLUDED_
#define _ERR_LEVEL_H_INCLUDED_

namespace Cog
{
	namespace Error
	{
		namespace ErrorLevel
		{
			enum Enum
			{
				Warning,
				Error,
				CriticalError
			};

			const char* ToString(Enum value);
		}
	}
}

#endif // _ERR_LEVEL_H_INCLUDED_
