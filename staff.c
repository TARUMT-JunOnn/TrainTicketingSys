#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#pragma warning (disable : 4996)

//Define employee login information structure
typedef struct {
	int emp_id;
	int manager_id;
	char staff_password[20];
	char manager_password[20];
}Difference;

// Define employee structure
typedef struct {
	int staff_id;
	int staff_phoneNo;
	char staff_name[40];
	char staff_email[20];
	char staff_position[30];
} Staff;

void staffCreateAcc(FILE* fptr);
void staffLogin();
void staff_Acc();
void staff_Manager();
void delect_ACC();
void search_Staff_information();
void update_StaffInformation();

// Staff main menu
main() {
	struct tm* hour;
	char buffer[50];
	time_t t;
	time(&t);

	hour = localtime(&t);
	strftime(buffer, 50, "%X", hour);

	FILE* fptr;
	FILE* fptr2;
	fptr = fopen("../TrainTicketingSys/res/staff.bin", "ab+");
	fptr2 = fopen("../TrainTicketingSys/res/result.bin", "wb+");

	if (fptr == NULL) {
		printf("Can't Open File.\n");
		exit(-1);
	}

	int choice;

	do {
		printf("------ STAFF MENU ------\n");
		printf("-------------------------\n");
		printf("1. Sign In Acc\n");
		printf("2. Log In Acc\n");
		printf("3. Exit\n");
		scanf("%d", &choice);
		if (choice != 3)
			printf("Please select again:\n");

		switch (choice) {
		case 1:
			staffCreateAcc(fptr);
			break;
		case 2:
			staffLogin(fptr);
			break;
		case 3:
			printf("\nYou are Log Out %s Right Now!\n", buffer);
			break;
		}
	} while (choice != 3);

	fclose(fptr);
	return 0;
}


// Staff create acc
void staffCreateAcc(FILE* fptr) {
	Staff staff;
	Difference dffid;
	staff.staff_id = 518518;

	rewind(stdin);
	printf("\nEnter your name: ");
	scanf("%[^\n]", staff.staff_name);
	rewind(stdin);
	printf("\nEnter your email:");
	scanf("%[^\n]", staff.staff_email);
	rewind(stdin);
	printf("\nCreate a password:");
	scanf("%[^\n]", dffid.staff_password);
	rewind(stdin);
	printf("\nEnter your position: ");
	scanf("%[^\n]", &staff.staff_position);
	rewind(stdin);

	fwrite(&staff, sizeof(Staff), 1, fptr);
	printf("\nAlready Add Staff Information To File\n");
}



// Staff Login Acc
void staffLogin(FILE* fptr) {
	int id;
	int manager_ID;
	char choice;
	Staff staff;

	printf("------ ONLY for STAFF Login ------\n");
	printf("\nEnter your staff ID: ");
	scanf("%d", &id);

	fseek(fptr, 0, SEEK_SET); //Move the file pointer to the beginning of the file

	while (fread(&staff, sizeof(Staff), 1, fptr) == 1) {
		if (id == staff.staff_id) {
			printf("Welcome %s", staff.staff_name);
			printf("\nLogin to Employee Acc (S/s) OR Manager Acc (M/m): ");
			rewind(stdin);
			scanf("%c", &choice);

			if (choice == 'M' || choice == 'm') {
				printf("You are logged in as an manager.\n");
				staff_Manager(fptr);
			}
			else if (choice == 'S' || choice == 's') {
				printf("You are logged in as an Employee.\n");
				staff_Acc();
			}
			else {		// maybe can add the checking if login failed 3 time logout directly
				printf("\nFailed to Login.\n");
			}
			return;
		}
	}
	printf("Can't founed the staff in system.\n");
}


// Login to manager acc
// Edit rest time schedules
//Delect staff Acc
void staff_Manager(FILE* fptr) {
	int id;
	char password[20];
	Difference dffid;
	Staff staff;

	printf("\nPlease enter you manager ID :");
	scanf("%d", &id);
	printf("\nPlease enter you Manager Password:");
	scanf("% [^\n]", &password);
	rewind(stdin);

	while (fread(&dffid, sizeof(Difference), 1, fptr) == 1) {
		if (id == dffid.emp_id) {
			if (id == dffid.manager_id && strcmp(password, dffid.manager_password) == 0) {
				printf("Manager login successful!\n");
				return;
			}
		}
		printf("Sorry can't found this staff\n");
	}




	// Login to emp acc
	void staff_Acc(); {
		// Can see the rest time schedules (asses from staff file)
		char password[20];
		Difference dffid;
		Staff staff;

		printf("Please enter your Emp.ID:"); // all is difference ID.
		scanf("%d", &dffid.emp_id);
		printf("Please enter your password:");
		scanf("% [^\n]", password);

		if (strcmp(password, dffid.staff_password) == 0) {
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



	//void update_StaffInformation() {
	//	char name[40];
	//	char confirm;
	//	char add;
	//
	//	Difference dffid;
	//  Staff staff;
	//
	//	printf("Enter Staff Name:");
	//	scanf("% [^\n]", name);
	//
	//	if (strcmp(name, staff.staff_name) == 0) {
	//
	//		printf("\n---------BEFOR EDIT-----------\n");
	//		printf("\nName : %s\n", staff.staff_name);
	//		printf("\nEmployee ID : %s\n", dffid.emp_id);
	//		printf("\nEmail: %s", staff.staff_email);
	// 
	//		printf("Please enter New email :");
	//		scanf("% [^\n]", staff.staff_email);
	//		printf("Please enter New phone No : ");
	//		scanf("%d", staff.staff_phone_No);
	// 		//maybe can let loop like when want to edit email only then just out for this edit menu.
	//
	//		printf("\n------------ADD---------------\n");
	//		printf("Do you want to add phone_No ?");
	//		printf(" \nY/y OR N/n : ");
	//		scanf("%c", &add);
	//		
	//		if (  add == 'Y || add == 'y' ) {
	// 
	//			printf("\nEnter Phone_No: ");
	//			scanf("%d", &staff.staff_phoneNo);
	//	} else {
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

	void delect_ACC(); {
		system("cls");
		char empname[50];
		char confirm;
		int size;

		printf("\nEnter Employee Name to DELECT :");
		scanf("%[^\n]", empname);
		printf("\nConfirm ?\n");
		scanf("%c", &confirm);

		while (confirm == 'y' || confirm == 'Y') {

			fptr = fopen("staff.bin", "wb+");
			rewind(fptr2);

			while (fread(&staff, size, 1, fptr) == 1) {
				if (strcmp(staff.staff_name, empname) != 0)
					fwrite(&staff, size, 1, fptr2);
			}

			fclose(fptr);
			//remove("staff.bin");
			rename("staff.bin", "result.bin");
			fptr2 = fopen("result.bin", "rb+");


			printf("\nWant to delete another"
				" record (Y/N) :");
			fflush(stdin);
			confirm = getche();
		}

	}



	// Searching staff information 
	void search_Staff_information(); {
		// Display the schedules (staff user)
		// Display the particular staff information (manager use)
	}
