#include "scanner.h"
#include "run.h"
#include <variant>

Token::Token(const TokenType& type, const scanner_variant& literal, const std::string& lexeme, int line) : type(type), literal(literal), lexeme(lexeme), line(line) {};

TokenType Token::get_type() const { return type; }
std::string Token::get_lexeme() const { return lexeme; }
int Token::get_line() const { return line; }

Scanner::Scanner(const std::string& source) : source(source) {};

bool Scanner::is_at_end() const {
	return current >= source.length();
}

char Scanner::advance() {
	return source.at(current++);
}

// Allows us to check for the next character - kind of an advance() preview
bool Scanner::match(char c) {
	if (is_at_end()) return false;
	if (source.at(current) != c) return false;

	current++;
	return true;
}

// Lookahead function for the source string
char Scanner::peek() const {
	if (is_at_end()) return '\0';
	return source.at(current);
}

char Scanner::peek_next() const {
	if (current + 1 >= source.length()) return '\0';
	return source.at(current + 1);
}

bool Scanner::is_digit(char c) const {
	return c >= '0' && c <= '9';
}

bool Scanner::is_alpha(char c) const {
	return (c <= 'Z' && c >= 'A') || (c <= 'z' && c >= 'a') || (c == '_');
}

bool Scanner::is_alphanumeric(char c) const {
	return is_digit(c) || is_alpha(c);
}

// Read a string until it terminates and store it as a token
void Scanner::scan_string() {
	// Read through tokens until the whole string is consumed
	while (peek() != '"' && !is_at_end()) {
		if (peek() == '\n') line++;
		advance();
	}

	// Report an error if the file ended without string closure
	if (is_at_end()) {
		report_error(line, "Unterminated string");
	}

	// Clear the '"' character
	advance();

	std::string value = source.substr(start + 1, current - start - 1);
	add_token(TokenType::STRING, value);
}

// Read a number until it terminates through '\n'
void Scanner::scan_number() {
	while (is_digit(source.at(current))) advance();

	// Check for and advance past a fractional part
	if (peek() == '.' && is_digit(peek_next())) {
		advance();

		while (is_digit(source.at(current))) advance();
	}

	add_token(TokenType::NUMBER, std::stod(source.substr(current, start)));
}

void Scanner::scan_identifier() {
	while (is_alpha(peek())) advance();

	std::string lexeme = source.substr(start, current - start);
	TokenType token_type;

	if (keywords.find(lexeme) != keywords.end()) {
		token_type = keywords.at(lexeme);
	} else {
		token_type = TokenType::IDENTIFIER;
	}

	add_token(token_type, lexeme);
}

void Scanner::add_token(const TokenType& type) {
	add_token(type, std::monostate());
}

void Scanner::add_token(const TokenType& type, const scanner_variant& literal) {
	// Set the lexeme equal to a substring of the source based on current and start
	std::string lexeme = source.substr(start, current - start);
	add_token(type, literal, lexeme);
}

void Scanner::add_token(const TokenType& type, const scanner_variant& literal, const std::string& lexeme) {
	token_list.push_back(Token(type, literal, lexeme, line));
}

void Scanner::scan_token() {
	char c = advance();
	
	switch(c) {
		case '(': add_token(TokenType::LEFT_PAREN); break;
		case ')': add_token(TokenType::RIGHT_PAREN); break;
		case '{': add_token(TokenType::LEFT_BRACE); break;
		case '}': add_token(TokenType::RIGHT_BRACE); break;
		case ',': add_token(TokenType::COMMA); break;
		case '.': add_token(TokenType::DOT); break;
		case '-': add_token(TokenType::MINUS); break;
		case '+': add_token(TokenType::PLUS); break;
		case ';': add_token(TokenType::SEMICOLON);
		case '*': add_token(TokenType::STAR); break;

		// Check for two-character lexemes
		case '!':
			add_token(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
			break;
		case '=':
			add_token(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
			break;
		case '>':
			add_token(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
			break;
		case '<':
			add_token(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
			break;
		case '/':
			if (match('/')) {
				// Comments go until the end of the line
				while (peek() != '\n' && !is_at_end()) advance();
			} else if (match('*')) {
				// Adding support for multi-line block comments
				while (peek() != '*' && peek_next() != '/' && !is_at_end()) {
					if (peek() == '\n') {
						line++;
					}

					advance();
				}

				// Clear the '*/'
				advance(); advance();

				if (peek() == '\n') {
					advance();
					line++;
				}
			} else {
				add_token(TokenType::SLASH);
			}

			break;

		case ' ':
		case '\r':
		case '\t':
			break;

		case '\n': line++; break;

		case '"': scan_string(); break;

		default:
			if (is_digit(c)) {
				scan_number();
			} else if (is_alpha(c)) {
				scan_identifier();
			} else {
				report_error(line, "Invalid syntax error");
			}

			break;
	}
}

std::vector<Token> Scanner::scan_tokens() {
	while (!is_at_end()) {
		start = current;
		scan_token();
	}

	token_list.push_back(Token(TokenType::EOFF, std::monostate(), "", line));
	return token_list;
}
