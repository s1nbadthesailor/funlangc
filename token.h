#define TOK_SEMICOLON	0
#define TOK_LPAREN		1
#define	TOK_RPAREN		2
#define	TOK_LBRACE		3
#define	TOK_RBRACE		4
#define	TOK_COMMA		5
#define	TOK_PLUS		6
#define	TOK_MINUS		7
#define	TOK_SLASH		8
#define	TOK_ASTERISK	9
#define	TOK_LT			10
#define	TOK_GT			11

#define TOK_ILLEGAL		12
#define TOK_EOF			13
#define TOK_ID			14
#define TOK_INT			15
#define TOK_ASSIGN		16
#define	TOK_BANG		17
#define	TOK_EQ			18
#define TOK_NEQ			19
#define	TOK_FUNCTION	20
#define	TOK_LET			21
#define	TOK_VAR			22
#define	TOK_RETURN		23
#define	TOK_IF			24
#define	TOK_ELSE		25
#define	TOK_WHILE		26
#define	TOK_TRUE		27
#define	TOK_FALSE		28
using namespace std;
const char* token_map[100] = {";", "(", ")", "{", "}", ",", "+", "-", "/", "*", "<", ">"};

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
