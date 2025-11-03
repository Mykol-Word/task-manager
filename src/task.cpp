#include <string>
#include "../inc/task.h"

Task::Task()
{
    t_task = "";
    t_due = "";
    t_status = 1; // In progress by default
    t_progress = 0; // 0% by default
    t_ID = -1;
}

//Obsolete but keeping for debug
std::string Task::GetPrintString()
{
    return
    (
        "==========================================\n"
        + t_task + "\n" 
        + "------------------------------------\n"
        + "Due: " + t_due + "\n"
        + "Status: " + std::to_string(t_status)
    );
}

std::string Task::GetStoreString()
{
    return
    (
        "//" + t_task + "|" + t_due + "|" + std::to_string(t_status) + "|" + std::to_string(t_progress)
    );
}