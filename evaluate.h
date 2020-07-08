#pragma once

#include "object.h"
#include "ast.h"

FunObject* evaluate(AstNode* node);
FunObject* evaluate_expression(Expression* node);
FunObject* evaluate_program(Program* program);
FunObject* evaluate_intlit(IntegerLiteral* node);
