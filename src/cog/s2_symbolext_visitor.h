#ifndef _S2_SYMBOLEXT_VISITOR_H_INCLUDED_
#define _S2_SYMBOLEXT_VISITOR_H_INCLUDED_

#include "ast_visitor.h"
#include "vm_value.h"
#include "sym_type.h"

namespace Cog
{
	namespace Stages
	{
		namespace Stage2
		{
			class SymbolExtensionVisitor : public AST::Visitor
			{
			public:
				bool local;

				bool linkid_defined;
				int linkid;

				bool nolink;

				std::string desc;

				bool mask_defined;
				int mask;

				SymbolExtensionVisitor(Symbols::Type::Enum type, Error::Report& report);

			private:
				Symbols::Type::Enum SymbolType;

				ASTCLASS_SYMBOL_EXTENSION(AVPROTO);

				bool ValidateExtension(const std::string& name, const std::string& filename,
					Error::Location& location);
			};
		}
	}
}

#endif // _S2_SYMBOLEXT_VISITOR_H_INCLUDED_
