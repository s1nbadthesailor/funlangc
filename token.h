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
#define	TOK_HEX			97

#include <iostream>
#include <map>
#include <string>

using namespace std;
map<string, int> keyword_map;

class Token {
	
public:
	char	type;
	string	literal;

	static char	keyword_lookup(string ident);
	static void initialize_maps();

	Token(char t, string l) {
		this->type = t;
		this->literal = l;
	}

	Token() {
		this->type = 0;
		this->literal = string(""); 
	}
};

void Token::initialize_maps() {
	keyword_map["fn"] = TOK_FUNCTION;
	keyword_map["let"] = TOK_LET;
	keyword_map["if"] = TOK_IF;
	keyword_map["else"] = TOK_ELSE;
	keyword_map["while"] = TOK_WHILE;
	keyword_map["return"] = TOK_RETURN;
}

char Token::keyword_lookup(string ident) {
	char type;
	try {
		type = keyword_map.at(ident);
	}
	catch(exception e) {
		type = TOK_ID;
	}
	return type;
}

/*
typedef struct {
	char type;
	char* literal;

	Token(char t, char* l) {
		this->type = t;
		this->literal = l;
		
	}

	Token() {
		this->literal = NULL;
	}
} Token;
*/
