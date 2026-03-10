#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "task.h"

std::vector<Task> tasks;

int getNextId() {
    int maxId = 0;

    for (const auto& task : tasks) {
        if (task.id > maxId) {
            maxId = task.id;
        }
    }

    return maxId + 1;
}

void loadTasks() {
    tasks.clear();

    std::ifstream file("../data/tasks.txt");
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
    std::ofstream file("../data/tasks.txt");

    for (const auto& task : tasks) {
        file << task.id << "|"
             << task.description << "|"
             << task.completed
             << "\n";
    }
}

void listTasks() {
    if (tasks.empty()) {
        std::cout << "There is no task.\n";
        return;
    }

    for (const auto& task : tasks) {
        std::cout << "[" << (task.completed ? 'x' : ' ') << "] "
                  << task.id << " - " << task.description << "\n";
    }
}

void addTask(const std::string& desc) {
    int id = getNextId();
    tasks.push_back(Task(id, desc, false));
    saveTasks();
}

bool removeTask(int id) {
    for (auto it = tasks.begin(); it != tasks.end(); ++it) {
        if (it->id == id) {
            tasks.erase(it);
            saveTasks();
            return true;
        }
    }

    return false;
}

bool changeTaskStatus(int id) {
    for (auto &task : tasks) {
        if (task.id == id) {
            task.completed = !task.completed;
            saveTasks();
            return true;
        }
    }

    return false;
}

bool updateTask(int id, const std::string& newDesc) {
    for (auto& task : tasks) {
        if (task.id == id) {
            task.description = newDesc;
            saveTasks();
            return true;
        }
    }

    return false;
}

void searchTask(const std::string& keyword) {
    bool found = false;

    for (const auto& task : tasks) {
        if (task.description.find(keyword) != std::string::npos) {
            std::cout << "[" << (task.completed ? 'x' : ' ') << "] "
                      << task.id << " - " << task.description << "\n";
            found = true;
        }
    }

    if (!found) {
        std::cout << "No matching tasks were found.\n";
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage:\n";
        std::cout << "  ./taskmanager list\n";
        std::cout << "  ./taskmanager add \"task description\"\n";
        std::cout << "  ./taskmanager remove [id]\n";
        std::cout << "  ./taskmanager completed [id]\n";
        std::cout << "  ./taskmanager update [id] \"new description\"\n";
        std::cout << "  ./taskmanager search \"keyword\"\n";
        return 1;
    }

    loadTasks();

    std::string command = argv[1];

    try {
        if (command == "list") {
            listTasks();
        } else if (command == "add") {
            if (argc < 3) {
                std::cout << "Usage: ./taskmanager add \"task description\"\n";
                return 1;
            }

            addTask(argv[2]);
        } else if (command == "remove") {
            if (argc < 3) {
                std::cout << "Usage: ./taskmanager remove [id]\n";
                return 1;
            }

            int id = std::stoi(argv[2]);

            if (!removeTask(id)) {
                std::cout << "Task not found\n";
            }
        } else if (command == "completed") {
            if (argc < 3) {
                std::cout << "Usage: ./taskmanager completed [id]\n";
                return 1;
            }

            int id = std::stoi(argv[2]);

            if (!changeTaskStatus(id)) {
                std::cout << "Task not found\n";
            }
        } else if (command == "update") {
            if (argc < 4) {
                std::cout << "Usage: ./taskmanager update [id] \"new description\"\n";
                return 1;
            }

            int id = std::stoi(argv[2]);

            if (!updateTask(id, argv[3])) {
                std::cout << "Task not found.\n";
            }
        } else if (command == "search") {
            if (argc < 3) {
                std::cout << "Usage: ./taskmanager search \"keyword\"\n";
                return 1;
            }

            searchTask(argv[2]);
        } else {
            std::cout << "Unknown command\n";
        }
    } catch (...) {
        std::cout << "Invalid ID or incorrect enter.\n";
        return 1;
    }

    return 0;
}