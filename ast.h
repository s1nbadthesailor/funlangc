#pragma once
using namespace std;
#include <vector>
#include <memory>

class AstNode {
	public:
		virtual	string Literal() = 0;
		virtual string String() = 0;
};


class Statement: public AstNode {
	public:
};


class Expression: public AstNode {
	public:
};


class ExpressionStatement : public Expression {
	public:
		string Literal() override;
		string String() override;
		std::unique_ptr<Token> token;
		std::unique_ptr<Expression> expression;
};

string ExpressionStatement::Literal() {
	return this->token->literal;
}

string ExpressionStatement::String() {
	if (this->expression) {
		return this->expression->String();
	}
	return "";
}

class PrefixExpression : public Expression {
	public:
		string Literal() override;
		string String() override;
		std::unique_ptr<Token> token;
		string operator_;
		unique_ptr<Expression> right;
};

string PrefixExpression::Literal() {
	return this->token->literal;
}

string PrefixExpression::String() {
	string ret;

	ret += "(";
	ret += this->operator_;
	ret += this->right->String();
	ret += ")";
	ret += ";";

	return ret;
}

class Identifier: public Statement {
	public:
		string Literal() override;
		string String() override;
		std::unique_ptr<Token> token;
		string	value;
};

string Identifier::Literal() {
	return this->token->literal;
}

string Identifier::String() {
	return this->value;
}


class IntegerLiteral: public Statement {
	public:
		string Literal() override;
		string String() override;
		unique_ptr<Token> token;
};

string IntegerLiteral::Literal() {
	return this->token->literal;
}

string IntegerLiteral::String() {
	return this->token->literal;
}


class LetStatement: public Statement {
	public:
		string Literal() override;
		string String() override;
		unique_ptr<Token> token;
		unique_ptr<Identifier> ident;
		unique_ptr<Expression>	value;	

		LetStatement() {};
};

string LetStatement::Literal() {
	return this->token->literal;
}

string LetStatement::String() {
	string ret;
	ret += this->Literal();
	ret += " ";
	ret += this->ident->value;
	ret += " = ";
	
	if (this->value) {
		ret += this->value->String();
	}

	return ret;
}


class ReturnStatement: public Statement {
	public:
		string Literal() override;
		string String() override;
		unique_ptr<Token> token;
		unique_ptr<Expression> value;
};

string ReturnStatement::Literal() {
	return this->token->literal;
}

string ReturnStatement::String() {
	string ret;

	ret += this->token->literal;
	ret += " ";
	ret += this->value->String();

	return ret;
}


class BlockStatement : public Statement {
	public:
		string Literal() override;
		string String() override;
		unique_ptr<Token> token;
		vector<unique_ptr<Statement>> stmts;
};


class Program {
	public:
		vector<unique_ptr<Statement>> Statements;
		string String();
};

string Program::String() {
	string ret;
	for (auto& s : Statements) {
		ret += s->String();
	}
	return ret;
}
