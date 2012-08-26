#include "err_location.h"

Cog::Error::Location::Location()
	: first_line(1), first_col(1), last_line(1), last_col(1)
{
	return;
}

Cog::Error::Location::Location(unsigned int firstline,
	unsigned int firstcol, unsigned int lastline, unsigned int lastcol)
	: first_line(firstline), first_col(firstcol), last_line(lastline), last_col(lastcol)
{
	return;
}
