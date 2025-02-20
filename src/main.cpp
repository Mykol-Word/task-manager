#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <vector>

#include "../inc/task.h"
#include "../inc/utils.h"

using namespace std;

vector<Task> task_list;
int task_list_length;

ifstream task_in;
ofstream task_out;
HANDLE  hConsole;

//Sort of like a task-list repl
int main()
{
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if(parse_tasks(task_list, task_list_length, task_in, task_out, hConsole))
    {
        cerr << "Failed to parse tasks. Exit program";
        while(true);
    }

    while(true)
    {
        clearConsole(hConsole);
        print_tasks(task_list, hConsole);

        SetConsoleTextAttribute(hConsole, 15); // White
        
        cout << "- - - - - - - - - - - - - - - - - - - - - -" << endl;
        cout << "[a] to add Task, [d] to delete task, [c] to change task status:" << endl;
        
        //Input
        string input_string;
        getline(cin, input_string);

        if(input_string == "a") // Add task
        {
            Task new_task = *(new Task());

            cout << "Task text: ";
            getline(cin, input_string);
            new_task.t_task = input_string;

            cout << "Task deadline: ";
            getline(cin, input_string);
            new_task.t_due = input_string;

            task_list_length += 1;
            new_task.t_ID = task_list_length;
            task_list.push_back(new_task);

            task_out.open("tasks.txt", fstream::app);
            task_out << new_task.GetStoreString();
            task_out << endl;
            task_out.close();
        }
        else if (input_string == "d")
        {
            cout << "Input the task ID of the task you want to delete: ";
            getline(cin, input_string);
            int delete_line = stoi(input_string) - 1;
            if(delete_line >= task_list_length || delete_line < 0)
            {
                cout << "Invalid task ID. Press enter to continue.";
                getline(cin, input_string);
                continue;
            }
            
            task_in.open("tasks.txt");
            
            char current_char;
            int current_line = 0;
            string new_task_list = "";

            while (task_in.get(current_char))
            {
                if(current_line != delete_line)
                    new_task_list += current_char;
                if(current_char == '\n')
                    current_line += 1;
                
            }
            task_in.close();

            task_out.open("tasks.txt");
            task_out << new_task_list;
            task_out.close();
            task_list_length = 0;

            task_list.clear();
            if(parse_tasks(task_list, task_list_length, task_in, task_out, hConsole))
            {
                cerr << "Failed to parse tasks. Exit program";
                while(true);
            }
        }
        else if (input_string == "c")
        {
            cout << "Input the task ID of the task you want to change the status of: ";
            getline(cin, input_string);
            int task_id = stoi(input_string) - 1;
            if(task_id >= task_list_length || task_id < 0)
            {
                cout << "Invalid task ID. Press enter to continue.";
                getline(cin, input_string);
                continue;
            }
            cout << "Input [0] for failed, [1] for in-progress, or [2] for completed: ";
            getline(cin, input_string);
            int status_input = stoi(input_string);
            if(status_input != 0 && status_input != 1 && status_input != 2)
            {
                cout << "Invalid status. Press enter to continue.";
                getline(cin, input_string);
                continue;
            }
            task_list[task_id].t_status = status_input;
        }
        else
        {
            cout << "Invalid command. Press enter to continue.";
            getline(cin, input_string);
        }
    }
}

