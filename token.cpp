#include "token.h"
using namespace std;

void initialize_keyword_map() {
	keyword_map["fn"] = TOK_FUNCTION;
	keyword_map["let"] = TOK_LET;
	keyword_map["if"] = TOK_IF;
	keyword_map["else"] = TOK_ELSE;
	keyword_map["while"] = TOK_WHILE;
	keyword_map["return"] = TOK_RETURN;
}

char keyword_lookup(string ident) {
	char type;
	try {
		type = keyword_map.at(ident);
	}
	catch(exception e) {
		type = TOK_ID;
	}
	return type;
}
