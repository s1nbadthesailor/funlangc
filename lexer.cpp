#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>
#include <string.h>

#include "token.h"
#include "lexer.h"

#include <array>
#include <iostream>
#include <map>
#include <string>
#include <memory>

#define		MAX_ID_LEN		25
#define		MAX_INT_LEN		8

using namespace std;

void Lexer::read_byte() {
	if (this->peek_pos >= this->input_size) {
		this->cur = 0;
	}
	else {
		this->cur = this->input[this->peek_pos];
	}
	
	this->position = this->peek_pos;
	this->peek_pos++;
}

char Lexer::peek_byte() {
	if (this->peek_pos >= this->input_size) {
		return 0;
	}
	else {
		return this->input[this->peek_pos];
	}
}

bool isLetter(char c) {
	return 'a' <= c && c <= 'z' || 'A' <= c && c <= 'Z' || c == '_';
}

bool isDigit(char c) {
	return '0' <= c && c <= '9';
}

void Lexer::skip_whitespace() {
	while (this->cur == ' ' || this->cur == '\t' || this->cur == '\n' || this->cur == '\r') {
		this->read_byte();
	}
}

string Lexer::read_identifier() {
	int start = this->position;
	for (int i = 0; isLetter(this->cur) && i < MAX_ID_LEN; i++) {
		this->read_byte();
	}

	return this->input.substr(start, this->position - start);
}

string Lexer::read_number() {
	int start = this->position;
	for (int i = 0; isDigit(this->cur) && i < MAX_INT_LEN; i++) {
		this->read_byte();
	}
	return this->input.substr(start, this->position - start);
}

unique_ptr<Token> Lexer::next_token() {
	auto t = make_unique<Token>(Token());
	char peek;
	this->skip_whitespace();
	switch (this->cur) {
		case '=':
			peek = this->peek_byte();
			if (peek == '=') {
				char b = this->cur;
				this->read_byte();
				t->type = TOK_EQ;
				t->literal += b;
				t->literal += this->cur;
			}
			else {
				t->type = TOK_ASSIGN;
				t->literal += this->cur;
			}
			break;
		case '!':
			peek = this->peek_byte();
			if (peek == '=') {
				t->type = TOK_NEQ;
				char b = this->cur;
				this->read_byte();
				t->literal += b;
				t->literal += this->cur;
			}
			else {
				t->type = TOK_BANG;
				t->literal += this->cur;
			}
			break;
		case 0:
			t->type = TOK_EOF;
			break;
		default:
			if (isLetter(this->cur)) {
				t->literal = this->read_identifier();
				t->type = keyword_lookup(t->literal);
				return std::move(t);
			}
			else if (isDigit(this->cur)) {
				t->literal = this->read_number();
				t->type = TOK_INT;
				return std::move(t);
			}
			else {
				// This is a fun 'hack', but it's not correct.
				t->type = this->cur;
				t->literal += this->cur;
			}
	}

	this->read_byte();
	return std::move(t);
}

void test_next_token() {
	string input = "let banana = 1337;\n!===";
	Lexer l(input);

	Token tests[] = {
		Token(TOK_LET, "let"),
		Token(TOK_ID, "banana"),
		Token(TOK_ASSIGN, "="),
		Token(TOK_INT, "1337"),
		Token(TOK_SEMICOLON, ";"),
		Token(TOK_NEQ, "!="),
		Token(TOK_EQ, "==")
	};

	for (const Token test : tests) {
		auto t = l.next_token();
		if (test.type != t->type) {
			printf("[!] mismatching types. expected:%d, got:%d\n", test.type, t->type);
			return;
		}

		if (test.literal != t->literal) {
			printf("[!] mismatching literals. expected:%s, got:%s\n", test.literal.c_str(), t->literal.c_str());
			return;
		}
	}

	printf("[*] test_next_token() passed.\n");
}

int main() {
	test_next_token();
}
