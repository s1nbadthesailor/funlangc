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
		char*		read_number();
		char*		read_identifier();
		Token*		next_token();
		void		skip_whitespace();
		char		peek_byte();

	Lexer() {};
	Lexer(char* in) {
		this->input = in;
		this->input_size = input.length();
		this->next_token();
		this->next_token();
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

char* Lexer::read_identifier() {
	int start = this->position;
	int c = 0;
	while (isLetter(this->cur) && c < 25) {
		++c;
		this->read_byte();
	}

	return const_cast<char*>(this->input.substr(start, c).c_str()); // Am I doing C++ right?
}

void Lexer::skip_whitespace() {
	while (this->cur == ' ' || this->cur == '\t' || this->cur == '\n' || this->cur == '\r') {
		this->read_byte();
	}
}

char* Lexer::read_number() {
	int pos = this->position;
	int c = 0;
	while (isDigit(this->cur) && c < 25) {
		++c;
		this->read_byte();
	}

	auto g = this->input.substr(pos, c);
	return const_cast<char*>(g.c_str());
}

Token* allocate_token(void) {
	Token* t = (Token*)malloc(sizeof(Token));
	t->literal = (char*)malloc(32);
	return t;
}

Token* Lexer::next_token() {
	Token* t = allocate_token();
	char peek;
	this->skip_whitespace();
	switch (this->cur) {
		case '=':
			t->type = TOK_EQ;
			peek = this->peek_byte();
			if (peek == '=') {
				char b = this->cur;
				this->read_byte();
				sprintf(t->literal, "%c%c", b, this->cur);
				printf("hit literal");
			}
			else {
				t->type = TOK_ASSIGN;
				sprintf(t->literal, "%c", this->cur);
			}
			break;
		case '!':
			peek = this->peek_byte();
			if (peek == '=') {
				t->type = TOK_NEQ;
				char b = this->cur;
				this->read_byte();
				sprintf(t->literal, "%c%c", b, this->cur);
			}
			else {
				t->type = TOK_BANG;
				sprintf(t->literal, "%c", this->cur);
			}
			break;
		case 0:
			t->type = TOK_EOF;
			break;
		default:
			if (isLetter(this->cur)) {
				t->literal = this->read_identifier();
				t->type = TOK_ID;
				return t;
			}
			else if (isDigit(this->cur)) {
				t->literal = this->read_number();
				t->type = TOK_INT;
				return t;
			}
			else {
				printf("this cur: %c\n", this->cur);
				t->type = this->cur;
				sprintf(t->literal, "%c", this->cur);
			}
	}

	this->read_byte();
	return t;
}

int main(void) {

	Token* t = NULL;
	char input[] = "{}()";
	Lexer l(input);
	t = l.next_token();
	for (int i=0; i < l.input_size; i++) {
		switch(i) {
			case 0:
				if (t->type != TOK_LPAREN) {
					printf("bad type! expected lparen. got=%d", t->type);
				}
			case 1:
				if (t->type != TOK_RPAREN) {
					printf("bad type! expected rparen. got=%d", t->type);
				}

		}
		t = l.next_token();
	}
}

