#include "token.h"
#include "lexer.h"
#include "parser.h"
#include "ast.h"
#include <memory>

int main(void) {
	initialize_maps();
	test_next_token();
	test_parse_let();
}
