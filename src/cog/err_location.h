#ifndef _TXT_LOCATION_H_INCLUDED_
#define _TXT_LOCATION_H_INCLUDED_

namespace Cog
{
	namespace Error
	{
		class Location
		{
		public:
			unsigned int first_line, first_col, last_line, last_col;

			Location();
			Location(unsigned int first_line, unsigned int first_col,
				unsigned int last_line, unsigned int last_col);
		};
	}
}

#endif // _TXT_LOCATION_H_INCLUDED_
