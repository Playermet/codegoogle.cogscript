#ifndef _S2_SYMBOLFIELD_VISITOR_H_INCLUDED_
#define _S2_SYMBOLFIELD_VISITOR_H_INCLUDED_

#include "ast_visitor.h"
#include <string>

namespace Cog
{
	namespace Stages
	{
		namespace Stage2
		{
			class SymbolFieldVisitor : public AST::Visitor
			{
			public:
				float float_value;
				bool is_float;

				int int_value;
				bool is_int;

				bool is_numeric;

				std::string str_value;
				bool is_str;

				SymbolFieldVisitor(Error::Report& report);

			private:
				ASTCLASS_SYMBOL_FIELD(AVPROTO);
			};
		}
	}
}

#endif // _S2_SYMBOLFIELD_VISITOR_H_INCLUDED_
