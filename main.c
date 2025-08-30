//Exarchou Athos
//it2022134

/* included libraries */
#include <stdio.h>
#include <stdlib.h>
#include "students.h" //includes header file containing the functions to be used in main.c
#include <string.h>

int main (int argc, char** argv) {

	init(); //called at start to initialize what is needed

	//declare variables
	int choice; //choice of user
	char name[MAXSTRING]; //name of student
	unsigned long id; //id of student

	//declare οbjects
	student st; //object to contain students' data
	Result ERR_check; //object intended for the checking of different types of errors
	list l; //object intended for containing students' data

	l = createList(); //creates an empty list
	
	if (argc < 2) {
    	printf("Error: No filename provided.\n");
    	return 1; // Exit the program with an error code
	}

	//puts the type 'Result' value 'load' returns in ERR_check to later check if any errors occurred
	ERR_check = load(argv[1], &l); //loads the file containing student data

	if (isError(ERR_check) == FALSE) { //NO_ERR case
		printf("\"%s\" was created/loaded successfully!\n", argv[1]); //prints appropriate message
	} else { //case where isError() is TRUE
		if (ERR_check == UNKNOWN_ERR) {

			//prints appropriate message
			printf("An error occurred in the proccess of creating a new file.\n");
			printf("Exiting...\n");

			destroyList(l); //deallocates all previously allocated memory

			//exits the program due to the occurrence of an error which
			//may disable/hinder the proper functioning of the program
			abort();

		} else { //case where ERR_check is F_READ_ERR

			//prints appropriate messages
			printf("An error occurred in the proccess of reading the content of \"%s\".\n", argv[1]);
			printf("Exiting...\n");

			destroyList(l); //deallocates all previously allocated memory

			//exits the program due to the occurrence of an error which
			//may disable/hinder the proper functioning of the program
			abort();
		}
	}

	while (1) { //infinite loop

		printMenu(); //prints the menu at the beginning to inform the user on the options available to them

		if (scanf("%d", &choice) != 1) { //checks if the input was an integer
			while (getchar() != '\n'); //reaches the end of the invalid input
			printf("Invalid input! Try again:\n"); //informs the user their input is invalid
			continue; //forces the next iteration of the loop
		}
		
		//the contruction of switch() was inspired by lab2
		switch (choice) {

			case 1: //case for addition of a student

				//requests input for student's name
				printf("Please enter the name of the student you want to add:\n"); //prints appropriate message
				if (scanf(" %s", st.name) != 1) { //checks whether the input is invalid
					printf("Invalid input!\n"); //informs the user their input is invalid
					break; //exits the switch
				}
				st.id = generateId(); //generates a random 6-digit id

				//the 'Result' type value the 'addStudent' function returns is put in ERR_check
				//in order to later check if any errors occurred
				ERR_check = addStudent(st, l); //adds a student's data to the list of students
				
				if (isError(ERR_check) == FALSE) { //checks for errors
					//prints appropriate message
					printf("A student with the name: %s and id: %lu has been succesfully added.\n", st.name, st.id);
				}
				else { //case where isError() is FALSE
					if (ERR_check == MALLOC_ERR) { //checks for specific error
						//prints appropriate messages
						printf("An error occured in the process of memory allocation.\n");
						printf("Exiting...\n");

						destroyList(l); //deallocates all previously allocated memory

						//exits the program due to the occurrence of an error which
						//may disable/hinder the proper functioning of the program
						abort();
					}
				}
				break; //exits the switch

			case 2: //case for deletion of a student

				if (l->head == NULL) { //checks if the list is empty
					//prints appropriate message
					printf("No students have been added, hence cannot delete a student.\n");
					break; //exits the switch
				}
				printf("Enter the id of the student you want to delete:\n"); //requests input for student's id
				if (scanf("%lu", &id) != 1) { //checks whether the input is invalid
					printf("Invalid input!\n"); //informs the user their input is invalid
					break; //exits the switch
				}
				//the 'Result' type value the 'deleteStudentById' function returns is put in ERR_check
				//in order to later check if any errors occurred
				ERR_check = deleteStudentById(id, l); //deletes a specified student's data

				if (isError(ERR_check) == FALSE) { //checks for errors
					printf("The deletion was completed successfully.\n"); //prints appropriate message
				} else { //case where isError() is TRUE
					printf("A student with this id does not exist.\n"); //prints appropriate message
				}
				break; //exits the switch

            case 3: //case for searching of a student

				if (l->head == NULL) { //checks whether the list is empty
					//prints appropriate message
					printf("No students have been added, hence cannot search for a student.\n");
					break; //exits the switch
				}
				//requests input for student's id
				printf("Enter the id of the student you're looking for:\n");
				if (scanf("%lu", &id) != 1) { //checks whether the input is invalid
					printf("Invalid input!\n"); //informs the user their input is invalid
					break; //exits the switch
				}
				//the 'Result' type value the 'findStudent' function returns is put in ERR_check
				//in order to later check if any errors occurred
                ERR_check = findStudent(id, l, &st); //searches for a student specified by the user

				if (isError(ERR_check) == FALSE) { //checks for errors
					if (st.id == -1) { //case where the student with the id specified by the user does not exist
						//prints appropriate message
						printf("A student with this id does not exist.\n"); //doesn't mention id to avoid redundancy
					} else {
						//prints appropriate message
						printf("This student does exist.\n"); //doesn't mention id to avoid redundancy
					}
				}
                break; //exits the switch

            case 4: //case for modifying characteristics (name) of students

				if (l->head == NULL) { //checks whether the list is empty
					//prints appropriate message
					printf("No students have been added, hence cannot modify a student's characteristics.\n");
					break; //exits the switch
				}
				student stUpdate; //object to contain a student's id who will have their name updated
				//requests input for student's id
				printf("Please enter the id of the student who's characteristics you want to modify:\n");
				
				if (scanf("%lu", &stUpdate.id) != 1) { //checks whether the input is invalid
					printf("Invalid input!\n"); //informs the user their input is invalid
					break; //exits the switch
				}
				student stRepeat; //object to contain a student's new name
				//the 'Result' type value the 'findStudent' function returns is put in ERR_check
				//in order to later check if any errors occurred
				findStudent(stUpdate.id, l, &stRepeat); //searches for a student specified by the user

				if (stRepeat.id == -1) {
					 //prints appropriate message
					printf("A student with this id does not exist.\n"); //doesn't mention id to avoid redundancy
					break; //exits the switch
				}
				printf("Enter new name:\n"); //prints appropriate message
				if (scanf(" %s", stUpdate.name) != 1) { //checks whether the input is invalid
					printf("Invalid input!\n"); //informs the user their input is invalid
					break; //exits the switch
				}
				int repeat = 1; //local variable for case 4
				while (repeat) {
					//checks if the new name is the same as the previous one
					if (strcmp(stRepeat.name, stUpdate.name) == 0) {
						//prints appropriate messages
						printf("New name can't be the same as the previous one.\n");
						printf("Enter a different name:\n");
						if (scanf(" %s", stUpdate.name) != 1) { //checks whether the input is invalid
							printf("Invalid input! Try again:\n"); //informs the user their input is invalid
						}
						continue; //forces the next iteration of the loop (prevents repeat from becoming 0)
					}
					repeat = 0; //repeat becomes 0, because the name change was successful (the loop is exited from)
				}
				//the 'Result' type value the 'updateStudent' function returns is put in ERR_check
				//in order to later check if any errors occurred
                ERR_check = updateStudent(stUpdate, l); //changes a student's name

				if (isError(ERR_check) == FALSE) { //checks for errors
					printf("Success! New name: %s.\n", stUpdate.name); //prints appropriate message
				}
				else { //case where isError() returns TRUE and ERR_check is UNKNOWN_ERR
					printf("An unknown error has occurred.\n"); //prints appropriate message
				}
                break; //exits the switch

            case 5: //case for printing a student

				if (l->head == NULL) { //checks whether the list is empty
					//prints appropriate message
					printf("No students have been added, hence cannot print a student.\n");
					break; //exits the switch
				}
				student stPrnt; //object to contain a student's id

				printf("Enter the id of the student you're looking for:\n"); //requests input for student's id
				if (scanf("%lu", &id) != 1) { //checks whether the input is invalid
					printf("Invalid input!\n"); //informs the user their input is invalid
					break; //exits the switch
				}
				//the 'Result' type value the 'findStudent' function returns is put in ERR_check
				//in order to later check if any errors occurred
				ERR_check = findStudent(id, l , &stPrnt); //searches for a student specified by the user

				if (stPrnt.id == -1) { //checks for errors
					printf("A student with this id does not exist.\n"); //prints appropriate message
					break; //exits the switch
				}
				printStudent(stPrnt); //print a specific student's data
				break; //exits the switch

            case 6: //case for printing all students

                printStudents(l); //prints all existing student's data
                break; //exits the switch

			case 7: //case for saving all student data in a file and exiting

				printf("You have chosen to exit the program. Saving...\n"); //prints appropriate message
				//the 'Result' type value the 'save' function returns is put in ERR_check
				//in order to later check if any errors occurred
				ERR_check = save(argv[1], l); //saves the students' data in the file previously chosen by the user
				
				if (isError(ERR_check) == FALSE) { //NO_ERR case
					//prints appropriate message
					printf("The content of \"%s\" was saved successfully!\n", argv[1]);
				}
				else { //case where isError() is TRUE
					if (ERR_check == UNKNOWN_ERR) {
						//prints appropriate messages
						printf("An error occurred in the proccess of saving the content of \"%s\".\n", argv[1]);
						printf("Exiting...\n");
						destroyList(l); //deallocates all previously allocated memory
						//exits the program due to the occurrence of an error which
						//may disable/hinder the proper functioning of the program
						abort();
					}
					else { //case where ERR_check is F_WRITE_ERR
						//prints appropriate messages
						printf("An error occurred in the proccess of writing the content of \"%s\".\n", argv[1]);
						printf("Exiting...\n");
						destroyList(l); //deallocates all previously allocated memory
						//exits the program due to the occurrence of an error which
						//may disable/hinder the proper functioning of the program
						abort();
					}
				}
				printf("Exiting...\n"); //prints appropriate message
				destroyList(l); //deallocates all previously allocated memory
				return 0; //exits the program

			default: //gets executed if no case matches the user's input

				//informs the user their input is invalid
				printf("Invalid input! You need to select one of the available choices.\n");
				break; //not necessary, the switch will be exited from anyways, is however considered good practice
		}
	}
}
