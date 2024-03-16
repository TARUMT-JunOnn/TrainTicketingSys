#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include<time.h>
#pragma warning (disable : 4996)

typedef struct {
	int emp_id;
	int manager_id;
}Difference;

typedef struct {
	int staff_id;
	int staff_phoneNo;
	char staff_name[40];
	char staff_email[20];
	char staff_password[20];
	char manager_password[20];
	Difference dffid;
	char staff_position[30];
} Staff;

void staffLogin(FILE *fptr);
void staffCreateAcc();
void staff_Acc();
void staff_Manager();
void search_Staff_information();
void update_StaffInformation();


main() {
	struct tm* hour;
	char buffer[50];
	time_t t;
	time(&t);
	
	hour = localtime(&t);
	strftime(buffer, 50, "%X", hour);
	FILE* fptr;
	fptr = fopen("../TrainTicketingSys/res/staff.bin", "ab+");

	if (fptr == NULL) {
		printf("Can't Open File.\n");
		exit(-1);
	}

	int choice = 3;

	do {
		printf("------ STAFF MENU ------\n");
		printf("-------------------------\n");
		printf("1. Log In\n");
		printf("2. Sign In Acc\n");
		printf("3. Exit\n");
		if (choice != 3)
			printf("Please select again:");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			staffLogin(fptr);
			break;
		case 2:
			staffCreateAcc();
			break;
		case 3:
			printf("You are Log Out %s Right Now\n",buffer);
			break;
		default:
			printf("Invalid Select\n");

		}
	} while (choice != 3);

	fclose(fptr);
	return 0;
}


void staffCreateAcc() {
	Staff staff;
	printf("Enter your name: ");
	scanf("%[^\n]", staff.staff_name);
	printf("Enter your email:");
	scanf("%[^\n]", staff.staff_email);
	printf("\nCreate a password:");
	scanf("%[^\n]", staff.staff_password);

	printf("Enter your position: ");
	scanf("%s", &staff.staff_position);

}




void staffLogin(FILE *fptr) {

	int id;
	int manager_ID;
	char choice;

	printf("------ ONLY for STAFF Login ------\n");
	printf("\nEnter your staff ID: ");
	scanf("%d", &id);

	Staff staff;
	fseek(fptr, 0, SEEK_SET); //Move the file pointer to the beginning of the file

	while (fread(&staff, sizeof(Staff), 1, fptr) == 1) {

		if (id == staff.staff_id) {

			printf("Welcome %s", staff.staff_name);
			printf("\nLogin to Employee Acc (S/s) OR Manager Acc (M/m): ");
			scanf("%c", &choice);

			if (choice == 'M' || choice == 'm') {
				printf("You are logged in as an employee.\n");
				staff_Acc();

			}
			else if (choice == 'S' || choice == 's') {
				printf("You are logged in as an Manager.\n");
				staff_Manager();
			}
			else {		// maybe can add the checking if login failed 3 time logout directly
				printf(" Failed to Login. ");
			}
			return;
		}
	}
	printf("Can't founed the staff in system.\n");
}



void search_Staff_information() {
	// Display the schedules 
	// Display the particular staff information
}


//void update_StaffInformation() {
//	char name[40];
//	char confirm;
//
//
//	Difference dffid;
//
//	printf("Enter Staff Name:");
//	scanf("% [^\n]", name);
//
//	if (strcmp(name, staff.staff_name) == 0) {
//
//		printf("---------BEFOR EDIT-----------");
//		printf("\nName : %s\n", staff.staff_name);
//		printf("\nEmployee ID : %s\n", dffid.emp_id);
//		printf("\nEmail: %s", staff.staff_email);
//
//		printf("------------ADD---------------");
//		printf("Do you want to add phone_No ?");
//		printf("\nEnter Phone_No: ");
//		scanf("%d", &staff.staff_phoneNo);
//
//		printf("Confirm? ");
//		scanf("%c", &confirm);
//		rewind(stdin);
//		if (confirm == 'Y' || confirm == 'y') {
//			printf("\n");
//			printf("Edit was successfully!\n");
//		}
//		
//		printf("--------After edit---------------\n");
//		printf("\nName : %s\n", staff.staff_name);
//		printf("\nEmployee ID : %s\n", dffid.emp_id);
//		printf("\nEmail: %s", staff.staff_email);
//		printf("Phone No :%d\n", staff.staff_phoneNo);
//		
//	}
//
//
//}



void staff_Acc() {
	// Can see the rest time schedules (asses from staff file)
	char password[20];
	Difference dffid;
	Staff staff;

	printf("Please enter your Emp.ID:"); // all is difference ID.
	scanf("%d", &dffid.emp_id);
	printf("Please enter your password:");
	scanf("% [^\n]", password);

	if (strcmp(password, staff.staff_password) ==0 ) {
		printf("Your are sucessful login Acc");
		printf("Check the see :\n");
		printf("1. Employee rest schedule\n");
		printf("2. Check IN\n");
		printf("3. Check OUT\n");
		printf("4. Update Information\n");

	}
	else
		printf("Wrong Password!\n");
	




}


void staff_Manager() {
	// Edit rest time schedules
	printf("");
}