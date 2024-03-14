#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#pragma warning(disable:4996)
#define MAX_BOOKING 10

char date[MAX_BOOKING][9];

struct train {
	int depart;
	int arrive;
};

struct date {
	int day, month, year;
	struct train time;
};

typedef struct {
	char destination[20];
	int pax;
	struct date prefer;
}Info;


addBooking();

void reset(Info userChoice[MAX_BOOKING]) {
	for (int i = 0; i < MAX_BOOKING; ++i) {
		userChoice[i].pax = NULL;
		userChoice[i].prefer.day = NULL;
		userChoice[i].prefer.month = NULL;
		userChoice[i].prefer.year = NULL;
		userChoice[i].prefer.time.depart = NULL;
		userChoice[i].prefer.time.arrive = NULL;
		for (int j = 0; j < 20; j++) {
			userChoice[i].destination[j] = NULL;
		}
	}
}


void title(void) {
	system("cls");
	printf("%10s %s %s", "Train", "Ticketing", "System");
	time_t t;
	time(&t);
	printf("%125s", ctime(&t));
	for (int i = 0; i < 155; i++) {
		printf("%s", "-");
	}
	printf("\n\n");
}

void createDate(Info userChoice[MAX_BOOKING]) {
	char takeDay[2][3];
	char takeYear[5];
	for (int i = 0; i < MAX_BOOKING; ++i) {
		if (userChoice[i].prefer.day != NULL && userChoice[i].prefer.month != NULL && userChoice[i].prefer.year != NULL) {
			itoa(userChoice[i].prefer.day, takeDay[0], 10);
			itoa(userChoice[i].prefer.month, takeDay[1], 10);
			itoa(userChoice[i].prefer.year, takeYear, 10);
			strcpy(date[i], takeDay[0]);
			strcat(date[i], "/");
			strcat(date[i], takeDay[1]);
			strcat(date[i], "/");
			strcat(date[i], takeYear);
		}
	}
	printf("%s", date[0]);
}

int calcFare(Info userChoice[MAX_BOOKING]) {
	title(NULL);
	for (int i = 0; i < 70; i++) {
		printf("_");
	}
	printf("\n");
	printf("| %-10s| %-13s| %-16s| %-14s| %-5s|\n", "Date", "Destination", "Departure Time", "Arrival Time", "Pax");
	for (int j = 0; j < 10; j++) {
		if ((int)userChoice[j].pax != -52) {
			printf("| %-10s| %-13s| %-16d| %-14d| %-5d|\n", date[j], userChoice[j].destination, userChoice[j].prefer.time.depart, userChoice[j].prefer.time.arrive, userChoice[j].pax);
		}
	}
	for (int i = 0; i < 70; i++) {
	printf("-");
	}
}

int main(void) {
	Info userChoice[MAX_BOOKING];
	reset(userChoice);
	userChoice[0].prefer.day = 1;
	userChoice[0].prefer.month = 4;
	userChoice[0].prefer.year = 2024;
	title(NULL);
	createDate(userChoice);
	calcFare(userChoice);
}

addBooking() {
	title(NULL);
	printf("Schedules: \n"); //Integerate with schedule module
}

