#ifndef _VM_CODEBUFFERWRITESTREAM_H_INCLUDED_
#define _VM_CODEBUFFERWRITESTREAM_H_INCLUDED_

#include "vm_codebuffer.h"

namespace Cog
{
	namespace VirtualMachine
	{
		class CodeBufferWriteStream
		{
		private:
			CodeBuffer& codeBuffer;
			size_t streamPtr;

		public:
			explicit CodeBufferWriteStream(CodeBuffer& cb);

			inline void Write(const void* src, size_t size)
			{
				codeBuffer.Write(streamPtr, src, size);
				streamPtr += size;
			}

			template <typename T> inline void Write(T value)
			{
				codeBuffer.Write<T>(value, streamPtr);
				streamPtr += sizeof(T);
			}

			inline size_t WriteBuffer(CodeBuffer& cb)
			{
				size_t retVal = streamPtr;
				size_t size = cb.Size();

				codeBuffer.Write(streamPtr, cb.ReadPointer(0, size), size);
				streamPtr += size;

				return retVal;
			}

			inline void Seek(size_t dest)
			{
				streamPtr = dest;
			}

			inline size_t Tell() const
			{
				return streamPtr;
			}
		};
	}
}

#endif // _VM_CODEBUFFERWRITESTREAM_H_INCLUDED_
