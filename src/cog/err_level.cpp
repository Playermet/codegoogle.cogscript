#include "err_level.h"

const char* Cog::Error::ErrorLevel::ToString(Enum value)
{
	switch(value)
	{
	case Warning:
		return "warning";

	case Error:
		return "error";

	case CriticalError:
		return "critical error";
	}

	return nullptr;
}
