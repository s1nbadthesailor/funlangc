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

#define TOK_ILLEGAL		1337
#define TOK_EOF			1338
#define TOK_ID			1339
#define TOK_INT			1340
#define TOK_ASSIGN		1341
#define	TOK_BANG		1342
#define	TOK_EQ			1343
#define TOK_NEQ			1344
#define	TOK_FUNCTION	1345
#define	TOK_LET			1346
#define	TOK_VAR			1347
#define	TOK_RETURN		1348
#define	TOK_IF			1349
#define	TOK_ELSE		1350
#define	TOK_WHILE		1351
#define	TOK_TRUE		1352
#define	TOK_FALSE		1353

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
