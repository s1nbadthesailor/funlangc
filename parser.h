#pragma once
#include <vector>
#include <memory>
#include <unordered_map>
#include "ast.h"

template<typename T>
struct MapWrap
{
	typedef std::map<char, T> map_type;
};

extern void test_parse_let();


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

			MapWrap<unique_ptr<Expression> (*)()>::map_type prefix_fns;
			prefix_fns[TOK_ID] = &Parser::parse_expression;

		}

		unique_ptr<Token>		cur_token;
		unique_ptr<Token>		peek_token;

		void					next_token();
		char					expect_peek(char type);
		char					peek_precedence();
		unique_ptr<Program> parse_program();
		unique_ptr<Statement> parse_statement();
		unique_ptr<LetStatement> parse_let_statement();
		unique_ptr<ExpressionStatement> parse_expression_statement();
		unique_ptr<Expression> parse_expression(char precedence);
		unique_ptr<Expression> parse_prefix_expression();
		unique_ptr<Identifier> parse_identifier();
		unique_ptr<IntegerLiteral> parse_integer_literal();

	protected:
		Lexer& lex;
};
