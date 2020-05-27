#pragma once
#include <vector>
#include <memory>
#include <unordered_map>
#include "ast.h"
#include "lexer.h"

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
		// Unfortunately tokens cannot be unique_ptr, as there are many cases
		// where cur_token is move'd into an object, and then used later in the
		// callstack before a next_token() call, which means we will try to use a null
		// reference. A workaround is to copy the Token that cur_token
		// points to and make a unique_ptr pointing to it, so then we never have to 
		// move() cur_token, and it will be a valid reference in subsequent uses. 
		//
		// Maybe the incurred overhead of just using shared_ptr is much lower?
		std::shared_ptr<Token>		cur_token;
		std::shared_ptr<Token>		peek_token;

		void					next_token();
		char					expect_peek(char type);
		char					peek_precedence();
		char					cur_precedence();
		std::map <char, char> precedence_map;

		std::unique_ptr<Program> parse_program();
		std::shared_ptr<Statement> parse_statement();
		std::unique_ptr<LetStatement> parse_let_statement();
		std::unique_ptr<BlockStatement> parse_block_statement();

		std::unique_ptr<ExpressionStatement> parse_expression_statement();
		std::shared_ptr<Expression> parse_grouped_expression();
		std::shared_ptr<Expression> parse_expression(char precedence);
		std::unique_ptr<Expression> parse_prefix_expression();

		std::unique_ptr<InfixExpression> parse_infix_expression(std::shared_ptr<Expression> left_expr);
		std::unique_ptr<FunctionLiteral> parse_function_literal();
		void parse_function_parameters(FunctionLiteral* fn);
		std::unique_ptr<Identifier> parse_identifier();
		std::unique_ptr<IntegerLiteral> parse_integer_literal();
		std::unique_ptr<Boolean> parse_boolean();

	protected:
		Lexer& lex;
};
