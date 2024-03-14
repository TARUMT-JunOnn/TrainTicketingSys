#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable:4996)

void memberMenu();
void menuLogin();
void memberLogin();
void memberRegister();
void forgotPass();

main() {
	memberMenu();

}

void menuLogin(){
	char *menu[] = {"Login", "Registration", "Forgot Password", "Exit Program"};
	int choice;
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
			memberLogin();
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

void memberMenu(){
	printf("Member Menu\n");
	printf("-----------\n");
	menuLogin();
}

void memberLogin() {


}
void memberRegister() {

}
void forgotPass() {

}