#include "vm_codebufferwritestream.h"

Cog::VirtualMachine::CodeBufferWriteStream::CodeBufferWriteStream(CodeBuffer& cBuffer)
	: codeBuffer(cBuffer), streamPtr(0)
{
	return;
}
