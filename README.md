# C++ Task Manager

![C++](https://img.shields.io/badge/language-C%2B%2B-blue)
![CMake](https://img.shields.io/badge/build-CMake-green)
![Platform](https://img.shields.io/badge/platform-Linux-lightgrey)
![Status](https://img.shields.io/badge/status-learning_project-orange)

A simple **Command Line Interface (CLI)** task manager written in **C++**.

This project was built to practice core C++ concepts such as:

- Object-Oriented Programming
- Working with header/source files
- STL containers (`vector`)
- File handling
- String parsing
- Command-line arguments
- Building C++ projects using **CMake**

---

# Features

- Add new tasks
- List all tasks
- Remove tasks by id
- Mark tasks as completed / uncompleted
- Update task description
- Search tasks by keyword
- Save tasks to file
- Load tasks from file on startup

---

# Project Structure

```
cpp-task-manager/
├── CMakeLists.txt
├── README.md
├── data/
│   └── tasks.txt
├── include/
│   └── task.h
├── src/
│   ├── main.cpp
│   └── task.cpp
└── build/
```

---

# Build

Clone the repository and build the project:

```bash
git clone https://github.com/YOUR_USERNAME/cpp-task-manager.git
cd cpp-task-manager

mkdir build
cd build
cmake ..
make
```

---

# Run

From the `build` directory:

```bash
./taskmanager list
```

---

# Usage

### List tasks

```bash
./taskmanager list
```

### Add a task

```bash
./taskmanager add "Learn C++"
```

### Remove a task

```bash
./taskmanager remove 2
```

### Mark task as completed

```bash
./taskmanager completed 1
```

### Update task

```bash
./taskmanager update 1 "Learn modern C++"
```

### Search tasks

```bash
./taskmanager search "C++"
```

---

# Example

```bash
./taskmanager add "Read a book"
./taskmanager add "Learn C++"
./taskmanager list
```

Output:

```
[ ] 1 - Read a book
[ ] 2 - Learn C++
```

---

# Data Format

Tasks are stored in `data/tasks.txt` using the following format:

```
id|description|completed
```

Example:

```
1|Read a book|0
2|Learn C++ STL|1
3|Build CLI project|0
4|Write GitHub README|0
5|Practice algorithms|1
```

| Field | Description |
|------|-------------|
| id | Unique task identifier |
| description | Task description |
| completed | Task status (`0 = not completed`, `1 = completed`) |

---

# Technologies Used

- C++
- STL
- CMake
- CLI development

---

# Learning Goals

This project helped practice:

- object-oriented programming
- working with multiple source files
- file I/O
- parsing structured text
- command-line applications
- organizing a real C++ project

---

# Future Improvements

- Task priority support
- Due dates
- Better input validation
- JSON export
- Terminal UI (TUI) version