#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "task.h"

std::vector<Task> tasks;

void loadTasks() {
    std::ifstream file("tasks.txt");
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        std::stringstream ss(line);

        std::string idStr;
        std::string description;
        std::string completedStr;

        std::getline(ss, idStr, '|');
        std::getline(ss, description, '|');
        std::getline(ss, completedStr, '|');

        if (idStr.empty() || description.empty() || completedStr.empty()) {
            continue;
        }

        int id = std::stoi(idStr);
        bool completed = std::stoi(completedStr);

        tasks.push_back(Task(id, description, completed));
    }
}

void saveTasks() {
    std::ofstream file("tasks.txt");

    for (auto &task : tasks) {
        file << task.id << "|"
             << task.description << "|"
             << task.completed
             << std::endl;
    }
}

void listTasks() {
    for (auto &task : tasks) {
        std::cout << task.id << " - " << task.description;

        if (task.completed) {
            std::cout << " ✔";
        }

        std::cout << std::endl;
    }
}

void addTask(std::string desc) {
    int id = tasks.size() + 1;
    tasks.push_back(Task(id, desc, false));
    saveTasks();
}

void removeTask(int id) {
    tasks.erase(tasks.begin() + id - 1);
    saveTasks();
}
void changeTaskStatus(int id){
    bool found = false;

    for(auto &task : tasks){
        if(task.id == id){
            task.completed = !task.completed;
            found = true;
            break;
        }
    }
    if (!found) {
        std::cout << "Bu id ile task bulunamadi\n";
    }
    saveTasks();
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: ./main [list|add|remove]" << std::endl;
        return 1;
    }

    loadTasks();

    std::string command = argv[1];

    if (command == "list") {
        listTasks();
    } else if (command == "add") {
        if (argc < 3) {
            std::cout << "Usage: ./main add \"task description\"" << std::endl;
            return 1;
        }

        std::string desc = argv[2];
        addTask(desc);
    } else if (command == "remove") {
        if (argc < 3) {
            std::cout << "Usage: ./main remove [id]" << std::endl;
            return 1;
        }

        int id = std::stoi(argv[2]);
        removeTask(id);
    }  else if (command == "completed") {
        if (argc < 3) {
            std::cout << "Usage: ./main completed [id]" << std::endl;
            return 1;
        }

        int id = std::stoi(argv[2]);
        changeTaskStatus(id);
    } else {
        std::cout << "Unknown command" << std::endl;
    }

    return 0;
}