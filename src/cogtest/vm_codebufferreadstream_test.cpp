#include <nullunit/nullunit.h>
#include "cog/vm_codebufferreadstream.h"
#include "cog/vm_codebufferwritestream.h"

BeginSuite(CodeBufferReadStreamTests);

Case(Seek)
{
	Cog::VirtualMachine::CodeBuffer cBuffer;
	Cog::VirtualMachine::CodeBufferReadStream cb(cBuffer);

	cb.Seek(128);
	Test_Assert_Eq(cb.Tell(), 128);
}

Case(ReadStream)
{
	Cog::VirtualMachine::CodeBuffer cBuffer;
	Cog::VirtualMachine::CodeBufferWriteStream cb(cBuffer);
	Cog::VirtualMachine::CodeBufferReadStream db(cBuffer);

	int value = 0xFEEDBEEF;

	cb.Write(&value, sizeof(int));

	int readValue = 0;

	db.Read(&readValue, sizeof(int));

	Test_Assert_Eq(readValue, 0xFEEDBEEF);
}

Case(ReadStreamTemplated)
{
	Cog::VirtualMachine::CodeBuffer cBuffer;
	Cog::VirtualMachine::CodeBufferWriteStream cb(cBuffer);
	Cog::VirtualMachine::CodeBufferReadStream db(cBuffer);

	cb.Write<int>(0xFEEDBEEF);
	cb.Write<int>(0xABACADAB);
	cb.Write<int>(0xF0F0F0F0);

	Test_Assert_Eq(db.Read<int>(), 0xFEEDBEEF);
	Test_Assert_Eq(db.Read<int>(), 0xABACADAB);
	Test_Assert_Eq(db.Read<int>(), 0xF0F0F0F0);
}

EndSuite(CodeBufferReadStreamTests);