#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <stdbool.h>
#include <ctype.h>
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

void title(void);
int tryAgain(int again);
void waitingScreen(void);
void memberMenu(struct Member* member);

//member Login
void memberLogin(struct Member* member);

//security question
void securityQuestion();
void questionTitle(int questionSelection[MAX_NUM_QUESTION], char questionName[MAX_NUM_QUESTION][100]);

//registration validation
void passwordFormat(void);
bool verify_password(char* pass);
bool verify_email(char* email);
bool verify_phone_no(char* phoneNo);
bool verify_IC(char gender, char* ic);
void memberRegister(struct Member* member);

//password recovery modules
void forgotPass(struct Member* member);

//memberMenu
void memberMainPage(struct Member* member, int memberNUM);

//modify and display modules
void viewProfile(struct Member* member, int memberNUM);


void viewSchedule();
void addBooking();
void bookingHistory();
void cancelBooking();

//reward point
void rewardPoint(struct Member* member, int memberNUM);

int validateNumberMember(void);

//search modules
void searchMemberTitle(void);
void searchMember(struct Member* member);
void searchMemberID(struct Member* member);
void searchMemberGender(struct Member* member);
void searchMemberAge(struct Member* member);
void searchMemberRewardPoints(struct Member* member);

//delete modules
void deleteMember(struct Member* member);

struct SecurityQuestion {
	int questionNum;
	char answer[100];
};

struct Member {
	char id[MEMBER_ID];
	char name[MEMBER_LENGTH_NAME];
	char pass[MEMBER_PASS];
	int age;
	char gender[MAX_LENGTH_GENDER];
	char ic[MAX_LENGTH_IC];
	char phoneNo[MAX_PHONE_NUM];
	char email[MAX_LENGTH_EMAIL];
	float rewardPoints;
	struct SecurityQuestion security[MAX_NUM_QUESTION];
};

int numMember = 0;

void title(void) {
	system("cls");
	printf("%10s %s %s", "Train", "Ticketing", "System");
	SYSTEMTIME t;
	GetLocalTime(&t);
	const char day[7][10] = { {"Sunday"} , {"Monday"} ,{"Tuesday"} ,{"Wednesday"} ,{"Thursday"} ,{"Friday"} ,{"Saturday"} };
	const char month[12][10] = { {"January"}, {"February"}, {"March"}, {"April"}, {"May"}, {"June"}, {"July"}, {"August"}, {"September"}, {"October"}, {"November"}, {"December"} };
	printf("%104s %02d %s %d %02d:%02d:%02d", day[t.wDayOfWeek], t.wDay, month[t.wMonth - 1], t.wYear, t.wHour, t.wMinute, t.wSecond);
	printf("\n");
	for (int i = 0; i < 155; i++) {
		printf("%s", "-");
	}
	printf("\n\n");
}

main(void) {
	struct Member member[MAX_NUMBER_MEMBER];
	struct Member member2;
	int choice;

	FILE *memberFptr;

	memberFptr = fopen("../TrainTicketingSys/res/member.bin", "rb");

	if (memberFptr == NULL) {
		printf("Can't Open The File\n");
		exit(-1);
	}

	fread(&member2, sizeof(member2), 1, memberFptr);
	while (!feof(memberFptr))
	{
	
		strcpy(member[numMember].id, member2.id);
		strcpy(member[numMember].name, member2.name);
		strcpy(member[numMember].pass, member2.pass);
		member[numMember].age = member2.age;
		strcpy(member[numMember].gender, member2.gender);
		strcpy(member[numMember].ic, member2.ic);
		strcpy(member[numMember].phoneNo, member2.phoneNo);
		strcpy(member[numMember].email, member2.email);
		member[numMember].rewardPoints = member2.rewardPoints;
		for (int i = 0; i < 3; i++)
			member[numMember].security[i].questionNum = member2.security[i].questionNum;


		for(int i = 0; i < 3; i++)
			strcpy(member[numMember].security[i].answer, member2.security[i].answer);

		numMember++;
		fread(&member2, sizeof(member2), 1, memberFptr);
	}

	fclose(memberFptr);

	//test to display all data
	for (int i = 0; i < numMember; i++) {
		printf("%d. %s\n", i + 1, member[i].id);
	}

	//test data
	//strcpy(member[numMember].id, "123");
	//strcpy(member[numMember].pass, "321");
	//strcpy(member[numMember].name, "Lee");
	//member[numMember].age = 20;
	//strcpy(member[numMember].gender, "M");
	//strcpy(member[numMember].ic, "123-321");
	//strcpy(member[numMember].phoneNo, "01161188688");
	//strcpy(member[numMember].email, "lee@gmail.com");
	//member[numMember].rewardPoints = 0.00;
	//member[numMember].security[0].questionNum = 1;
	//member[numMember].security[1].questionNum = 2;
	//member[numMember].security[2].questionNum = 3;
	//strcpy(member[numMember].security[0].answer, "1");
	//strcpy(member[numMember].security[1].answer, "2");
	//strcpy(member[numMember].security[2].answer, "3");
	//numMember++;

	//deleteMember(member);

	//searchMember(member);

	do {
		printf("test\n");
		printf("1.member menu\n");
		printf("2. delete member\n");
		printf("3. search member\n");
		printf("Please Enter Your Choice: ");
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			memberMenu(member);
			break;
		case 2:
			deleteMember(member);
			break;
		case 3:
			searchMember(member);
			break;
		case 4:
			printf("EXITING PROGRAM.....\n");
			break;
		default:
			printf("Invalid Choice!\n");
			printf("Please Try Again\n");
		}
	} while (choice != 4);

	memberFptr = fopen("../TrainTicketingSys/res/member.bin", "wb");

	for (int i = 0; i < numMember; i++) {
		fwrite(&member[i], sizeof(member[0]), 1, memberFptr);
	}

	fclose(memberFptr);

	//memberMenu(member);

}

int tryAgain(int again) {
	int choice, invalidChoice;

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

void memberMenu(struct Member* member) {
	char *menu[] = {"Login", "Registration", "Forgot Password", "Exit Program"};
	int choice;
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
	char id[MEMBER_ID], password[MEMBER_PASS];
	int memberNUM;
	int loginSuccess = 0, again;
	
	do {
		again = 0;

		title();
		printf("ID: ");
		scanf(" %[^\n]", id);
		printf("Password: ");
		scanf(" %[^\n]", password);

		for (int i = 0; i < MAX_NUMBER_MEMBER; i++) {
			if (strcmp(member[i].id, id) == 0 && strcmp(member[i].pass, password) == 0) {
				printf("Login Successful. ");

				waitingScreen();
				
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
		

		if (email[i] == ' ' || email[i] == '/' || email == ':' || email[i] == ';'
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

void memberRegister(struct Member* member) {
	
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
		scanf(" %[^\n]", password);
		printf("Password Confirm: ");
		scanf(" %[^\n]", passConfirm);

		if (strcmp(password, passConfirm) != 0) {
			printf("\nNew Password and Confrim Password Are Not Same!\n");
			again = tryAgain(again);
			if (again == 0)
				return 0;
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
				printf("\nInvalid Choice!\n");
				printf("Please Enter Number 1 - 6. ");

				waitingScreen();
				
				success = 0;
				break;
			}
			if (i > 0) {
				for (int x = 0; x < i; x++) {
					if (questionSelection[i] == questionSelection[x]) {
						printf("\nThe Selected Security Question Must Be Different From The Previous One.\n");
						printf("Please Try Again. ");

						waitingScreen();
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
	member[numMember].rewardPoints = 0.00;

	printf("\nInformation Added. ");
	waitingScreen();

	numMember++;

}

void forgotPass(struct Member* member) {
	bool resultPass;
	char id[MEMBER_ID], question[MAX_NUM_QUESTION][100], answer[MAX_NUM_QUESTION][100];
	int num, questionSelection[MAX_NUMBER_MEMBER], newPassword[MEMBER_PASS], newPassConfirm[MEMBER_PASS];
	int idExist = 0, again = 0, securityPass = 0, choice, invalidChoice = 0;

	do {
		title();
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
				do {
					again = 0;
					title();

					printf("ID: %s\n", id);

					printf("\n");

					passwordFormat();

					printf("New Password: ");
					scanf(" %[^\n]", newPassword);
					printf("New Password Confirm: ");
					scanf(" %[^\n]", newPassConfirm);

					if (strcmp(newPassword, newPassConfirm) != 0) {
						printf("\nNew Password and Confrim Password Are Not Same!\n");
						again = tryAgain(again);
						if (again == 0)
							return 0;
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

				} while (again == 1);
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
		title();
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
			rewardPoint(member, memberNUM);
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
		title();
		again = 0;
		printf("Profile Information\n");
		printf("--------------------\n");
		printf("ID: %s\n", member[memberNUM].id);
		printf("Name: %s\n", member[memberNUM].name);
		printf("Contact Number: %s\n", member[memberNUM].phoneNo);
		printf("Email: %s\n", member[memberNUM].email);
		printf("\nEnter 1 to MODIFY PROFILE (0 EXIT)\n");
		scanf("%d", &choice);

		if (choice == 1) {
			printf("\n");
			printf("----------------------\t ----------------------\t  ----------------------\n");
			printf("| 1 | Password       |\t | 2 | Contact Number |\t  | 3 | Email          |\n");
			printf("----------------------\t ----------------------\t  ----------------------\n");

			printf("\nEnter your choice: ");
			scanf("%d", &modify);

			if (modify == 1) {
				do {
					again = 0;
					title();
					printf("Old Password: ");
					scanf(" %[^\n]", oldPassword);
					printf("\n");
					printf("New Password: ");
					scanf(" %[^\n]", newPassword);
					printf("\n");
					printf("Confirm Password: ");
					scanf(" %[^\n]", passConfirm);
					printf("\n");

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
					waitingScreen();
					printf("\n");
				}

			}

			else if (modify == 2){
				title();
				printf("Current Contact Number: %s\n\n", member[memberNUM].phoneNo);
				printf("New Contact Number: ");
				scanf(" %[^\n]", member[memberNUM].phoneNo);
				printf("\nContact Number is changing. ");
				waitingScreen();
			}
			else if (modify == 3) {
				title();
				printf("Current Email: %s\n\n", member[memberNUM].email);
				printf("New Email: ");
				scanf(" %[^\n]", member[memberNUM].email);
				printf("\nEmail is changing. ");
				waitingScreen();
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

void bookingHistory() {

}

void cancelBooking() {

}

//havent done yet
void rewardPoint(struct Member* member, int memberNUM) {

	printf("Current Points \n%.2f\n", member[memberNUM].rewardPoints);
	/*printf("1. Terms and conditions");*/
}

//havent done yet
void searchMember(struct Member* member) {
	char* menu[] = { "ID", "Gender", "Age", "Reward Points", "Exit"};
	int choice;

	do {

		title();
		for (int i = 0; i < sizeof(menu) / sizeof(menu[0]); i++) {
			printf("-----\n");
			printf("| %d | %s\n", i + 1, menu[i]);
			printf("-----\n");
		}
		printf("Please Enter Your Choice: ");
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			searchMemberID(member);
			break;
		case 2:
			searchMemberGender(member);
			break;
		case 3:
			searchMemberAge(member);
			break;
		case 4:
			searchMemberRewardPoints(member);
			break;
		case 5:
			//not exiting program
			printf("EXITING. ");
			waitingScreen();
			break;
		default:
			printf("Invalid Choice!\n");
			printf("Please Try Again\n");
		}
	} while (choice != 5);
}

int validateNumberMember() {
	title();
	if (numMember == 0) {
	
		printf("\nThere is no member. ");
		waitingScreen();
		return 0;
	}
}

void searchMemberTitle(void) {
	printf("----------------------------------------------------------------------------------------------------------------------\n");
	printf("| ID         | NAME                 | AGE | GENDER | CONTACT NUMBER | EMAIL                          | Reward Points |\n");
	printf("----------------------------------------------------------------------------------------------------------------------\n");
}

void searchMemberID(struct Member* member) {
	char id[MEMBER_ID], next[10];
	int success = 0, again = 0;

	if (validateNumberMember() == 0)
		return 0;

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
	} while (again == 1);
}

void searchMemberGender(struct Member* member) {
	char* menu[] = { "Male", "Female"};
	char next[10];
	int again = 0, gender, memberExist =0;

	if (validateNumberMember() == 0)
		return 0;

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

		scanf("%d", &gender);
			if (gender == 1 || gender == 2){
			
					do {
						again = 0;
						title();
						if (gender == 1) {
						
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
					}while (again == 1);
			}
			else {
				printf("Invalid Choice\n");
				again = tryAgain(again);
			}
			
	} while (again == 1);
}

void searchMemberAge(struct Member* member) {
	char* menu[] = { "Equal To ", "Greater Than or Equal To ", "Less Than or Equal To " };
	char next[10];
	int age, again=0, choice, memberExist = 0;

	if (validateNumberMember() == 0)
		return 0;

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
			else if(choice == 3) {
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

	}while (again == 1);
}

void searchMemberRewardPoints(struct Member* member) {
	char* menu[] = { "Equal To ", "Greater Than or Equal To ", "Less Than or Equal To " };
	char next[10];
	float rewardPoints;
	int again = 0, choice, memberExist = 0;

	if (validateNumberMember() == 0)
		return 0;

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

	} while (again == 1);
}

void deleteMember(struct Member* member) {
	char* confirmationMenu[] = { "Confirm", "Cancel" };
	char id[MEMBER_ID];
	int confirmation, again = 0, success = 0;

	if (validateNumberMember() == 0)
		return 0;

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
	} while (again == 1);
}

