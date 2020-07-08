#include "object.h"

FunObject* fun_allocate(FunType type) {
	FunObject* obj = (FunObject*) std::malloc(sizeof(FunObject));
	return obj;
}
