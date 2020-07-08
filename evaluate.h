#pragma once

#include "object.h"
#include "ast.h"

FunObject* evaluate(AstNode* node);
FunObjecT* evaluate_expression(Expression* node);
FunObject* evaluate_program(Program* program);
