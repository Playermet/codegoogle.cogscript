#ifndef _S2_LABEL_VISITOR_H_INCLUDED_
#define _S2_LABEL_VISITOR_H_INCLUDED_

#include "ast_visitor.h"
#include "sym_table.h"

#include <string>
#include <unordered_set>

namespace Cog
{
	namespace Stages
	{
		namespace Stage2
		{
			class LabelVisitor : public AST::Visitor
			{
			protected:
				std::unordered_set<std::string>& SeenLabels;

			public:
				LabelVisitor(std::unordered_set<std::string>& SeenLabels, Error::Report& report);

			private:
				ASTCLASS_STATEMENT(AVPROTO);
			};
		}
	}
}

#endif // _S2_LABEL_VISITOR_H_INCLUDED_
