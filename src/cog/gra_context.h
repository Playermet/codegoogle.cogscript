#ifndef _GRA_CONTEXT_H_INCLUDED_
#define _GRA_CONTEXT_H_INCLUDED_

#include <string>
#include <iosfwd>
#include <memory>

#include "ast_factory.h"
#include "err_report.h"

namespace Cog
{
	namespace Grammar
	{
		class Context
		{
		private:
			Error::Report& errorReport;
			const std::string filename;
			std::istream& inputFilestream;
			AST::Factory& astFactory;

			// Scanner initialization members
			// implemented in gra_lexer.lex
			void InitScanner();
			void DestroyScanner();

			void* scanner;

		public:
			Context(const std::string& filename, std::istream& inputFilestream, Error::Report& errorReport, AST::Factory& factory);
			~Context();

			char GetNext();

			inline void* GetScanner()
			{
				return scanner;
			}

			inline Error::Report& GetErrorReport()
			{
				return errorReport;
			}

			inline const std::string& GetFilename()
			{
				return filename;
			}

			void Parse();

			std::string TokenBuffer;
			AST::TranslationUnit* translation_unit;

			inline AST::Factory& GetASTFactory()
			{
				return astFactory;
			}
		};
	}
}

#endif // _GRA_CONTEXT_H_INCLUDED_
