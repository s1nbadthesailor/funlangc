#include "token.h"
#include "lexer.h"
#include "parser.h"
#include "ast.h"
#include "parser_tests.h"
#include "evaluate_tests.h"
#include "evaluate.h"
#include <memory>
#include <stdio.h>
#include <iostream>


// TODO:
// Long term:
//	- virtual machine
//	- bytecode compiler
//
// Short term:
// 	- proper parser error handling, logging macros
//	- refactor to use jump tables

void repl() {
	std::string input;

	std::cout << "Welcome to funlang!\n";
	while (1) {
		std::cout << ">> ";
		std::cin >> input;		
		auto l = Lexer(input);
		auto p = Parser(l);
		auto prog = p.parse_program();
		evaluate_program(prog.get());
	}

}

int main() {
	initialize_maps();

#ifdef RUN_TESTS
	test_infix_expressions();
	test_operator_precedence();
	test_function_literal();
	test_if_expression(false);
	test_call_expression(false);
	test_eval_integer();
#endif
	repl();
}
