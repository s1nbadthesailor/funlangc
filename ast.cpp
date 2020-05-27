#include "ast.h"
#include "token.h"
using namespace std;
string ExpressionStatement::Literal() {
	return this->token->literal;
}

string ExpressionStatement::String() {
	if (this->expression) {
		return this->expression->String();
	}
	return "";
}


string PrefixExpression::Literal() {
	return this->token->literal;
}

string PrefixExpression::String() {
	string ret;

	ret += "(";
	ret += this->operator_;
	ret += this->right->String();
	ret += ")";

	return ret;
}


string Identifier::Literal() {
	return this->token->literal;
}

string Identifier::String() {
	return this->value;
}


string IntegerLiteral::Literal() {
	return this->token->literal;
}

string IntegerLiteral::String() {
	return this->token->literal;
}


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


string BlockStatement::Literal() {
	return this->token->literal;
}

string BlockStatement::String() {
	string ret;
	for (auto& s : this->statements) {
		ret += s->String();
	}
	return ret;
}


string FunctionLiteral::Literal() {
	return this->token->literal;
}

string FunctionLiteral::String() {
	string ret;

	ret += this->Literal();
	ret += "(";
	for (const auto& s : this->parameters) {
		ret += s->String();
		ret += ",";
	}
	ret += ")";
	ret += this->block->String();
	return ret;
}


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


string Boolean::Literal() {
	return this->token->literal;
}

string Boolean::String() {
	return this->token->literal;
}


string Program::String() {
	string ret;
	for (auto& s : Statements) {
		ret += s->String();
	}
	return ret;
}




