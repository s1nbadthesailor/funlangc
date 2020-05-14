#ifndef TOKEN_H
#define TOKEN_H
#include "token.h"
#endif

#ifndef LEXER_H
#define LEXER_H
#include "lexer.h"
#endif

#ifndef PARSER_H
#define PARSER_H
#include "parser.h"
#endif

#ifndef AST_H
#define AST_H
#include "ast.h"
#endif


int main(void) {
	Token::initialize_maps();
	test_next_token();
	test_parse_let();
}
