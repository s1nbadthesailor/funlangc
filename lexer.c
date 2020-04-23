#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


typedef struct Lexer {
	void		(*read_byte)();
	void		(*peek_byte)();
	void		(*read_identifier)(void);
	int			position;
	int			peek_pos;
	char		byte;
	char*		input;
	size_t		input_size;
} Lexer __attribute__((packed));

void read_byte(Lexer* self) {
	if (self->peek_pos >= self->input_size) {
		self->byte = 0;
	}
	else {
		self->byte = self->input[self->peek_pos];
	}
	
	self->position = self->peek_pos;
	self->peek_pos++;
}

char peek_byte(Lexer* self) {
	if (self->peek_pos >= self->input_size) {
		return 0;
	}
	else {
		return self->input[self->peek_pos];
	}
}

uint8_t isLetter(char byte) {
	return 'a' <= byte && byte <= 'z' || 'A' <= byte && byte <= 'Z' || byte == '_';
}

char* read_identifier(Lexer* self) {
	int pos = self->position;
	while (isLetter(self->byte)) {
		self->read_byte(self);
	}
}

void main(void) {

}
