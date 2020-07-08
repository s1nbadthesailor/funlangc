#include "ast.h"
#include "object.h"
#include "evaluate.h"
#include <stdio.h>
using namespace std;

// Evaluate recursively
FunObject* evaluate(AstNode* node) {
	switch (node->ast_type) {
		case AST_EXPRSTMT: {
			evaluate_
			break;
	    }
		case AST_INTLIT: {
			break;
	 	}
		default:
			return NULL;
	}
}

FunObject* evaluate_program(Program* program) {
	for (auto s : program->Statements) {
		evaluate(s.get());
	}

}
