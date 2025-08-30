/* included libraries */
#include <stdio.h>
#include <stdlib.h>
#include "students.h" //includes header file containing the functions to be used in students.c
#include <time.h>

//function for initializations
void init() {

	srand(time(NULL)); //randomization
}

void printMenu() {
	//prints appropriate messages
	printf("Please choose from 1 to 7:\n1. Add a student\n2. Delete a student by id\n3. Find a student\n");
	printf("4. Modify a student's characteristics(change name)\n5. Print a student\n6. Print all students\n7. Quit\n");
}

unsigned long generateId() { //generates a random id

	return rand()%899999+100000; //returns a random 6-digit id
}

list createList() { //inspired by list.c

	list l = malloc(sizeof(struct listR)); //allocates needed memory

	if (l == NULL) { //checks whether the memory allocation was completed successfully
		//prints appropriate messages
		printf("An error occured in the process of memory allocation.\n");
		printf("Exiting...\n");

		//I don't use destroyList, since the memory allocation was not completed

		//exits the program due to the occurrence of an error which
		//may disable/hinder the proper functioning of the program
		abort();
	}
	//instantiates the head and tail of the list
	l->head = NULL;
	l->tail = NULL;

	return l; //returns list
}

Result load(char *stFile, list *l) {
	
	FILE *stream; //FILE-type object
	Result err; //object intended for the checking of different types of errors

	//inspired by: https://stackoverflow.com/questions/43777913/the-difference-in-file-access-mode-w-and-wb
	if ((stream = fopen(stFile, "rb")) == NULL) { //checks whether the file can be opened
		//showcases appropriate message
		printf("Failed to open \"%s\". Creating \"%s\"...\n", stFile, stFile);
		//inspired by: https://stackoverflow.com/questions/50738964/about-binary-modes-in-fopen
		if ((stream = fopen(stFile, "wb+")) == NULL) { //checks if there were any errors in fopen()
			return UNKNOWN_ERR; //returns the type of error that occurred
		}
		return NO_ERR; //returns the type of error that occurred (none in this case)
	}
	student ST; //object to be used in 'addStudent'
	//loads the students to the file and adds them to the list
	while (fread(&ST, sizeof(student), 1, stream) == 1) { //checks if there were any errors in fread()

		//the 'Result' type value the 'addStudent' function returns is put in err
		//in order to later check if any errors occurred
		err = addStudent(ST, *l); //adds a student's data to the list of students

		if (isError(err) == TRUE) {
			fclose(stream); //not necessary, is however considered good practice
			return F_READ_ERR; //returns the type of error that occurred
		}
	}
	//NO_ERR case
	fclose(stream); //not necessary, is however considered good practice
	return NO_ERR; //returns the type of error that occurred (none in this case)
}

Result save(char *stFile, list l) {

	FILE *stream; //FILE-type object
	//inspired by: https://stackoverflow.com/questions/50738964/about-binary-modes-in-fopen
	if ((stream = fopen(stFile, "wb+")) == NULL) { //checks if there were any errors in fopen()
		return UNKNOWN_ERR; //returns the type of error that occurred
	}
	node currentNode = l->head; //currentNode now shows to the beginning of the list
	while (currentNode != NULL) { //executes the code inside the brackets until reaching the end of the list
		//checks if there were any errors in fwrite()
		if (fwrite(&(currentNode->data), sizeof(student), 1, stream) != 1) {
			fclose(stream); //not necessary, is however considered good practice
			return F_WRITE_ERR; //returns the type of error that occurred
		}
		currentNode = currentNode->next; //has currentNode show to the next node
	}
	fclose(stream); //not necessary, is however considered good practice
	return NO_ERR; //returns the type of error that occurred (none in this case)
}

Result addStudent(student st, list l) {

	node n = malloc(sizeof(struct nodeR)); //allocates needed memory
	if (n == NULL) //checks whether the memory allocation was completed successfully
		return MALLOC_ERR; //returns the type of error that occurred

	//instantiates all attributes of the node n
	n->data = st;
	n->next = NULL;
	n->previous = NULL;
	
	if (l->head == NULL) {
		//instantiates the list
		l->head = n;
		l->tail = n;

		return NO_ERR; //returns the type of error that occurred (none in this case)
	}

	//has the pointers show to the next node
	//inspired by: https://intellipaat.com/blog/tutorial/c-tutorial/doubly-linked-list-in-c/?US
	n->previous = l->tail;
	l->tail->next = n;
	l->tail = n;

	return NO_ERR; //returns the type of error that occurred (none in this case)
}

Result findStudentNode(unsigned long id, list l, node *np) {

	node currentNode = l->head; //currentNode now shows to the beginning of the list

	while (currentNode != NULL) { //executes the code inside the brackets until reaching the end of the list

		if (currentNode->data.id == id) { //if currentNode equals the id given by the user then
										  //the code in the brackets is executed
			*np = currentNode; //puts currentNode in *np
			return NO_ERR; //returns the type of error that occurred (none in this case)
		}
		currentNode = currentNode->next; //has currentNode show to the next node
	}
	*np = NULL; //makes *np NULL because an error occurred

	return UNKNOWN_ERR; //returns the type of error that occurred
}

Result deleteStudentById(unsigned long id, list l) {

    node stNode; //object to be used in 'findStudentNode'
	Result err; //object intended for the checking of different types of errors
	//the 'Result' type value the 'findStudentNode' function returns is put in err
	//in order to later check if any errors occurred
	err = findStudentNode(id, l, &stNode); //searches for a student's node specified by the user

    if (isError(err) == TRUE) {
        return UNKNOWN_ERR; //returns the type of error that occurred
    }
	//NO_ERR case
    if (l->head == stNode) { //checks whether the to be deleted node is the head

        l->head = stNode->next;

        if (l->head == NULL) {
            l->tail = NULL; //makes the tail NULL
        } else {
            l->head->previous = NULL; //makes the previous pointer of the new head NULL
        }
        free(stNode); //deallocates the node's memory
        return NO_ERR; //returns the type of error that occurred (none in this case)
    }
    if (l->tail == stNode) { //checks whether the to be deleted node is the tail
        l->tail = l->tail->previous; //has the tail show to the previous one
        l->tail->next = NULL; //makes the next tail NULL
        free(stNode); //deallocates the node's memory
        return NO_ERR; //returns the type of error that occurred (none in this case)
    }
	//instantiates currentNode and previousNode
	node currentNode = l->head; //currentNode now shows to the beginning of the list
    node previousNode = NULL;
	
    while(currentNode != NULL) { //executes the code inside the brackets until reaching the end of the list
        if (currentNode == stNode){
            previousNode->next = currentNode->next;
            free(currentNode); //deallocates the node's memory
            return NO_ERR; //returns the type of error that occurred
        }
        previousNode = currentNode; //has previousNode show to currentNode
        currentNode = currentNode->next; //has currentNode show to the next node
    }
}

Result findStudent(unsigned long id, list l, student *st) {

	node currentNode = l->head; //currentNode now shows to the beginning of the list

	while (currentNode != NULL) { //executes the code inside the brackets until reaching the end of the list
		if (currentNode->data.id == id) { //if currentNode equals the id given by the user then
										  //the code in the brackets is executed
			*st = currentNode->data; //puts the data of the student with this id to *st
			return NO_ERR; //returns the type of error that occurred
		}
		currentNode = currentNode->next; //has currentNode show to the next node
	}
	st->id = -1; //shows that the id specified by the user does not exist
	
	return NO_ERR; //returns the type of error that occurred (none in this case)
}

Result updateStudent(student stUpdate, list l) {
	
	node st; //object to be used in 'findStudentNode'
	Result err; //object intended for the checking of different types of errors
	//the 'Result' type value the 'findStudentNode' function returns is put in err
	//in order to later check if any errors occurred
	err = findStudentNode(stUpdate.id, l, &st); //searches for a student's node specified by the user

	if (isError(err) == TRUE) //checks if any errors occurred
		return UNKNOWN_ERR; //returns the type of error that occurred
	
	st->data = stUpdate; //updates the student's data

	return NO_ERR; //returns the type of error that occurred (none in this case)
}

void printStudent(student stPrnt) {

	//prints the student's data
	printf("Student's data:\n");
	printf("id: %lu\tname: %s\n", stPrnt.id, stPrnt.name);
	return; //returns to main
}

void printStudents(list l) {

	node currentNode = l->head; //currentNode now shows to the beginning of the list
	if (currentNode == NULL) { //checks whether any students have been added to the list
		//showcases appropriate message
		printf("No students have been added, hence cannot print any students.\n");
		return; //returns to main
	}
	while (currentNode != NULL) { //prints student data until it reaches the end of the list
		//prints the data of each student
		printf("Student's data:\n");
		printf("id: %lu\tname: %s\n", currentNode->data.id, currentNode->data.name);
		currentNode = currentNode->next; //has currentNode show to the next node
	}
	return; //returns to main
}

int isError(Result err) {

	if (err == NO_ERR) //checks if no errors occurred
		return FALSE; //returns FALSE in the case that no errors occurred
	//case where an error did occur
	return TRUE; //returns TRUE in the case that an error occurred
}

void destroyList(list l) { //used from list.c

	node currentNode = l->head; //currentNode now shows to the beginning of the list

	//deallocates all previously allocated memory until reaching the end of the list
	while (currentNode != NULL) {
		node tmp = currentNode->next;
		free(currentNode);
		currentNode = tmp;
	}
	free(l);
}
