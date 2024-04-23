#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<windows.h>
#include<conio.h>
#include<ctype.h>
#pragma warning(disable:4996);
SYSTEMTIME t;
int mem_point;

int menu(void);

void dayOfWeek(int numOfWeek, char(*dayReturn)[10]) {
	const char day[7][10] = { {"Sunday"} , {"Monday"} ,{"Tuesday"} ,{"Wednesday"} ,{"Thursday"} ,{"Friday"} ,{"Saturday"} };
	strcpy((*dayReturn), day[numOfWeek]);
}

void title(void) {
	char day[10];
	system("cls");
	printf("%10s %s %s", "Train", "Ticketing", "System");
	GetLocalTime(&t);
	dayOfWeek(t.wDayOfWeek, &day);
	const char month[12][10] = { {"January"}, {"February"}, {"March"}, {"April"}, {"May"}, {"June"}, {"July"}, {"August"}, {"September"}, {"October"}, {"November"}, {"December"} };
	printf("%104s %02d %s %d %02d:%02d:%02d", day, t.wDay, month[t.wMonth - 1], t.wYear, t.wHour, t.wMinute, t.wSecond);
	printf("\n");
	for (int i = 0; i < 155; i++) {
		printf("%s", "-");
	}
	printf("\n\n");
}

int readFile() {
	FILE* fptr[4];
	int status;
	for (int i = 0; i < 4; i++) {
		switch (i) {
		case 0:
			status = readMemberFile(&fptr[i]);
			break;
		case 1:
			status = readStaffFile(&fptr[i]);
			break;
		case 2:
			status = readScheduleFile(&fptr[i]);
			break;
		case 3:
			status = readBookingFile(&fptr[i]);
			break;
		}
		if (status == -1)
			return status;
	}
}

int menu(void) {
	int choice, status, identifier;
	do {
		title();
		printf("Menu\n");
		printf("-----\n");
		printf("1. Employee\n");
		printf("2. Member\n");
		printf("0. Exit\n");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			status = employeeMenu();
			identifier = 10;
			break;
		case 2:
			status = memberMenu();
			identifier = 20;
			break;
		case 0:
			exit(-1);
			break;
		}
	} while (status == 0);
	return status + identifier;
}

int subMenu(int input) {
	int status;
	do {
		switch (input) {
		case 11:
			status = staffMenu();
			switch (status) {
			case 1: 
				staff_login();
				break;
			case 2:
				staff_registration();
				break;
					
			}
			break;
		case 12:
			manager_menu();
			break;
		case 21:
			status = memberLogin();
			switch (status) {
				case 2:
					DisplaySchedule();
					break;
				case 3:
					
					break;
				case 4:
					
					break;
				case 5: 
					cancelBooking();
					break;
			}
			break;
		case 22:
			memberRegister();
			return 0;
			break;
		case 23:
			forgotPass();
			return 0;
			break;
		}
	} while (status != 0);
}

int main(void) {
	int status;
	if (readFile() == -1) {
		printf("Unable open file");
		return -1;
	}
	do {
		status = menu();
		status = subMenu(status);
	} while (status == 0);
}

int chooseTime() {
	allSchedule(); 
	int dateSeperate[3];
	char date[11], day[80];
	printf("What time you would like to booking ?\n");
	for (int i = 0; i < 14; ++i) {
		countDate(i, &dateSeperate[0], &dateSeperate[0], &dateSeperate[0], day);

	}
}