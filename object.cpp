#include "object.h"

FunValue* fun_allocate(FunType type) {
	FunValue* obj = (FunValue*) std::malloc(sizeof(FunObject));
	return obj;
}
