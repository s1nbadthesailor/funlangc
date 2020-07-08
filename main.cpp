#include "token.h"
#include "lexer.h"
#include "parser.h"
#include "ast.h"
#include "parser_tests.h"
#include "evaluate_tests.h"
#include <memory>

// TODO:
// Long term:
//	- virtual machine
//	- bytecode compiler
//
// Short term:
// 	- proper parser error handling, logging macros
//	- refactor to use jump tables

void repl() {
	

}

int main() {
	initialize_maps();
	test_infix_expressions();
	test_operator_precedence();
	test_function_literal();
	test_if_expression(false);
	test_call_expression(false);

	test_eval_integer();
}
