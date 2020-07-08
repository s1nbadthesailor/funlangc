#include "ast.h"
#include "object.h"
#include "evaluate.h"
#include <stdio.h>
using namespace std;

// Evaluate recursively
FunObject* evaluate(AstNode* node) {
	switch (node->ast_type) {
		case AST_EXPRSTMT: {
//			evaluate(reinterpret_cast<AstNode>(node)->expression);
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
	auto stmts = program->Statements;
}
