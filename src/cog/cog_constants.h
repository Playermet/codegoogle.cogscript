#ifndef _COG_CONSTANTS_H_INCLUDED_
#define _COG_CONSTANTS_H_INCLUDED_

namespace Cog
{
	namespace Constants
	{
		const int DefaultInt = -1;
		const float DefaultFloat = 0.0f;
		extern const char* DefaultString;

		const int DefaultLinkId = 0xFFFFFFFF;

		const int DefaultMask = 0xFFFFFFFF;
		const int DefaultSectorMask = 0x400;
		const int DefaultSurfaceMask = 0x400;
		const int DefaultThingMask = 0x404;
	}
}

#endif // _COG_CONSTANTS_H_INCLUDED_
