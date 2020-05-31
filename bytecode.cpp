#include <memory>
#include <cstdio>

#include "bytecode.h"
using namespace std;


void make_op(uint8_t opcode, std::vector<uint8_t>& operands) {
	vector<uint8_t> instruction;

	int instruction_len = 1;
	for (const auto& o : operands) {
		instruction_len += o;
	}

	instruction.reserve(instruction_len);
	instruction[0] = opcode;

	int width = 0;
	for (const auto& o : operands) {
	}

}

int main(void) {

}
