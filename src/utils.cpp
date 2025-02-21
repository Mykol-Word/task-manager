#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <vector>

#include "../inc/task.h"
#include "../inc/utils.h"

using namespace std;

//Parses tasks from tasks.txt file in directory
bool parse_tasks(vector<Task>& task_list, int& task_list_length, ifstream& task_in, ofstream& task_out, HANDLE& hConsole, string file_name)
{
    task_in.open(file_name);

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
                        new_task = *(new Task());
                        progress_tracker++;
                    }
                    else
                        { print_error("Improper task opening formatting."); return 1; }
                    break;

                case 2: // Add non "|" chars to new_task t_task, if "|" go to next phase
                    if(current_char == '|')
                    {
                        progress_tracker++;
                        break;
                    }
                    new_task.t_task += current_char;
                    break;

                case 3: // Add non "|" chars to new_task t_due, if "|" go to next phase
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
                            print_error("Invalid task status."); 
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
        { print_error("Last task is incomplete."); return 1; }

    //Success!
    return 0;
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
        string status_string = "";
        switch (status)
        {
            case 0:
                SetConsoleTextAttribute(hConsole, 12); // Red
                status_string = "FAILED (0)";
                break;
            case 1:
                SetConsoleTextAttribute(hConsole, 14); // Yellow
                status_string = "IN PROGRESS (1)";
                break;
            case 2:
                SetConsoleTextAttribute(hConsole, 10); // Green
                status_string = "COMPLETED (2)";
                break;
        }
        cout << "Status: " << status_string << endl;
        SetConsoleTextAttribute(hConsole, 15); // White
        cout << endl;
    }
}

void print_error(string err_message, int fatal)
{
    cerr << err_message << endl;
    if(fatal)
        while(true);
    string dummy_line = "";
    getline(cin, dummy_line);
}

void print_help_message()
{
    cout << endl;
    cout << "Below is a list of all supported commands." << endl;
    cout << "Brackets [] encapsulate the commands for distinguishability." << endl;
    cout << "- - - - - - - - - - - - - - - - - - - - - -" << endl;
    cout << "[a] ---- Add a task to your task list." << endl;
    cout << "[d] ---- Delete a task permanently from your task list." << endl;
    cout << "[da] --- Delete a task and archive it in the task archive." << endl;
    cout << "[c] ---- Change the status of an existing task." << endl;
    cout << "[la] --- List all archived tasks." << endl;
    cout << "[help] - List all supported commands." << endl;
    cout << "- - - - - - - - - - - - - - - - - - - - - -" << endl;
    cout << "Press enter to return to continue." << endl;
}