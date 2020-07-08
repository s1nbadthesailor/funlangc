#include "object.h"
#include "parser.h"
#include "lexer.h"
#include "ast.h"
#include <iostream>
#include <vector>
#include <iterator>

#include "evaluate.h"
#include "evaluate_tests.h"
using namespace std;

//#define PARSE_PROGRAM(input)	Parser(Lexer(input)).parse_program()

void test_eval_integer() {
	struct {
		std::string input;
		int expected;
	} tests[] = {

		{"3+4", 5},
		{"69;", 69},

	};

	for (const auto& t : tests) {
		auto l = Lexer(t.input);
		auto p = Parser(l);
		auto program = p.parse_program();
		p.show_parser_errors();
		
		evaluate_program(program.get());
	}
}


