#ifndef _AST_OP_H_INCLUDED_
#define _AST_OP_H_INCLUDED_

namespace Cog
{
	namespace AST
	{
		namespace UnaryOperator
		{
			enum Enum
			{
				Plus,
				Minus,
				Not
			};
		}

		namespace InfixOperator
		{
			enum Enum
			{
				Addition,
				Subtraction,
				Multiplication,
				Division,
				Modulo,

				Greater,
				GreaterEqual,
				Less,
				LessEqual,
				Equal,
				NotEqual,

				And,
				Or,
				Xor,

				LogicalAnd,
				LogicalOr
			};
		}
	}
}

#endif // _AST_OP_H_INCLUDED_
