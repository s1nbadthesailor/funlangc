#ifndef VECTOR_H
#define VECTOR_H
#include <vector>
#endif

#ifndef MEMORY_H
#define MEMORY_H
#include <vector>
#endif


#ifndef AST_H
#define	AST_H
#include "ast.h"
#endif

class Parser {
	public:
		Parser(Lexer& l) : lex(l){}
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

