#pragma once

#include "object.h"
#include "ast.h"

FunValue evaluate(AstNode* node);
FunValue evaluate_expression(Expression* node);
FunValue evaluate_program(Program* program);
FunValue evaluate_intlit(IntegerLiteral* node);
