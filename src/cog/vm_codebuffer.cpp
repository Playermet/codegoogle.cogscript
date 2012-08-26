#include "vm_codebuffer.h"
#include "vm_exception.h"

Cog::VirtualMachine::CodeBuffer::CodeBuffer()
	: data(128, 0), topPtr(0)
{
	return;
}

void Cog::VirtualMachine::CodeBuffer::throwCodeBufferOverflowException() const
{
	throw CodeBufferOverflowException();
}

void Cog::VirtualMachine::CodeBuffer::Write(size_t dest, const void* src, size_t size)
{
	resizeDataForWrite(dest, size);
	memcpy(&data[dest], src, size);
}

void Cog::VirtualMachine::CodeBuffer::Read(void* dest, size_t src, size_t size) const
{
	tryRead(src, size);
	memcpy(dest, &data[src], size);
}
