#include "token.h"
#include "lexer.h"
#include "ast.h"

class Parser {
public:
	Parser(Lexer& l) : lex(l){}

	Token		cur;
	Token		peek;
	void		next_token();
	bool		expect_peek(int id);
	Statement	parseStatement();

	LetStatement* parse_let_statement();

protected:
	Lexer& lex;
};

bool Parser::expect_peek(int id) {
	if (this->peek.type == id) {
		this->next_token();
		return true;
	}
	else {
		return false;
	}
}

void Parser::next_token() {
	this->cur = this->peek;
	this->peek = this->lex.next_token();
}

LetStatement* Parser::parse_let_statement() {
	LetStatement let = LetStatement();
	if ((this->expect_peek(TOK_ID)) == false) {
		return NULL;
	}
}

int main(void) {
	return 1;
}
