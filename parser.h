#pragma once
#include <vector>
#include <memory>
#include <unordered_map>
#include "ast.h"

extern void test_parse_let();

#define PREC_LOWEST			1
#define PREC_EQUALS			2
#define PREC_LESSGREATER	3
#define PREC_SUM			4
#define PREC_PRODUCT		5
#define PREC_PREFIX			6
#define PREC_CALL			7

static map<char, char> precedence_map;

class Parser {
	public:
		Parser(Lexer& l) : lex(l) { 
			precedence_map[TOK_PLUS] = PREC_SUM;
			precedence_map[TOK_MINUS] = PREC_SUM;
			precedence_map[TOK_EQ] = PREC_EQUALS;
			precedence_map[TOK_NEQ] = PREC_EQUALS;
			precedence_map[TOK_LT] = PREC_LESSGREATER;
			precedence_map[TOK_GT] = PREC_LESSGREATER;
			precedence_map[TOK_SLASH] = PREC_PRODUCT;
			precedence_map[TOK_ASTERISK] = PREC_PRODUCT;
			precedence_map[TOK_LPAREN] = PREC_CALL;

			this->next_token(); 
			this->next_token();
		}

		unique_ptr<Token>		cur_token;
		unique_ptr<Token>		peek_token;

		void					next_token();
		char					expect_peek(char type);
		char					peek_precedence();
		char					cur_precedence();
		unique_ptr<Program> parse_program();
		shared_ptr<Statement> parse_statement();
		unique_ptr<LetStatement> parse_let_statement();
		unique_ptr<ExpressionStatement> parse_expression_statement();

		shared_ptr<Expression> parse_expression(char precedence);
		unique_ptr<Expression> parse_prefix_expression();
		unique_ptr<InfixExpression> parse_infix_expression(std::shared_ptr<Expression> exp);

		unique_ptr<Identifier> parse_identifier();
		unique_ptr<IntegerLiteral> parse_integer_literal();
		unique_ptr<Boolean> parse_boolean();

	protected:
		Lexer& lex;
};
