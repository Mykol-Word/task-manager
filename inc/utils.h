#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <fstream>
#include <windows.h>
#include <vector>

#include "task.h"

bool parse_tasks(std::vector<Task>& task_list, int& task_list_length, std::ifstream& task_in, std::ofstream& task_out, HANDLE& hConsole);
void clearConsole(HANDLE& hConsole);
void print_tasks(std::vector<Task>& task_list, HANDLE& hConsole);

#endif