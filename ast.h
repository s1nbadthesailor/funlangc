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
#define AST_LET 12
#define AST_BLOCK 13

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
		ExpressionStatement() {
			ast_type = AST_EXPRSTMT;
		}
};


class PrefixExpression : public Expression {
	public:
		std::string Literal() override;
		std::string String() override;
		std::shared_ptr<Token> token;
		std::string operator_;
		std::shared_ptr<Expression> right;
		PrefixExpression() {
			ast_type = AST_PREFIX;
		}
};


class Identifier: public Expression {
	public:
		std::string Literal() override;
		std::string String() override;
		std::shared_ptr<Token> token;
		std::string	value;

		Identifier() {
			ast_type = AST_IDENT;
		}
		void Identifer(std::shared_ptr<Token> t, std::string v) {
			ast_type = AST_IDENT;
			token = t;
			value = v;
		}
};


class IntegerLiteral: public Expression {
	public:
		std::string Literal() override;
		std::string String() override;
		std::shared_ptr<Token> token;
		double	value;
		IntegerLiteral() {
			ast_type = AST_INTLIT;
		}
};


class LetStatement: public Statement {
	public:
		std::string Literal() override;
		std::string String() override;
		std::shared_ptr<Token> token;
		std::unique_ptr<Identifier> ident;
		std::shared_ptr<Expression>	value;
		LetStatement() { 
			ast_type = AST_LET;
		}
};


class ReturnStatement: public Statement {
	public:
		std::string Literal() override;
		std::string String() override;
		std::shared_ptr<Token> token;
		std::shared_ptr<Expression> value;
		ReturnStatement() {
			ast_type = AST_RETURN;
		}
};


class BlockStatement : public Expression {
	public:
		std::string Literal() override;
		std::string String() override;
		std::shared_ptr<Token> token;
		std::vector<std::shared_ptr<Statement>> statements;
		BlockStatement() {
			ast_type = AST_BLOCK;
		}
};

class FunctionLiteral : public Expression {
	public:
		std::string Literal() override;
		std::string String() override;
		std::shared_ptr<Token> token;
		std::vector<std::shared_ptr<Identifier>> parameters;
		std::shared_ptr<BlockStatement> block;

		void parse_parameters();
		FunctionLiteral() {
			ast_type = AST_FNLIT;
		}
};


class InfixExpression : public Expression {
	public:
		std::string Literal() override;
		std::string String() override;
		std::shared_ptr<Token> token;
		std::shared_ptr<Expression> left;
		std::string operator_;
		std::shared_ptr<Expression> right;
		InfixExpression() {
			ast_type = AST_INFIX;
		}
};


class Boolean : public Expression {
	public:
		std::string Literal() override;
		std::string String() override;
		std::shared_ptr<Token> token;
		bool value;
		Boolean() {
			ast_type = AST_BOOL;
		}
};

class IfExpression: public Expression {
	public:
		std::string Literal() override;
		std::string String() override;
		std::shared_ptr<Token> token;
		std::shared_ptr<Expression> condition;
		std::shared_ptr<BlockStatement> consequence;
		std::shared_ptr<BlockStatement> alternative;
		IfExpression() {
			ast_type = AST_IF;
		}
};

class CallExpression: public Expression {
	public:
		std::string Literal() override;
		std::string String() override;
		std::shared_ptr<Token> token;
		std::shared_ptr<Expression> function;
		std::vector<std::shared_ptr<Expression>> arguments;
		CallExpression() {
			ast_type = AST_CALL;
		}
};


class Program {
	public:
		std::vector<std::shared_ptr<Statement>> Statements;
		std::string String();
};
