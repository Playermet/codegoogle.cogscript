#include "vm_codebufferreadstream.h"

Cog::VirtualMachine::CodeBufferReadStream::CodeBufferReadStream(const CodeBuffer& cBuffer)
	: codeBuffer(cBuffer), streamPtr(0)
{
	return;
}
