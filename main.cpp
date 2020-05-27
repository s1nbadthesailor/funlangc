#include "token.h"
#include "lexer.h"
#include "parser.h"
#include "ast.h"
#include "parser_tests.h"
#include <memory>

int main(void) {
	initialize_maps();
//	test_let_statement();
	test_infix_expression();
}
