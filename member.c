#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <time.h>
#pragma warning(disable:4996)
#define MEMBER_NAME 100
#define MEMBER_PASS 100
#define MAX_NUMBER_MEMBER 100 
#define MAX_NUM_QUESTION 3
#define MAX_PHONE_NUM 15
#define MAX_LENGTH_EMAIL 50

int tryAgain(int again);
void memberMenu(struct Member* member);
void memberLogin(struct Member* member);
void securityQuestion();
void questionTitle(int questionSelection[MAX_NUM_QUESTION], char questionName[MAX_NUM_QUESTION][100]);
void memberRegister(struct Member* member);
void forgotPass(struct Member* member);
void memberMainPage(struct Member* member, int memberNUM);
void viewProfile(struct Member* member, int memberNUM);
void viewSchedule();
void addBooking();
void bookingHistory();
void cancelBooking();
void rewardPoint();




struct SecurityQuestion {
	int questionNum;
	char answer[100];
};

struct Member {
	char id[MEMBER_NAME];
	char pass[MEMBER_PASS];
	char phoneNo[MAX_PHONE_NUM];
	char email[MAX_LENGTH_EMAIL];
	struct SecurityQuestion security[MAX_NUM_QUESTION];

};

int numMember = 0;

main() {
	struct Member member[MAX_NUMBER_MEMBER];
	system("cls");
	memberMenu(member);

}

int tryAgain(int again) {
	int choice, invalidChoice = 0;

	do {
		again = 0;
		invalidChoice = 0;
		printf("Do you want to try again?\n");
		printf("1. Yes\n");
		printf("2. No\n");
		printf("Please Enter Your Choice: ");
		scanf("%d", &choice);

		if (choice == 1) {
			again++;
			return again;
		}
		else if (choice == 2)
			return 0;
		else {
			printf("Invalid Choice\n");
			printf("Please Enter A Valid Choice\n");
			invalidChoice++;
		}
	} while (invalidChoice == 1);
}

void memberMenu(struct Member* member) {
	char *menu[] = {"Login", "Registration", "Forgot Password", "Exit Program"};
	int choice;
	do {

	system("cls");
	printf("Member Menu\n");
	printf("-----------\n");
	for (int i = 0; i < sizeof(menu)/sizeof(menu[0]); i++) {
		printf("-----\n");
		printf("| %d | %s\n", i + 1, menu[i]);
		printf("-----\n");
	}
	printf("Please Enter Your Choice: ");
	scanf("%d", &choice);
		switch (choice) {
		case 1: 
			memberLogin(member);
			break;
		case 2:
			memberRegister(member);
			break;
		case 3: 
			forgotPass(member, numMember);
			break;
		case 4:
			printf("EXITING PROGRAM.....\n");
			break;
		default:
			printf("Invalid Choice!\n");
			printf("Please Try Again\n");
		}
	} while (choice !=4);
}

void memberLogin(struct Member* member) {
	char name[MEMBER_NAME], password[MEMBER_PASS];
	int memberNUM;
	int loginSuccess = 0, again = 0;
	
	do {
		again = 0;

		system("cls");
		printf("ID: ");
		scanf(" %[^\n]", name);
		printf("Password: ");
		scanf(" %[^\n]", password);

		for (int i = 0; i < MAX_NUMBER_MEMBER; i++) {
			if (strcmp(member[i].id, name) == 0 && strcmp(member[i].pass, password) == 0) {
				printf("Login successful...\n");
				memberNUM = i;
				memberMainPage(member, memberNUM);
				loginSuccess++;
			}
		}

		if (loginSuccess == 0) {

				printf("Invalid ID or Password\n");
				again = tryAgain(again);			
		}
	} while (again == 1);
	

}

void securityQuestion() {
		printf("\nSecurity Questions\n");

		printf("\n-----------------------\n");
		printf("1. My Favourite Color\n");
		printf("2. My Favourite Car\n");
		printf("3. My favourite movie\n");
		printf("4. The Title Of The First Book I Read\n");
		printf("5. Name Of My Childhood Best Friend\n");
		printf("6. Model Of My First Car\n");

		printf("\nPlease Choose 3 Security Questions\n");
}

void questionTitle(int questionSelection[MAX_NUM_QUESTION], char questionName[MAX_NUM_QUESTION][100]) {
	for (int i = 0; i < 3; i++) {

		if (questionSelection[i] == 1) {
			strcpy(questionName[i], "My Favourite Color");
		}
		else if (questionSelection[i] == 2) {
			strcpy(questionName[i], "My Favourite Car");
		}
		else if (questionSelection[i] == 3) {
			strcpy(questionName[i], "My favourite movie");
		}
		else if (questionSelection[i] == 4) {
			strcpy(questionName[i], "The Title Of The First Book I Read");
		}
		else if (questionSelection[i] == 5) {
			strcpy(questionName[i], "Name Of My Childhood Best Friend");
		}
		else {
			strcpy(questionName[i], "Model Of My First Car");
		}
	}
}

void memberRegister(struct Member* member) {
	
	char memberID[MEMBER_NAME], password[MEMBER_PASS], phone[MAX_PHONE_NUM], email[MAX_LENGTH_EMAIL];
	int again;
	int questionSelection[MAX_NUM_QUESTION], success;
	char question[MAX_NUM_QUESTION][100], answer[MAX_NUM_QUESTION][100];


	do {
		again = 0;
		system("cls");

		printf("ID: ");
		scanf(" %[^\n]", memberID);
		printf("Password: ");
		scanf(" %[^\n]", password);

		for (int i = 0; i < MAX_NUMBER_MEMBER; i++) {
			if (strcmp(member[i].id, memberID) == 0) {
					printf("The username %s already exits.\n", memberID);
					printf("Please choose a different username.\n");
					again = tryAgain(again);
					if (again == 0)
						return 0;
			}
		}
	} while (again == 1);

	strcpy(member[numMember].id, memberID);
	strcpy(member[numMember].pass, password);

	do {
		again = 0;
		success = 1;

		securityQuestion();

		for (int i = 0; i < MAX_NUM_QUESTION; i++) {
			printf("%d. ", i + 1);
			scanf("%d", &questionSelection[i]);

			if (questionSelection[i] > 6 || questionSelection[i] < 1) {
				printf("Invalid Choice!\n");
				printf("Please Enter Number 1 - 6!\n");
				success = 0;
				break;
			}
			if (i > 0) {
				for (int x = 0; x < i; x++) {
					if (questionSelection[i] == questionSelection[x]) {
						printf("\nThe Selected Security Question Must Be Different From The Previous One.\n");
						printf("Please Try Again.\n");
						again++;
						success = 0;
						break;
					}
				}
				if (again == 1)
					break;
			}
		}
	} while(success != 1);

	for (int i = 0; i < 3; i++) {
		member[numMember].security[i].questionNum = questionSelection[i];
	}

	questionTitle(questionSelection, question);



	for (int i = 0; i < MAX_NUM_QUESTION; i++) {
		printf("%s ?\n", question[i]);
		printf("Answer: ");
		scanf(" %[^\n]", answer[i]);
		strcpy(member[numMember].security[i].answer, answer[i]);
	}

	printf("\nRegistration successfully\n\n");

	printf("Phone number(011-XXXXXXX): ");
	scanf(" %[^\n]", phone);
	printf("Email: ");
	scanf(" %[^\n]", email);

	strcpy(member[numMember].phoneNo, phone);
	strcpy(member[numMember].email, email);

	printf("Phone and email are added\n");

	numMember++;

}

void forgotPass(struct Member* member) {
	char id[MEMBER_NAME], question[MAX_NUM_QUESTION][100], answer[MAX_NUM_QUESTION][100];
	int num, questionSelection[MAX_NUMBER_MEMBER], newPassword[100];
	int idExist = 0, again = 0, securityPass = 0, choice, invalidChoice = 0;

	do {
		system("cls");
		printf("ID: ");
		scanf(" %[^\n]", id);
		
		for (int i = 0; i < MAX_NUMBER_MEMBER; i++) {
			if (strcmp(member[i].id, id) == 0) {
				num = i;
				idExist++;
			}
			
		}

		
		if (idExist == 1) {
			do {
				again = 0;
				securityQuestion();

				for (int i = 0; i < MAX_NUM_QUESTION; i++) {
					printf("%d. ", i + 1);
					scanf("%d", &questionSelection[i]);

					if (questionSelection[i] > 6 || questionSelection[i] < 1) {
						printf("Invalid Choice!\n");
						printf("Please Enter Number 1 - 6 !\n");
						again = 1;
						break;
					}

				}
			} while (again == 1);

			questionTitle(questionSelection, question);

			for (int i = 0; i < MAX_NUM_QUESTION; i++) {
				printf("%s ?\n", question[i]);
				printf("Answer: ");
				scanf(" %[^\n]", answer[i]);
			}

			for (int i = 0; i < MAX_NUM_QUESTION; i++) {
				for (int x = 0; x < MAX_NUM_QUESTION; x++) {
					if (member[num].security[i].questionNum == questionSelection[x] && strcmp(member[num].security[i].answer, answer[x]) == 0)
						securityPass++;

				}
			}
			if (securityPass == 3) {
				printf("Please Enter New Password: ");
				scanf(" %[^\n]", newPassword);
				strcpy(member[num].pass, newPassword);
				printf("\nYour Password Has Been Updated Successfully\n");
				return 0;
			}
			else {
				printf("\nInvalid Security Questions Or Answer!\n");
				again = tryAgain(again);
			}
		}
		else {
			printf("Invalid ID!\n");
				
			again = tryAgain(again);

		}

		
	} while (again == 1);


}

void memberMainPage(struct Member* member, int memberNUM) {
	int choice;
	char* menu[] = { "Display Profile", "View Schedule", "Add Booking",
					"Display Booking History", "Cancel Booking", "Reward Points", "Exit" };

	do
	{
		system("cls");
		printf("Welcome %s\n", member[memberNUM].id);
		//remove id and pass
		printf("Pass: %s", member[memberNUM].pass);
		printf("Member Menu\n");
		printf("-----------\n");
		for (int i = 0; i < sizeof(menu) / sizeof(menu[0]); i++) {
			printf("-----\n");
			printf("| %d | %s\n", i + 1, menu[i]);
			printf("-----\n");
		}

		printf("Enter Your Choice: ");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			viewProfile(member, memberNUM);
			break;
		case 2:
			viewSchedule();
			break;
		case 3: 
			addBooking();
			break;
		case 4:
			bookingHistory();
			break;
		case 5:
			cancelBooking();
			break;
		case 6:
			rewardPoint();
			break;
		case 7:
			printf("EXITING MEMBER MENU\n");
			break;
		default:
			printf("Invalid Choice\n");
		}
	} while (choice != 7);

}

void viewProfile(struct Member* member, int memberNUM) {
	int choice, modify, again = 0;
	char oldPassword[MEMBER_PASS], newPassword[MEMBER_PASS], passConfirm[MEMBER_PASS];

	do {
		system("cls");
		again = 0;
		printf("Profile Information\n");
		printf("--------------------\n");
		printf("ID: %s\n", member[memberNUM].id);
		printf("Contact Number: %s\n", member[memberNUM].phoneNo);
		printf("Email: %s\n", member[memberNUM].email);
		printf("\nEnter 1 to MODIFY PROFILE (0 EXIT)\n");
		scanf("%d", &choice);

		if (choice == 1) {
			printf("----------------------\t ----------------------\t ----------------------\n");
			printf("| 1 | Password       |\t | 2 | Contact Number |\t | 3 | Email          |\n");
			printf("----------------------\t ----------------------\t ----------------------\n");

			printf("\nEnter your choice: ");
			scanf("%d", &modify);

			if (modify == 1) {
				do {
					again = 0;
					system("cls");
					printf("Old Password: ");
					scanf(" %[^ \n]", oldPassword);
					printf("New Password: ");
					scanf(" %[^ \n]", newPassword);
					printf("Confirm Password: ");
					scanf(" %[^ \n]", passConfirm);

					if (strcmp(member[memberNUM].pass, oldPassword) != 0) {
						printf("Old Password Incorrect\n");
						again = tryAgain(again);
						continue;
					}

					if (strcmp(newPassword, passConfirm) != 0) {
						printf("New Password and Confrim Password Are Not Same\n");
						again = tryAgain(again);
						continue;
					}


				} while (again == 1);

				if (strcmp(member[memberNUM].pass, oldPassword) == 0 && strcmp(newPassword, passConfirm) == 0) {
					strcpy(member[memberNUM].pass, newPassword);
					printf("Password is changing. ");
					for (int i = 0; i < 3; i++) {
						Sleep(300);
						printf(". ");
						Sleep(300);
					}
				}

			}

			else if (modify == 2) {
				printf("New Contact Number: ");
				scanf(" %[^\n]", member[memberNUM].pass);
				printf("Contact Number successfully changed\n");
			}
			else if (modify == 3) {
				printf("New Email: ");
				scanf(" %[^\n]", member[memberNUM].email);
				printf("email successfully changed\n");
			}
			else {
				printf("Invalid Choice\n");
				again = tryAgain(again);
			}
		}
		else if (choice == 0)
			return 0;

		else
			again++;
	} while(again == 1);
}

void viewSchedule() {

}

void addBooking() {

}

void bookingHistory(){
}

void cancelBooking() {

}

void rewardPoint() {

}