#include "token.h"
#include "ast.h"
#include "lexer.h"

class Parser {
	public:
		Parser(Lexer& l) : lex(l){}
		Token		cur;
		Token		peek;
		void		next_token();
		bool		expect_peek(char type);
		bool		peek_is(char type);
		bool		cur_is(char type);
		Statement*	parse_statement();
		LetStatement* parse_let_statement();

	protected:
		Lexer& lex;
};

void Parser::next_token() {
	this->cur = this->peek;
	this->peek = this->lex.next_token();
}

bool Parser::expect_peek(char type) {
	if (peek_is(type)) {
		next_token();
		return true;
	}
	else {
		return false;
	}
}

bool Parser::peek_is(char type) {
	return (this->peek.type == type);
}

bool Parser::cur_is(char type) {
	return (this->cur.type == type);
}

Statement* Parser::parse_statement() {
	switch (this->cur.type) {
		case TOK_LET:
			return this->parse_let_statement();
		case TOK_RETURN:
//			return this->parse_return_statement();
		default:
//			return this->parse_expression();
	}
}

LetStatement* Parser::parse_let_statement() {
	LetStatement& let = LetStatement();
	if ((this->expect_peek(TOK_ID)) == false) {
		return NULL;
	}
}

int main(void) {
	return 1;
}
