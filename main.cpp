#include "run.h"
#include <iostream>
#include <cstdlib>

int main(int argc, char *argv[]) {
	if (argc > 2) {
		std::cout << "Usage: ./lox [script]\n";
		exit(64);
	} else if (argc == 2) {
		run_file(argv[1]);
	} else {
		run_prompt();
	}

	return 0;
}
