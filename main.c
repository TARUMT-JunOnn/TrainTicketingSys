#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#define USE_STRUCT
#define USE_TITLE

#include "booking.c"
#include "schedules.c"
#include "member.c"
#include "staff.c"
#include"common.c"
#pragma warning(disable:4996);

#ifndef USE_STRUCT
#define MAX_PAX 10
#define MAX_RECORDS 5000
struct train {
	float depart;
	float arrive;
};

struct date {
	int day, month, year;
	char weekday[20];
	struct train time;
};

typedef struct {
	char trainId[6];
	char departFrom[20];
	char destination[20];
	float price;
	struct date prefer;
}Info;
#endif

#ifndef USE_TITLE
#include<Windows.h>
#include<string.h>
SYSTEMTIME t;
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
#endif

SYSTEMTIME t;
int mem_point;
int menu(void);

typedef struct {
	char name[50];
	char mode[4];
}FileMode;

int readFile() {
	FILE* fptr[5];
	FileMode read[5] = { 
		{"../TrainTicketingSys/res/member.bin",  "rb"},
		{"../TrainTicketingSys/res/staff.bin",  "rb"},
		{"../TrainTicketingSys/res/schedule.txt",  "r"},
		{"../TrainTicketingSys/res/booking.txt",  "r" },
		{"../TrainTicketingSys/res/feedback.txt", "r"}
};
	int status;
	for (int i = 0; i < 5; i++) {
		fptr[i] = fopen(read[i].name, read[i].mode);
		if (fptr[i] == NULL)
			return -1;
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
		case 4:
			status = readFeedbackFile(&fptr[i]);
			break;
		}
		fclose(fptr[i]);
	}
}

int writeFile() {
	FILE* fptr[5];
	FileMode write[5] = {
	{"../TrainTicketingSys/res/member.bin",  "wb"},
	{"../TrainTicketingSys/res/staff.bin",  "wb"},
	{"../TrainTicketingSys/res/schedule.txt",  "w"},
	{ "../TrainTicketingSys/res/booking.txt",  "w" },
	{"../TrainTicketingSys/res/feedback.txt", "w"}
	};
	int status;
	for (int i = 0; i < 5; i++) {
		fptr[i] = fopen(write[i].name, write[i].mode);
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
		case 4:
			status = writeFeedbackFile(&fptr[i]);
			break;
		}
		fclose(fptr[i]);
	}
}

int booking(int mem_num) {
	int dateSeperate[3], status = 0, seats[2], mem_point = 0, trip;
	char date[11], day[80];
	float price = 0;
	Info userChoice[MAX_TRIP][MAX_PAX];
	for (int i = 0; i < MAX_TRIP; i++) {
		for (int j = 0; j < MAX_PAX; j++)
			reset(&userChoice[i][j]);
	}
	do {
		title();
		trip = chooseTime(&userChoice, &seats);
		switch (trip) {
		case 0:
			return 0;
			break;
		case 1:
		case 2:
			switch (mem_num) {
			case -1:
				mem_point = 0;
				status = addBooking(&userChoice, "Employee", "EMP", &mem_point, &seats, &price);
				break;
			default:
				mem_point = member[mem_num].rewardPoints;
				status = addBooking(&userChoice, member[mem_num].name, member[mem_num].id, &member[mem_num].rewardPoints, &seats, &price);
				if (status == 1) {
					if (mem_point == member[mem_num].rewardPoints && price > 0) {
						memPointCal(&mem_point, price);
						addMemPoint(mem_num, mem_point);
					}
				}
				break;
			}
			if (status == 1)
				writeFile();
			break;
		}
	} while (status == -1);
	return status;
}

int menu(int choice) {
	char* menu[] = { "Employee", "Member", "Exit Program"};
	int status = 0, identifier;
	int mem_num;
	do {
		status = 0;
		if (choice == 0) {
				title();
				printf("\t\t----------------------------------------------------------------------------------------------------------------------------\n");
				printf("\t\t|  _____              _          _____  _        _          _    _                  ____              _                    |\n");
				printf("\t\t| |_   _|__ ___ ____ (_) _ __   |_   _|(_)  ____| | __ ___ | |_ (_) ___    ______  / ___| _   _  ___ | |_  ___ _ __  ___   |\n");
				printf("\t\t|   | |  | '__// _` || || '_ \\    | |  | | / __|| |/ // _ \\| __|| || '_ \\ /  _  |  \\___ \\| | | |/ __|| __|/ _ \\| '_ ` _ \\  |\n");
				printf("\t\t|   | |  | |  | (_| || || | | |   | |  | || (__ |   < | __/| |_ | || | | || (_| |  ___) || |_| |\\__ \\| |_ | __/| | | | | | |\n");
				printf("\t\t|   |_|  |_|   \\__,_||_||_| |_|   |_|  |_| \\___||_|\\_\\\\___\\\\___||_||_| |_| \\__, |  |____/ \\__, ||___/\\___|\\___||_| |_| |_| |\n");
				printf("\t\t|                                                                          |___/          |___/                            |\n");
				printf("\t\t----------------------------------------------------------------------------------------------------------------------------\n");
				printf("\n");
				printf("Menu\n");
				printf("-----\n");

				for (int i = 0; i < sizeof(menu) / sizeof(menu[0]); i++) {
					printf("-----\n");
					if (i == 2)
						printf("| %d | %s\n", 0, menu[i]);

					else
						printf("| %d | %s\n", i + 1, menu[i]);

					printf("-----\n");
				}
				printf("\nEnter Your Choice: ");
				rewind(stdin);
				if (scanf("%d", &choice) != 1)
					choice = 3;
				
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
		default: 
			status = 0;
			choice = 0;
			break;
		}
	} while (status == 0);
	return status + identifier;
}

int subMenu(int input) {
	int status, member_num, now, mem_point;
	float price;
	Info trainList[10];
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
							int check = checkTime(&trainList);
							switch (staff_main_page(check)) {
							case 3:
								scheduleMain(0);
								writeFile();
								status = 3;
								break;
							case 4:
								searchMember();
								status = 4;
								break;
							case 6:
								status = booking(-1);
								status = 6;
								break;
							case 7:
								chooseList(&trainList, check);
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
					status = staff_registration();
					if (status == 1)
						writeFile();
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
									writeFile();
									status = 6;
									break;
								case 7:
									deleteMember();
									status = 7;
									break;
								case 8:
									loginHistory();
									status = 8;
									break;
								case 9:
									displayFeedback();
									status = 9;
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
					if (status == 1)
						writeFile();
					status = -1;
					break;
				}
			} while (status == -1);
			break;
		case 21:
				status = memberLogin(&member_num, &now);
				switch (status) {
				case 1:
					do {
						switch (memberMainPage(member_num, now)) {
						case 2:
							scheduleMain(0);
							status = 2;
							break;
						case 3:
							booking(member_num);
							status = 3;
							break;
						case 4:
							do{
							price = 0;
							status = bookingHistory(member[member_num].id, &price);
							if (status == 1 && price > 0) {
								price *= 100;
								memPointCal(&mem_point, price);
								addMemPoint(member_num, mem_point);
								writeFile();
							}
							} while (status == 1);
							status = 4;
							break;
						case 0:
							return 2;
							break;
						}
					} while (status != 0);
					break;
				case 0:
					return 2;
					break;
				}
		case 22:
			memberRegister();
			writeFile();
			return 2;
			break;
		case 23:
			passRecovery();
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
}
