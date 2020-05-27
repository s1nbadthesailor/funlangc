#pragma once
#include <memory>

class Lexer {
	std::string	input;

public:
	int			input_size;
	int			position;
	int			peek_pos;
	char		cur;

	void		read_byte();
	std::string		read_number();
	std::string		read_identifier();
	std::shared_ptr<Token> next_token();
	void		skip_whitespace();
	char		peek_byte();

	Lexer(std::string in) {
		this->input = in;
		this->input_size = in.length();
		this->position = 0;
		this->peek_pos = 0;
		this->read_byte();
	}
};

extern void test_next_token();
