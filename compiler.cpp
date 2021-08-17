#include "compiler.h"

int Compiler::compile_program() {
	for (auto stmt : this->program->Statements) {
		auto ast_type = static_cast<std::shared_ptr<AstNode>>(stmt)->ast_type;
		switch (ast_type) {
			case AST_EXPRESSION:
				break;
			case AST_INFIX:
				break;
			default:
				std::cout << "[Compiler::compile_program] unknown ast type" << '\n';
				break;
		}
	}
}
