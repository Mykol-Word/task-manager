#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <vector>
#include <cstdlib>
#include <time.h>

#include "../inc/task.h"
#include "../inc/utils.h"

using namespace std;

vector<Task> task_list;
int task_list_length;

ifstream task_in;
ofstream task_out;
HANDLE  hConsole;

int main()
{
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    //Parse tasks. Freeze program if fails.
    if(parse_tasks(task_list, task_list_length, task_in, task_out, hConsole))
        print_error("Failed to parse tasks. Exit program", 1);

    //main repl
    while(true)
    {
        system("cls");
        print_tasks(task_list, hConsole);
        SetConsoleTextAttribute(hConsole, 15); // White
        
        cout << "- - - - - - - - - - - - - - - - - - - - - -" << endl;
        cout << "[a] to add Task, [d] to delete task, [c] to change task status:" << endl;
        
        //Initial input
        string input_string;
        getline(cin, input_string);

        //Handle input characters
        if(input_string == "a") // Add new task to task list
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
            task_out << new_task.GetStoreString() << endl;
            task_out.close();
        }
        else if (input_string == "d") // Delete task from the task list
        {
            cout << "Input the task ID of the task you want to delete: ";
            getline(cin, input_string);

            int delete_line = stoi(input_string) - 1;
            if(delete_line >= task_list_length || delete_line < 0)
                { print_error("Invalid task ID. Press enter to continue."); continue; }

            //Add task to task archive and note time
            task_out.open("tasks-archive.txt", fstream::app);
            time_t time_deleted = time(NULL);
            task_out << task_list[delete_line].GetStoreString() << "|" << ctime(&time_deleted) << endl;
            task_out.close();
            
            char current_char;
            int current_line = 0;
            string new_task_list = "";

            task_in.open("tasks.txt");
            //Rewrite task file to not include specific task (not efficient but okay for now)
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
            
            //Reparse tasks with new task file
            task_list_length = 0;
            task_list.clear();
            if(parse_tasks(task_list, task_list_length, task_in, task_out, hConsole))
                print_error("Failed to parse tasks. Exit program", 1);
        }
        else if (input_string == "c") //Change task completion status
        {
            cout << "Input the task ID of the task you want to change the status of: ";
            getline(cin, input_string);

            int task_id = stoi(input_string) - 1;
            if(task_id >= task_list_length || task_id < 0)
                { print_error("Invalid task ID. Press enter to continue."); continue; }

            cout << "Input [0] for failed, [1] for in-progress, or [2] for completed: ";
            getline(cin, input_string);

            int status_input = stoi(input_string);
            if(status_input != 0 && status_input != 1 && status_input != 2)
                { print_error("Invalid status. Press enter to continue."); continue; }

            task_list[task_id].t_status = status_input;
        }
        else // Invalid input
        {
            cout << "Invalid command. Press enter to continue.";
            getline(cin, input_string);
        }
    }
}

