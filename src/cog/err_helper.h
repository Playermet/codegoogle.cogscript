#ifndef _COG_ERRORHELPER_H_INCLUDED_
#define _COG_ERRORHELPER_H_INCLUDED_

#include "err_report.h"

namespace Cog
{
	namespace Error
	{
		namespace Helper
		{
			// Compiler internal errors
			void FeatureNotImplemented(Error::Report& report, const std::string& visitorname, const std::string& action);

			// Lexical errors
			void UnrecognizedInput(Error::Report& report, const std::string& input, const std::string& filename, const Location& location);
			void EofInStringLiteral(Error::Report& Report, const std::string& filename, const Location& location);
			void UnknownEscapeSequence(Error::Report& report, const std::string& sequence, const std::string& filename, const Location& location);
			void UnescapedNewlineInString(Error::Report& report, const std::string& filename, const Location& location);

			// Semantic errors
			void UnknownType(Error::Report& report, const std::string& visitorname, const std::string& type, const std::string& filename, const Location& location);
			void IllegalAssignment(Error::Report& report, const std::string& visitorname, const std::string& filename, const Location& location);
			void TypeMismatch(Error::Report& report, const std::string& visitorname, const std::string& filename, const Location& location);
			void UnknownExtension(Error::Report& report, const std::string& visitorname, const std::string& extension, const std::string& filename, const Location& location);
			void IllegalExtensionAssignment(Error::Report& report, const std::string& visitorname, const std::string& extension, const std::string& filename, const Location& location);
			void ExtensionTypeMismatch(Error::Report& report, const std::string& visitorname, const std::string& extension, const std::string& filename, const Location& location);
			void SymbolRedefinition(Error::Report& report, const std::string& visitorname, const std::string& name, const std::string& filename, const Location& location);
			void ExtensionRedefinition(Error::Report& report, const std::string& visitorname, const std::string& extension, const std::string& filename, const Location& location);
			void ExtensionValueMissing(Error::Report& report, const std::string& visitorname, const std::string& extension, const std::string& filename, const Location& location);
			void IllegalExtension(Error::Report& Report, const std::string& visitorname, const std::string& extension, const std::string& filename, const Location& location);
			void BreakOutsideLoop(Error::Report& Report, const std::string& visitorname, const std::string& filename, const Location& location);
			void LabelInsideBlock(Error::Report& Report, const std::string& visitorname, const std::string& labelname, const std::string& filename, const Location& location);
			void UnknownVerb(Error::Report& Report, const std::string& visitorname, const std::string& verbname, const std::string& filename, const Location& location);
			void InvalidArgumentCount(Error::Report& Report, const std::string& visitorname, const std::string& verbname, int wanted, int found, const std::string& filename, const Location& location);
			void UndefinedSymbol(Error::Report& Report, const std::string& visitorname, const std::string& symbolname, const std::string& filename, const Location& location);
			void IllegalVoidResult(Error::Report& Report, const std::string& visitorname, const std::string& filename, const Location& location);
			void ResultNotBoolean(Error::Report& Report, const std::string& visitorname, const std::string& filename, const Location& location);
			void CallToUnusedLabel(Error::Report& Report, const std::string& visitorname, const std::string& labelname, const std::string& filename, const Location& location);
			void LabelRedefinition(Error::Report& Report, const std::string& visitorname, const std::string& labelname, const std::string& filename, const Location& location);
			void MissingExport(Error::Report& Report, const std::string& visitorname, const std::string& labelname, const std::string& filename, const Location& location);
			void AssignToRValue(Error::Report& Report, const std::string& visitorname, const std::string& filename, const Location& location);
			void UndefinedArrayBase(Error::Report& Report, const std::string& visitorname, const std::string& symbolname, const std::string& filename, const Location& location);
		}
	}
}

#endif // _COG_ERRORHELPER_H_INCLUDED_
