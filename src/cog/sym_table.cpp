#include "sym_table.h"
#include "sym_exception.h"

using namespace Cog::Symbols;

SymbolTable::~SymbolTable()
{
	for(auto it = strings.begin(); it != strings.end(); ++it)
	{
		free((void*)(*it));
	}
}

void SymbolTable::AddSymbol(Type::Enum type, const std::string& name,
	const Cog::VirtualMachine::Value& defaultValue,
	bool local, const std::string& desc, int mask, int linkid, bool nolink)
{
	if(IsSymbolDefined(name))
	{
		throw SymbolRedefinitionException();
	}

	ReplaceSymbol(type, name, defaultValue, local, desc, mask, linkid, nolink);
}

void SymbolTable::AddSymbol(Type::Enum type, const std::string& name,
	bool local, const std::string& desc, int mask, int linkid, bool nolink)
{
	if(IsSymbolDefined(name))
	{
		throw SymbolRedefinitionException();
	}

	ReplaceSymbol(type, name, local, desc, mask, linkid, nolink);
}

void SymbolTable::AddSymbol(const std::string& name)
{
	if(IsSymbolDefined(name))
	{
		throw SymbolRedefinitionException();
	}

	ReplaceSymbol(name);
}

void SymbolTable::ReplaceSymbol(Type::Enum type, const std::string& name,
	const Cog::VirtualMachine::Value& defaultValue,
	bool local, const std::string& desc, int mask, int linkid, bool nolink)
{
	size_t index = symbols.size();
	symbols.push_back(Symbol(type, name, defaultValue, local, desc, mask, linkid, nolink));
	symbolMap.insert(std::make_pair(name, index));
}

void SymbolTable::ReplaceSymbol(Type::Enum type, const std::string& name,
	bool local, const std::string& desc, int mask, int linkid, bool nolink)
{
	// Generate default value
	VirtualMachine::Value defaultValue(0);

	switch(type)
	{
	case Symbols::Type::Flex:
		defaultValue = VirtualMachine::Value(-1.0f);
		break;

	case Symbols::Type::Float:
		defaultValue = VirtualMachine::Value(-1.0f);
		break;

	case Symbols::Type::Int:
		defaultValue = VirtualMachine::Value(-1);
		break;

	case Symbols::Type::String:
		defaultValue = VirtualMachine::Value("");
		break;

	case Symbols::Type::Vector:
		defaultValue = VirtualMachine::Value(Generics::Vector<float>());
		break;
	}

	ReplaceSymbol(type, name, defaultValue, local, desc, mask, linkid, nolink);
}

void SymbolTable::ReplaceSymbol(const std::string& name)
{
	ReplaceSymbol(Type::Int, name, true, "", 0, 0, true);
}

const Symbol& SymbolTable::GetSymbol(size_t index) const
{
	if(index >= 0 && index < symbols.size())
	{
		return symbols[index];
	}
	else
	{
		throw UndefinedSymbolException();
	}
}

const Symbol& SymbolTable::GetSymbol(const std::string& name) const
{
	auto it = symbolMap.find(name);
	if(it != symbolMap.end())
	{
		return GetSymbol(it->second);
	}
	else
	{
		throw UndefinedSymbolException();
	}
}

bool SymbolTable::IsSymbolDefined(size_t index) const
{
	return index >= 0 && index < symbols.size();
}

bool SymbolTable::IsSymbolDefined(const std::string& name) const
{
	auto it = symbolMap.find(name);
	return it != symbolMap.end();
}

const char* SymbolTable::AddString(const std::string& str)
{
	const char* newstr = _strdup(str.c_str());
	strings.push_back(newstr);

	return newstr;
}

size_t SymbolTable::GetSymbolIndex(const std::string& name) const
{
	auto it = symbolMap.find(name);
	if(it != symbolMap.end())
	{
		return it->second;
	}
	else
	{
		throw UndefinedSymbolException();
	}
}
