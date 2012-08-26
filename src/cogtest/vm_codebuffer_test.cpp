#include <nullunit/nullunit.h>
#include "cog/vm_codebuffer.h"
#include "cog/vm_exception.h"

#include <string>

BeginSuite(CodeBufferTests);

Case(Write)
{
	Cog::VirtualMachine::CodeBuffer cb;

	std::string hello = "Hello, World!\n";

	cb.Write(0, hello.c_str(), static_cast<size_t>(hello.length()));
	cb.Write(96, hello.c_str(), static_cast<size_t>(hello.length()));
}

Case(WriteTemplated)
{
	Cog::VirtualMachine::CodeBuffer cb;
	cb.Write<int>(0xFEEDBEEF, 5);
}

Case(Read)
{
	Cog::VirtualMachine::CodeBuffer cb;

	int value = 0xFEEDBEEF;

	cb.Write(0, &value, sizeof(int));

	int readValue = 0;

	cb.Read(&readValue, 0, sizeof(int));

	Test_Assert_Eq(readValue, 0xFEEDBEEF);
}

Case(ReadFailure)
{
	Cog::VirtualMachine::CodeBuffer cb;

	int value = 0xFEEDBEEF;

	cb.Write(0, &value, sizeof(int));

	try
	{
		int readValue = 0;
		cb.Read(&readValue, 2, sizeof(int));
	}
	catch(Cog::VirtualMachine::CodeBufferOverflowException&)
	{
		return;
	}

	Test_Assert_Always("Code buffer overflow exception not thrown.");
}

Case(ReadTemplated)
{
	Cog::VirtualMachine::CodeBuffer cb;
	cb.Write<int>(0xFEEDBEEF, 5);
	Test_Assert_Eq(cb.Read<int>(5), 0xFEEDBEEF);
}

Case(ReadTemplatedFailure)
{
	Cog::VirtualMachine::CodeBuffer cb;
	cb.Write<int>(0xFEEDBEEF, 4);
	try
	{
		cb.Read<int>(5);
	}
	catch(Cog::VirtualMachine::CodeBufferOverflowException&)
	{
		return;
	}

	Test_Assert_Always("Code buffer overflow exception not thrown.");
}

Case(ReadPointer)
{
	Cog::VirtualMachine::CodeBuffer cb;
	cb.Write<int>(0xFEEDBEEF, 0);
	const void* rp = cb.ReadPointer(0, sizeof(int));

	int readValue = 0;
	memcpy(&readValue, rp, sizeof(int));

	Test_Assert_Eq(readValue, 0xFEEDBEEF);
}

Case(WritePointer)
{
	Cog::VirtualMachine::CodeBuffer cb;
	void* wp = cb.WritePointer(0, sizeof(int));

	int writeValue = 0xFEEDBEEF;
	memcpy(wp, &writeValue, sizeof(int));

	Test_Assert_Eq(cb.Read<int>(0), 0xFEEDBEEF);
}

Case(Size)
{
	Cog::VirtualMachine::CodeBuffer cb;
	cb.Write<int>(0xFEEDBEEF, 0);
	cb.Write<int>(0xDEADBEEF, sizeof(int));
	cb.Write<int>(0xFEEDDEAD, sizeof(int) * 2);

	Test_Assert_Eq(cb.Size(), sizeof(int) * 3);
}

EndSuite(CodeBufferTests);
