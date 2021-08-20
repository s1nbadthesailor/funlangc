#pragma once

#include "object.h"
#include "ast.h"

class Scope {
	std::map<std::string, FunValue> identity_map;
};

static std::map<std::string, FunValue> identity_map;
static std::map<std::string, std::shared_ptr<BlockStatement>> function_map;

class Evaluator {
	public:
		Scope current_scope;
		FunValue evaluate(AstNode* node);
		FunValue evaluate_expression(Expression* node);
		FunValue evaluate_intlit(IntegerLiteral* node);
		FunValue evaluate_prefix(std::string op, FunValue right);
		void evaluate_program(Program* program);
		Evaluator() {
		}
};
