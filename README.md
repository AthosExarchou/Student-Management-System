# Student Management System

## Overview
Developed as a project for the **Programming-II** course at [Harokopio University of Athens – Dept. of Informatics and Telematics](https://www.dit.hua.gr), this C program provides a simple student management system.

It allows users to:
- Add a student.
- Delete a student by ID.
- Find a student by ID.
- Modify a student's name.
- Print a student's data.
- Print all students.
- Save the data to a file and exit the program.

The system stores students' data in a doubly linked list and provides basic file handling to load and save student information from a file.

## Files
- **main.c**: The main entry point of the program, which manages the user interface and the logic for performing various operations.
- **students.c**: Contains the implementations of the functions declared in `students.h`, including those for handling student data and interacting with the linked list.
- **students.h**: The header file that defines the necessary structures, functions, and constants used across the program.

## Functions

#### 1. `init()`
Initializes the program, primarily used for random number generation.

#### 2. `printMenu()`
Prints the menu of available operations to the user.

#### 3. `generateId()`
Generates a random 6-digit student ID.

#### 4. `createList()`
Creates and initializes a new doubly linked list.

#### 5. `load(char *stFile, list *l)`
Loads student data from a file into the list. If the file doesn't exist, it creates a new one.

#### 6. `save(char *stFile, list l)`
Saves the current list of students to a file.

#### 7. `addStudent(student st, list l)`
Adds a new student to the list.

#### 8. `findStudentNode(unsigned long id, list l, node* np)`
Finds a student by ID and returns the node containing the student.

#### 9. `deleteStudentById(unsigned long id, list l)`
Deletes a student by ID from the list.

#### 10. `findStudent(unsigned long id, list l, student *st)`
Finds a student by ID and returns the student's data.

#### 11. `updateStudent(student stUpdate, list l)`
Updates the name of a student in the list.

#### 12. `printStudent(student st)`
Prints a student's data.

#### 13. `printStudents(list l)`
Prints all students in the list.

#### 14. `isError(Result err)`
Checks if an error occurred during any operation.

#### 15. `destroyList(list l)`
Deallocates all memory used by the list and its nodes.

## Error Handling
The program uses an enum `Result` to handle various types of errors:
- `NO_ERR`: No error occurred.
- `MALLOC_ERR`: Memory allocation error.
- `F_READ_ERR`: Error reading from the file.
- `F_WRITE_ERR`: Error writing to the file.
- `UNKNOWN_ERR`: Unknown error.
- `SYNTAX_ERR`: Syntax error.

The program checks for errors after every major operation (such as adding, deleting, or updating a student) and handles them appropriately.

## Compilation and Execution
To compile and run the program, use the following commands:

```bash
gcc main.c students.c -o student_manager
./student_manager students.dat
```

Here, `students.dat` is the file where student data is saved. If the file does not exist, it will be created.

## Author

- **Name**: Exarchou Athos
- **Student ID**: it2022134
- **Email**: it2022134@hua.gr, athosexarhou@gmail.com

## License
This project is licensed under the MIT License.
