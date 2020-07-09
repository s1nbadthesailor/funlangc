#pragma once

#include "object.h"
#include "ast.h"

FunValue evaluate(AstNode* node);
FunValue evaluate_expression(Expression* node);
FunValue evaluate_intlit(IntegerLiteral* node);
FunValue evaluate_prefix(std::string op, FunValue right);
void evaluate_program(Program* program);
