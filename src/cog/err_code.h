#ifndef _ERR_CODE_H_INCLUDED_
#define _ERR_CODE_H_INCLUDED_

namespace Cog
{
	namespace Error
	{
		namespace ErrorCode
		{
			enum Enum
			{
				// Compiler internal errors
				Internal =						1000,
				FeatureNotImplemented =			1001,

				// Tokenizer errors
				UnrecognizedInput =				2000,
				EofInStringLiteral =			2001,
				UnknownEscapeSequence =			2002,
				UnescapedNewlineInString =		2003,

				// Syntax errors
				SyntaxError =					3000,

				// Semantic errors
				UnknownType =					4000,
				IllegalAssignment =				4001,
				TypeMismatch =					4002,
				UnknownExtension =				4003,
				IllegalExtensionAssignment =	4004,
				ExtensionTypeMismatch =			4005,
				SymbolRedefinition =			4006,
				ExtensionRedefinition =			4007,
				ExtensionValueMissing =			4008,
				IllegalExtension =				4009,
				BreakOutsideLoop =				4010,
				LabelInsideBlock =				4011,
				UnknownVerb =					4012,
				InvalidArgumentCount =			4013,
				UndefinedSymbol =				4014,
				IllegalVoidResult =				4015,
				ResultNotBoolean =				4016,
				CallToUnusedLabel =				4017,
				LabelRedefinition =				4018,
				MissingExport =					4019,
				AssignToRValue =				4020,
				UndefinedArrayBase =			4021,

				// Other text asset errors
				FileCorrupt =					5000,
				ExpectedInteger =				5001,
				ExpectedDouble =				5002,
				ExpectedPunctuator =			5003,
				ExpectedIdentifier =			5004,
				ExpectedFilename =				5005,
				ExpectedString =				5006,
				ExpectedLabel =					5007,
				UnexpectedEndOfFileInString =	5008
			};
		}
	}
}

#endif // _ERR_CODE_H_INCLUDED_
