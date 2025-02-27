#ifndef RUN_H
#define RUN_H

#include <string>

void run(const std::string& source);
void run_file(const std::string& path);
void run_prompt();

void report_error(int line, const std::string& error);

#endif
