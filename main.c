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

int writeFile() {
	FILE* fptr[4];
	int status;
	for (int i = 0; i < 4; i++) {
		switch (i) {
		case 0:
			status = writeMemberFile(&fptr[i]);
			break;
		case 1:
			status = writeStaffFile(&fptr[i]);
			break;
		case 2:
			status = writeScheduleFile(&fptr[i]);
			break;
		case 3:
			status = writeBookingFile(&fptr[i]);
			break;
		}
		if (status == -1)
			return status;
	}
}

int menu(int choice) {
	int status, identifier;
	do {
		if (choice == 0) {
			title();
			printf("Menu\n");
			printf("-----\n");
			printf("1. Employee\n");
			printf("2. Member\n");
			printf("0. Exit\n");
			scanf("%d", &choice);
		}

		switch (choice) {
		case 1:
			status = employeeMenu();
			choice = 0;
			identifier = 10;
			break;
		case 2:
			status = memberMenu();
			choice = 0;
			identifier = 20;
			break;
		case 0:
			writeFile();
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
			do {
				status = staffMenu();
				switch (status) {
				case 1:
					status = staff_login();
					switch (status) {
					case 1:
						do {
							status = -1;
							switch (staff_main_page()) {
							case 3:
								scheduleMain(0);
								status = 3;
								break;
							case 4:
								searchMember();
								status = 4;
								break;
							case 6:
								chooseTime();
								status = 6;
								break;
							case 0:
								status = -1;
								break;
							}
						} while (status != -1);
						break;
					case 0:
						status = -1;
						break;
					}
					break;
				case 2:
					staff_registration();
					status = -1;
					break;
				case 0:
					return 1;
					break;
				}
			} while (status == -1);
			break;
		case 12:
			do{
				status = manager_menu();
				switch (status) {
				case 0:
					return 1;
					break;
				case 1:
						switch (manager_login()) {
						case 1:
							do {
								switch (manager_main_page()) {
								case 6:
									scheduleMain(1);
									status = 6;
									break;
								case 7:
									loginHistory();
									status = 7;
									break;
								case 0:
									status = -1;
									break;
							}
							} while (status != -1);
							break;
						case 0:
							status = -1;
							break;
						}
					break;
				case 2:
					manager_registration();
					status = -1;
					break;
				}
			} while (status == -1);
			break;
		case 21:
			status = memberLogin();
			switch (status) {
			case 1:
				return 2;
				break;
				case 3:
					chooseTime();
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
			return 2;
			break;
		case 23:
			forgotPass();
			return 2;
			break;
		}
	} while (status != 0);
}

int main(void) {
	int status = 0;
	if (readFile() == -1) {
		printf("Unable open file");
		return -1;
	}
	do {
		status = menu(status);
		status = subMenu(status);
	} while (status == 0 || status == 1 || status == 2);
	chooseTime();
}

int chooseTime() {
	int dateSeperate[3];
	char date[11], day[80];
	title();
	beforeBooking();
	system("pause");
}
