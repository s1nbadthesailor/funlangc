#include <cstdint>

class Instruction {
	string name;
	vector<int> operand_widths;
	uint64_t raw; // uniform-size opcodes? 
};
