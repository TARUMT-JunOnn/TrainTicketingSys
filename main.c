#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#define USE_STRUCT

#include "booking.c"
#include "schedules.c"
#include "member.c"
#include "staff.c"
#pragma warning(disable:4996);

SYSTEMTIME t;
int mem_point;
int menu(void);

typedef struct {
	char name[50];
	char mode[4];
}FileMode;

int readFile() {
	FILE* fptr[4];
	FileMode read[4] = { 
		{"../TrainTicketingSys/res/member.bin",  "rb"},
		{"../TrainTicketingSys/res/staff.bin",  "rb"},
		{"../TrainTicketingSys/res/schedule.txt",  "r"},
		{ "../TrainTicketingSys/res/booking.txt",  "r" }
};
	int status;
	for (int i = 0; i < 4; i++) {
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
		}
		fclose(fptr[i]);
	}
}

int writeFile() {
	FILE* fptr[4];
	FileMode write[4] = {
	{"../TrainTicketingSys/res/member.bin",  "wb"},
	{"../TrainTicketingSys/res/staff.bin",  "wb"},
	{"../TrainTicketingSys/res/schedule.txt",  "w"},
	{ "../TrainTicketingSys/res/booking.txt",  "w" }
	};
	int status;
	for (int i = 0; i < 4; i++) {
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
			mem_point = member[mem_num].rewardPoints;
			status = addBooking(&userChoice, member[mem_num].name, member[mem_num].id, &member[mem_num].rewardPoints, &seats, &price);
			if (status == 1) {
				if (mem_point == member[mem_num].rewardPoints && price > 0) {
					memPointCal(&mem_point, price);
					addMemPoint(mem_num, mem_point);
				}
				writeFile();
			}
			break;
		}
	} while (status == -1);
	return status;
}

int menu(int choice) {
	int status, identifier;
	int mem_num;
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
	int status, member_num, now, mem_point;
	float price;
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
								status = booking(-1);
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
						case 5:
					//		searchBooking(member[member_num].id);
							status = 5;
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
}
