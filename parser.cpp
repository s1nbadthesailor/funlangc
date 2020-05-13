#include "token.h"
#include "ast.h"
#include "lexer.h"
#include <memory>

class Parser {
	public:
		Parser(Lexer& l) : lex(l){}
		Token		cur_token;
		Token		peek_token;
		void		next_token();
		bool		expect_peek(char type);
		bool		peek_is(char type);
		bool		cur_is(char type);
		unique_ptr<Statement> parse_statement();
		unique_ptr<LetStatement> parse_let_statement();

	protected:
		Lexer& lex;
};

void Parser::next_token() {
	this->cur_token = this->peek_token;
	this->peek_token = this->lex.next_token();
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
	return (this->peek_token.type == type);
}

bool Parser::cur_is(char type) {
	return (this->cur_token.type == type);
}

unique_ptr<Statement> Parser::parse_statement() {
	switch (this->cur_token.type) {
		case TOK_LET:
			return this->parse_let_statement();
		case TOK_RETURN:
//			return this->parse_return_statement();
		default:
			break;
//			return this->parse_expression();
	}
}

unique_ptr<LetStatement> Parser::parse_let_statement() {
 	auto let = std::make_unique<LetStatement>(LetStatement());
	let->token = std::move(this->cur_token);

	if ((this->expect_peek(TOK_ID)) == false) {
		return NULL;
	}

	auto id = std::make_unique<Identifier>(Identifier());
	id->token = std::move(this->cur_token);
	id->value = this->cur_token->literal;
}

int main(void) {
	return 1;
}
