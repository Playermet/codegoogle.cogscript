#ifndef _COG_STAGES_H_INCLUDED_
#define _COG_STAGES_H_INCLUDED_

#include <string>
#include <unordered_map>
#include <iosfwd>

namespace Cog
{
	namespace Error
	{
		class Report;
	}

	namespace AST
	{
		class TranslationUnit;
		class Factory;
	}

	namespace Symbols
	{
		class SymbolTable;
	}

	namespace Verbs
	{
		class VerbTable;
	}

	namespace VirtualMachine
	{
		class Value;
	}

	namespace IR
	{
		class Printer;
	}

	namespace Stages
	{
		namespace Stage1
		{
			AST::TranslationUnit* GenerateAST(const std::string& filename, std::istream& inputFilestream, Error::Report& errorReport, AST::Factory& astFactory);
		}

		namespace Stage2
		{
			void SemanticAnalysis(AST::TranslationUnit* ast, Symbols::SymbolTable& symbolTable, const std::unordered_map<std::string, VirtualMachine::Value>& constantTable,
				Verbs::VerbTable& verbTable, Error::Report& report);
		}

		namespace Stage3
		{
			void ConstantFolding(AST::Factory& factory, AST::TranslationUnit* ast, Symbols::SymbolTable& symbolTable,
				const std::unordered_map<std::string, VirtualMachine::Value>& constantTable, Error::Report& report);
		}

		namespace Stage4
		{
			void CodeGeneration(AST::TranslationUnit* ast, IR::Printer& printer, Error::Report& report);
		}
	}
}

#endif // _COG_STAGES_H_INCLUDED_
