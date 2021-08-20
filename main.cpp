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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

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
		auto eval = Evaluator();
		eval.evaluate_program(prog.get());
	}
}

int main() {
	const char* test_prog = "./yay.fun";
	initialize_keyword_map();
#ifdef RUN_TESTS
	test_infix_expressions();
	test_operator_precedence();
	test_function_literal();
	test_if_expression(false);
	test_call_expression(false);
	test_eval_integer();
#endif

	int tfd = open(test_prog, O_RDONLY);
	auto count = lseek(tfd, 0, SEEK_END);
	lseek(tfd, 0, 0);
	char* tbuf = (char*)malloc(count + 1);
	read(tfd, tbuf, count);
	
	std::string tinput(tbuf);

	auto l = Lexer(tinput);
	auto p = Parser(l);
	auto prog = p.parse_program();
	auto eval = Evaluator();
	eval.evaluate_program(prog.get());
	//repl();
}
