#include "parser.h"
#include "lexer.h"
#include "ast.h"
#include <iostream>
#include <vector>
using namespace std;


void test_parse_let() {
	string input = "let bananaasdf = 5;";
	auto l = Lexer(input);
	auto p = Parser(l);
	auto program = p.parse_program();

	[[unlikely]]
	if (program->Statements.size() != 2) {
		cout << "[!] (program->Statements.size() != 1)\n";
		return;
	}


	auto let = static_pointer_cast<LetStatement>(program->Statements[0]);
	if (let->ident->value.compare("bananaasdf") != 0) {
		cout << "[!] bad identifier!\n";
	}

	cout << "[*] test_parse_let() passed\n";
}

void test_operator_precedence() {
	struct OpTest {
		string input;
		string expected;
	} tests[] = {
		{
			"-a * b",
			"((-a) * b)"
		},
		{
			"!-a",
			"(!(-a))"
		},
		{
			"3 < 5 == false",
			"((3 < 5) == false)"
		},
		{
			"2 / (5 + 5)",
			"(2 / (5 + 5))"
		}
	};

	for (auto& test : tests) {
		auto l = Lexer(test.input);
		auto p = Parser(l);
		auto program = p.parse_program();

		string result = program->String();
		if (result.compare(test.expected) != 0) {
			printf("[!] in test_operator_precedence, expected:%s, got:%s", test.expected.c_str(),
				result.c_str());
			return;
		}
	}

	cout << "[*] test_operator_precedence passed.\n";
}

void test_infix_expression() {
	
	struct InfixTest {
		string input;
		int left;
		string operator_;
		int right;
	} tests[] = {
		{
			"5+5",
			5,
			"+",
			5
		},
		{
			"6 * 9",
			6,
			"*",
			9
		},
		{
			"5 > 3",
			5,
			">",
			3
		},
		{
			"6 < 9",
			6,
			"<",
			9
		},
		{
			"6 - 9",
			6,
			"-",
			9
		},
		{
			"6 / 9",
			6,
			"/",
			9
		},
		{
			"1 == 1",
			1,
			"==",
			1	
		},
		{
			"1 != 1",
			1,
			"!=",
			1
		}
	};

	for (auto& test : tests) {
		auto l = Lexer(test.input);
		auto p = Parser(l);
		auto program = p.parse_program();

		[[unlikely]]
			/*
		if (program->Statements.size() != 1) {
			cout << "[!] (program->Statements.size() != 1)\n";
			return;
		}
*/
		auto s = static_pointer_cast<ExpressionStatement>(program->Statements[0]);
		auto infix = static_pointer_cast<InfixExpression>(s->expression);
		auto left = static_pointer_cast<IntegerLiteral>(infix->left);
		auto right = static_pointer_cast<IntegerLiteral>(infix->right);

		if (left->value != test.left) {
			printf("[!] left->value != test.left, expected:%d, got:%d\n", test.left, left->value);
			return;
		}

		if (infix->operator_.compare(test.operator_) != 0) {
			printf("[!] infix->operator != test.operator_, expected:%s, got:%s\n", 
					infix->operator_.c_str(), test.operator_.c_str());
			return;
		}

		if (right->value != test.right) {
			printf("[!] right->value != test.right, expected:%d, got:%d\n", test.right, right->value);
			return;
		}

	}

	cout << "[*] test parse_infix_expression passed.\n";
}

void test_integer_literal() {
	string input = "69;";
	auto l = Lexer(input);
	auto p = Parser(l);
	auto program = p.parse_program();

	[[unlikely]]
	if (program->Statements.size() != 1) {
		cout << "[!] (program->Statements.size() != 1)\n";
		return;
	}

	auto s = static_pointer_cast<ExpressionStatement>(program->Statements[0]);
	auto lit = static_pointer_cast<IntegerLiteral>(s->expression);

	if (lit->value != 69) {
		cout << "[!] bad integer literal value!\n";
		return;
	}

	cout << "[*] test_integer_literal() passed.\n";
}

