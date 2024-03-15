#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable:4996)
#define memberName 100
#define memberPass 100
#define maxMember 100 


void memberMenu();
void menuLogin();
void memberLogin();
void memberRegister();
void forgotPass();
void memberMainPage();

struct Member {
	char id[memberName];
	char pass[memberPass];
	
};

main() {
	struct Member member[maxMember];
	system("cls");
	memberMenu(member);

}

void memberMenu(struct Member* member) {
	char *menu[] = {"Login", "Registration", "Forgot Password", "Exit Program"};
	int choice;
	printf("Member Menu\n");
	printf("-----------\n");
	for (int i = 0; i < sizeof(menu)/sizeof(menu[0]); i++) {
		printf("-----\n");
		printf("| %d | %s\n", i + 1, menu[i]);
		printf("-----\n");
	}
	printf("Please Enter Your Choice: ");
	scanf("%d", &choice);
	do {
		switch (choice) {
		case 1: 
			memberLogin(member);
			break;
		case 2:
			memberRegister();
			break;
		case 3: 
			forgotPass();
			break;
		default:
			printf("Invalid Choice!\n");
			printf("Please Try Again\n");
		}
	} while (choice !=4);
}

//void memberMenu(){
//	printf("Member Menu\n");
//	printf("-----------\n");
//	menuLogin();
//}

void memberLogin(struct Member* member) {
	char name[memberName], password[memberPass];
	
	system("cls");
	printf("Name: ");
	scanf(" %[^\n]", name);
	printf("Password: ");
	scanf(" %[^\n]", password);
	
	for (int i = 0; i < maxMember; i++) {
		if (strcmp(member[i].id, name) == 0 && strcmp(member[i].pass, password) == 0) {
			printf("Login successful...\n");

		}
	}


}
void memberRegister() {

}
void forgotPass() {

}

void memberMainPage();