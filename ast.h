#pragma once
using namespace std;
#include <vector>
#include <memory>

class AstNode {
	public:
		virtual	string Literal() = 0;
		virtual string String() = 0;
};

class Expression: public AstNode {
	public:
};

class Statement: public AstNode {
	public:
};

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
};

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
	ret += this->ident->String();
	ret += " = ";
	
	if (this->value != nullptr) {
		ret += this->value->String();
	}

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
