#ifndef _V_VERBID_H_INCLUDED_
#define _V_VERBID_H_INCLUDED_

namespace Cog
{
	namespace Verbs
	{
		class VerbTable;

		class VerbId
		{
			friend class VerbTable;

		private:
			size_t id;

		public:
			VerbId(size_t id);
		};
	}
}

#endif // _V_VERBID_H_INCLUDED_
