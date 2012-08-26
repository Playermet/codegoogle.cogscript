#ifndef _COG_COMPILER_H_INCLUDED_
#define _COG_COMPILER_H_INCLUDED_

#include "v_table.h"
#include "vm_value.h"
#include "cog_script.h"
#include "err_report.h"
#include <iosfwd>
#include <string>
#include <unordered_map>

namespace Cog
{
	class Compiler
	{
	private:
		Verbs::VerbTable& VerbTable;
		std::unordered_map<std::string, Cog::VirtualMachine::Value> ConstantTable;
		std::unordered_map<std::string, Cog::MessageId::Enum> MessageTable;

	public:
		Compiler(Verbs::VerbTable& verbTable);

		void Compile(Cog::Script& output, const std::string& filename, std::istream& fileStream, Error::Report& errorReport);
	};
}

#endif // _COG_COMPILER_H_INCLUDED_
