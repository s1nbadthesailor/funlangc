#include "ast.h"
#include "object.h"
#include "evaluate.h"
using namespace std;

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
		case AST_PREFIX: {
			auto right = evaluate(reinterpret_cast<PrefixExpression*>(node)->right.get());
			return evaluate_prefix(reinterpret_cast<PrefixExpression*>(node)->operator_, right); 
		}
		default:
			return 0;
	}
}

FunValue evaluate_intlit(IntegerLiteral* node) {
	FunValue obj = Value(node->value).getDouble();
	return obj;
}

FunValue evaluate_prefix(string op, FunValue right) {
	if (op.compare("!") == 0) {

	}
}

void evaluate_program(Program* program) {
	for (auto s : program->Statements) {
		FunValue e = evaluate(s.get());
		if (e.isInt32()) {
			cout << e.getInt32() << "\n";
		}
	}
}
