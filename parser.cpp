#ifndef	TOKEN_H
#define TOKEN_H
#include "token.h"
#endif

#ifndef AST_H
#define AST_H
#include "ast.h"
#endif

#ifndef LEXER_H
#define LEXER_H
#include "lexer.h"
#endif

#ifndef MEMORY_H
#define MEMORY_H
#include <memory>
#endif

class Parser {
	public:
		Parser(Lexer& l) : lex(l){}
		unique_ptr<Token>		cur_token;
		unique_ptr<Token>		peek_token;
		void		next_token();
		bool		expect_peek(char type);
		bool		peek_is(char type);
		bool		cur_is(char type);
		unique_ptr<Program> parse_program();
		unique_ptr<Statement> parse_statement();
		unique_ptr<LetStatement> parse_let_statement();

	protected:
		Lexer& lex;
};

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
	auto l = Lexer("let g = 5;");
	auto p = Parser(l);
	auto program = p.parse_program();

	Token tests[] = {
		Token(TOK_LET, "let"),
		Token(TOK_ID, "g"),
		Token(TOK_ASSIGN, "="),
	};

	for (auto& stmt : program->Statements) {

	}
}

int main(void) {
	test_parse_let();
}
