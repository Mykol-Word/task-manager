#include <string>
#include "../inc/task.h"

Task::Task()
{
    t_task = "! Unassigned Task Text !";
    t_due = "! Unassigned Due Date !";
    t_status = Status::IN_PROGRESS;
}

std::string Task::GetPrintString()
{
    return
    (
        "==========================================\n"
        + t_task + "\n" 
        + "------------------------------------\n"
        + "Due: " + t_due + "\n"
        + "Status: " + std::to_string(static_cast<int>(t_status))
    );
}