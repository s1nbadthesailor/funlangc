#include "token.h"
#include "ast.h"
#include "lexer.h"
#include "parser.h"
#include <memory>
#include <stdio.h>

void Parser::next_token() {
	this->cur_token = std::move(this->peek_token);
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
	return (this->peek_token->type == type);
}

bool Parser::cur_is(char type) {
	return (this->cur_token->type == type);
}

unique_ptr<Program> Parser::parse_program() {
	auto p = std::make_unique<Program>(Program());
	while (this->cur_token->type != TOK_EOF) {
		auto statement = this->parse_statement();
		if (statement != nullptr) {
			p->Statements.push_back(std::move(statement));
		}
		this->next_token();
	}
	return std::move(p);
}

unique_ptr<Statement> Parser::parse_statement() {
	switch (this->cur_token->type) {
		case TOK_LET:
			return std::move(this->parse_let_statement());
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

	if (!this->expect_peek(TOK_ID)) {
		return NULL;
	}

	auto id = std::make_unique<Identifier>(Identifier());
	id->token = std::move(this->cur_token);
	id->value = id->token->literal;

	if (!this->expect_peek(TOK_ASSIGN)) {
		return NULL;
	}

	while (!this->cur_is(TOK_SEMICOLON)) {
		this->next_token();
	}

	// TODO: Handle expressions
	//
	return std::move(let);
}

void test_parse_let() {
	string input = "let g = 5;";
	auto l = Lexer(input);
	auto p = Parser(l);
	auto program = p.parse_program();
	Token tests[] = {
		Token(TOK_LET, "let"),
		Token(TOK_ID, "g"),
		Token(TOK_ASSIGN, "="),
	};

	cout << program->Statements.size();

}

int main() {
	test_parse_let();
}
