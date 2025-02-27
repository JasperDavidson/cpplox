#include "scanner.h"

Token::Token(TokenType type, std::string lexeme, int line) : type(type), lexeme(lexeme), line(line) {};

TokenType Token::get_type() const { return type; }
std::string Token::get_lexeme() const { return lexeme; }
int Token::get_line() const { return line; }

bool Scanner::is_at_end() {
	return current >= source.length();
}

std::vector<Token> Scanner::scan_tokens() {
	while (!is_at_end()) {
		// scan more tokens
	}

	token_list.push_back(Token(TokenType::EOFF, "", line));
	return token_list;
}
