#include "run.h"
#include "scanner.h"

#include <fstream>
#include <iterator>
#include <string>
#include <vector>
#include <iostream>

static bool had_error;

void run(const std::string& source) {
	Scanner scanner(source);
	std::vector<Token> tokens = scanner.scan_tokens();

	for (int i = 0; i < tokens.size(); i++) {
		std::cout << tokens.at(i).get_lexeme() << '\n';
	}
}

void run_prompt() {
	std::string line;

	while (true) {
		std::cout << "> ";
		std::cin >> line;

		if (line.empty()) break;
		run(line);

		had_error = false;
	}
}

void run_file(const std::string& path) {
	std::ifstream infile(path, std::ios_base::binary);
	std::vector<char> buffer( std::istreambuf_iterator<char>{infile}, std::istreambuf_iterator<char>{} );

	run(std::string(buffer.begin(), buffer.end()));

	if (had_error) exit(65);
}

void report_error(int line, const std::string& error_message) {
	std::cerr << "[line: " << line << "]: " << error_message << '\n';
	had_error = true;
}
