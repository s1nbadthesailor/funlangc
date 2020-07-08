#include "ast.h"
#include "object.h"
#include "evaluate.h"

// Evaluate recursively
FunValue evaluate(AstNode* node) {
	switch (node->ast_type) {
		case AST_EXPRSTMT: {
			evaluate(reinterpret_cast<ExpressionStatement*>(node)->expression.get());
			break;
	    }
		case AST_INTLIT: {
			return evaluate_intlit(reinterpret_cast<IntegerLiteral*>(node));		
			break;
	 	}
		default:
			return NULL;
	}
}

FunValue evaluate_intlit(IntegerLiteral* node) {
	FunValue obj = fun_allocate(VAL_NUM);
}
	

FunValue evaluate_program(Program* program) {
	for (auto s : program->Statements) {
		evaluate(s.get());
	}

}
