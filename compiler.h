#pragma once

#include <vector>
#include <memory>
#include <unordered_map>
#include "object.h"
#include "ast.h"

class Compiler {
	public:
		std::vector<uint8_t> bytecode;
		std::unordered_map<std::string, FunValue> constants;
	
		Compiler(Program* p) : program(p) {}
		int compile_program();

	protected:
		Program* program;
};

class FunAssembler {
	public:
		FunAssembler() {}
		uint8_t* fasm(std::string mnem) {
			return (uint8_t*)NULL;
		}
};
