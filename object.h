#pragma once

typedef enum {
	FUN_FN,
	FUN_STRING,
	FUN_UPVALUE
} HeapType;

typedef enum {
	VAL_NULL,
	VAL_TRUE,
	VAL_FALSE,
	VAL_NUM,
	VAL_UNDEFINED
} FunType;

class HeapObj {
	HeapType type;
};

class FunValue {
	FunType type;
	struct {
		HeapObj* obj;
		double num;
	} value;
};

