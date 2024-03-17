#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<math.h>
#pragma warning(disable:4996)
#define MAX_PAX 10
#define MAX_TRIP 2

//Global Structure Declaration
struct train {
	float depart;
	float arrive;
};

struct date {
	int day, month, year;
	struct train time;
};

typedef struct {
	char trainId[6];
	char departFrom[20];
	char destination[20];
	float price;
	struct date prefer;
}Info;

//Global Variable

//Function Declaration
void createDate(Info (*userChoice)[MAX_TRIP][MAX_PAX], char (*date)[MAX_PAX][11]);
void calcPax(Info (*userChoice)[MAX_TRIP][MAX_PAX], int (*pax)[2]);
float calcFare(Info (*userChoice)[MAX_TRIP][MAX_PAX], char (*)[MAX_PAX][11], int (*pax)[2]);
float calcTax(int, float);
char userAction();
void editPax(Info(*userChoice)[MAX_TRIP][MAX_PAX], char(*)[MAX_PAX][11], int(*pax)[2]);
addBooking();

void reset(Info (*userChoice)[MAX_TRIP][MAX_PAX]) {
	for (int j = 0; j < MAX_TRIP; ++j) {
		for (int i = 0; i < MAX_PAX; ++i) {
			(*userChoice)[j][i].prefer.day = NULL;
			(*userChoice)[j][i].prefer.month = NULL;
			(*userChoice)[j][i].prefer.year = NULL;
			(*userChoice)[j][i].prefer.time.depart = 0;
			(*userChoice)[j][i].prefer.time.arrive = 0;
			strcpy((*userChoice)[j][i].destination, "NULL");
			strcpy((*userChoice)[j][i].trainId, "NULL");
			strcpy((*userChoice)[j][i].departFrom, "NULL");
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

int main(void) {
	char dateAdd[MAX_TRIP][MAX_PAX][11], action = ' ';
	int pax[2], status;
	Info userChoice[MAX_TRIP][MAX_PAX];
	reset(userChoice);
	userChoice[0][0] = (Info) {"T1001", "KL Sentral",  "Kampar", 50, { 1, 4, 2024,{ 9, 13} } };
	userChoice[1][0] = (Info){ "T1004", "Kampar", "KL Sentral", 25, { 2, 4, 2024,{ 5, 8} } };
	do {
		createDate(userChoice, dateAdd);
		if (action == '2') {
			editPax(userChoice, dateAdd, pax);
		}
		calcPax(userChoice, pax);
		float fare = calcFare(userChoice, dateAdd, pax);
		action = userAction();
	} while (action == '2');
	switch (action)
	{
		case '1':
			return 1; //Back to Schedules
			break;
		case '3':
			//status = payment();
			break;
		case '0':
			return 0;
	}
}

void createDate(Info (*userChoice)[MAX_TRIP][MAX_PAX], char (*date)[MAX_TRIP][MAX_PAX][11]) {
	char takeDay[2][3];
	char takeYear[5];
	for (int j = 0; j < MAX_TRIP; ++j) {
		for (int i = 0; i < MAX_PAX; ++i) {
			if ((*userChoice)[j][i].prefer.day != NULL && (*userChoice)[j][i].prefer.month != NULL && (*userChoice)[j][i].prefer.year != NULL) {
				itoa((*userChoice)[j][i].prefer.day, takeDay[0], 10);
				itoa((*userChoice)[j][i].prefer.month, takeDay[1], 10);
				itoa((*userChoice)[j][i].prefer.year, takeYear, 10);
				strcpy((*date)[j][i], takeDay[0]);
				if ((*userChoice)[j][i].prefer.day >= 1 && (*userChoice)[j][i].prefer.day <= 9) {
					(*date)[j][i][0] = '0';
					strcat((*date)[j][i], takeDay[0]);
				}
				strcat((*date)[j][i], "/");
				strcat((*date)[j][i], takeDay[1]);
				if ((*userChoice)[j][i].prefer.month >= 1 && (*userChoice)[j][i].prefer.month <= 9) {
					(*date)[j][i][3] = '0';
					strcat((*date)[j][i], takeDay[1]);
				}
				strcat((*date)[j][i], "/");
				strcat((*date)[j][i], takeYear);
			}
		}
	}
}

void calcPax(Info (*userChoice)[MAX_TRIP][MAX_PAX], int (*pax)[2]){
	for (int j = 0; j < MAX_TRIP; ++j) {
		(*pax)[j] = 0;
		for (int i = 0; i < MAX_PAX; ++i) {
			if (strcmp((*userChoice)[j][i].destination, "NULL") != 0)
				++(*pax)[j];
		}
	}
}

float calcFare(Info (*userChoice)[MAX_TRIP][MAX_PAX], char (*date)[MAX_TRIP][MAX_PAX][11], int (*pax)[2]) {
	float totalPrice[10], sumPrice = 0, adj = 0, tax = 0,  negative;
	int sumPriceint;
	//print price list
	title(NULL);
	for (int i = 0; i < 115; i++) {
		printf("-");
	}
	printf("\n");
	printf("%-11s\t %-5s\t %-5s\t %-5s\t \%-10s\t %-10s\t %-2s\t %-13s\t %-10s\n", "Date", "From", "To", "TrainID", "Depart From", "Destination", "Pax", "Price per Pax", "Net Price");
	for (int i = 0; i < 115; i++) {
		printf("-");
	}
	printf("\n");
	for (int i = 0; i < MAX_TRIP; ++i) {
		if ((*pax)[i] != 0 && (*date)[i][0][2] == '/') {
			totalPrice[0] = (*userChoice)[i][0].price * (float)(*pax)[i];
			printf("%s\t %.2f\t %.2f\t %-7s\t %-15s %-15s %d\t RM %-10.02f\t RM %.02f\n", (*date)[i][0], (*userChoice)[i][0].prefer.time.depart, (*userChoice)[i][0].prefer.time.arrive, (*userChoice)[i][0].trainId, (*userChoice)[i][0].departFrom, (*userChoice)[i][0].destination, (*pax)[i], (*userChoice)[i][0].price, totalPrice[0]);
			sumPrice += totalPrice[0];
		}
	}
	for (int i = 0; i < 115; i++) {
		printf("-");
	}
	printf("\n");
	printf("%102s : RM%6.02f\n", "Total", sumPrice);
	int count = 0;
	float sst = calcTax(count, sumPrice);
	++count;
	float gst = calcTax(count, sumPrice);
	tax = gst + sst;
	sumPrice += tax;;
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
		printf("%102s : -RM%6.02f\n", "Rounding Adjustment", negative);
	}
	else {
		printf("%102s : RM%6.02f\n", "Rounding Adjustment", adj);
	}
	sumPrice += adj;
	printf("%102s : RM%6.02f\n", "Total Price should payment", sumPrice);
	printf("\n\n");
	return sumPrice;
}

float calcTax(int count, float sumPrice) {
	if (count == 0) {
		float sst;
		sst = sumPrice * 0.1;
		printf("%102s : RM%6.02f\n", "Service Tax 10%", sst);
		return sst;
	}
	else if (count == 1) {
		float gst;
		gst = sumPrice * 0.06;
		printf("%102s : RM%6.02f\n", "GST 6%", gst);
		return gst;
	}
}

char userAction() {
	char action;
	printf("What action you would like to perform ?\n");
	printf("\t1. Edit trip\n\t2. Edit Number of Pax\n\t3. Payment & Booking\n\t0. Return\n\n");
	printf("Enter the number : ");
	rewind(stdin);
	scanf("%c", &action);
	return action;
}

void editPax(Info(*userChoice)[MAX_TRIP][MAX_PAX], char(*date)[MAX_TRIP][MAX_PAX][11], int(*pax)[2]) {
	char paxInC[3];
	int paxInD = 0, j = 0;
	do{
		title(NULL);
	/*	for (int i = 0; i < 75; i++) {
			printf("_");
		}*/
		printf("\n");
		printf("%-11s\t %-5s\t %-5s\t %-5s\t \%-10s\t %-10s\t %-2s\n", "Date", "From", "To", "TrainID", "Depart From", "Destination", "Pax (1-10)");
		while (j < MAX_TRIP)	{
			if ((*date)[j][0][2] == '/') {
				printf("%s\t %.2f\t %.2f\t %-7s\t %-15s %-15s ", (*date)[j][0], (*userChoice)[j][0].prefer.time.depart, (*userChoice)[j][0].prefer.time.arrive, (*userChoice)[j][0].trainId, (*userChoice)[j][0].departFrom, (*userChoice)[j][0].destination);
				rewind(stdin);
				scanf("%s", &paxInC);
				paxInD = atoi(&paxInC);
			}
			if (paxInD < 0 || paxInD > 10) {
				break;
			}
			else if (paxInD > (*pax)[j]) {
				for (int k = 0; k < paxInD; ++k) {
					if (strcmp((*userChoice)[j][k].destination, "NULL") == 0){
						(*userChoice)[j][k] = (*userChoice)[j][0];
					}
				}
			}
			else if (paxInD < (*pax)[j] || paxInD == 0) {
				for (int k = 9; k >= paxInD; --k) {
					if (strcmp((*userChoice)[j][k].destination, "NULL") != 0) {
						(*userChoice)[j][k].prefer.day = NULL;
						(*userChoice)[j][k].prefer.month = NULL;
						(*userChoice)[j][k].prefer.year = NULL;
						(*userChoice)[j][k].prefer.time.depart = 0;
						(*userChoice)[j][k].prefer.time.arrive = 0;
						strcpy((*userChoice)[j][k].destination, "NULL");
						strcpy((*userChoice)[j][k].trainId, "NULL");
						strcpy((*userChoice)[j][k].departFrom, "NULL");
					}
				}
			}
			++j;
		}
	} while (paxInD < 0 || paxInD > 10);
}

addBooking() {
	title();
	printf("Schedules: \n"); //Integerate with schedule module
}

