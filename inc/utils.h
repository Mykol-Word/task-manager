#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <fstream>
#include <windows.h>
#include <vector>

#include "task.h"

bool parse_tasks(std::vector<Task>& task_list, int& task_list_length, std::ifstream& task_in, std::ofstream& task_out, HANDLE& hConsole, std::string file_name);
void print_tasks(std::vector<Task>& task_list, HANDLE& hConsole);
void print_error(std::string err_message, int fatal = 0);

#endif