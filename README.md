# Task Management System using Red-Black Trees

## Overview
This project implements a Task Management System using Red-Black Trees in C++. The system manages assignees and their tasks, supporting efficient insertion, deletion, and search operations.

## Features
- **Assignee Management:**
  - Add, search, and delete assignees.
  - Search by ID or name.
  - List assignees with no tasks.
- **Task Management:**
  - Add, delete, and update tasks.
  - Assign tasks to assignees.
  - Search tasks by priority, assignee, or completion status.
  - Find the highest priority task.
- **Red-Black Tree Implementation:**
  - Both assignees and tasks are managed using separate Red-Black Trees for efficient operations.

## Main Classes
- `Task` and `Assignee`: Represent tasks and assignees.
- `RedBlackTree` and `T_RedBlackTree`: Red-Black Trees for assignees and tasks.
- `taskManagementSystem`: Main interface for managing tasks and assignees.

## Requirements
- C++11 or later
- Standard C++ libraries (iostream, string, sstream, queue, etc.)

## Author
- Name: Ayaan (i220832)
- Course: Data Structures, Semester 3
