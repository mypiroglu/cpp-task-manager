#include "task.h"

Task::Task(int id, std::string description, bool completed) {
    this->id = id;
    this->description = description;
    this->completed = completed;
}