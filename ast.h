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
		Identifier*	ident;
		Expression	value;	

		LetStatement() {};
};

class BlockStatement : public Statement {
	public:
		Token token;
		vector<Statement> stmts;
		string Literal() override;
		string String() override;
};


string LetStatement::Literal() {
	return this->token->literal;
}

class Program {
	public:
		vector<Statement> Statements;
		string String();
};

string Program::String() {
	string ret;
	for (Statement s : Statements) {
		ret += s.String();
	}
	return ret;
}
