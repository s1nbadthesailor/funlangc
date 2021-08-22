#pragma once

#include "object.h"
#include "ast.h"

class Scope {
	public:
		std::map<std::string, FunValue> identity_map;
};


static std::map<std::string, std::shared_ptr<BlockStatement>> function_map;

class Evaluator {
	public:
		std::vector<Scope*> scope_stack;

		// I’m rich but I’m ridin’, I’m low on exotic
		void pop_scope() {
			scope_stack.pop_back();
			current_scope = scope_stack.back();
		}

		void push_scope(Scope* s) {
			scope_stack.push_back(s);
			current_scope = s;
		}

		Scope* global_scope = new Scope();
		Scope* current_scope;

		FunValue evaluate(AstNode* node);
		FunValue evaluate_expression(Expression* node);
		FunValue evaluate_intlit(IntegerLiteral* node);
		FunValue evaluate_prefix(std::string op, FunValue right);
		void evaluate_program(Program* program);

		Evaluator() {
			push_scope(global_scope);
		}
};
