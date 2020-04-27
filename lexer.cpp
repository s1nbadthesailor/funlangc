#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>
#include <string.h>
#include "token.h"
#include "util.h"

#include <array>

typedef uint8_t uint8;

class Lexer {
	int			position;
	int			peek_pos;
	uint8		cur;
	char*		input;
	size_t		input_size;

	public:
		void		read_byte();
		char*		read_number();
		char*		read_identifier();
		void*		next_token();
		void		consume_whitespace();
		uint8		peek_byte();

	Lexer() {};
	Lexer(char* in) {
		this->input = in;
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

uint8 Lexer::peek_byte() {
	if (this->peek_pos >= this->input_size) {
		return 0;
	}
	else {
		return this->input[this->peek_pos];
	}
}

bool isLetter(uint8 c) {
	return 'a' <= c && c <= 'z' || 'A' <= c && c <= 'Z' || c == '_';
}

bool isDigit(uint8 c) {
	return '0' <= c && c <= '9';
}

char* Lexer::read_identifier() {
	int start = this->position;
	int c = 0;
	while (isLetter(this->cur) && c < 25) {
		++c;
		this->read_byte();
	}

	char* ident = (char*)malloc(c+1);
	memcpy(ident, this->input + start, c);
	ident[c] = '\0';
	printf("DEBUG: identifier: %s\n", ident);
	return ident;
}

void Lexer::consume_whitespace() {
	while (this->cur == ' ' || this->cur == '\t' || this->cur == '\n' || this->cur == '\r') {
		this->read_byte();
	}
}

char* Lexer::read_number() {
	int pos = this->position;
	while (isDigit(this->cur)) {
		this->read_byte();
	}
	auto g = std::copy(pos, this->position, std::array);
}

Token* allocate_token(void) {
	Token* t =(Token*) malloc(sizeof(Token));
	t->literal = (char*)malloc(32);
	bzero(t, sizeof(Token));
	bzero(t->literal, 32);
	return t;
}

void* Lexer::next_token() {
	Token* t = allocate_token();
	uint8 peek;
	this->consume_whitespace();
	switch (this->cur) {
		case '=':
			t->type = TOK_EQ;
			peek = this->peek_byte();
			if (peek == '=') {
				uint8 b = this->cur;
				this->read_byte();
				sprintf(t->literal, "%c%c", b, this->cur);
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
				uint8 b = this->cur;
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
				//t->type = token_map[this->cur];
			}
	}

	this->read_byte();
	return t;
}

int main(void) {
	char input[] = "();{}!=";
	Lexer l;
	/*
	Token* t = allocate_token();
	for (int i=0; i<l->input_size; i++) {
		t = l->next_token(l);
		switch(i) {
			case 0:
				if (t->type != TOK_LPAREN) {
					printf("bad type! expected lparen, got:%s", token_map[t->type]);
				}
		}

	}
	*/

}
