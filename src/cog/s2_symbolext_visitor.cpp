#include "s2_symbolext_visitor.h"
#include <algorithm>
#include <boost/format.hpp>
#include "err_helper.h"
#include "s2_symbolfield_visitor.h"
#include "cog_constants.h"

using namespace Cog::AST;
using Cog::Stages::Stage2::SymbolExtensionVisitor;

SymbolExtensionVisitor::SymbolExtensionVisitor(Cog::Symbols::Type::Enum type, Cog::Error::Report& report)
	: AST::Visitor("Stage2::SymbolExtensionVisitor", report), SymbolType(type)
{
	// Set sensible default extensions.
	local = false;

	linkid_defined = false;
	linkid = Cog::Constants::DefaultLinkId;

	nolink = false;

	mask_defined = false;

	switch(SymbolType)
	{
	default:
		mask = Cog::Constants::DefaultMask;
		break;

	case Symbols::Type::Sector:
		mask = Cog::Constants::DefaultSectorMask;
		break;

	case Symbols::Type::Surface:
		mask = Cog::Constants::DefaultSurfaceMask;
		break;

	case Symbols::Type::Thing:
		mask = Cog::Constants::DefaultThingMask;
		break;
	}

	return;
}

bool SymbolExtensionVisitor::ValidateExtension(const std::string& name, const std::string& filename,
	Cog::Error::Location& location)
{
	if(name == "local")
	{
		if(local)
		{
			Error::Helper::ExtensionRedefinition(ErrorReport, VisitorName, name, filename, location);
		}

		switch(SymbolType)
		{
		case Symbols::Type::Message:
			Error::Helper::IllegalExtension(ErrorReport, VisitorName, name, filename, location);
			break;

		default:
			break;
		}
	}
	else if(name == "linkid")
	{
		if(linkid_defined)
		{
			Error::Helper::ExtensionRedefinition(ErrorReport, VisitorName, name, filename, location);
		}

		switch(SymbolType)
		{
		case Symbols::Type::Sector:
		case Symbols::Type::Surface:
		case Symbols::Type::Thing:
			break;

		default:
			Error::Helper::IllegalExtension(ErrorReport, VisitorName, name, filename, location);
		}
	}
	else if(name == "nolink")
	{
		if(nolink)
		{
			Error::Helper::ExtensionRedefinition(ErrorReport, VisitorName, name, filename, location);
		}

		switch(SymbolType)
		{
		case Symbols::Type::Cog:
		case Symbols::Type::Sector:
		case Symbols::Type::Surface:
		case Symbols::Type::Thing:
			break;

		default:
			Error::Helper::IllegalExtension(ErrorReport, VisitorName, name, filename, location);
		}
	}
	else if(name == "desc")
	{
		if(!desc.empty())
		{
			Error::Helper::ExtensionRedefinition(ErrorReport, VisitorName, name, filename, location);
		}

		switch(SymbolType)
		{
		case Symbols::Type::Message:
			Error::Helper::IllegalExtension(ErrorReport, VisitorName, name, filename, location);
			break;

		default:
			break;
		}
	}
	else if(name == "mask")
	{
		if(mask_defined)
		{
			Error::Helper::ExtensionRedefinition(ErrorReport, VisitorName, name, filename, location);
		}

		switch(SymbolType)
		{
		case Symbols::Type::Sector:
		case Symbols::Type::Surface:
		case Symbols::Type::Thing:
			break;

		default:
			Error::Helper::IllegalExtension(ErrorReport, VisitorName, name, filename, location);
		}
	}
	else
	{
		Error::Helper::UnknownExtension(ErrorReport, VisitorName, name, filename, location);
		return false;
	}

	return true;
}

void SymbolExtensionVisitor::VisitBareExtension(BareExtension& ext)
{
	std::transform(ext.Name.begin(), ext.Name.end(), ext.Name.begin(), tolower);

	if(!ValidateExtension(ext.Name, *ext.Filename, ext.Location))
	{
		return;
	}

	if(ext.Name == "linkid" || ext.Name == "desc" || ext.Name == "mask")
	{
		Error::Helper::ExtensionValueMissing(ErrorReport, VisitorName, ext.Name, *ext.Filename, ext.Location);
		return;
	}
	else if(ext.Name == "local")
	{
		local = true;
	}
	else if(ext.Name == "nolink")
	{
		nolink = true;
	}
}

void SymbolExtensionVisitor::VisitValuedExtension(ValuedExtension& ext)
{
	std::transform(ext.Name.begin(), ext.Name.end(), ext.Name.begin(), tolower);

	if(!ValidateExtension(ext.Name, *ext.Filename, ext.Location))
	{
		return;
	}

	SymbolFieldVisitor v(ErrorReport);
	ext.Value->Accept(v);

	if(ext.Name == "local" || ext.Name == "nolink")
	{
		Error::Helper::IllegalExtensionAssignment(ErrorReport, VisitorName, ext.Name, *ext.Filename, ext.Location);
		return;
	}
	else if(ext.Name == "linkid")
	{
		if(v.is_int)
		{
			linkid = v.int_value;
		}
		else
		{
			Error::Helper::ExtensionTypeMismatch(ErrorReport, VisitorName, ext.Name, *ext.Filename, ext.Location);
		}

		linkid_defined = true;
	}
	else if(ext.Name == "desc")
	{
		if(v.is_int)
		{
			desc = boost::str(boost::format("%d") % v.int_value);
		}
		else if(v.is_float)
		{
			desc = boost::str(boost::format("%f") % v.float_value);
		}
		else if(v.is_str)
		{
			desc = v.str_value;
		}
		else
		{
			Error::Helper::ExtensionTypeMismatch(ErrorReport, VisitorName, ext.Name, *ext.Filename, ext.Location);
		}
	}
	else if(ext.Name == "mask")
	{
		if(v.is_int)
		{
			mask = v.int_value;
		}
		else
		{
			Error::Helper::ExtensionTypeMismatch(ErrorReport, VisitorName, ext.Name, *ext.Filename, ext.Location);
		}

		mask_defined = true;
	}
}
