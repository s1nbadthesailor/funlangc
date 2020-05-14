
#ifndef MEMORY_H
#define MEMORY_
#include <memory>
#endif

using namespace std;

class Lexer {
	string	input;

public:
	int			input_size;
	int			position;
	int			peek_pos;
	char		cur;

	void		read_byte();
	string		read_number();
	string		read_identifier();
	unique_ptr<Token> next_token();
	void		skip_whitespace();
	char		peek_byte();

	Lexer(string in) {
		this->input = in;
		this->input_size = in.length();
		this->position = 0;
		this->peek_pos = 0;
		this->read_byte();

		Token::initialize_maps();
	}
};
