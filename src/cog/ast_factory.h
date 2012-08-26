#ifndef _AST_FACTORY_H_INCLUDED_
#define _AST_FACTORY_H_INCLUDED_

#include "ast_node.h"
#include "gen_arena.h"
#include "gra_parser.hpp"

#define MAKE_NOLINES( x )										\
	x* val = new(data) x;										\
	nodes.push_back(val);

#define MAKE( x )												\
	MAKE_NOLINES(x)												\
	val->Filename = &current_filename;							\
	val->Location = Error::Location(yyl.first_line,				\
	yyl.first_column, yyl.last_line, yyl.last_column);

namespace Cog
{
	namespace AST
	{
		class Factory
		{
		private:
			Generics::Arena<> data;
			std::vector<Node*> nodes;
			const std::string current_filename;

			template <typename T> class ListNode : public Node
			{
			public:
				ListNode()
				{
					return;
				}

				std::vector<T*> Nodes;

				void Accept(Visitor& v)
				{
					return;
				}
			};

		public:
			template <typename T> std::vector<T*>* MakeList(T* initial_value)
			{
				MAKE_NOLINES(ListNode<T>);
				val->Nodes.push_back(initial_value);
				return &val->Nodes;
			}

			template <typename T> std::vector<T*>* MakeList()
			{
				MAKE_NOLINES(ListNode<T>);
				return &val->Nodes;
			}

			StringFragmentField* MakeStringFragmentField(const char* text, YYLTYPE& yyl);
			IntegerField* MakeIntegerField(int value, YYLTYPE& yyl);
			FloatField* MakeFloatField(float value, YYLTYPE& yyl);

			BareExtension* MakeBareExtension(const char* name, YYLTYPE& yyl);
			ValuedExtension* MakeValuedExtension(const char* name, SymbolField* value, YYLTYPE& yyl);

			Symbol* MakeSymbol(const char* type, const char* name, std::vector<SymbolExtension*>* extensions, YYLTYPE& yyl);
			ValuedSymbol* MakeValuedSymbol(const char* type, const char* name, std::vector<SymbolExtension*>* extensions, SymbolField* value, YYLTYPE& yyl);

			ConstantValueExpression* MakeConstantValueExpression(const VirtualMachine::Value& value, const std::string* filename, const Error::Location& loc);
			StringLiteralExpression* MakeStringLiteralExpression(const char* value, YYLTYPE& yyl);
			IntegerLiteralExpression* MakeIntegerLiteralExpression(int value, YYLTYPE& yyl);
			FloatLiteralExpression* MakeFloatLiteralExpression(float value, YYLTYPE& yyl);
			VectorLiteralExpression* MakeVectorLiteralExpression(float x, float y, float z, YYLTYPE& yyl);
			IdentifierExpression* MakeIdentifierExpression(const char* identifier, YYLTYPE& yyl);
			SubscriptExpression* MakeSubscriptExpression(const char* base, Expression* index, YYLTYPE& yyl);
			MethodCallExpression* MakeMethodCallExpression(const char* base, std::vector<Expression*>* arguments, YYLTYPE& yyl);
			UnaryExpression* MakeUnaryExpression(Expression* base, UnaryOperator::Enum op, YYLTYPE& yyl);
			InfixExpression* MakeInfixExpression(Expression* left, Expression* right, InfixOperator::Enum op, YYLTYPE& yyl);
			AssignmentExpression* MakeAssignmentExpression(Expression* target, Expression* value, YYLTYPE& yyl);
			CommaExpression* MakeCommaExpression(Expression* left, Expression* right, YYLTYPE& yyl);

			CompoundStatement* MakeCompoundStatement(std::vector<Statement*>* code, YYLTYPE& yyl);
			EmptyStatement* MakeEmptyStatement(YYLTYPE& yyl);
			ExpressionStatement* MakeExpressionStatement(Expression* expression, YYLTYPE& yyl);
			BreakStatement* MakeBreakStatement(YYLTYPE& yyl);
			ReturnStatement* MakeReturnStatement(YYLTYPE& yyl);
			CallStatement* MakeCallStatement(const char* label, YYLTYPE& yyl);
			IfStatement* MakeIfStatement(Expression* condition, Statement* code, YYLTYPE& yyl);
			IfElseStatement* MakeIfElseStatement(Expression* condition, Statement* code, Statement* elsecode, YYLTYPE& yyl);
			WhileStatement* MakeWhileStatement(Expression* condition, Statement* code, YYLTYPE& yyl);
			DoStatement* MakeDoStatement(Statement* code, Expression* condition, YYLTYPE& yyl);
			ForOptionalExpression* MakeForOptionalExpression(YYLTYPE& yyl);
			ForExpression* MakeForExpression(Expression* condition, YYLTYPE& yyl);
			ForStatement* MakeForStatement(ForOptionalExpression* initializer, ForOptionalExpression* condition, ForOptionalExpression* incrementer, Statement* code, YYLTYPE& yyl);
			LabeledStatement* MakeLabeledStatement(const char* label, Statement* code, YYLTYPE& yyl);

			TranslationUnit* MakeTranslationUnit(std::vector<Symbol*>* symbols, std::vector<Statement*>* code, YYLTYPE& yyl);

			Factory(const std::string& current_filename);
			~Factory();
		};
	}
}

#endif // _AST_FACTORY_H_INCLUDED_
