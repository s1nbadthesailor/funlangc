#include "token.h"
#include "lexer.h"


int main(void) {
	Token::initialize_maps();
	test_next_token();
}
