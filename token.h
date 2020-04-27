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

#define TOK_ILLEGAL		80
#define TOK_EOF			81
#define TOK_ID			82
#define TOK_INT			83
#define TOK_ASSIGN		84
#define	TOK_BANG		85
#define	TOK_EQ			86
#define TOK_NEQ			87
#define	TOK_FUNCTION	88
#define	TOK_LET			89
#define	TOK_VAR			90
#define	TOK_RETURN		91
#define	TOK_IF			92
#define	TOK_ELSE		93
#define	TOK_WHILE		94
#define	TOK_TRUE		95
#define	TOK_FALSE		96

#include <iostream>
#include <map>
#include <string>

using namespace std;
map<char*, int> keyword_map;
/*
class Token {
		char	type;
		char*	literal;
};
*/
typedef struct {
	char type;
	char* literal;
} Token;
