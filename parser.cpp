#include "token.h"
#include "ast.h"
#include "lexer.h"
#include "parser.h"
#include <memory>

#define PARSER_PEEK_IS(t) (this->peek_token->type == t)
#define PARSER_CUR_IS(t)  (this->cur_token->type == t)

void Parser::next_token() {
	this->cur_token = std::move(this->peek_token);
	this->peek_token = this->lex.next_token();
}

char Parser::expect_peek(char type) {
	if (PARSER_PEEK_IS(type)) {
		next_token();
		return true;
	}
	else {
		return false;
	}
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
	let->ident = std::move(id);

	if (!this->expect_peek(TOK_ASSIGN)) {
		return NULL;
	}

	while (!PARSER_PEEK_IS(TOK_SEMICOLON)) {
		this->next_token();
	}

	// TODO: Handle expressions
	//
	return std::move(let);
}

unique_ptr<ExpressionStatement> Parser::parse_expression_statement() {
	auto expr = std::make_unique<ExpressionStatement>(ExpressionStatement());
	expr->token = std::move(cur_token);

	if (this->peek_token->type == TOK_SEMICOLON) {
		this->next_token();
	}

	return std::move(expr);
}

unique_ptr<Identifier> Parser::parse_identifier() {
	auto id = std::make_unique<Identifier>(Identifier());
	id->token = std::move(this->cur_token);
	id->value = id->token->literal;
	return std::move(id);
}

// bp: binding power or 'precedence'
unique_ptr<Expression> Parser::parse_expression(char bp) {
	
	switch (this->cur_token->type) {
		case TOK_ID:
			auto left = parse_identifier();
			break;
	}

/*	
	while ((!PARSER_PEEK_IS(TOK_SEMICOLON)) && bp < this->peek_precedence()) {


	}
*/


}

unique_ptr<Expression> Parser::parse_prefix_expression() {
	auto expr = make_unique<PrefixExpression>(PrefixExpression());
	expr->token = std::move(cur_token);
	expr->operator_ = expr->token->literal;
	
	this->next_token();
	expr->right = this->parse_expression(PREC_PREFIX);
	return expr;
}

void test_parse_let() {
	string input = "let bananaasdf = 5;";
	auto l = Lexer(input);
	auto p = Parser(l);
	auto program = p.parse_program();

	[[unlikely]]
	if (program->Statements.size() != 1) {
		cout << "[!] (program->Statements.size() != 1) in test_parse_let()\n";
		return;
	}

	shared_ptr<Statement> s = program->Statements[0];
	LetStatement* let = static_cast<LetStatement*>(s.get());


	cout << "[*] test_parse_let() passed";
}

int main() {
	initialize_maps();
	test_next_token();
	test_parse_let();
}
