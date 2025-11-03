#ifndef TASK_H
#define TASK_H

#include <string>

class Task
{
    public:
        std::string t_task;
        std::string t_due;
        int t_status;
        int t_progress;
        int t_ID;

        Task();
        std::string GetPrintString();
        std::string GetStoreString();
};

#endif