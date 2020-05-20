#pragma once
using namespace std;
#include <vector>
#include <memory>

class AstNode {
	public:
		virtual	string Literal() = 0;
		virtual string String() = 0;
};


class Statement: public AstNode {
	public:
};


class Expression: public Statement {
	public:
		char type;
};


class ExpressionStatement : public Expression {
	public:
		string Literal() override;
		string String() override;
		std::unique_ptr<Token> token;
		std::shared_ptr<Expression> expression;
};

string ExpressionStatement::Literal() {
	return this->token->literal;
}

string ExpressionStatement::String() {
	if (this->expression) {
		return this->expression->String();
	}
	return "";
}

class PrefixExpression : public Expression {
	public:
		string Literal() override;
		string String() override;
		std::unique_ptr<Token> token;
		string operator_;
		shared_ptr<Expression> right;
};

string PrefixExpression::Literal() {
	return this->token->literal;
}

string PrefixExpression::String() {
	string ret;

	ret += "(";
	ret += this->operator_;
	ret += this->right->String();
	ret += ")";
	ret += ";";

	return ret;
}

// Statement?
class Identifier: public Expression {
	public:
		string Literal() override;
		string String() override;
		std::unique_ptr<Token> token;
		string	value;
};

string Identifier::Literal() {
	return this->token->literal;
}

string Identifier::String() {
	return this->value;
}


class IntegerLiteral: public Expression {
	public:
		string Literal() override;
		string String() override;
		unique_ptr<Token> token;
		int	value;
};

string IntegerLiteral::Literal() {
	return this->token->literal;
}

string IntegerLiteral::String() {
	return this->token->literal;
}


class LetStatement: public Statement {
	public:
		string Literal() override;
		string String() override;
		shared_ptr<Token> token;
		unique_ptr<Identifier> ident;
		unique_ptr<Expression>	value;	

		LetStatement() {};
};

string LetStatement::Literal() {
	return this->token->literal;
}

string LetStatement::String() {
	string ret;
	ret += this->Literal();
	ret += " ";
	ret += this->ident->value;
	ret += " = ";
	
	if (this->value) {
		ret += this->value->String();
	}

	return ret;
}


class ReturnStatement: public Statement {
	public:
		string Literal() override;
		string String() override;
		unique_ptr<Token> token;
		unique_ptr<Expression> value;
};

string ReturnStatement::Literal() {
	return this->token->literal;
}

string ReturnStatement::String() {
	string ret;

	ret += this->token->literal;
	ret += " ";
	ret += this->value->String();

	return ret;
}


class BlockStatement : public Expression {
	public:
		string Literal() override;
		string String() override;
		unique_ptr<Token> token;
		vector<shared_ptr<Statement>> stmts;
};

string BlockStatement::Literal() {
	return this->token->literal;
}

string BlockStatement::String() {
	string ret;
	for (auto& s : this->stmts) {
		ret += s->String();
	}
	return ret;
}

class FunctionLiteral : public Expression {
	public:
		string Literal() override;
		string String() override;
		unique_ptr<Token> token;
		vector<unique_ptr<Identifier>> parameters;
		shared_ptr<BlockStatement> block;
};

string FunctionLiteral::Literal() {
	return this->token->literal;
}

string FunctionLiteral::String() {
	string ret;

	ret += this->Literal();
	ret += "(";
	for (auto& s : this->parameters) {
		ret += s->String();
		ret += ",";
	}
	ret += ")";
	ret += this->block->String();
	return ret;
}


class InfixExpression : public Expression {
	public:
		string Literal() override;
		string String() override;
		unique_ptr<Token> token;
		shared_ptr<Expression> left;
		string operator_;
		shared_ptr<Expression> right;
};

string InfixExpression::Literal() {
	return this->token->literal;
}

string InfixExpression::String() {
	string ret;

	ret += "(";
	ret += this->left->String();
	ret += " ";
	ret += this->operator_;
	ret += " ";
	ret += this->right->String();
	ret += ")";

	return ret;
}

class Boolean : public Expression {
	public:
		string Literal() override;
		string String() override;
		unique_ptr<Token> token;
		bool value;
};

string Boolean::Literal() {
	return this->token->literal;
}

string Boolean::String() {
	return this->token->literal;
}

class Program {
	public:
		vector<shared_ptr<Statement>> Statements;
		string String();
};

string Program::String() {
	string ret;
	for (auto& s : Statements) {
		ret += s->String();
	}
	return ret;
}
