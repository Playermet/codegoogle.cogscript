#include "s2_symbol_visitor.h"
#include "s2_symbolfield_visitor.h"
#include "s2_symbolext_visitor.h"
#include "err_helper.h"

#include <algorithm>
#include <boost/format.hpp>

using namespace Cog::AST;
using Cog::Stages::Stage2::SymbolVisitor;

SymbolVisitor::SymbolVisitor(Cog::Symbols::SymbolTable& symbolTable,
	const std::unordered_set<std::string>& SeenLabels, Cog::Error::Report& report)
	: AST::Visitor("Stage2::SymbolVisitor", report), SeenLabels(SeenLabels), SymbolTable(symbolTable)
{
	return;
}

void SymbolVisitor::VisitSymbol(Symbol& symbol)
{
	Symbols::Type::Enum type = GetType(symbol);

	// Convert symbol name to lowercase for processing.
	std::transform(symbol.Name.begin(), symbol.Name.end(), symbol.Name.begin(), tolower);

	// Visit extension
	SymbolExtensionVisitor w(type, ErrorReport);
	for(auto it = symbol.Extensions->begin(); it != symbol.Extensions->end(); ++it)
	{
		(*it)->Accept(w);
	}

	if(SymbolTable.IsSymbolDefined(symbol.Name))
	{
		Error::Helper::SymbolRedefinition(ErrorReport, VisitorName, symbol.Name, *symbol.Filename, symbol.Location);
		SymbolTable.ReplaceSymbol(type, symbol.Name, w.local, w.desc, w.mask, w.linkid, w.nolink);
	}
	else
	{
		SymbolTable.AddSymbol(type, symbol.Name, w.local, w.desc, w.mask, w.linkid, w.nolink);

		if(type == Symbols::Type::Message)
		{
			if(SeenLabels.find(symbol.Name) == SeenLabels.end())
			{
				Error::Helper::MissingExport(ErrorReport, VisitorName, symbol.Name, *symbol.Filename, symbol.Location);
			}
		}
	}
}

void SymbolVisitor::VisitValuedSymbol(ValuedSymbol& symbol)
{
	SymbolFieldVisitor v(ErrorReport);
	symbol.Value->Accept(v);

	Symbols::Type::Enum type = GetType(symbol);

	VirtualMachine::Value defaultValue(0);

	switch(type)
	{
	case Symbols::Type::Flex:
	case Symbols::Type::Float:
		if(!v.is_numeric)
		{
			Error::Helper::TypeMismatch(ErrorReport, VisitorName, *symbol.Filename, symbol.Location);
		}
		else
		{
			defaultValue = VirtualMachine::Value(v.float_value);
		}
		break;

	case Symbols::Type::Int:
		if(!v.is_numeric)
		{
			Error::Helper::TypeMismatch(ErrorReport, VisitorName, *symbol.Filename, symbol.Location);
		}
		else
		{
			defaultValue = VirtualMachine::Value(v.int_value);
		}
		break;
	
	case Symbols::Type::Ai:
	case Symbols::Type::Keyframe:
	case Symbols::Type::Material:
	case Symbols::Type::Model:
	case Symbols::Type::Sound:
	case Symbols::Type::Template:
		if(!v.is_str)
		{
			Error::Helper::TypeMismatch(ErrorReport, VisitorName, *symbol.Filename, symbol.Location);
		}
		else
		{
			defaultValue = VirtualMachine::Value(SymbolTable.AddString(v.str_value));
		}
		break;

	default:
	case Symbols::Type::Cog:
	case Symbols::Type::Message:
	case Symbols::Type::Sector:
	case Symbols::Type::String:
	case Symbols::Type::Surface:
	case Symbols::Type::Thing:
	case Symbols::Type::Vector:
		Error::Helper::IllegalAssignment(ErrorReport, VisitorName, *symbol.Filename, symbol.Location);
		break;
	}

	// Convert symbol name to lowercase for processing.
	std::transform(symbol.Name.begin(), symbol.Name.end(), symbol.Name.begin(), tolower);

	// Visit extension
	SymbolExtensionVisitor w(type, ErrorReport);
	for(auto it = symbol.Extensions->begin(); it != symbol.Extensions->end(); ++it)
	{
		(*it)->Accept(w);
	}

	if(SymbolTable.IsSymbolDefined(symbol.Name))
	{
		Error::Helper::SymbolRedefinition(ErrorReport, VisitorName, symbol.Name, *symbol.Filename, symbol.Location);
		SymbolTable.ReplaceSymbol(type, symbol.Name, defaultValue, w.local, w.desc, w.mask, w.linkid, w.nolink);
	}
	else
	{
		SymbolTable.AddSymbol(type, symbol.Name, defaultValue, w.local, w.desc, w.mask, w.linkid, w.nolink);
	}
}

Cog::Symbols::Type::Enum SymbolVisitor::GetType(Symbol& symbol)
{
	// Convert symbol type to lowercase for processing.
	std::transform(symbol.Type.begin(), symbol.Type.end(), symbol.Type.begin(), tolower);

	if(symbol.Type == "ai")
	{
		return Symbols::Type::Ai;
	}
	else if(symbol.Type == "cog")
	{
		return Symbols::Type::Cog;
	}
	else if(symbol.Type == "flex")
	{
		return Symbols::Type::Flex;
	}
	else if(symbol.Type == "float")
	{
		return Symbols::Type::Float;
	}
	else if(symbol.Type == "int")
	{
		return Symbols::Type::Int;
	}
	else if(symbol.Type == "keyframe")
	{
		return Symbols::Type::Keyframe;
	}
	else if(symbol.Type == "material")
	{
		return Symbols::Type::Material;
	}
	else if(symbol.Type == "message")
	{
		return Symbols::Type::Message;
	}
	else if(symbol.Type == "model")
	{
		return Symbols::Type::Model;
	}
	else if(symbol.Type == "sector")
	{
		return Symbols::Type::Sector;
	}
	else if(symbol.Type == "sound")
	{
		return Symbols::Type::Sound;
	}
	else if(symbol.Type == "string")
	{
		return Symbols::Type::String;
	}
	else if(symbol.Type == "surface")
	{
		return Symbols::Type::Surface;
	}
	else if(symbol.Type == "template")
	{
		return Symbols::Type::Template;
	}
	else if(symbol.Type == "thing")
	{
		return Symbols::Type::Thing;
	}
	else if(symbol.Type == "vector")
	{
		return Symbols::Type::Vector;
	}
	else
	{
		Error::Helper::UnknownType(ErrorReport, VisitorName, symbol.Type, *symbol.Filename, symbol.Location);

		return Symbols::Type::Int;
	}
}
