#include "err_helper.h"
#include <boost/format.hpp>

namespace Cog
{
	namespace Error
	{
		namespace Helper
		{
			void FeatureNotImplemented(Error::Report& report, const std::string& visitorname, const std::string& action)
			{
				report.AddCriticalError(Error::ErrorCode::FeatureNotImplemented, visitorname,
					boost::str(boost::format("feature not implemented: %s") % action));
			}

			void UnrecognizedInput(Error::Report& report, const std::string& input, const std::string& filename, const Error::Location& location)
			{
				report.AddError(Error::ErrorCode::UnrecognizedInput, "Scanner", filename,
					boost::str(boost::format("illegal character \'%s\'") % input), location);
			}

			void EofInStringLiteral(Error::Report& report, const std::string& filename, const Error::Location& location)
			{
				report.AddError(Error::ErrorCode::EofInStringLiteral, "Scanner", filename,
					"unexpected end of file in string", location);
			}

			void UnknownEscapeSequence(Error::Report& report, const std::string& sequence, const std::string& filename, const Error::Location& location)
			{
				report.AddError(Error::ErrorCode::UnknownEscapeSequence, "Scanner", filename,
					boost::str(boost::format("unknown escape sequence \'\\%s\'") % sequence), location);
			}

			void UnescapedNewlineInString(Error::Report& report, const std::string& filename, const Error::Location& location)
			{
				report.AddError(Error::ErrorCode::UnescapedNewlineInString, "Scanner", filename,
					"unescaped newline in string", location);
			}

			void UnknownType(Error::Report& report, const std::string& visitorname, const std::string& type, const std::string& filename, const Error::Location& location)
			{
				report.AddError(Error::ErrorCode::UnknownType, visitorname, filename, boost::str(boost::format("unknown type \'%s\'") % type), location);
			}

			void IllegalAssignment(Error::Report& report, const std::string& visitorname, const std::string& filename, const Error::Location& location)
			{
				report.AddError(Error::ErrorCode::IllegalAssignment, visitorname, filename, "symbol does not accept a default value", location);
			}

			void TypeMismatch(Error::Report& report, const std::string& visitorname, const std::string& filename, const Error::Location& location)
			{
				report.AddError(Error::ErrorCode::TypeMismatch, visitorname, filename, "type mismatch", location);
			}

			void UnknownExtension(Error::Report& report, const std::string& visitorname, const std::string& extension, const std::string& filename, const Error::Location& location)
			{
				report.AddWarning(Error::ErrorCode::UnknownExtension, visitorname, filename,
					boost::str(boost::format("unknown extension \'%s\'") % extension), location);
			}

			void IllegalExtensionAssignment(Error::Report& report, const std::string& visitorname, const std::string& extension, const std::string& filename, const Error::Location& location)
			{
				report.AddError(Error::ErrorCode::IllegalExtensionAssignment, visitorname, filename,
					boost::str(boost::format("extension \'%s\' does not accept a value") % extension), location);
			}

			void ExtensionTypeMismatch(Error::Report& report, const std::string& visitorname, const std::string& extension, const std::string& filename, const Error::Location& location)
			{
				report.AddError(Error::ErrorCode::ExtensionTypeMismatch, visitorname, filename,
					boost::str(boost::format("extension \'%s\' value type mismatch") % extension), location);
			}

			void SymbolRedefinition(Error::Report& report, const std::string& visitorname, const std::string& name, const std::string& filename, const Error::Location& location)
			{
				report.AddWarning(Error::ErrorCode::SymbolRedefinition, visitorname, filename,
					boost::str(boost::format("symbol \'%s\' redefinition") % name), location);
			}

			void ExtensionRedefinition(Error::Report& report, const std::string& visitorname, const std::string& extension, const std::string& filename, const Error::Location& location)
			{
				report.AddWarning(Error::ErrorCode::ExtensionRedefinition, visitorname, filename,
					boost::str(boost::format("extension \'%s\' redefinition") % extension), location);
			}

			void ExtensionValueMissing(Error::Report& report, const std::string& visitorname, const std::string& extension, const std::string& filename, const Error::Location& location)
			{
				report.AddError(Error::ErrorCode::ExtensionValueMissing, visitorname, filename,
					boost::str(boost::format("extension \'%s\' requires a value") % extension), location);
			}

			void IllegalExtension(Error::Report& report, const std::string& visitorname, const std::string& extension, const std::string& filename, const Error::Location& location)
			{
				report.AddWarning(Error::ErrorCode::IllegalExtension, visitorname, filename,
					boost::str(boost::format("symbol does not accept extension \'%s\'") % extension), location);
			}

			void BreakOutsideLoop(Error::Report& report, const std::string& visitorname, const std::string& filename, const Error::Location& location)
			{
				report.AddError(Error::ErrorCode::BreakOutsideLoop, visitorname, filename,
					"break outside loop scope", location);
			}

			void LabelInsideBlock(Error::Report& report, const std::string& visitorname, const std::string& labelname, const std::string& filename, const Error::Location& location)
			{
				report.AddWarning(Error::ErrorCode::LabelInsideBlock, visitorname, filename,
					boost::str(boost::format("label \'%s\' inside block expression") % labelname), location);
			}

			void UnknownVerb(Error::Report& report, const std::string& visitorname, const std::string& verbname, const std::string& filename, const Error::Location& location)
			{
				report.AddError(Error::ErrorCode::UnknownVerb, visitorname, filename,
					boost::str(boost::format("unknown verb \'%s\'") % verbname), location);
			}

			void InvalidArgumentCount(Error::Report& report, const std::string& visitorname, const std::string& verbname, int wanted, int found, const std::string& filename, const Error::Location& location)
			{
				report.AddError(Error::ErrorCode::InvalidArgumentCount, visitorname, filename,
					boost::str(boost::format("verb \'%s\' expects %d arguments, found %d") % verbname % wanted % found), location);
			}

			void UndefinedSymbol(Error::Report& report, const std::string& visitorname, const std::string& symbolname, const std::string& filename, const Error::Location& location)
			{
				report.AddWarning(Error::ErrorCode::UndefinedSymbol, visitorname, filename,
					boost::str(boost::format("symbol \'%s\' used without being defined") % symbolname), location);
			}

			void IllegalVoidResult(Error::Report& report, const std::string& visitorname, const std::string& filename, const Error::Location& location)
			{
				report.AddError(Error::ErrorCode::IllegalVoidResult, visitorname, filename,
					"value expected, but expression has result type \'void\'", location);
			}

			void ResultNotBoolean(Error::Report& report, const std::string& visitorname, const std::string& filename, const Error::Location& location)
			{
				report.AddWarning(Error::ErrorCode::ResultNotBoolean, visitorname, filename,
					"boolean expression expected", location);
			}

			void CallToUnusedLabel(Error::Report& report, const std::string& visitorname, const std::string& labelname, const std::string& filename, const Error::Location& location)
			{
				report.AddError(Error::ErrorCode::CallToUnusedLabel, visitorname, filename,
					boost::str(boost::format("label \'%s\' is called but not defined") % labelname), location);
			}

			void LabelRedefinition(Error::Report& report, const std::string& visitorname, const std::string& labelname, const std::string& filename, const Error::Location& location)
			{
				report.AddError(Error::ErrorCode::LabelRedefinition, visitorname, filename,
					boost::str(boost::format("label \'%s\' already defined") % labelname), location);
			}

			void MissingExport(Error::Report& report, const std::string& visitorname, const std::string& labelname, const std::string& filename, const Error::Location& location)
			{
				report.AddError(Error::ErrorCode::MissingExport, visitorname, filename,
					boost::str(boost::format("message \'%s\' exported but label not defined") % labelname), location);
			}

			void AssignToRValue(Error::Report& report, const std::string& visitorname, const std::string& filename, const Error::Location& location)
			{
				report.AddError(Error::ErrorCode::AssignToRValue, visitorname, filename,
					"assignment target is not an L-value", location);
			}

			void UndefinedArrayBase(Error::Report& report, const std::string& visitorname, const std::string& symbolname, const std::string& filename, const Error::Location& location)
			{
				report.AddError(Error::ErrorCode::UndefinedArrayBase, visitorname, filename,
					boost::str(boost::format("undefined array base \'%s\'") % symbolname), location);
			}
		}
	}
}
