#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <vector>

enum class TokenType {
	// Single-character tokens
	LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
	COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

	// One or two character tokens
	BANG, BANG_EQUAL,
	EQUAL, EQUAL_EQUAL,
	GREATER, GREATER_EQUAL,
	LESS, LESS_EQUAL,

	// Literals
	IDENTIFIER, STRING, NUMBER,

	// Keywords
	AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
	PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

	EOFF
};

class Token {
	const TokenType type;
	const std::string lexeme;
	const int line;

public:
	Token(TokenType type, std::string lexeme, int line);

	TokenType get_type() const;
	std::string get_lexeme() const;
	int get_line() const;
};

class Scanner {
	const std::string source;
	std::vector<Token> token_list;

	int start = 0;
	int current = 0;
	int line = 1;

	bool is_at_end() const;

	char advance();
	bool match(char c);
	char peek() const;
	char peek_next() const;
	bool is_digit(char c) const;

	void add_token(const TokenType& type);
	void add_token(const TokenType& type, const std::string& lexeme);
	
	void scan_token();
	void scan_string();
	void scan_number();

public:
	Scanner(const std::string& source);

	std::vector<Token> scan_tokens();
};

#endif
