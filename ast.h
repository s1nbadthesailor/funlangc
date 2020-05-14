#pragma once
using namespace std;
#include <vector>
#include <memory>

class AstNode {
	public:
		virtual	string Literal();
		virtual string String();
};

class Expression: public AstNode {
	public:
		string	Literal() override {}
		string	String() override {}
};

class Statement: public AstNode {
	public:
		string Literal() override {}
		string String() override {}
};

struct Identifier {
	std::unique_ptr<Token> token;
	string	value;
};

class IntegerLiteral: public Statement {
	public:
		string Literal() override {}
		string String() override {}
};

class LetStatement: public Statement {
	public:
		string Literal() override { return this->token->literal; }
		string String() override {}
		unique_ptr<Token> token;
		unique_ptr<Identifier> ident;
		unique_ptr<Expression>	value;	

		LetStatement() {};
};

class BlockStatement : public Statement {
	public:
		string Literal() override {}
		string String() override {}
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
