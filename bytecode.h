#pragma once

#ifndef CSTDINT_H
#include <cstdint>
#endif

#ifndef VECTOR_H
#include <vector>
#endif

#define FUNOP_CONSTANT

struct Instruction {
	uint64_t raw; // uniform-size opcodes? 
};

struct Definition {
	std::string name;
	std::vector<int> operand_widths;
};

void make_op(uint8_t opcode, std::vector<uint8_t>& operands);
