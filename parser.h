#pragma once
#include <vector>
#include <memory>
#include "ast.h"

extern void test_parse_let();
static map<char, void (*)(void)> prefix_fns;

#define PREC_LOWEST			0
#define PREC_EQUALS			1
#define PREC_LESSGREATER	2
#define PREC_SUM			3
#define PREC_PRODUCT		4
#define PREC_PREFIX			5
#define PREC_CALL			6

class Parser {
	public:
		Parser(Lexer& l) : lex(l) { 
			this->next_token(); 
			this->next_token();

		//	prefix_fns[TOK_ID] = &parse_identifier;
		}
		unique_ptr<Token>		cur_token;
		unique_ptr<Token>		peek_token;
		void					next_token();
		bool					expect_peek(char type);
		unique_ptr<Program> parse_program();
		unique_ptr<Statement> parse_statement();
		unique_ptr<LetStatement> parse_let_statement();
		unique_ptr<ExpressionStatement> parse_expression_statement();
		unique_ptr<Expression> parse_expression(char precedence);
		unique_ptr<Expression> parse_prefix_expression();
		unique_ptr<Expression> parse_identifier();

	protected:
		Lexer& lex;
};
