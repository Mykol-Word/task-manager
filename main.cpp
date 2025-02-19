#include <iostream>
#include <fstream>
#include <windows.h>
#include <string> 

using namespace std;

void clearConsole() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
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

        clearConsole();

        task_out.open("tasks.txt", fstream::app);
        int task_length = new_task.length();
        task_out << new_task;
        task_out << endl;
        task_out.close();

        task_in.open("tasks.txt");
        if (task_in.is_open())
        {
            char current_char;
            while(task_in.get(current_char))
            {
                if(task_in.eof()) break;
                cout << current_char;
            }
        }
        task_in.close();
    }
}