using namespace std;

#ifndef VECTOR_H
#define VECTOR_H
#include <vector>
#endif

#ifndef MEMORY_H
#define	MEMORY_H
#include <memory>
#endif

class AstNode {
	public:
		virtual	string Literal();
		virtual string String();
};

class Expression: public AstNode {
	public:
		string	Literal() override;
		string	String() override;
};

class Statement: public AstNode {
};

struct Identifier {
	std::unique_ptr<Token> token;
	string	value;
};

class IntegerLiteral: public Statement {
	public:
		string Literal() override;
};

class LetStatement: public Statement {
	public:
		string Literal() override;
		unique_ptr<Token> token;
		unique_ptr<Identifier> ident;
		unique_ptr<Expression>	value;	

		LetStatement() {};
};

class BlockStatement : public Statement {
	public:
		Token token;
		vector<unique_ptr<Statement>> stmts;
		string Literal() override;
		string String() override;
};


string LetStatement::Literal() {
	return this->token->literal;
}

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
