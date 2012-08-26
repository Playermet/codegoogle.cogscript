#ifndef _VM_TYPE_H_INCLUDED_
#define _VM_TYPE_H_INCLUDED_

namespace Cog
{
	namespace VirtualMachine
	{
		namespace Type
		{
			enum Enum : unsigned char
			{
				Void,
				Integer,
				Float,
				Boolean,
				String,
				Vector
			};
		}
	}
}

#endif // _VM_TYPE_H_INCLUDED_
