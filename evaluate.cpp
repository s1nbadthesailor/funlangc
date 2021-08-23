#include "ast.h"
#include "object.h"
#include "evaluate.h"
using namespace std;

FunValue Evaluator::scoped_lookup(std::string ident, Scope* s) {
	FunValue val = 0;
	try {
		val = s->identity_map.at(ident);
	}
	catch(exception e) {
		return 0;
	}
}

FunValue Evaluator::scoped_lookup(std::string ident) {
	FunValue val = 0;
	try {
		val = this->current_scope->identity_map.at(ident);
	}
	catch(exception e) {
		return 0;
	}
}

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
			fnlit_map[fnlit->identifier] = fnlit;

			auto new_scope = new Scope();
			for (const auto p: fnlit->parameters) {
			// Pull the variables into this function's 'template scope'
				new_scope->add_identifier(p->value);
			}
			// Set this function's template scope
			scope_map[fnlit->identifier] = new_scope;
			break;
		}
		case AST_RETURN: {
			// Probably exit scope here?
			auto ret = reinterpret_cast<ReturnStatement*>(node);
			return evaluate(ret->value.get());
		}

		// Shouldn't push the scope here unless we can know if we
		// are in an IfExpression :)
		// Maybe we can search for the fnlit in the fnlit_map but it's fucking slow
		// I mean this shit is already slow af lmao, we need a compiler dammit
		case AST_BLOCK: {
			auto block = reinterpret_cast<BlockStatement*>(node);
			FunValue ret = 0;
			for (const auto s : block->statements) {
				[[unlikely]]
				if (s->ast_type == AST_RETURN) {
					ret = evaluate(s.get());
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
		case AST_CALL: {
			auto call = reinterpret_cast<CallExpression*>(node);
			auto id = call->function->String();
			auto args = call->arguments;
			auto scope = scope_map[id];
			auto fnlit = fnlit_map[id];

			FunValue ret = 0;

			// Bring the arguments into block's scope
			std::shared_ptr<BlockStatement> block = nullptr;
			
			if (args.size() > fnlit->parameters.size()) {
				std::cout << "too many parameters passed to function literal\n";
				break;
			}

			for (unsigned i = 0; i < args.size(); i++) {
				scope->add_identifier(fnlit->parameters[i]->value, evaluate(args[i].get()));
			}

			// Lookup this function's template scope and push it
			push_scope(scope);
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
				return left <= right;
			}

			if (!op.compare(">=")) {
				return left >= right;
			}

			if (!op.compare("==")) {
				return left == right;
			}

			if (!op.compare("!=")) {
				return left != right;
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


