class AstNode {
	public:
		virtual	string TokenLiteral();
}

class Expression: public AstNode {

}

class Statement: public AstNode {

}

class LetStatement: public Statement {

}
