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
			break;
		}
		case AST_FNLIT: {
			auto fnlit = reinterpret_cast<FunctionLiteral*>(node);
			function_map[fnlit->identifier] = fnlit->block;
			break;
		}
		case AST_RETURN: {
			// Probably exit scope here?
			auto ret = reinterpret_cast<ReturnStatement*>(node);
			return evaluate(ret->value.get());
		}
		case AST_BLOCK: {
			auto block = reinterpret_cast<BlockStatement*>(node);
			FunValue ret = 0;
			push_scope(new Scope());
			for (const auto s : block->statements) {
				[[unlikely]]
				if (s->ast_type == AST_RETURN) {
					ret = evaluate(s.get());
					pop_scope();
					return ret;
				}
				evaluate(s.get());
			}
			break;
		}
		case AST_IDENT: {
			return current_scope->identity_map[reinterpret_cast<Identifier*>(node)->value];
		}
		case AST_IF: {
			auto if_exp = reinterpret_cast<IfExpression*>(node);
			auto condition = evaluate(if_exp->condition.get());
			if (condition) {
				return evaluate(if_exp->consequence.get());
			} 
			else if (if_exp->alternative) {
				return evaluate(if_exp->alternative.get());
			}
			break;
		}
		case AST_GROUP: {
//			std::cout << "ast_group\n";
//			evaluate(node);
			break;
		}
		case AST_CALL: {
			auto call = reinterpret_cast<CallExpression*>(node);
			auto id = call->function->String();
			auto args = call->arguments;
			FunValue ret = 0;
			// Bring the arguments into block's scope
			std::shared_ptr<BlockStatement> block = nullptr;
			
			push_scope(new Scope());

			try {
				block = function_map.at(id);
				// TODO: Enter a new scope here
				for (auto s : block->statements) {
					[[unlikely]]
					if (s->ast_type == AST_RETURN) {
						ret = evaluate(s.get());
						pop_scope();
						return ret;
					}
					evaluate(s.get());
				}
				pop_scope();
			}
			catch(exception e) {
				std::cout << "[evaluate] ast_call\n";
				pop_scope();
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

			if (!op.compare("<=")) {
				printf("left: %d right: %d\n", left, right);
				return left <= right;
			}

			if (!op.compare(">=")) {
				return left >= right;
			}
			break;
		}
		case AST_LET: { 
			auto let = reinterpret_cast<LetStatement*>(node);
			auto right = evaluate(let->value.get());
			current_scope->identity_map[let->ident->value] = right;
			break;
		}
		case AST_BOOL: {
			return reinterpret_cast<Boolean*>(node)->value;
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

	printf("x: %d y: %d g: %d z: %d\n", global_scope->identity_map["x"], global_scope->identity_map["y"], global_scope->identity_map["g"], global_scope->identity_map["z"]);
}


