#include "token.h"
#include "ast.h"
#include "lexer.h"
#include "parser.h"
#include <memory>
#include <typeinfo>
using namespace std;

#define PARSER_PEEK_IS(t) (this->peek_token->type == t)
#define PARSER_CUR_IS(t)  (this->cur_token->type == t)

void Parser::next_token() {
	this->cur_token = this->peek_token;
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

char Parser::peek_precedence() {
	try {
		return precedence_map.at(this->peek_token->type);
	} catch (exception e) {
		return PREC_LOWEST;
	}
}

char Parser::cur_precedence() {
	try {
		return precedence_map.at(this->cur_token->type);
	} catch (exception e) {
		return PREC_LOWEST;
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

shared_ptr<Statement> Parser::parse_statement() {
	switch (this->cur_token->type) {
		case TOK_LET:
			return this->parse_let_statement();
//		case TOK_RETURN:
//			return this->parse_return_statement();
		default:
			return std::move(this->parse_expression_statement());
	}
}

unique_ptr<LetStatement> Parser::parse_let_statement() {
 	auto let = std::make_unique<LetStatement>(LetStatement());
	let->token = this->cur_token;

	if (!this->expect_peek(TOK_ID)) {
		return NULL;
	}

	auto id = std::make_unique<Identifier>(Identifier());
	id->token = this->cur_token;
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
	expr->token = this->cur_token;
	expr->expression = this->parse_expression(PREC_LOWEST);

	if (PARSER_PEEK_IS(TOK_SEMICOLON)) {
		this->next_token();
	}

	return std::move(expr);
}

unique_ptr<Identifier> Parser::parse_identifier() {
	auto id = std::make_unique<Identifier>(Identifier());
	id->token = this->cur_token;
	id->value = id->token->literal;
	return std::move(id);
}

// bp: binding power or 'precedence'
// TODO: refactor this to use jumptables
shared_ptr<Expression> Parser::parse_expression(char bp) {
	
	shared_ptr<Expression> left_expr = nullptr;
	shared_ptr<Expression> infix = nullptr;

	switch (this->cur_token->type) {
		case TOK_ID: {
			left_expr = parse_identifier();
			break;
		}
		case TOK_INT: {
			left_expr = parse_integer_literal();
			break;
		}
		case TOK_BANG: {
			left_expr = parse_prefix_expression();
			break;
		}
		case TOK_MINUS: {
			left_expr = parse_prefix_expression();
			break;
		}
		case TOK_LPAREN: {
			left_expr = parse_grouped_expression();
			break;
	 	}
		case TOK_TRUE: {
			left_expr = parse_boolean();
			break;
		}
		case TOK_FALSE: {
			left_expr = parse_boolean();
			break;
		}
		default:
			cout << "in parse_expression: no prefix parse function for " << this->cur_token->literal << "\n";
			return nullptr;
	}

	while ((!(PARSER_PEEK_IS(TOK_SEMICOLON))) && bp < this->peek_precedence()) {
		switch (this->peek_token->type) {
			case TOK_PLUS:
			case TOK_MINUS:
			case TOK_SLASH:
			case TOK_ASTERISK:
			case TOK_EQ:
			case TOK_NEQ:
			case TOK_LT:
			case TOK_GT: 
			{
				this->next_token();
				left_expr = parse_infix_expression(left_expr);
				break;
			}
			default:
				return std::move(left_expr);
		}
	}

	return std::move(left_expr);
}


shared_ptr<Expression> Parser::parse_grouped_expression() {
	shared_ptr<Expression> expr = nullptr;
	this->next_token();
	expr = this->parse_expression(PREC_LOWEST);
	if (expr == nullptr) {
		cout << "[!] in parse_grouped_expression: got null expression.\n";
		return nullptr;
	}
	if (!this->expect_peek(TOK_RPAREN)) {
		cout << "[!] in " << __FUNCTION__ << ": Expected RPAREN after grouped expression\n";
		return nullptr;
	}
	return expr;
}

unique_ptr<InfixExpression> Parser::parse_infix_expression(shared_ptr<Expression> left_expr) {
	auto expr = make_unique<InfixExpression>(InfixExpression());
	expr->token = this->cur_token;
	expr->operator_ = this->cur_token->literal;
	expr->left = left_expr;

	char prec = this->cur_precedence();
	this->next_token();
	expr->right = this->parse_expression(prec);
	return std::move(expr);
}

unique_ptr<Expression> Parser::parse_prefix_expression() {
	auto expr = make_unique<PrefixExpression>(PrefixExpression());
	expr->token = cur_token;
	expr->operator_ = expr->token->literal;
	
	this->next_token();
	expr->right = this->parse_expression(PREC_PREFIX);
	return std::move(expr);
}

unique_ptr<IntegerLiteral> Parser::parse_integer_literal() {
	auto lit = make_unique<IntegerLiteral>(IntegerLiteral());
	lit->token = this->cur_token;
	lit->value = std::stoi(lit->token->literal);
	return std::move(lit);
}

unique_ptr<Boolean> Parser::parse_boolean() {
	auto b = make_unique<Boolean>(Boolean());
	b->token = this->cur_token;
	b->value = b->token->type == TOK_TRUE ? true : false;
	return std::move(b);
}

unique_ptr<FunctionLiteral> Parser::parse_function_literal() {
	auto fn = make_unique<FunctionLiteral>(FunctionLiteral());
	fn->token = this->cur_token;
	if (!(this->expect_peek(TOK_LPAREN))) {
		cout << "TOK_LPAREN expected in FunctionLiteral";
		return nullptr;
	}
	
	fn->parse_parameters();

}
