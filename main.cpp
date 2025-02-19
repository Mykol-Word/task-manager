#include <iostream>
#include <fstream>
#include <windows.h>
#include <string> 

using namespace std;

//Sort of like a task-list repl
int main()
{
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    ifstream task_in;
    ofstream task_out;

    while(true)
    {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << "Add a task: ";
        SetConsoleTextAttribute(hConsole, 15);

        string new_task;
        getline(cin, new_task);

        printf("\033c");

        task_out.open("tasks.txt", fstream::app);
        int task_length = new_task.length();
        task_out << new_task;
        task_out << endl;
        task_out.close();

        task_in.open("tasks.txt");
        if (task_in.is_open())
        {
            char current_char;
            while(task_in)
            {
                current_char = task_in.get();
                cout << current_char;
            }
        }
        task_in.close();
    }
}