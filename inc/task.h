#ifndef TASK_H
#define TASK_H

#include <string>

enum class Status {
  FAILED = -1,
  IN_PROGRESS = 0,
  COMPLETED = 1
};

class Task
{
    public:
        std::string t_task;
        std::string t_due;
        enum Status t_status;

        Task();
        std::string GetPrintString();
        std::string GetStoreString();
};

#endif