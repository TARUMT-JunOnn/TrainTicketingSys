#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<math.h>
#pragma warning(disable:4996)
#define MAX_BOOKING 10

//Function Declaration
float calcFare();
addBooking();

//Global Structure Declaration
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
	float price;
	struct date prefer;
}Info;

//Global Variable

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

void createDate(Info userChoice[MAX_BOOKING], char *date[MAX_BOOKING][9]) {
	void* add = &date;
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
}

float calcFare(Info userChoice[MAX_BOOKING], char date[MAX_BOOKING][9]) {
	float totalPrice[10], sumPrice = 0, adj = 0, negative;
	int sumPriceint;
	//print price list
	title(NULL);
	for (int i = 0; i < 110; i++) {
		printf("_");
	}
	printf("\n");
	printf("| %-10s| %-13s| %-16s| %-14s| %-5s| %-20s| %-18s|\n", "Date", "Destination", "Departure Time", "Arrival Time", "Pax", "Price per Pax (RM)", "Total Price (RM)");
	for (int j = 0; j < 10; j++) {
		if (userChoice[j].pax != NULL) {
			totalPrice[j] = userChoice[j].price * (float)userChoice[j].pax;
		printf("| %-10s| %-13s| %-16d| %-14d| %-5d| %-20.02f| %-18.02f|\n", date[j], userChoice[j].destination, userChoice[j].prefer.time.depart, userChoice[j].prefer.time.arrive, userChoice[j].pax, userChoice[j].price, totalPrice[j]);
			sumPrice += totalPrice[j];
		}
	}
	for (int i = 0; i < 110; i++) {
		printf("-");
	}
	printf("\n");
	printf("%97s : RM %.02f\n", "Total", sumPrice);
	//count Rounding
	sumPriceint = sumPrice * 100;
	sumPriceint %= 10;
	switch (sumPriceint) {
	case 1:
	case 2:
		adj = -((float)sumPriceint / 100);
		break;
	case 3:
	case 4:
		adj = 0.05 - ((float)sumPriceint / 100);
		break;
	case 6:
	case 7:
		adj = -(((float)sumPriceint / 100) - 0.05);
		break;
	case 8:
	case 9:
		adj = 0.1 - ((float)sumPriceint / 100);
		break;
	}
	if (adj < 0) {
		negative = adj * -1;
		printf("%97s : -RM %.02f\n", "Rounding Adjustment", negative);
	}
	else {
		printf("%97s : RM %.02f\n", "Rounding Adjustment", adj);
	}
	sumPrice += adj;
	printf("%97s : RM %.02f\n", "Total Price should payment", sumPrice);
	return sumPrice;
}

int main(void) {
	char dateAdd[MAX_BOOKING][9];
	Info userChoice[MAX_BOOKING] = { "Kampar", 1, 1, 4, 2024, 8, 11 };
	reset(userChoice);
	userChoice[0] = (Info) { "Kampar", 1, 50, { 1, 4, 2024,{ 8, 11} } };
	createDate(userChoice, dateAdd);
	calcFare(userChoice, dateAdd);
}

addBooking() {
	title();
	printf("Schedules: \n"); //Integerate with schedule module
}

