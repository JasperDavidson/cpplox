#ifndef SCANNER_H
#define SCANNER_H

#include <iterator>
#include <string>
#include <unordered_map>
#include <variant>
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

inline std::unordered_map<std::string, TokenType> keywords = {
	{"and", TokenType::AND},
	{"class", TokenType::CLASS},
	{"else", TokenType::ELSE},
	{"false", TokenType::FALSE},
	{"fun", TokenType::FUN},
	{"for", TokenType::FOR},
	{"if", TokenType::IF},
	{"nil", TokenType::NIL},
	{"or", TokenType::OR},
	{"print", TokenType::PRINT},
	{"return", TokenType::RETURN},
	{"super", TokenType::SUPER},
	{"this", TokenType::THIS},
	{"true", TokenType::TRUE},
	{"var", TokenType::VAR},
	{"while", TokenType::WHILE}
};

using scanner_variant = std::variant<std::string, double, std::monostate>;

class Token {
	const TokenType type;
	const scanner_variant literal;
	const std::string lexeme;
	const int line;

public:
	Token(const TokenType& type, const scanner_variant&, const std::string& lexeme, int line);

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
	bool is_alpha(char c) const;
	bool is_alphanumeric(char c) const;

	void add_token(const TokenType& type);
	void add_token(const TokenType& type, const scanner_variant& literal);
	void add_token(const TokenType& type, const scanner_variant& literal, const std::string& lexeme);
	
	void scan_token();
	void scan_string();
	void scan_number();
	void scan_identifier();

public:
	Scanner(const std::string& source);

	std::vector<Token> scan_tokens();
};

#endif
