#include "token.h"
#include "ast.h"
#include "lexer.h"
#include "parser.h"
#include <memory>
#include <typeinfo>
using namespace std;

#define PARSER_PEEK_IS(t) (this->peek_token->type == t)
#define PARSER_CUR_IS(t)  (this->cur_token->type == t)

void Parser::add_parser_error(string s) {
	string error;
	error += "[!] ";
	error += s;
	error += "\n";
	this->errors.push_back(error);
}

void Parser::show_parser_errors() {
	if (this->errors.size() == 0) {
		return;
	}
	else {
		for (const auto s : this->errors) {
			cout << s;
		}
	}
}

void Parser::next_token() {
	this->cur_token = this->peek_token;
	this->peek_token = this->lex.next_token();
}

char Parser::expect_peek(char type) {
	if (PARSER_PEEK_IS(type)) {
		next_token();
		return true;
	}
	else {
		return false;
	}
}

char Parser::peek_precedence() {
	try {
		return precedence_map.at(this->peek_token->type);
	} catch (exception e) {
		return PREC_LOWEST;
	}
}

char Parser::cur_precedence() {
	try {
		return precedence_map.at(this->cur_token->type);
	} catch (exception e) {
		return PREC_LOWEST;
	}
}

unique_ptr<Program> Parser::parse_program() {
	auto p = std::make_unique<Program>(Program());

	while (this->cur_token->type != TOK_EOF) {
		auto statement = this->parse_statement();
		if (statement != nullptr) {
			p->Statements.push_back(std::move(statement));
		}
		this->next_token();
	}

	return std::move(p);
}

shared_ptr<Statement> Parser::parse_statement() {
	switch (this->cur_token->type) {
		case TOK_LET:
			return this->parse_let_statement();
		case TOK_RETURN:
			return this->parse_return_statement();
		default:
			return this->parse_expression_statement();
	}
}

unique_ptr<LetStatement> Parser::parse_let_statement() {
 	auto let = std::make_unique<LetStatement>(LetStatement());
	let->token = this->cur_token;

	if (!this->expect_peek(TOK_ID)) {
		return NULL;
	}

	auto id = std::make_unique<Identifier>(Identifier());
	id->token = this->cur_token;
	id->value = id->token->literal;
	let->ident = std::move(id);

	if (!this->expect_peek(TOK_ASSIGN)) {
		return NULL;
	}

	this->next_token();
	let->value = this->parse_expression(PREC_LOWEST);

	if (PARSER_PEEK_IS(TOK_SEMICOLON)) {
		this->next_token();
	}

	return std::move(let);
}

shared_ptr<ReturnStatement> Parser::parse_return_statement() {
	auto ret = std::make_shared<ReturnStatement>(ReturnStatement());
	ret->ast_type = AST_RETURN;
	ret->token = this->cur_token;
	this->next_token();
	ret->value = this->parse_expression(PREC_LOWEST);
	if (PARSER_PEEK_IS(TOK_SEMICOLON)) {
		this->next_token();
	}

	return ret;
}

unique_ptr<ExpressionStatement> Parser::parse_expression_statement() {
	auto expr = std::make_unique<ExpressionStatement>(ExpressionStatement());
	expr->ast_type = AST_EXPRSTMT;
	expr->token = this->cur_token;
	expr->expression = this->parse_expression(PREC_LOWEST);

	if (PARSER_PEEK_IS(TOK_SEMICOLON)) {
		this->next_token();
	}

	return std::move(expr);
}

unique_ptr<Identifier> Parser::parse_identifier() {
	auto id = std::make_unique<Identifier>(Identifier());
	id->token = this->cur_token;
	id->value = id->token->literal;
	id->ast_type = AST_IDENT;
	return std::move(id);
}

// bp: binding power or 'precedence'
// TODO: refactor this to use jumptables
shared_ptr<Expression> Parser::parse_expression(char bp) {
	
	shared_ptr<Expression> left_expr = nullptr;
	shared_ptr<Expression> infix = nullptr;

	switch (this->cur_token->type) {
		case TOK_ID: 
			left_expr = parse_identifier();
			left_expr->ast_type = AST_IDENT;
			break;
		
		case TOK_FUNCTION: 
			left_expr = parse_function_literal();
			left_expr->ast_type = AST_FNLIT;
			break;
	  	
		case TOK_INT: 
			left_expr = parse_integer_literal();
			left_expr->ast_type = AST_INTLIT;
			break;
		
		case TOK_MINUS:
		case TOK_BANG: 
			left_expr = parse_prefix_expression();
			left_expr->ast_type = AST_PREFIX;
			break;
		
		case TOK_IF: 
			left_expr = parse_if_expression();
			left_expr->ast_type = AST_IF;
			break;
	 	
		case TOK_LPAREN: 
			left_expr = parse_grouped_expression();
			left_expr->ast_type = AST_GROUP;
			break;
	 	
		case TOK_TRUE: 
		case TOK_FALSE: 
			left_expr = parse_boolean();
			left_expr->ast_type = AST_BOOL;
			break;
		
		default:
			cout << "in parse_expression: no prefix parse function for " << this->cur_token->literal << "\n";
			return nullptr;
	}

	while ((!(PARSER_PEEK_IS(TOK_SEMICOLON))) && bp < this->peek_precedence()) {
		switch (this->peek_token->type) {
			case TOK_PLUS:
			case TOK_MINUS:
			case TOK_SLASH:
			case TOK_ASTERISK:
			case TOK_EQ:
			case TOK_NEQ:
			case TOK_LT:
			case TOK_GT: 
				this->next_token();
				left_expr = parse_infix_expression(left_expr);
				left_expr->ast_type = AST_INFIX;
				break;

			case TOK_LPAREN: 
				this->next_token();
				left_expr = parse_call_expression(left_expr);
				left_expr->ast_type = AST_CALL;
				break;

			default:
				return left_expr;
		}
	}

	return left_expr;
}

shared_ptr<Expression> Parser::parse_grouped_expression() {
	shared_ptr<Expression> expr = nullptr;
	this->next_token();
	expr = this->parse_expression(PREC_LOWEST);
	if (expr == nullptr) {
		add_parser_error("got null expression");
		return nullptr;
	}
	if (!this->expect_peek(TOK_RPAREN)) {
		add_parser_error("expected TOK_RPAREN");
		return nullptr;
	}
	return expr;
}

unique_ptr<InfixExpression> Parser::parse_infix_expression(shared_ptr<Expression> left_expr) {
	auto expr = make_unique<InfixExpression>(InfixExpression());
	expr->token = this->cur_token;
	expr->operator_ = this->cur_token->literal;
	expr->left = left_expr;

	char prec = this->cur_precedence();
	this->next_token();
	expr->right = this->parse_expression(prec);
	return std::move(expr);
}

unique_ptr<Expression> Parser::parse_prefix_expression() {
	auto expr = make_unique<PrefixExpression>(PrefixExpression());
	expr->token = cur_token;
	expr->operator_ = expr->token->literal;
	
	this->next_token();
	expr->right = this->parse_expression(PREC_PREFIX);
	return std::move(expr);
}

shared_ptr<IntegerLiteral> Parser::parse_integer_literal() {
	auto lit = make_shared<IntegerLiteral>(IntegerLiteral());
	lit->token = this->cur_token;
	lit->value = std::stoi(lit->token->literal);
//	return std::move(lit);
	return lit;
}

unique_ptr<Boolean> Parser::parse_boolean() {
	auto b = make_unique<Boolean>(Boolean());
	b->token = this->cur_token;
	b->value = b->token->type == TOK_TRUE ? true : false;
	return std::move(b);
}

shared_ptr<BlockStatement> Parser::parse_block_statement() {
	auto bs = make_shared<BlockStatement>(BlockStatement());
	bs->token = this->cur_token;
	this->next_token();
	while (!PARSER_CUR_IS(TOK_RBRACE) && !PARSER_CUR_IS(TOK_EOF)) {
		auto statement = this->parse_statement();
		if (statement) {
			bs->statements.push_back(statement);
		}
		this->next_token();
	}
	return bs;
}

void Parser::parse_function_parameters(FunctionLiteral* fn) {
	if (PARSER_PEEK_IS(TOK_RPAREN)) {
		return; // No arguments to function
	}

	this->next_token();

	if (this->cur_token->type != TOK_ID) {
		add_parser_error("expected identifier");
		return;
	}

	shared_ptr<Identifier> id = nullptr;
	id = make_shared<Identifier>(Identifier());
	id->token = this->cur_token;
	id->value = this->cur_token->literal;
	fn->parameters.push_back(id);

	while (PARSER_PEEK_IS(TOK_COMMA)) {
		this->next_token();
		this->next_token();
		id = std::make_shared<Identifier>(Identifier());
		id->token = this->cur_token;
		id->value = this->cur_token->literal;
		fn->parameters.push_back(id);
	}

	if (!this->expect_peek(TOK_RPAREN)) {
		add_parser_error("expected TOK_RPAREN");
		return;
	}
}

unique_ptr<FunctionLiteral> Parser::parse_function_literal() {
	auto fn = make_unique<FunctionLiteral>(FunctionLiteral());
	fn->token = this->cur_token;

	if (!this->expect_peek(TOK_LPAREN)) {
		add_parser_error("TOK_LPAREN expected.");
	}
	
	this->parse_function_parameters(fn.get());

	if (!this->expect_peek(TOK_LBRACE)) {
		add_parser_error("TOK_RPAREN expected.");
	}

	fn->block = this->parse_block_statement();
	return std::move(fn);
}

unique_ptr<IfExpression> Parser::parse_if_expression() {
	auto iff =  make_unique<IfExpression>(IfExpression());
	iff->token = this->cur_token;

	if (!this->expect_peek(TOK_LPAREN)) {
		add_parser_error("TOK_LPAREN expected.");
	}

	this->next_token();
	iff->condition = this->parse_expression(PREC_LOWEST);

	if (!this->expect_peek(TOK_RPAREN)) {
		add_parser_error("TOK_RPAREN expected.");
	}

	if (!this->expect_peek(TOK_LBRACE)) {
		add_parser_error("TOK_LBRACE expected.");
	}

	iff->consequence = this->parse_block_statement();
	if (PARSER_PEEK_IS(TOK_ELSE)) {
		this->next_token();
		if (!this->expect_peek(TOK_LBRACE)) {
			add_parser_error("TOK_LBRACE expected.");
			return nullptr;
		}
		iff->alternative = this->parse_block_statement();
	}

	return std::move(iff);
}

unique_ptr<CallExpression> Parser::parse_call_expression(shared_ptr<Expression> fn) {
	auto call = make_unique<CallExpression>(CallExpression());
	call->token = this->cur_token;
	call->function = fn;
	this->parse_call_arguments(call.get());
	return std::move(call);
}

void Parser::parse_call_arguments(CallExpression* call) {
	if (PARSER_PEEK_IS(TOK_RPAREN)) {
		this->next_token();
		return;
	}

	this->next_token();
	call->arguments.push_back(this->parse_expression(PREC_LOWEST));

	while (PARSER_PEEK_IS(TOK_COMMA)) {
		this->next_token();
		this->next_token();
		call->arguments.push_back(this->parse_expression(PREC_LOWEST));
	}

	if (!this->expect_peek(TOK_RPAREN)) {
		add_parser_error("expected TOK_RPAREN.");
		return;
	}

	return;
}
