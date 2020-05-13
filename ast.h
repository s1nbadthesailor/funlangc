using namespace std;
#include <vector>

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

class Identifier {
	Token	token;
	string	value;
};

class IntegerLiteral: public Statement {
	public:
		string Literal() override;
};

class LetStatement: public Statement {
	public:
		string Literal() override;
		Token		token;
		Identifier	ident;
		Expression	value;	
};

class BlockStatement : public Statement {
	public:
		Token token;
		vector<Statement> stmts;
		string Literal() override;
		string String() override;
};


string LetStatement::Literal() {
	return this->token.literal;
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
