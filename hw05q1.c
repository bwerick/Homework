
// CSE240 Spring 2019 HW5
// Erick Duarte
// Visual studio and gcc

// READ BEFORE YOU START:
// You are given a partially completed program that creates a list of patients, like patients' record.
// Each record has this information: patient's name, doctor's name, critical level of patient, room number.
// The struct 'patientRecord' holds information of one patient. Critical level is enum type.
// An array of structs called 'list' is made to hold the list of patients.
// To begin, you should trace through the given code and understand how it works.
// Please read the instructions above each required function and follow the directions carefully.
// You should not modify any of the given code, the return types, or the parameters, you risk getting compile error.
// You are not allowed to modify main ().
// You can use string library functions.

// WRITE COMMENTS FOR IMPORANT STEPS IN YOUR CODE.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable: 4996) // for Visual Studio Only

#define MAX_PATIENTS 15
#define MAX_NAME_LENGTH 25

typedef enum { very_critical = 0, critical, not_critical } criticalType; // enum type 

struct patientRecord {					// struct for patient details
	char patientName[MAX_NAME_LENGTH];
	char doctorName[MAX_NAME_LENGTH];
	criticalType criticalLevel;
	unsigned int roomNumber;
};

struct patientRecord list[MAX_PATIENTS]; // declare list of patients
int count = 0;							// the number of patients currently stored in the list (initialized to 0)

// functions already implmented
void flushStdIn();
void executeAction(char);
void save(char* fileName);

// functions that need implementation:
int add(char* patientName_input, char* doctorName_input, char* criticalLevel_input, unsigned int roomNumber_input); // 20 points
void display();				// 10 points
void sort();				// 10 points
void load(char* fileName);	// 10 points

int main()
{
	char* fileName = "Patient_List.txt";
	load(fileName);	// load list of patients from file (if it exists). Initially there will be no file.
	char choice = 'i';		// initialized to a dummy value
	do
	{
		printf("\nEnter your selection:\n");
		printf("\t a: add a new patient\n");
		printf("\t d: display patient list\n");
		printf("\t s: sort patient list by name\n");				
		printf("\t q: quit\n");
		choice = getchar();
		flushStdIn();
		executeAction(choice);
	} while (choice != 'q');

	save(fileName); // save list of patients to file (overwrites file, if it exists)
	return 0;
}

// flush out leftover '\n' characters
void flushStdIn()
{
	char c;
	do c = getchar(); 
	while (c != '\n' && c != EOF);
}

// ask for details from user for the given selection and perform that action
void executeAction(char c)
{
	char patientName_input[MAX_NAME_LENGTH], doctorName_input[MAX_NAME_LENGTH];
	unsigned int roomNumber_input, add_result= 0;
	char criticalLevel_input[20];
	switch (c)
	{
	case 'a':
		// input patient record from user
		printf("\nEnter patient name: ");
		fgets(patientName_input, sizeof(patientName_input), stdin);
		patientName_input[strlen(patientName_input) - 1] = '\0';	// discard the trailing '\n' char
		printf("Enter doctor name: ");
		fgets(doctorName_input, sizeof(doctorName_input), stdin);
		doctorName_input[strlen(doctorName_input) - 1] = '\0';	// discard the trailing '\n' char
		
		printf("Enter whether patient is 'very critical' or 'critical' or 'not critical': ");
		fgets(criticalLevel_input, sizeof(criticalLevel_input), stdin);
		criticalLevel_input[strlen(criticalLevel_input) - 1] = '\0';	// discard the trailing '\n' char
		printf("Please enter room number: ");
		scanf("%d", &roomNumber_input);
		flushStdIn();

		// add the patient to the list
		add_result = add(patientName_input, doctorName_input, criticalLevel_input, roomNumber_input);
		if (add_result == 0)
			printf("\nPatient is already on the list! \n\n");
		else if (add_result == 1)
			printf("\nPatient successfully added to the list! \n\n");
		else
			printf("\nUnable to add. Patient list is full! \n\n");

		break;
	case 'd': display();	break;
	case 's': sort();		break;
	
	case 'q': break;
	default: printf("%c is invalid input!\n",c);
	}
}

// Q1 : add (20 points)
// This function is used to add a patient into the list. You can simply add the new patient to the end of list (array of structs).
// Do not allow the patient to be added to the list if it already exists in the list. You can do that by checking patient names already in the list.
// If the patient already exists then return 0 without adding it to the list. If the patient does not exist in the list then go on to add the patient at the end of the list and return 1.
// If patient list is full, then do not add new patientto the list and return 2.
// NOTE: Notice how return type of add() is checked in case 'a' of executeAction()
// NOTE: You must convert the string 'criticalLevel_input' to an enum type and store it in the list because the critical level has enum type (not string type).
// The list should be case sensitive. For instance, 'Roger' and 'roger' should be considered two different names.
// Hint: 'count' holds the number of patients currently in the list
int add(char* patientName_input, char* doctorName_input, char* criticalLevel_input, unsigned int roomNumber_input)
{
	int i;
	if (count == MAX_PATIENTS) { //if patients list is full it will return this
		return 2;
	}
	else {

		for (i = 0; i < count; i++) {  //loops through the elements of the struct array to see if patient name already exists
			if (strcmp(patientName_input, list[i].patientName) == 0) {
				return 0; //if match found, returns 0
			}
		}//end for loop, if it doesnt return 0, it moves on to the next line
		strcpy(list[count].patientName, patientName_input); //adds patient name
		strcpy(list[count].doctorName, doctorName_input); //adds doctor name
		
		list[count].roomNumber = roomNumber_input; //adds room number

		if (strcmp(criticalLevel_input, "very critical") == 0) { //series of if statemetns compare the critical level input 

			list[count].criticalLevel = very_critical; //if match, set to very critical
		}
		else if (strcmp(criticalLevel_input, "critical") == 0) {

			list[count].criticalLevel = critical; //if match, set to critical
		}
		else if (strcmp(criticalLevel_input, "not critical") == 0) {

			list[count].criticalLevel = not_critical; //if match set to not critical
		}
		else {
			list[count].criticalLevel = critical; //default if input is wonky
		}


		count++;
		return 1;			// edit this line as needed
	}
}


// Q2 : display (10 points)
// This function displays the patient list with the details (struct elements) of each patient. 
// Parse through the list and print the patient details one after the other. See expected output screenshots in question pdf file.
// NOTE: Critical level is stored in the struct as enum type. You need to display 'very critical','critical' or 'not critical'
void display()
{
	int i;
	char critl[16]; //gave enough characters for the diffrenet critical messges
	for (i = 0; i < count; i++) { //loops up until the net open indez\x
		printf("Patient name: %s\n", list[i].patientName); //prints patuent name
		printf("Doctor name: %s\n", list[i].doctorName);//prints doc name

		if (list[i].criticalLevel == not_critical) {
			strcpy(critl, "not critical");		//if else if to figure out which critical state and print the correct one
		}
		else if (list[i].criticalLevel == very_critical) {
			strcpy(critl, "very critical");
		}
		else {
			strcpy(critl, "critical");
		}

		printf("Critical level: %s\n", critl); //prints criticl state
		printf("Room number: %d\n\n", list[i].roomNumber); //prints room
	}
}

// Q3 : sort (10 points)
// This function is used to sort the list(array of structs) alphabetically by patient name.
// Parse the list and compare the patient names to check which one should appear before the other in the list.
// Sorting should happen within the list. That is, you should not create a new array of structs having sorted patients.
// Hint: One of the string library function can be useful to implement this function because the sorting needs to happen by patient name which is a string.
//       Use a temp struct (already declared) if you need to swap two structs in your logic
void sort()
{	
	struct patientRecord patientTemp;	// needed for swapping structs. Not absolutely necessary to use.
	// enter code here
	int i;
	int j;
	for (i = 0; i < count; i++) { //loops until next open index
		for (j = i + 1; j < count; j++) { //compares the i to the next index
			if (strcmp(list[i].patientName, list[j].patientName) > 0) {
				patientTemp = list[i];
				list[i] = list[j];  //good ol' swap
				list[j] = patientTemp;
			}
		}
	}


	// display message for user to check the result of sorting.
	printf("\nPatient list sorted! Use display option 'd' to view sorted list.\n");
}

// save() is called at the end of main()
// This function saves the array of structures to file. It is already implemented.
// You should read and understand how this code works. It will help you with 'load()' function.
// save() is called at end of main() to save the patient list to a file.
// The file is saved at the same place as your C file. For VS, the default directory looks like this:
// C:\Users\<username>\Documents\Visual Studio 2017\Projects\Project1\Project1
// You can simply delete the file to 'reset the list' or to avoid loading from it.
void save(char* fileName)
{	
	FILE* file;
    int i, criticalLevelValue=0;
	file = fopen(fileName, "wb");		// open file for writing
	
	fwrite(&count, sizeof(count), 1, file);		// First, store the number of patients in the list
	
	// Parse the list and write patient record to file
	// 
	for (i = 0; i < count; i++)
	{
		fwrite(list[i].patientName, sizeof(list[i].patientName), 1, file);
		fwrite(list[i].doctorName, sizeof(list[i].doctorName), 1, file);
		// convert enum to a number for storing
		if (list[i].criticalLevel == very_critical)
			criticalLevelValue = 0;		// 0 for very_critical
		else if (list[i].criticalLevel == critical)
			criticalLevelValue = 1;		// 1 for critical
		else
			criticalLevelValue = 2;		// 2 for not_critical

		fwrite(&criticalLevelValue, sizeof(criticalLevelValue), 1, file);
		fwrite(&list[i].roomNumber, sizeof(list[i].roomNumber), 1, file);
	}
	
	fclose(file);			// close the file after writing
}

// Q4:  load (10 points)
// This function is called in the beginning of main().
// This function reads the patient list from the saved file and builds the array of structures 'list'. 
// In the first run of the program, there will be no saved file because save() is called at the end of program.
// So at the begining of this function, write code to open the file and check if it exists. If file does not exist, then return from the function.
// (See expected output of add() in homework question file. It displays "Patient_List.txt not found" because the file did not exist initially.)
// If the file exists, then parse the patient list to read the patient details from the file.
// Use the save function given above as an example of how to write this function. Notice the order in which the struct elements are saved in save()
// You need to use the same order to read the list back.
// NOTE: The saved file is not exactly readable because all elements of the struct are not string or char type.
//       So you need to implement load() similar to how save() is implemented. Only then the 'list' will be loaded correctly.
//		You can simply delete the file to 'reset the list' or to avoid loading from it.
void load(char* fileName)
{
	FILE* file;
	int i = 0, criticalLevelValue = 0;
	file = fopen(fileName, "r"); //opens file
	if (file == NULL) {//executes if file didnt exist
		printf("Patient_List.txt not found.\n\n");
	}
	else
	{ 
		printf("Patients record loaded from Patient_List.txt.\n\n");
		fread(&count, sizeof(count), 1, file); //reads file entries, and brings count back to where it was last time
		for (i = 0; i < count; i++)
		{
			fread(list[i].patientName, sizeof(list[i].patientName), 1, file); //repopulates the array
			fread(list[i].doctorName, sizeof(list[i].doctorName), 1, file);
			// convert enum to a number for storing
			fread(&criticalLevelValue, sizeof(criticalLevelValue), 1, file);
			fread(&list[i].roomNumber, sizeof(list[i].roomNumber), 1, file);
			if (criticalLevelValue == 0) {

				list[i].criticalLevel = very_critical;// 0 for very_critical  //convert from int critical level value back to enum to be used elsewehere
			}
			else if (criticalLevelValue == 1) {
				list[i].criticalLevel = critical;// 1 for critical
			}
			else
				list[i].criticalLevel = not_critical;;		// 2 for not_critical

			
			
		}

	}
}
