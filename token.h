#pragma once 

#define TOK_SEMICOLON	59
#define TOK_LPAREN		40
#define	TOK_RPAREN		41
#define	TOK_LBRACE		123
#define	TOK_RBRACE		125
#define	TOK_COMMA		44
#define	TOK_PLUS		43
#define	TOK_MINUS		45
#define	TOK_SLASH		47
#define	TOK_ASTERISK	42
#define	TOK_LT			60
#define	TOK_GT			62

#define TOK_ILLEGAL		0
#define TOK_EOF			1
#define TOK_ID			2
#define TOK_INT			3
#define TOK_ASSIGN		4
#define	TOK_BANG		5
#define	TOK_EQ			6
#define TOK_NEQ			7
#define	TOK_FUNCTION	8
#define	TOK_LET			9
#define	TOK_VAR			10
#define	TOK_RETURN		11
#define	TOK_IF			12
#define	TOK_ELSE		13
#define	TOK_WHILE		14
#define	TOK_TRUE		15
#define	TOK_FALSE		16
#define	TOK_HEX			17

#include <iostream>
#include <map>
#include <string>

using namespace std;
static map<string, char> keyword_map;

class Token {
	public:
		char	type;
		string	literal;

		Token(char t, string l) {
			this->type = t;
			this->literal = l;
		}

		Token() {
			this->type = 0;
			this->literal = string(""); 
		}
};

extern void initialize_maps();
extern char keyword_lookup(string ident);
