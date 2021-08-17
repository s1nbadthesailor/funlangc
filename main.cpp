#include "token.h"
#include "lexer.h"
#include "parser.h"
#include "ast.h"
#include "parser_tests.h"
#include "evaluate_tests.h"
#include "evaluate.h"
#include "compiler.h"
#include <memory>
#include <stdio.h>
#include <iostream>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// TODO:
// Long term:
//	- virtual machine/runtime [FOCUS]
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

//#define RUN_TESTS
// TODO: some test is corrupting memory or?
int main(int argc, char** argv) {

#ifdef RUN_TESTS
	test_infix_expressions();
	test_operator_precedence();
	test_function_literal();
	test_if_expression(false);
	test_call_expression(false);
	test_eval_integer();
#endif

	if (argc < 2) {
		repl();
		return 1;
	}

	char* source_file = argv[1];
	int sfd = open(source_file, O_RDONLY);
	if (sfd < 0) {
		std::cout << "[main] failed to read file " << source_file << '\n';
		return -1;
	}

	unsigned long count = lseek(sfd, 0, SEEK_END);
	lseek(sfd, 0, 0);
	char* sbuf = (char*)malloc(count + 1);
	read(sfd, sbuf, count);
	
	std::string sinput(sbuf);
	std::cout << sinput << '\n';

	auto l = Lexer(sinput);
	auto p = Parser(l);
	auto prog = p.parse_program();
	//auto compiler = new Compiler(prog.get()); // UB FTW
	//compiler->compile_program();
}
