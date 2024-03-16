#include <stdio.h>
#include <stdlib.h>
#pragma warning ( disable : 4996 )

struct Staff {
	int staff_id;
	char staff_name[40];
	char staff_email[20];
	char staff_password[20];
	char staff_position[30];
	};








main() {
	
	struct Staff staff;
	system("pause");
}

void staffMenu() {
	char yes;

	printf("------ STAFF MENU ------\n");
	printf("-------------------------\n");
	printf("Already have an account?(Y/N):");
	scanf("%s",&yes)
		if (yes == Y) {
			staffLogin();
		}
		else {
			printf("Sign In -->");
			staffCreateAcc();
		}
		

}


void staffLogin() {
	int id

	printf("ONLY for STAFF Login\n");
	while (id == staff_id) {
		printf("||")
	}
}

void staffCreateAcc() {

	printf("Enter your name: ");
	scanf("% [^\n]", staff_name);
	printf("Enter your email:");
	scanf("% [^\n]", staff_email);
	printf("\nCreate a password:");
	scanf("% [^\n]", staff_password);

	printf("Enter your position: ");
	scanf("%s", &staff_position);

}

void search_Staff_information() {

}

void search_Staff_restTime() {

}

void update_StaffInformation() {

}

void staff_position() {
	printf("Manager(M) OR Staff(S): ");

}