#include "compiler.h"
#include "parser.h"
#include "ast.h"


struct TestCase {
	input string;
};

void run_compiler_tests(TestCase tests[]) {

	for (const auto& test : tests) {
		auto l = Lexer(test.input);
		auto p = Parser(l);
		auto program = p.parse_program();
		auto compiler = Compiler(program);

		auto bytecode = compiler.bytecode();

	}
}
