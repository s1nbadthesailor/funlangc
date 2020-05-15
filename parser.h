#pragma once
#include <vector>
#include <memory>

class Parser {
	public:
		Parser(Lexer& l) : lex(l) { 
			this->next_token(); 
			this->next_token();
		}
		unique_ptr<Token>		cur_token;
		unique_ptr<Token>		peek_token;
		void		next_token();
		bool		expect_peek(char type);
		bool		peek_is(char type);
		bool		cur_is(char type);
		unique_ptr<Program> parse_program();
		unique_ptr<Statement> parse_statement();
		unique_ptr<LetStatement> parse_let_statement();

	protected:
		Lexer& lex;
};

extern void test_parse_let();
