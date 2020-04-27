#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>
#include <string.h>
#include "token.h"
#include "util.h"

#include <array>
#include <iostream>
#include <map>
#include <string>

class Lexer {
	std::string	input;

public:
	int			input_size;
	int			position;
	int			peek_pos;
	char		cur;

	void		read_byte();
	string		read_number();
	string		read_identifier();
	Token		next_token();
	void		skip_whitespace();
	char		peek_byte();

	Lexer(string in) {
		this->input = in;
		this->input_size = input.length();
		this->read_byte();
	}
};

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
	int c = 0;
	while (isLetter(this->cur) && c < 25) {
		++c;
		this->read_byte();
	}

	return this->input.substr(start, c);
}

string Lexer::read_number() {
	int pos = this->position;
	int c = 0;
	while (isDigit(this->cur) && c < 25) {
		++c;
		this->read_byte();
	}

	return this->input.substr(pos, c);
}

Token Lexer::next_token() {
	Token t = Token();
	char peek;
	this->skip_whitespace();
	switch (this->cur) {
		case '=':
			t.type = TOK_EQ;
			peek = this->peek_byte();
			if (peek == '=') {
				char b = this->cur;
				this->read_byte();
				t.literal += b;
				t.literal += this->cur;
			}
			else {
				t.type = TOK_ASSIGN;
				t.literal += this->cur;
			}
			break;
		case '!':
			peek = this->peek_byte();
			if (peek == '=') {
				t.type = TOK_NEQ;
				char b = this->cur;
				this->read_byte();
				t.literal += b;
				t.literal += this->cur;
			}
			else {
				t.type = TOK_BANG;
				t.literal += this->cur;

			}
			break;
		case 0:
			t.type = TOK_EOF;
			break;
		default:
			if (isLetter(this->cur)) {
				t.literal = this->read_identifier();
				t.type = t.keyword_lookup(t.literal);
				return t;
			}
			else if (isDigit(this->cur)) {
				t.literal = this->read_number();
				t.type = TOK_INT;
				return t;
			}
			else {
				t.type = this->cur;
				t.literal += this->cur;
			}
	}

	this->read_byte();
	return t;
}

void test_next_token() {
	Token t = Token();
	char input[] = "()";
	Lexer l(input);
	Token tests[] = {
		Token(TOK_LPAREN, "("),
		Token(TOK_RPAREN, ")"),
	};

	for (const Token test : tests) {
		t = l.next_token();
		if (test.type != t.type) {
			printf("[!] mismatching types. expected:%d, got:%d\n", test.type, t.type);
		}

		if (test.literal != t.literal) {
			printf("[!] mismatching literals. expected:%c, got:%c\n", test.literal, t.literal);
		}
	}
}

int main(void) {
	test_next_token();
}

