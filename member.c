#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include "common.c"
#pragma warning(disable:4996)

//ensure the strncat_s no warning even the size is larger
#define _CRT_SECURE_NO_WARNINGS

#define MEMBER_ID 11
#define MEMBER_PASS 100
#define MEMBER_LENGTH_NAME 20
#define MAX_NUMBER_MEMBER 100 
#define MAX_NUM_QUESTION 3
#define MAX_PHONE_NUM 15
#define MAX_LENGTH_EMAIL 50
#define MAX_LENGTH_IC 15
#define MAX_LENGTH_GENDER 2
#define LENGTH_CHOICE 10
#define MAX_NUM_FEEDBACK 100


int tryAgain(int again);
void waitingScreen(void);
int memberMenu();

//member Login
int memberLogin();

//security question
void securityQuestion();
void questionTitle(int questionSelection[MAX_NUM_QUESTION], char questionName[MAX_NUM_QUESTION][100]);

//registration validation
void passwordFormat(void);
bool verify_password(char* pass);
bool verify_email(char* email);
bool verify_phone_no(char* phoneNo);
bool verify_IC(char gender, char* ic);
int questionSelected(int questionSelection[3]);
int memberRegister();

//password recovery modules
void forgotPass();

//memberMenu
int memberMainPage(int memberNUM, int now);

//modify and display modules
void viewProfile(int memberNUM);

//reward point
void rewardPoint(int memberNUM);

//search modules
void searchMemberTitle(void);
int searchMember();
int searchMemberID();
int searchMemberGender();
int searchMemberAge();
int searchMemberRewardPoints();

//delete modules
int deleteMember();

char passwordStore(char password[]);

void loginHistory();

struct SecurityQuestion {
	int questionNum;
	char answer[100];
};

typedef struct {
	long int diff;
	char loginTimeDate[100];
	char logoutTimeDate[100];
}LoginOutRecords;

struct Member {
	char id[MEMBER_ID];
	char name[MEMBER_LENGTH_NAME];
	char pass[MEMBER_PASS];
	int age;
	char gender[MAX_LENGTH_GENDER];
	char ic[MAX_LENGTH_IC];
	char phoneNo[MAX_PHONE_NUM];
	char email[MAX_LENGTH_EMAIL];
	int rewardPoints;
	int numLoginRecords;
	struct SecurityQuestion security[MAX_NUM_QUESTION];
	LoginOutRecords logInOutTime[20];
};

struct Feedback {
	char memberID[MEMBER_ID];
	char type[30];
	float rating;
	char comment[50];
};

struct Member member[MAX_NUMBER_MEMBER];
struct Member member2;
struct Feedback feedback[MAX_NUM_FEEDBACK];

int feedbackNum = 0;
int numMember = 0;

int readMemberFile(FILE** memberFptr) {

	fread(&member2, sizeof(member2), 1, *memberFptr);
	while (!feof(*memberFptr))
	{
		member[numMember] = member2;

		numMember++;
		fread(&member2, sizeof(member2), 1, *memberFptr);
	}
}

int readFeedbackFile(FILE** feedbackFptr) {

	while (fscanf(*feedbackFptr, "%[^|]|%[^|]|%f|%[^\n]\n", feedback[feedbackNum].memberID, feedback[feedbackNum].type, &feedback[feedbackNum].rating, feedback[feedbackNum].comment) != EOF) {
		feedbackNum++;
	}
}

int writeMemberFile(FILE** memberFptr) {
	for (int i = 0; i < numMember; i++) {
		fwrite(&member[i], sizeof(member[0]), 1, *memberFptr);
	}
}

int writeFeedbackFile(FILE** feedbackFptr) {
	for (int i = 0; i < feedbackNum; i++) {
		fprintf(*feedbackFptr, "%s|%s|%f|%s\n", feedback[i].memberID, feedback[i].type, feedback[i].rating, feedback[i].comment);
	}
}

void memberMain(){
	int choice;
	//test to display all data
	for (int i = 0; i < numMember; i++) {
		printf("%d. %s\n", i + 1, member[i].id);
	}

	do {
		printf("test\n");
		printf("1.member menu\n");
		printf("2. delete member\n");
		printf("3. search member\n");
		printf("Please Enter Your Choice: ");
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			memberMenu();
			break;
		case 2:
			deleteMember();
			break;
		case 3:
			searchMember();
			break;
		case 4:
			printf("EXITING PROGRAM.....\n");
			break;
		default:
			printf("Invalid Choice!\n");
			printf("Please Try Again\n");
		}
	} while (choice != 4);
}

int tryAgain(int again) {
	char choice[LENGTH_CHOICE];
	int invalidChoice;

	do {

		again = 0;
		invalidChoice = 0;
		printf("Do you want to try again?\n");
		printf("1. Yes\n");
		printf("2. No\n");
		printf("Please Enter Your Choice: ");
		scanf(" %[^\n]", choice);

		if (strcmp(choice, "1") == 0) {
			again = 2;
			return again;
		}
		else if (strcmp(choice, "2") == 0)
			return 0;
		else {
			title();
			printf("Invalid Choice\n");
			printf("Please Enter A Valid Choice\n");
			invalidChoice++;
		}
	} while (invalidChoice == 1);
}

void waitingScreen(void) {
	for (int i = 0; i < 3; i++) {
		Sleep(300);
		printf(". ");
		Sleep(300);
	}
}

int memberMenu() {
	char *menu[] = {"Login", "Registration", "Forgot Password", "Exit",};
	char choice[LENGTH_CHOICE];

	do {

	title();
	printf("Member Menu\n");
	printf("-----------\n");
	for (int i = 0; i < sizeof(menu)/sizeof(menu[0]); i++) {
		printf("-----\n");
		printf("| %d | %s\n", i + 1, menu[i]);
		printf("-----\n");
	}
	printf("Please Enter Your Choice: ");
	scanf(" %[^\n]", choice);

	if (strcmp(choice, "1") == 0)
		return atoi(choice);
	
	else if (strcmp(choice, "2") == 0) 
		return atoi(choice);
	
	else if (strcmp(choice, "3") == 0) 
		return atoi(choice);
	
	else if (strcmp(choice, "4") == 0) {
		printf("EXITING. ");
		waitingScreen();
		return 0;
	}
	
	else{
		printf("Invalid Choice!\n");
		printf("Please Try Again. ");
		waitingScreen();
		}

	} while (strcmp(choice, "4") !=0);
}

int memberLogin(int *memberNUM, int *num) {
	char id[MEMBER_ID], password[MEMBER_PASS];
	int loginSuccess = 0, again;
	
	do {
		again = 0;

		title();
		printf("---------\n");
		printf("| Login |\n");
		printf("---------\n\n");
		printf("ID: ");
		scanf(" %[^\n]", id);
		printf("\nPassword: ");
		passwordStore(password);
		printf("\n\n");

		for (int i = 0; i < numMember; i++) {
			if (strcmp(member[i].id, id) == 0 && strcmp(member[i].pass, password) == 0) {
				printf("Login Successful. ");

				waitingScreen();
				
				*memberNUM = i;

				time_t now = time(NULL);

				struct tm* logInTime = localtime(&now);

				strftime(member[*memberNUM].logInOutTime[member[*memberNUM].numLoginRecords].loginTimeDate, 100, "%x - %I:%M%p", logInTime);

				*num = now;

				return 1;

				loginSuccess++;
			}
		}
		
		if (loginSuccess == 0) {

				printf("Invalid ID or Password\n");
				again = tryAgain(again);			
		}
	} while (again == 2);
	return again;
}


void securityQuestion() {
	title();
		printf("\nSecurity Questions\n");

		printf("-----------------------\n");
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

void passwordFormat(void) {

	printf("-------------------------------------------------------------------\n");
	printf("| Please Set A Password That Meets The Following Requirements:    |\n");
	printf("| Must Be At Least 8 Characters Long                              |\n");
	printf("| Must Contain At Least 1 Uppercase Letter                        |\n");
	printf("| Must Contain At Least 1 Lowercase Letter                        |\n");
	printf("| Must Contain At Least 1 Digit                                   |\n");
	printf("| Must Contain At Least 1 Symbol                                  |\n");
	printf("-------------------------------------------------------------------\n");
}

bool verify_password(char *pass) {
	int length = strlen(pass);
	bool hasUpper = false;
	bool hasLower = false;
	bool hasDigit = false;
	bool hasSymbol = false;

	if (length < 8)
		return false;

	for (int i = 0; i < length; i++) {
		if (isupper(pass[i]))
			hasUpper = true;
		if (islower(pass[i]))
			hasLower = true;
		if (isdigit(pass[i]))
			hasDigit = true;
		if (ispunct(pass[i]))
			hasSymbol = true;
	}

	if (!hasUpper) return false;
	if (!hasLower) return false;
	if (!hasDigit) return false;
	if (!hasSymbol) return false;

	return true;

}

bool verify_email(char* email) {
	int count = 0;

	for (int i = 0; i < strlen(email); i++) {
		if (email[i] == '@') 
			count++;
		

		if (email[i] == ' ' || email[i] == '/' || email[i] == ':' || email[i] == ';'
			|| email[i] == '[' || email[i] == ']' || email[i] == '<' || email[i] == '>'
			|| email[i] == ',') 
			return false;
	}

	if (count == 1) {
		if (email[0] != '@') {
			char* dot = strchr(email, '.');

			if (dot != NULL && dot > strchr(email, '@')) 
				return true;
			
		}
	}

	return false;
}

bool verify_phone_no(char* phoneNo) {
	int length = strlen(phoneNo);
	
	if (length != 11 && length != 12)
		return false;

	if (phoneNo[0] != '0' || phoneNo[1] != '1')
		return false;

	for (int i = 0; i < 3; i++) {

		if (!isdigit(phoneNo[i])) 
			return false;	
	}

	for (int i = 4; i < length; i++) {
		if (!isdigit(phoneNo[i]))
			return false;
	}

	if (phoneNo[3] != '-')
		return false;

	return true;

}

bool verify_IC(char* gender, char* ic) {
	if (strlen(ic) != 14) 
		return false;

	if (ic[6] != '-' || ic[9] != '-')
		return false;

	if (strcmp(gender, "M") == 0) {
		if (ic[13] != '1' && ic[13] != '3' && ic[13] != '5' && ic[13] != '7' && ic[13] != '9')
			return false;
	}
	else if(strcmp(gender, "F") == 0) {
		if (ic[13] != '0' && ic[13] != '2' && ic[13] != '4' && ic[13] != '6' && ic[13] != '8')
			return false;
	}
	else 
		return false;

	for (int i = 0; i < 6; i++) {
		if (!isdigit(ic[i]))
			return false;
	}

	for (int i = 7; i < 9; i++) {
		if (!isdigit(ic[i]))
			return false;
	}

	for (int i = 10; i < 14; i++) {
		if (!isdigit(ic[i]))
			return false;
	}
	
	return true;
}

char passwordStore(char password[]) {
	int i = 0;
	char ch;
	while (1) {
		ch = _getch();
		if (ch == 13)
			break;
		else if (ch == 8) {
			if (i > 0) {
				i--;
				password[i] = '\0';
				printf("\b \b");
			}
		}
		else {
			password[i] = ch;
			i++;
			printf("*");
		}
	}
	password[i] = '\0';

	return password;
}

int questionSelected(int questionSelection[3]) {
	int i = 0, success = 0;

	do {
		success = 1;
		securityQuestion();

		do {
			printf("%d. ", i + 1);
			scanf("%d", &questionSelection[i]);

			if (questionSelection[i] > 6 || questionSelection[i] < 1) {
				printf("\nInvalid Choice!\n");
				printf("Please Enter Number 1 - 6. ");

				waitingScreen();

				i = 0;
				success = 0;

			}
			else {
				i++;
			}
			if (i > 1 && success == 1) {
				for (int y = 0; y < i - 1; y++) {

					if (questionSelection[y] == questionSelection[i - 1]) {
						printf("\nThe Selected Security Question Must Be Different From The Previous One.\n");
						printf("Please Try Again. ");

						waitingScreen();
						i = 0;
						success = 0;

					}

				}

			}
		} while (i < 3 && success == 1);

	} while (i < 3 && success == 0);

	return questionSelection;
}

int memberRegister() {
	
	char memberID[MEMBER_ID];
	char numID[5];
	int iDUnique;
	bool resultPass = false, resultEmail = false, resultPhoneNo = false, resultIC = false;
	char name[MEMBER_LENGTH_NAME], password[MEMBER_PASS], passConfirm[MEMBER_PASS], ic[MAX_LENGTH_IC], gender[MAX_LENGTH_GENDER], phone[MAX_PHONE_NUM], email[MAX_LENGTH_EMAIL];
	int age;
	int again;
	int questionSelection[MAX_NUM_QUESTION], success;
	char question[MAX_NUM_QUESTION][100], answer[MAX_NUM_QUESTION][100];

	for (int i = 0; i < numMember + 1; i++) {

		iDUnique = 1;
		strcpy(memberID, "M");
		sprintf(numID, "%03d", i+1);

			
		strncat_s(memberID, MEMBER_ID, numID, MEMBER_ID - strlen(memberID) - 1);

			for (int x = 0; x < numMember; x++) {
				if (strcmp(member[x].id, memberID) == 0) {
					iDUnique = 0;
				}
			}
		
		if (iDUnique == 1) {
				break;
		}
	}	

	do {
		again = 0;
		title();

		printf("ID: %s\n", memberID);

		printf("\n");

		passwordFormat();
		
		printf("Password: ");

		passwordStore(password);
		printf("\n\n");

		printf("Password Confirm: ");

		passwordStore(passConfirm);

		printf("\n\n");

		if (strcmp(password, passConfirm) != 0) {
			printf("\nNew Password and Confrim Password Are Not Same!\n");
			again = tryAgain(again);

		}
		else {
			resultPass = verify_password(password);
			
			if (!resultPass) {
				printf("Error: Password Does Not Meet The Required Format!\n");
				printf("Please Try Again. ");

				waitingScreen();
				again++;
			}
		}

	} while (again == 2);

	if (again == 0 && resultPass) {
		strcpy(member[numMember].id, memberID);
		strcpy(member[numMember].pass, password);

		questionSelected(questionSelection);

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

		printf("\nRegistration Successfully. ");
		waitingScreen();

		title();

		printf("Name: ");
		scanf(" %[^\n]", name);

		//validate age
		do {
			title();
			printf("Name: %s\n\n", name);

			printf("Age: ");
			scanf("%d", &age);
		} while (age <= 0 || age > 100);

		//validate gender
		do {
			title();
			printf("Name: %s\n\n", name);
			printf("Age: %d\n\n", age);

			printf("Gender(M/F): ");
			scanf(" %[^\n]", gender);

			for (int i = 0; i < strlen(gender); i++) {
				gender[i] = toupper(gender[i]);
			}

			if (strcmp(gender, "M") != 0 && strcmp(gender, "F") != 0) {
				printf("\nInvalid Gender!\n");
				printf("Please Try Again. ");
				waitingScreen();
			}

		} while (strcmp(gender, "M") != 0 && strcmp(gender, "F") != 0);

		//validate IC
		do {
			title();
			printf("Name: %s\n\n", name);
			printf("Age: %d\n\n", age);
			printf("Gender(M/F): %s\n\n", gender);

			printf("IC(XXXXXX-XX-XXXX): ");
			scanf(" %[^\n]", ic);

			resultIC = verify_IC(gender, ic);

			if (!resultIC) {
				printf("\nInvalid IC!\n");
				printf("Please Try Again. ");
				waitingScreen();
			}
		} while (!resultIC);

		//validate Phone Number
		do {
			title();
			printf("Name: %s\n\n", name);
			printf("Age: %d\n\n", age);
			printf("Gender(M/F): %s\n\n", gender);
			printf("IC(XXXXXX-XX-XXXX): %s\n\n", ic);

			printf("Phone number(011-XXXXXXX): ");
			scanf(" %[^\n]", phone);

			resultPhoneNo = verify_phone_no(phone);

			if (!resultPhoneNo) {
				printf("\nInvalid Phone Number!\n");
				printf("Please Try Again. ");
				waitingScreen();
			}
		} while (!resultPhoneNo);

		//validate email
		do {
			title();
			printf("Name: %s\n\n", name);
			printf("Age: %d\n\n", age);
			printf("Gender(M/F): %s\n\n", gender);
			printf("IC(XXXXXX-XX-XXXX): %s\n\n", ic);
			printf("Phone number(011-XXXXXXX): %s\n\n", phone);

			printf("Email: ");
			scanf(" %[^\n]", email);

			resultEmail = verify_email(email);

			if (!resultEmail) {
				printf("\nInvalid Email!\n");
				printf("Please Try Again. ");
				waitingScreen();
			}
		} while (!resultEmail);

		strcpy(member[numMember].name, name);
		member[numMember].age = age;
		strcpy(member[numMember].ic, ic);
		strcpy(member[numMember].gender, gender);
		strcpy(member[numMember].phoneNo, phone);
		strcpy(member[numMember].email, email);
		member[numMember].rewardPoints = 0;
		member[numMember].numLoginRecords = 0;

		printf("\nzrmation Added. ");
		waitingScreen();

		numMember++;
	}

	return again;
}

void forgotPass() {
	bool resultPass;
	char id[MEMBER_ID], question[MAX_NUM_QUESTION][100], answer[MAX_NUM_QUESTION][100];
	int num, questionSelection[MAX_NUMBER_MEMBER], newPassword[MEMBER_PASS], newPassConfirm[MEMBER_PASS];
	int idExist, again, securityPass = 0, choice;

	do {
		again = 0;
		idExist = 0;
		securityPass = 0;
		title();
		printf("ID: ");
		scanf(" %[^\n]", id);
		
		for (int i = 0; i < numMember; i++) {
			if (strcmp(member[i].id, id) == 0) {
				num = i;
				idExist++;
			}
		}
		
		if (idExist == 1) {

			questionSelected(questionSelection);

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
				do {
					again = 0;
					title();

					printf("ID: %s\n", id);

					printf("\n");

					passwordFormat();

					printf("New Password: ");
					passwordStore(newPassword);
					printf("\n\n");
					printf("New Password Confirm: ");
					passwordStore(newPassConfirm);
					printf("\n\n");

					if (strcmp(newPassword, newPassConfirm) != 0) {
						printf("\nNew Password and Confrim Password Are Not Same!\n");
						again = tryAgain(again);
					}
					else {
						resultPass = verify_password(newPassword);

						if (!resultPass) {
							printf("Error: Password Does Not Meet The Required Format!\n");
							printf("Please Try Again. ");

							waitingScreen();
							again++;
						}
						else {
							strcpy(member[num].pass, newPassword);
							printf("\nYour Password Has Been Updated Successfully. ");
							waitingScreen();
						}
					}

				} while (again == 2);
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
	} while (again == 2);
	return again;

}

int memberMainPage(int memberNUM, int now) {
	char choice[LENGTH_CHOICE];
	char* menu[] = { "Display Profile", "View Schedule", "Add Booking",
					"Display Booking History", "Cancel Booking", "Reward Points", "Submit Feedback" ,"Exit"};

	do
	{
		title();
		printf("Member Menu\n");
		printf("-----------\n");
		for (int i = 0; i < sizeof(menu) / sizeof(menu[0]); i++) {
			printf("-----\n");
			printf("| %d | %s\n", i + 1, menu[i]);
			printf("-----\n");
		}

		printf("Enter Your Choice: ");
		scanf(" %[^\n]", choice);

		if (strcmp(choice, "1") == 0)
			viewProfile(memberNUM);

		else if (strcmp(choice, "2") == 0)
			return atoi(choice);

		else if (strcmp(choice, "3") == 0)
			return atoi(choice);

		else if (strcmp(choice, "4") == 0)
			return atoi(choice);
		/*bookingHistory();*/

		else if (strcmp(choice, "5") == 0)
			return atoi(choice);
		//	cancelBooking();


		else if (strcmp(choice, "6") == 0)
			rewardPoint(memberNUM);

		else if (strcmp(choice, "7") == 0)
			sendFeedback(&memberNUM);

		else if (strcmp(choice, "8") == 0) {
			title();
			printf("Logging Out. ");

			time_t now2 = time(NULL);

			struct tm* logOutTime = localtime(&now2);

			strftime(member[memberNUM].logInOutTime[member[memberNUM].numLoginRecords].logoutTimeDate, 100, "%x - %I:%M%p", logOutTime);

			member[memberNUM].logInOutTime[member[memberNUM].numLoginRecords].diff = now2 - now;

			member[memberNUM].numLoginRecords++;

			waitingScreen();
			return 0;
		}
		else {
			printf("Invalid Choice!\n");
			printf("Please Try Again. ");
			waitingScreen();
		}
	} while (strcmp(choice, "8") != 0);

	return 1;
}

void viewProfile(int memberNUM) {
	char choice[LENGTH_CHOICE], modify[LENGTH_CHOICE];
	int again;
	int age;
	char oldPassword[MEMBER_PASS], newPassword[MEMBER_PASS], passConfirm[MEMBER_PASS], phone[MAX_PHONE_NUM], email[MAX_LENGTH_EMAIL];
	bool resultPass = false, resultEmail = false, resultPhoneNo = false;

	do {
		title();
		again = 0;
		printf("Profile Information\n");
		printf("--------------------\n");
		printf("ID            : %s\n", member[memberNUM].id);
		printf("Name          : %s\n", member[memberNUM].name);
		printf("Age           : %d\n", member[memberNUM].age);
		printf("Contact Number: %s\n", member[memberNUM].phoneNo);
		printf("Email         : %s\n", member[memberNUM].email);
		printf("\nEnter 1 to MODIFY PROFILE (0 EXIT)\n");
		scanf(" %[^\n]", choice);


		if (strcmp(choice, "1") == 0) {
			printf("\n");
			printf("----------------------\t ----------------------\t ----------------------\t  ----------------------\n");
			printf("| 1 | Password       |\t | 2 | Age            |\t | 3 | Contact Number |\t  | 4 | Email          |\n");
			printf("----------------------\t ----------------------\t ----------------------\t  ----------------------\n");

			printf("\nEnter your choice: ");
			scanf(" %[^\n]", modify);

			if (strcmp(modify, "1") == 0) {
				do {
					again = 0;
					title();
					printf("Old Password: ");
					passwordStore(oldPassword);
					printf("\n\n");

					printf("New Password: ");
					passwordStore(newPassword);
					printf("\n\n");

					printf("Confirm Password: ");
					passwordStore(passConfirm);
					printf("\n\n");

					if (strcmp(member[memberNUM].pass, oldPassword) != 0) {
						printf("Old Password Incorrect\n");
						again = tryAgain(again);
					}

					if (again != 2 && again != 1) {
						if (strcmp(newPassword, passConfirm) != 0) {
							printf("New Password and Confrim Password Are Not Same\n");
							again = tryAgain(again);
						}

						if (again != 2 && again != 1) {
							resultPass = verify_password(passConfirm);

							if (!resultPass) {
								printf("Error: New Password Does Not Meet The Required Format!\n");
								printf("Please Try Again. ");
								waitingScreen();
								again = 2;
							}
						}
					}
					

				} while (again == 2);

				if (strcmp(member[memberNUM].pass, oldPassword) == 0 && strcmp(newPassword, passConfirm) == 0 && resultPass == true) {
					strcpy(member[memberNUM].pass, newPassword);
					printf("Password is changing. ");
					waitingScreen();
					printf("\n");
				}

			}

			else if (strcmp(modify, "2") == 0) {
				do {
					title();
					printf("Current Age: %d\n\n", member[memberNUM].age);
					printf("New Age: ");
					scanf("%d", &age);

				} while (age <= 0 || age > 100);

				if (age > 0 && age < 100) {
					member[memberNUM].age = age;
					printf("\nAge is changing. ");
					waitingScreen();
				}
			}

			else if (strcmp(modify, "3") == 0){
				do {
					title();
					printf("Current Contact Number: %s\n\n", member[memberNUM].phoneNo);
					printf("New Contact Number: ");
					scanf(" %[^\n]", phone);

					resultPhoneNo = verify_phone_no(phone);
					if (!resultPhoneNo) {
						printf("\nInvalid Phone Number!\n");
						printf("Please Try Again. ");
						waitingScreen();
					}
				} while (!resultPhoneNo);

				if (resultPhoneNo) {
					strcpy(member[memberNUM].phoneNo, phone);
					printf("\nContact Number is changing. ");
					waitingScreen();
				}
				
			}
			else if (strcmp(modify, "4") == 0) {
				do {
					title();
					printf("Current Email: %s\n\n", member[memberNUM].email);
					printf("New Email: ");
					scanf(" %[^\n]", email);

					resultEmail = verify_email(email);

					if (!resultEmail) {
						printf("\n");
						printf("Invalid Email!\n");
						printf("Please Try Again. ");
						waitingScreen();
					}

				} while (!resultEmail);

				if (resultEmail) {
					strcpy(member[memberNUM].email, email);
					printf("\nEmail is changing. ");
					waitingScreen();
				}
			}
			else {
				printf("Invalid Choice\n");
				again = tryAgain(again);
			}
		}
		else if (strcmp(choice, "0") == 0)
			again = 0;

		else
			again = 2;
	} while(again == 2);

	return 0;
}


void rewardPoint(int memberNUM) {
	title();
	printf("\t\t\t\t\t\t\t\t   Current Points \n\t\t\t\t\t\t\t\t\t  %d\n\n", member[memberNUM].rewardPoints);
	for (int i = 0; i < 155; i++) {
		printf("%s", "-");
	}
	printf("\n\n");
	printf("\t\t\t\t\t\t\t\tTerms and conditions\n");
	printf("\t\t\t\t\t\t\t\t--------------------\n\n");
	printf("\t\t\t\t-> Customers earn reward points for every eligible purchase made on our system. \n\t\t\t\t   For every RM1 spent, customers receive 1 reward points.\n\n");
	printf("\t\t\t\t-> Reward points can be redeemed for discounts when booking train tickets on our system.\n\n");
	printf("\t\t\t\t-> The conversion rate for reward points is 100 points = RM1.\n\n");
	printf("\t\t\t\t-> Reward points cannot be exchanged for cash or transferred to another account.\n\n");
	printf("\t\t\t\t-> When canceling a booking, the refund will be issued in the form of reward points instead of cash.\n\n");
	printf("\t\t\t\t");
	system("pause");


}

void memPointCal(int *rewardPoint, float price) {
	*rewardPoint = (int)price;

	if (price - (int)price > 0.49)
		*rewardPoint++;
}

void addMemPoint(int mem_num, int rewardPoint) {
	member[mem_num].rewardPoints += rewardPoint;
}

int searchMember() {
	char* menu[] = { "ID", "Gender", "Age", "Reward Points", "Exit"};
	char choice[LENGTH_CHOICE];

	do {

		title();
		for (int i = 0; i < sizeof(menu) / sizeof(menu[0]); i++) {
			printf("-----\n");
			printf("| %d | %s\n", i + 1, menu[i]);
			printf("-----\n");
		}
		printf("Please Enter Your Choice: ");
		scanf(" %[^\n]", &choice);

		if(strcmp(choice, "1") == 0)
			searchMemberID();

		else if(strcmp(choice, "2") == 0)
			searchMemberGender();

		else if (strcmp(choice, "3") == 0)
			searchMemberAge();

		else if (strcmp(choice, "4") == 0)
			searchMemberRewardPoints();

		else if (strcmp(choice, "5") == 0) {
			printf("EXITING. ");
			waitingScreen();
		}
		else {
			printf("Invalid Choice!\n");
			printf("Please Try Again. ");
			waitingScreen();
		}
		
	} while (strcmp(choice, "5") != 0);
}

void searchMemberTitle(void) {
	printf("----------------------------------------------------------------------------------------------------------------------\n");
	printf("| ID         | NAME                 | AGE | GENDER | CONTACT NUMBER | EMAIL                          | Reward Points |\n");
	printf("----------------------------------------------------------------------------------------------------------------------\n");
}

int searchMemberID() {
	char id[MEMBER_ID], next[10];
	int success = 0, again = 0;

	if (numMember > 0) {
		do {
			success = 0;
			again = 0;
			title();
			printf("Enter Member's ID to search: ");
			scanf(" %[^\n]", id);

			for (int i = 0; i < numMember; i++) {
				if (strcmp(member[i].id, id) == 0) {
					do {
						again = 0;
						title();
						printf("Enter Member's ID to search: %s\n\n", id);
						searchMemberTitle();
						printf("| %-10s | %-20s | %-3d | %-6s | %-14s | %-30s | %-.2f          |\n", member[i].id, member[i].name, member[i].age, member[i].gender, member[i].phoneNo, member[i].email, member[i].rewardPoints);
						printf("----------------------------------------------------------------------------------------------------------------------\n");
						printf("\n\nClick 0 To Continue.....\n");
						scanf(" %[^\n]", next);
						if (strcmp(next, "0") == 0) {
							again = 0;
							success++;
						}
						else
							again++;

					} while (again == 1);
				}
			}
			if (success == 0) {
				printf("There is no member(%s)\n", id);
				again = tryAgain(again);
			}
		} while (again == 2);
	}
	else {
		title();
		printf("\nThere is no member. ");
		waitingScreen();
		return 0;

		//return something(maybe not return 0)
	}

	//return something back to menu
}

int searchMemberGender() {
	char* menu[] = { "Male", "Female"};
	char next[10];
	int again = 0, memberExist =0;
	char gender[LENGTH_CHOICE];


	if (numMember > 0) {
		do {
			memberExist = 0;
			again = 0;
			title();
			for (int i = 0; i < sizeof(menu) / sizeof(menu[0]); i++) {
				printf("-----\n");
				printf("| %d | %s\n", i + 1, menu[i]);
				printf("-----\n");
			}
			printf("\nPlease Enter Your Choice: ");

			scanf(" %[^\n]", gender);
			if (strcmp(gender, "1") == 0 || strcmp(gender, "2") == 0) {

				do {
					again = 0;
					title();
					if (strcmp(gender, "1") == 0) {

						for (int i = 0; i < numMember; i++) {
							if (strcmp(member[i].gender, "M") == 0)
								memberExist++;
						}

						if (memberExist == 0) {
							printf("There Are No Records For Male Members. ");
							waitingScreen();
							return 0;
						}

						printf("MALE:\n\n");
						searchMemberTitle();
						for (int i = 0; i < numMember; i++) {
							if (strcmp(member[i].gender, "M") == 0) {
								printf("| %-10s | %-20s | %-3d | %-6s | %-14s | %-30s | %-.2f          |\n", member[i].id, member[i].name, member[i].age, member[i].gender, member[i].phoneNo, member[i].email, member[i].rewardPoints);
								printf("----------------------------------------------------------------------------------------------------------------------\n");
							}
						}
						printf("\n\nClick 0 To Continue.....\n");
						scanf(" %[^\n]", next);
						if (strcmp(next, "0") == 0)
							again = 0;
						else
							again++;
					}
					else {

						for (int i = 0; i < numMember; i++) {
							if (strcmp(member[i].gender, "F") == 0)
								memberExist++;
						}

						if (memberExist == 0) {
							printf("There Are No Records For Female Members. ");
							waitingScreen();
							return 0;
						}

						printf("FEMALE:\n\n");

						searchMemberTitle();;

						for (int i = 0; i < numMember; i++) {
							if (strcmp(member[i].gender, "F") == 0) {
								printf("| %-10s | %-20s | %-3d | %-6s | %-14s | %-30s | %-.2f          |\n", member[i].id, member[i].name, member[i].age, member[i].gender, member[i].phoneNo, member[i].email, member[i].rewardPoints);
								printf("----------------------------------------------------------------------------------------------------------------------\n");
							}
						}

						printf("\n\nClick 0 To Continue.....\n");
						scanf(" %[^\n]", next);
						if (strcmp(next, "0") == 0)
							again = 0;
						else
							again++;
					}
				} while (again == 1);
			}
			else {
				printf("Invalid Choice\n");
				again = tryAgain(again);
			}

		} while (again == 2);
	}
	else {
		title();
		printf("\nThere is no member. ");
		waitingScreen();
		return 0;

		//return something(maybe not return 0)
	}

	//return something back to menu
}

int searchMemberAge() {
	char* menu[] = { "Equal To ", "Greater Than or Equal To ", "Less Than or Equal To " };
	char next[10];
	int age, again=0, choice, memberExist = 0;

	if (numMember > 0) {
		do {
			again = 0, memberExist = 0;
			title();
			printf("Enter An Age (1-100): ");
			scanf("%d", &age);

			if (age > 0 && age < 101) {
				printf("\n");
				for (int i = 0; i < sizeof(menu) / sizeof(menu[0]); i++) {
					printf("-----\n");
					printf("| %d | %s%d\n", i + 1, menu[i], age);
					printf("-----\n");
				}
				printf("\nPlease Enter Your Choice: ");
				scanf("%d", &choice);

				if (choice == 1) {
					do {
						again = 0, memberExist = 0;
						title();
						for (int i = 0; i < numMember; i++) {
							if (member[i].age == age)
								memberExist++;
						}

						if (memberExist == 0) {
							printf("No Members Found With The Entered Age. ");
							waitingScreen();
							return 0;
							//not return 0;
							//return something back to the menu
						}

						searchMemberTitle();
						for (int i = 0; i < numMember; i++) {
							if (member[i].age == age) {
								printf("| %-10s | %-20s | %-3d | %-6s | %-14s | %-30s | %-.2f          |\n", member[i].id, member[i].name, member[i].age, member[i].gender, member[i].phoneNo, member[i].email, member[i].rewardPoints);
								printf("----------------------------------------------------------------------------------------------------------------------\n");
							}
						}

						printf("\n\nClick 0 To Continue.......\n");
						scanf(" %[^\n]", next);

						if (strcmp(next, "0") == 0)
							again = 0;
						else again++;
					} while (again == 1);
				}
				else if (choice == 2) {
					do {
						again = 0, memberExist = 0;
						title();
						for (int i = 0; i < numMember; i++) {
							if (member[i].age >= age)
								memberExist++;
						}

						if (memberExist == 0) {
							printf("No Members Found With The Entered Age. ");
							waitingScreen();
							return 0;
						}

						searchMemberTitle();
						for (int i = 0; i < numMember; i++) {
							if (member[i].age >= age) {
								printf("| %-10s | %-20s | %-3d | %-6s | %-14s | %-30s | %-.2f          |\n", member[i].id, member[i].name, member[i].age, member[i].gender, member[i].phoneNo, member[i].email, member[i].rewardPoints);
								printf("----------------------------------------------------------------------------------------------------------------------\n");
							}
						}

						printf("\n\nClick 0 To Continue.......\n");
						scanf(" %[^\n]", next);

						if (strcmp(next, "0") == 0)
							again = 0;
						else again++;
					} while (again == 1);
				}
				else if (choice == 3) {
					do {
						again = 0, memberExist = 0;
						title();
						for (int i = 0; i < numMember; i++) {
							if (member[i].age <= age)
								memberExist++;
						}

						if (memberExist == 0) {
							printf("No Members Found With The Entered Age. ");
							waitingScreen();
							return 0;
						}

						searchMemberTitle();
						for (int i = 0; i < numMember; i++) {
							if (member[i].age <= age) {
								printf("| %-10s | %-20s | %-3d | %-6s | %-14s | %-30s | %-.2f          |\n", member[i].id, member[i].name, member[i].age, member[i].gender, member[i].phoneNo, member[i].email, member[i].rewardPoints);
								printf("----------------------------------------------------------------------------------------------------------------------\n");
							}
						}

						printf("\n\nClick 0 To Continue.......\n");
						scanf(" %[^\n]", next);

						if (strcmp(next, "0") == 0)
							again = 0;
						else again++;
					} while (again == 1);
				}
				else {
					printf("Invalid Choice");
					again = tryAgain(again);
					
				}
			}
			else {
				printf("Invalid Age\n");
				again = tryAgain(again);
			}

		} while (again == 2);
	}
	else {
		title();
		printf("\nThere is no member. ");
		waitingScreen();
		return 0;

		//return something(maybe not return 0)
		}

		//return something back to menu
}

int searchMemberRewardPoints() {
	char* menu[] = { "Equal To ", "Greater Than or Equal To ", "Less Than or Equal To " };
	char next[10];
	float rewardPoints;
	int again = 0, choice, memberExist = 0;


	if (numMember > 0) {
		do {
			again = 0, memberExist = 0;
			title();
			printf("Enter Reward Points: ");
			scanf("%f", &rewardPoints);
			if (rewardPoints < 0) {
				printf("INVALID INPUT\n");
				return 0;
			}
			printf("\n");
			for (int i = 0; i < sizeof(menu) / sizeof(menu[0]); i++) {
				printf("-----\n");
				printf("| %d | %s%.2f\n", i + 1, menu[i], rewardPoints);
				printf("-----\n");
			}
			printf("\nPlease Enter Your Choice: ");
			scanf("%d", &choice);

			if (choice == 1) {
				do {
					again = 0, memberExist = 0;
					title();
					for (int i = 0; i < numMember; i++) {
						if (member[i].rewardPoints == rewardPoints)
							memberExist++;
					}

					if (memberExist == 0) {
						printf("No Members Found With The Entered Age. ");
						waitingScreen();
						return 0;
					}

					searchMemberTitle();
					for (int i = 0; i < numMember; i++) {
						if (member[i].rewardPoints == rewardPoints) {
							printf("| %-10s | %-20s | %-3d | %-6s | %-14s | %-30s | %-.2f          |\n", member[i].id, member[i].name, member[i].age, member[i].gender, member[i].phoneNo, member[i].email, member[i].rewardPoints);
							printf("----------------------------------------------------------------------------------------------------------------------\n");
						}
					}

					printf("\n\nClick 0 To Continue.......\n");
					scanf(" %[^\n]", next);

					if (strcmp(next, "0") == 0)
						again = 0;
					else again++;
				} while (again == 1);
			}
			else if (choice == 2) {
				do {
					again = 0, memberExist = 0;
					title();
					for (int i = 0; i < numMember; i++) {
						if (member[i].rewardPoints >= rewardPoints)
							memberExist++;
					}

					if (memberExist == 0) {
						printf("No Members Found With The Entered Age. ");
						waitingScreen();
						return 0;
					}

					searchMemberTitle();
					for (int i = 0; i < numMember; i++) {
						if (member[i].rewardPoints >= rewardPoints) {
							printf("| %-10s | %-20s | %-3d | %-6s | %-14s | %-30s | %-.2f          |\n", member[i].id, member[i].name, member[i].age, member[i].gender, member[i].phoneNo, member[i].email, member[i].rewardPoints);
							printf("----------------------------------------------------------------------------------------------------------------------\n");
						}
					}

					printf("\n\nClick 0 To Continue.......\n");
					scanf(" %[^\n]", next);

					if (strcmp(next, "0") == 0)
						again = 0;
					else again++;
				} while (again == 1);
			}
			else if (choice == 3) {
				do {
					again = 0, memberExist = 0;
					title();
					for (int i = 0; i < numMember; i++) {
						if (member[i].rewardPoints <= rewardPoints)
							memberExist++;
					}

					if (memberExist == 0) {
						printf("No Members Found With The Entered Age. ");
						waitingScreen();
						return 0;
					}

					searchMemberTitle();
					for (int i = 0; i < numMember; i++) {
						if (member[i].rewardPoints <= rewardPoints) {
							printf("| %-10s | %-20s | %-3d | %-6s | %-14s | %-30s | %-.2f          |\n", member[i].id, member[i].name, member[i].age, member[i].gender, member[i].phoneNo, member[i].email, member[i].rewardPoints);
							printf("----------------------------------------------------------------------------------------------------------------------\n");
						}
					}

					printf("\n\nClick 0 To Continue.......\n");
					scanf(" %[^\n]", next);

					if (strcmp(next, "0") == 0)
						again = 0;
					else again++;
				} while (again == 1);
			}
			else {
				printf("Invalid Choice");
				again = tryAgain(again);
			}

		} while (again == 2);
	}
	else {
		title();
		printf("\nThere is no member. ");
		waitingScreen();
		return 0;

		//return something(maybe not return 0)
	}

	//return something back to menu
}

int deleteMember() {
	char* confirmationMenu[] = { "Confirm", "Cancel" };
	char id[MEMBER_ID];
	int confirmation, again = 0, success = 0;

	if (numMember > 0) {
		do {
			title();
			printf("Enter An ID to Delete: ");
			scanf(" %[^\n]", id);

			for (int i = 0; i < numMember; i++) {
				if (strcmp(member[i].id, id) == 0) {
					do {
						title();
						again = 0;
						success = 0;
						searchMemberTitle();
						printf("| %-10s | %-20s | %-3d | %-6s | %-14s | %-30s | %-.2f          |\n", member[i].id, member[i].name, member[i].age, member[i].gender, member[i].phoneNo, member[i].email, member[i].rewardPoints);
						printf("----------------------------------------------------------------------------------------------------------------------\n");

						printf("Are You Sure You Want To Delete This Member Account?\n\n");
						for (int i = 0; i < sizeof(confirmationMenu) / sizeof(confirmationMenu[0]); i++) {
							printf("-----\n");
							printf("| %d | %s\n", i + 1, confirmationMenu[i]);
							printf("-----\n");
						}
						printf("\nEnter Your Choice: ");
						scanf("%d", &confirmation);

						if (confirmation == 1) {
							for (i; i < numMember; i++) {
								strcpy(member[i].id, member[i + 1].id);
								strcpy(member[i].pass, member[i + 1].pass);
								member[i].age = member[i + 1].age;
								strcpy(member[i].gender, member[i + 1].gender);
								strcpy(member[i].ic, member[i + 1].ic);
								strcpy(member[i].phoneNo, member[i + 1].phoneNo);
								strcpy(member[i].email, member[i + 1].email);
								member[i].rewardPoints = member[i + 1].rewardPoints;

								for (int x = 0; x < 3; x++) {
									member[i].security[x].questionNum = member[i + 1].security[x].questionNum;
									strcpy(member[i].security[x].answer, member[i + 1].security[x].answer);
								}
							}
							numMember--;
							title();
							printf("Deleting. ");
							waitingScreen();

							printf("\n\nThe Member Account(%s) Has Been Successfully Deleted. ", id);
							waitingScreen();
							success++;
						}
						else if (confirmation == 2) {
							title();
							printf("Cancelling. ");
							waitingScreen();
							return 0;
						}
						else
							again++;

					} while (again == 1);
				}
			}

			if (success == 0) {
				again = 0;
				printf("Invalid ID\n");
				again = tryAgain(again);
			}
		} while (again == 2);
	}
	else {
		title();
		printf("\nThere is no member. ");
		waitingScreen();
		return 0;

		//return something(maybe not return 0)
	}

	//return something back to menu
}

void loginHistory() {
	int recordsExist = 0;
	char id[MEMBER_ID];
	char name[MEMBER_LENGTH_NAME];
	int logInTime;

	title();

	for (int i = 0; i < numMember; i++) {
		for (int j = 0; j < member[i].numLoginRecords; j++) {
			if (member[i].logInOutTime[j].diff != 0) {
				recordsExist++;
			}

		}
	}

	if (recordsExist != 0) {
		printf("--------------------------------------------------------------------------------------------------------------------------\n");
		printf("| ID         | NAME                 | Log In Date Time          | Log Out Date Time         | Duratoion                  |\n");
		printf("--------------------------------------------------------------------------------------------------------------------------\n");

		for (int i = 0; i < numMember; i++) {
			for (int j = 0; j < member[i].numLoginRecords; j++) {



				int hours = member[i].logInOutTime[j].diff / 3600;

				int remainingSecs = member[i].logInOutTime[j].diff % 3600;

				int minutes = remainingSecs / 60;

				int seconds = remainingSecs % 60;

				printf("| %-10s | %-20s | %-25s | %-25s | %02d Hours %02d Mins %02d Sec    |\n", member[i].id, member[i].name, member[i].logInOutTime[j].loginTimeDate, member[i].logInOutTime[j].logoutTimeDate, hours, minutes, seconds);
				printf("--------------------------------------------------------------------------------------------------------------------------\n");
			}
		}
		system("pause");
	}
	else {
		printf("No Member Login Records. ");
		waitingScreen();

	}
}

int sendFeedback(int* memberNUM) {
	char* menu[] = { "Customer Service Rating", "Cleanliness Rating", "Punctuality Rating", "Safety and Security Rating", "Return Back" };
	char choice[30];
	int choiceResult;
	float rating;

	char* comment = (char*)malloc(50 * sizeof(char));

	do {
		title();
		for (int j = 0; j < sizeof(menu) / sizeof(menu[0]); j++) {
			printf("-----\n");
			printf("| %d | %s\n", j + 1, menu[j]);
			printf("-----\n");
		}
		printf("\nPlease Enter Your Choice: ");
		scanf(" %[^\n]", choice);

		choiceResult = atoi(choice);

		if (choiceResult >= 1 && choiceResult < 5) {
			do {
				title();
				printf("-----------------------------------------------------------------------------------------------\n");
				printf("| Type of Feedback               | Rating(0.0-5.0) | Comment(ENTER 0 IF NO COMMENT)(MAX 500C)  |\n");
				printf("-----------------------------------------------------------------------------------------------\n");
				printf("| %-30s | ", menu[choiceResult - 1]);
				scanf("%f", &rating);

			} while (rating < 0.0 || rating > 5.0);

			title();
			printf("-----------------------------------------------------------------------------------------------\n");
			printf("| Type of Feedback               | Rating(0.0-5.0) | Comment(ENTER 0 IF NO COMMENT)(MAX 50C)  |\n");
			printf("-----------------------------------------------------------------------------------------------\n");
			printf("| %-30s | %-15.1f | ", menu[choiceResult - 1], rating);
			rewind(stdin);
			fgets(comment, 50, stdin);
			printf("\nSending Feedback. ");

			if (strcmp(comment, "0") != 0) {
				strcpy(feedback[feedbackNum].comment, comment);
			}
			else
				strcpy(feedback[feedbackNum].comment, "-");

			strcpy(feedback[feedbackNum].memberID, member[*memberNUM].id);
			strcpy(feedback[feedbackNum].type, menu[choiceResult - 1]);
			feedback[feedbackNum].rating = rating;
			feedbackNum++;
			waitingScreen();
			free(comment);
		}
		if (choiceResult == 5)
			return 0;
	} while (choiceResult < 0 || choiceResult > 5);
}

void displayFeedback() {
	char* menu[] = { "Customer Service Rating", "Cleanliness Rating", "Punctuality Rating", "Safety and Security Rating", "Return Back" };

	if (feedbackNum > 0) {
		printf("----------------------------------------------------------------------------------------------------------------------\n");
		printf("| MEMBER ID  | Type of Feedback               | Rating(0.0-5.0) | Comment                                            |\n");
		printf("----------------------------------------------------------------------------------------------------------------------\n");
		for (int j = 0; j < feedbackNum; j++) {
			printf("| %-10s | %-30s | %-15.1f | %-50s |\n", feedback[j].memberID, feedback[j].type, feedback[j].rating, feedback[j].comment);
			printf("----------------------------------------------------------------------------------------------------------------------\n");
		}
		system("pause");
	}
	else {
		printf("No Feedback Record. ");
		waitingScreen();
	}
}