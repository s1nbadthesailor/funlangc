#include "ast.h"
#include "object.h"
#include "evaluate.h"
using namespace std;

FunValue Evaluator::evaluate(AstNode* node) {
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
		case AST_FNLIT: {
			auto fnlit = reinterpret_cast<FunctionLiteral*>(node);
			function_map[fnlit->identifier] = fnlit->block;
			break;
		}
		case AST_CALL: {
			auto call = reinterpret_cast<CallExpression*>(node);
			auto id = call->function->String();
			std::shared_ptr<BlockStatement> block = nullptr;
			try {
				block = function_map.at(id);
				// TODO: Enter a new scope here
				for (const auto s : block->statements) {
					evaluate(s.get());
				}
			}
			catch(exception e) {
			}
			break;
		}
		case AST_INFIX: {
			auto infix = reinterpret_cast<InfixExpression*>(node);
			auto left = evaluate(infix->left.get());
			auto right = evaluate(infix->right.get());
			auto op = infix->operator_;
			
			if (!op.compare("+")) {
				return left + right;
			}

			if (!op.compare("-")) {
				return left - right;
			}

			if (!op.compare("*")) {
				return left * right;
			}

			if (!op.compare("/")) {
				if (!right) {
					return 0;
				}
				return left / right;
			}
			break;
		}
		case AST_LET: { 
			auto let = reinterpret_cast<LetStatement*>(node);
			auto right = evaluate(let->value.get());
			identity_map[let->ident->value] = right;
			break;
		}
		default:
			return 0;
	}

	return 0;
}

FunValue Evaluator::evaluate_intlit(IntegerLiteral* node) {
	FunValue obj = Value(node->value).getInt32();
	return obj;
}

FunValue Evaluator::evaluate_prefix(string op, FunValue right) {
	if (!op.compare("!")) {
		return !right;
	}
	if (!op.compare("++")) {
		right++;
		return right;
	}
}

void Evaluator::evaluate_program(Program* program) {
	for (auto s : program->Statements) {
		FunValue e = evaluate(s.get());
	}

	printf("x: %d y: %d\n", identity_map["x"], identity_map["y"]);
}
