#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "token.h"

typedef struct Lexer {
	void		(*read_byte)();
	void		(*peek_byte)();
	void		(*read_identifier)(void);
	int			position;
	int			peek_pos;
	uint8_t		cur;
	char*		input;
	size_t		input_size;
} Lexer __attribute__((packed));

void read_byte(Lexer* self) {
	if (self->peek_pos >= self->input_size) {
		self->cur = 0;
	}
	else {
		self->cur = self->input[self->peek_pos];
	}
	
	self->position = self->peek_pos;
	self->peek_pos++;
}

uint8_t peek_byte(Lexer* self) {
	if (self->peek_pos >= self->input_size) {
		return 0;
	}
	else {
		return self->input[self->peek_pos];
	}
}

bool isLetter(uint8_t c) {
	return 'a' <= c && c <= 'z' || 'A' <= c && c <= 'Z' || c == '_';
}

bool isDigit(uint8_t c) {
	return '0' <= c && c <= '9';
}

char* read_identifier(Lexer* self) {
	int pos = self->position;
	
	while (isLetter(self->cur)) {
		read_byte(self);
	}


}

void consume_whitespace(Lexer* self) {
	while (self->cur == ' ' || self->cur == '\t' || self->cur == '\n' || self->cur == '\r') {
		self->read_byte(self);
	}
}

char* read_number(Lexer* self) {
	int pos = self->position;
	while (isDigit(self->cur)) {
		self->read_byte(self);
	}
}

Token* allocate_token(uint8_t type, uint8_t byte) {
	Token* t = malloc(sizeof(Token));
	t->type = type;
}

Token* next_token(Lexer* self) {
	Token* t = NULL;
	uint8_t type, byte;
	self->consume_whitespace();
	switch (self->cur) {
		case ';':
			type = TOK_SEMICOLON;
			break;
		case '(':
			type = TOK_LPAREN;
			break;
		case ')':
			type = TOK_RPAREN;

	}
}

void main(void) {

}
