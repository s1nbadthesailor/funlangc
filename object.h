#pragma once

#include <cstdlib>

typedef enum {
	FUN_FN,
	FUN_STRING,
	FUN_UPVALUE
} HeapType;

typedef enum {
	VAL_NULL,
	VAL_BOOL,
	VAL_NUM,
	VAL_UNDEFINED,
	VAL_OBJ
} FunType;

typedef struct {
	HeapType type;
} Obj;

typedef struct {
	FunType type;
	struct {
		Obj* obj;
		double num;
	} v;
} FunObject;

FunObject* fun_allocate(FunType type); 
