#include <nullunit/nullunit.h>
#include "cog/vm_codebufferwritestream.h"
#include "cog/vm_codebufferreadstream.h"

BeginSuite(CodeBufferWriteStreamTests);

Case(Seek)
{
	Cog::VirtualMachine::CodeBuffer cBuffer;
	Cog::VirtualMachine::CodeBufferWriteStream cb(cBuffer);

	cb.Seek(128);
	Test_Assert_Eq(cb.Tell(), 128);
}

Case(WriteStream)
{
	Cog::VirtualMachine::CodeBuffer cBuffer;
	Cog::VirtualMachine::CodeBufferWriteStream cb(cBuffer);

	std::string hello = "Hello, World!\n";

	cb.Write(hello.c_str(), static_cast<unsigned int>(hello.length()));
	cb.Write(hello.c_str(), static_cast<unsigned int>(hello.length()));
}

Case(WriteStreamTemplated)
{
	Cog::VirtualMachine::CodeBuffer cBuffer;
	Cog::VirtualMachine::CodeBufferWriteStream cb(cBuffer);

	cb.Write<int>(0xFEEDBEEF);
	cb.Write<int>(0xABACADAB);
	cb.Write<int>(0xF0F0F0F0);
}

Case(WriteBuffer)
{
	Cog::VirtualMachine::CodeBuffer cBufferOne;
	cBufferOne.Write<int>(0xFEEDBEEF, 0);

	Cog::VirtualMachine::CodeBuffer cBuffer;
	Cog::VirtualMachine::CodeBufferWriteStream cb(cBuffer);
	size_t destOffset = cb.WriteBuffer(cBufferOne);
	size_t destOffset2 = cb.WriteBuffer(cBufferOne);

	Test_Assert_Eq(cBuffer.Read<int>(0), 0xFEEDBEEF);
	Test_Assert_Eq(cBuffer.Read<int>(sizeof(int)), 0xFEEDBEEF);
	Test_Assert_Eq(destOffset, 0);
	Test_Assert_Eq(destOffset2, sizeof(int));
}

EndSuite(CodeBufferWriteStreamTests);