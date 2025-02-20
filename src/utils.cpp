#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <vector>

#include "../inc/task.h"
#include "../inc/utils.h"

using namespace std;

//Parses tasks from tasks.txt file in directory
bool parse_tasks(vector<Task>& task_list, int& task_list_length, ifstream& task_in, ofstream& task_out, HANDLE& hConsole)
{
    task_in.open("tasks.txt");

    //Progress tracker: 4 when done
    int progress_tracker = 0;

    if (task_in.is_open())
    {
        char current_char;
        Task new_task;
        while(task_in.get(current_char))
        {
            switch(progress_tracker)
            {
                case 0: // Nothing found yet, check for "/" opening tag
                    if(current_char == '/')
                        progress_tracker++;
                    break;
                case 1: // One open tag found, look for another "/"
                    if(current_char == '/')
                    {
                        new_task = *(new Task()); // Create new task since we'll use it now
                        progress_tracker++;
                    }
                    else
                    {
                        cerr << "Improper task opening formatting." << endl;
                        return 1;
                    }
                    break;
                case 2: // Add non "|" chars to new_task t_task, if "|" go to due by phase
                    if(current_char == '|')
                    {
                        progress_tracker++;
                        break;
                    }
                    new_task.t_task += current_char;
                    break;
                case 3: // Add non "|" chars to new_task t_due, if "|" go to status phase
                    if(current_char == '|')
                    {
                        progress_tracker++;
                        break;
                    }
                    new_task.t_due += current_char;
                    break;
                case 4: //Add status to new_task t_status and go to closing tag phase
                    switch(current_char)
                    {
                        case '0':
                            new_task.t_status = 0;
                            break;
                        case '1':
                            new_task.t_status = 1;
                            break;
                        case '2':
                            new_task.t_status = 2;
                            break;
                        default:
                            cerr << "Improper task status formatting." << endl;
                            return 1;
                    }
                    task_list_length += 1;
                    new_task.t_ID = task_list_length;

                    task_list.push_back(new_task);
                    progress_tracker = 0;
                    break;
            }
        }
    }
    task_in.close();

    if(progress_tracker != 0)
    {
        cerr << "Last task is incomplete" << endl;
        return 1;
    }

    //Success!
    return 0;
}

//Clears console, courtesy of ChatGPT
void clearConsole(HANDLE& hConsole) {
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coordScreen = { 0, 0 };    // Home position for cursor
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;

    // Get the number of character cells in the current buffer.
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        return;
    }
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

    // Fill the entire screen with blanks.
    FillConsoleOutputCharacter(hConsole, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);

    // Get the current text attribute.
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    // Reset text attributes and move the cursor home.
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
    SetConsoleCursorPosition(hConsole, coordScreen);
}

//Print tasks from task_list with pretty colors
void print_tasks(vector<Task>& task_list, HANDLE& hConsole)
{
    // Ugly :(
    for(Task task : task_list)
    {
        SetConsoleTextAttribute(hConsole, 9); // Blue
        cout << "==========================================" << endl;
        cout << task.t_ID << endl;
        SetConsoleTextAttribute(hConsole, 15); // White
        cout << task.t_task << endl;
        SetConsoleTextAttribute(hConsole, 11); // Light blue
        cout << " ----------------------------------------" << endl;
        SetConsoleTextAttribute(hConsole, 8); // Gray
        cout << "Due: ";
        SetConsoleTextAttribute(hConsole, 15); // White
        cout << task.t_due << endl;
        SetConsoleTextAttribute(hConsole, 8); // Gray
        SetConsoleTextAttribute(hConsole, 15); // White
        int status = static_cast<int>(task.t_status);
        switch (status)
        {
            case 0:
                SetConsoleTextAttribute(hConsole, 12); // Red
                break;
            case 1:
                SetConsoleTextAttribute(hConsole, 14); // Yellow
                break;
            case 2:
                SetConsoleTextAttribute(hConsole, 10); // Green
                break;
        }
        cout << "Status: " << std::to_string(task.t_status) << endl;
        cout << endl;
    }
}