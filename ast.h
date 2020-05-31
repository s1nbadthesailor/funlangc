#pragma once
#include "token.h"
#include <vector>
#include <memory>

#define AST_EXPRESSION 	0
#define AST_EXPRSTMT	1
#define AST_PREFIX 		2
#define AST_INFIX		3
#define AST_RETURN		4
#define AST_IDENT		5
#define AST_FNLIT		6
#define AST_INTLIT		7
#define AST_IF			8
#define AST_GROUP		9
#define AST_BOOL		10
#define AST_CALL		11


class AstNode {
	public:
		char ast_type;
		virtual	std::string Literal() = 0;
		virtual std::string String() = 0;
};

class Statement : public AstNode {
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

		Identifier() {}
		void Identifer(std::shared_ptr<Token> t, std::string v) {
			this->token = t;
			this->value = v;
		}
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
		std::shared_ptr<Expression>	value;	
};


class ReturnStatement: public Statement {
	public:
		std::string Literal() override;
		std::string String() override;
		std::shared_ptr<Token> token;
		std::shared_ptr<Expression> value;
};


class BlockStatement : public Expression {
	public:
		std::string Literal() override;
		std::string String() override;
		std::shared_ptr<Token> token;
		std::vector<std::shared_ptr<Statement>> statements;
};

class FunctionLiteral : public Expression {
	public:
		std::string Literal() override;
		std::string String() override;
		std::shared_ptr<Token> token;
		std::vector<std::shared_ptr<Identifier>> parameters;
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

class IfExpression: public Expression {
	public:
		std::string Literal() override;
		std::string String() override;
		std::shared_ptr<Token> token;
		std::shared_ptr<Expression> condition;
		std::shared_ptr<BlockStatement> consequence;
		std::shared_ptr<BlockStatement> alternative;
};

class CallExpression: public Expression {
	public:
		std::string Literal() override;
		std::string String() override;
		std::shared_ptr<Token> token;
		std::shared_ptr<Expression> function;
		std::vector<std::shared_ptr<Expression>> arguments;
};


class Program {
	public:
		std::vector<std::shared_ptr<Statement>> Statements;
		std::string String();
};
