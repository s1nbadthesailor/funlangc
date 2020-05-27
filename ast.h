#pragma once
#include "token.h"
#include <vector>
#include <memory>

#define AST_EXPRESSION 	0
#define AST_STATEMENT 	1
#define AST_EXPRSTMT 	2
#define AST_PREFIX 		3
#define AST_INFIX		4


class AstNode {
	public:
		char ast_type;
		virtual	std::string Literal() = 0;
		virtual std::string String() = 0;
};


class Statement: public AstNode {
	public:
};


class Expression: public Statement {
	public:
};


class ExpressionStatement : public Statement {
	public:
		std::string Literal() override;
		std::string String() override;
		std::shared_ptr<Token> token;
		std::shared_ptr<Expression> expression;
};


class PrefixExpression : public Expression {
	public:
		std::string Literal() override;
		std::string String() override;
		std::shared_ptr<Token> token;
		std::string operator_;
		std::shared_ptr<Expression> right;
};


class Identifier: public Expression {
	public:
		std::string Literal() override;
		std::string String() override;
		std::shared_ptr<Token> token;
		std::string	value;
};


class IntegerLiteral: public Expression {
	public:
		std::string Literal() override;
		std::string String() override;
		std::shared_ptr<Token> token;
		int	value;
};


class LetStatement: public Statement {
	public:
		std::string Literal() override;
		std::string String() override;
		std::shared_ptr<Token> token;
		std::unique_ptr<Identifier> ident;
		std::unique_ptr<Expression>	value;	

		LetStatement() {};
};


class ReturnStatement: public Statement {
	public:
		std::string Literal() override;
		std::string String() override;
		std::shared_ptr<Token> token;
		std::unique_ptr<Expression> value;
};


class BlockStatement : public Expression {
	public:
		std::string Literal() override;
		std::string String() override;
		std::shared_ptr<Token> token;
		std::vector<std::shared_ptr<Statement>> stmts;
};


class FunctionLiteral : public Expression {
	public:
		std::string Literal() override;
		std::string String() override;
		std::shared_ptr<Token> token;
		std::vector<std::unique_ptr<Identifier>> parameters;
		std::shared_ptr<BlockStatement> block;

		void parse_parameters();
};


class InfixExpression : public Expression {
	public:
		std::string Literal() override;
		std::string String() override;
		std::shared_ptr<Token> token;
		std::shared_ptr<Expression> left;
		std::string operator_;
		std::shared_ptr<Expression> right;
};


class Boolean : public Expression {
	public:
		std::string Literal() override;
		std::string String() override;
		std::shared_ptr<Token> token;
		bool value;
};


class Program {
	public:
		std::vector<std::shared_ptr<Statement>> Statements;
		std::string String();
};
