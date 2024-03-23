#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<math.h>
#include<windows.h>
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
float calcFare(Info (*userChoice)[MAX_TRIP][MAX_PAX], char (*)[MAX_PAX][11], int (*pax)[2], int);
float calcTax(int, float);
char userAction();
void editPax(Info(*userChoice)[MAX_TRIP][MAX_PAX], char(*)[MAX_PAX][11], int(*pax)[2]);
int payment(float, Info(*userChoice)[MAX_TRIP][MAX_PAX], char(*)[MAX_PAX][11], int(*pax)[2]);
int card(float*, char *name[20]);
int bank(float*);
int eWallet();
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
	int pax[2], status = 0;
	float fare;
	Info userChoice[MAX_TRIP][MAX_PAX];
	reset(userChoice);
	userChoice[0][0] = (Info){ "T1001", "KL Sentral",  "Kampar", 50, { 1, 4, 2024,{ 9, 13} } };
	userChoice[1][0] = (Info){ "T1004", "Kampar", "KL Sentral", 25, { 2, 4, 2024,{ 5, 8} } };
	do{
		do {
			createDate(userChoice, dateAdd);
			if (action == '2') {
				editPax(userChoice, dateAdd, pax);
			}
			calcPax(userChoice, pax);
			do {
				fare = calcFare(userChoice, dateAdd, pax, status);
				if (fare == 0)
					title(NULL);
				action = userAction();
			} while (action == 'N');
		} while (action == '2');
		switch (action)
		{
			case '1':
				return 1; //Back to Schedules
				break;
			case '3':
				fare = calcFare(userChoice, dateAdd, pax, status);
				status = payment(fare, userChoice, dateAdd, pax);
				break;
			case '0':
				return 0;
		}
	} while (status != 1);
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

float calcFare(Info (*userChoice)[MAX_TRIP][MAX_PAX], char (*date)[MAX_TRIP][MAX_PAX][11], int (*pax)[2], int status) {
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
	if (status == 1)
		printf("%102s : RM%6.02f\n", "Total Price should payment before", sumPrice);
	else if (status == 0)
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
	if (action != '1' && action != '2' && action != '3' && action != '0')
		action = 'N';
	return action;
}

void editPax(Info(*userChoice)[MAX_TRIP][MAX_PAX], char(*date)[MAX_TRIP][MAX_PAX][11], int(*pax)[2]) {
	char paxInC[3];
	int paxInD = 0, j = 0;
	do{
		title(NULL);
		for (int i = 0; i < 92; i++) {
			printf("-");
		}
		printf("\n");
		printf("%-11s\t %-5s\t %-5s\t %-5s\t \%-10s\t %-10s\t %-2s\n", "Date", "From", "To", "TrainID", "Depart From", "Destination", "Pax (1-10)");
		for (int i = 0; i < 92; i++) {
			printf("-");
		}
		printf("\n");
		while (j < MAX_TRIP) {
			if ((*date)[j][0][2] == '/') {
				printf("%s\t %.2f\t %.2f\t %-7s\t %-15s %-15s ", (*date)[j][0], (*userChoice)[j][0].prefer.time.depart, (*userChoice)[j][0].prefer.time.arrive, (*userChoice)[j][0].trainId, (*userChoice)[j][0].departFrom, (*userChoice)[j][0].destination);
				rewind(stdin);
				scanf("%2s", &paxInC);
				paxInD = atoi(&paxInC);
				for (int k = 0; k < 3 && paxInC[k] != '\0'; ++k) {
					if ((int)paxInC[k] < 48 || (int)paxInC[k] > 57) {
						paxInD = -1;
						break;
					}
				}
			}
			if (paxInD < 0 || paxInD > 10) {
				break;
			}
			else if (paxInD > (*pax)[j]) {
				for (int k = 0; k < paxInD; ++k) {
					if (strcmp((*userChoice)[j][k].destination, "NULL") == 0) {
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
						for (int l = 0; l < 11; ++l) {
							(*date)[j][k][l] = '\0';
						}
					}
				}
			}
			++j;
		}
	} while (paxInD < 0 || paxInD > 10 );
}

int payment(float price, Info(*userChoice)[MAX_TRIP][MAX_PAX], char(*date)[MAX_PAX][11], int(*pax)[2]) {
	char memName[20];
	int mem_point;
	strcpy(memName, "Marco");
	mem_point = 1000;
	char input;
	int status = 0;
	float redeem;
	printf("Member Name : %s\tRemaining Member Points : %d pts\n", memName, mem_point);
	do {
		if (mem_point > 0) {
			printf("You can redeem up to %d pts points as cashback !\n", mem_point);
			if ((float)mem_point / 100 < price)
				redeem = (float)mem_point / 100;
			else
				redeem = price;
			printf("Would you like to redeem? \n\n\t1. Yes(-%d pts)\n\t2. No\n\t0. Return\n\n", (int)(redeem*100));
			printf("Enter the number : ");
			rewind(stdin);
			scanf("%c", &input);
		}
		switch (input) {
		case '1':
			mem_point -= (int)(redeem * 100);
			price -= redeem;
			status = 1;
			break;
		case '2':
			break;
		case '0':
			return 0;
			break;
		default:
			break;
		}
	} while (input != '1' && input != '2' && input != '0');
	calcFare((*userChoice), (*date), (*pax), status);
	if (status == 1) {
		printf("%102s :-RM%6.02f\n", "Point Redeemed", redeem);
		printf("%102s : RM%6.02f\n", "Total Price should payment", price);
	}
	printf("Payments method :\n\t1. Credit/Debit Card\n\t2. Online Banking\n\t3. E-Wallet\n\t0. Cancel Payment (Return)\n\n");
	printf("Enter the number : ");
	rewind(stdin);
	scanf("%c", &input);
	switch (input) {
	case '1':
		status = card(&price, memName);
		break;
	case '2':
		status = bank(&price);
		break;
	case '3':
		//status = eWallet();
		break;
	case '0':
		return 0;
		break;
	default:
		return  -1;
		break;
	}
	for (int i = 0; i < 3; ++i) {
		system("cls");
		printf("Verifying .");
		for (int j = 0; j < 2; ++j) {
			Sleep(250);
			printf(" .");
			Sleep(250);
		}
	}
	title(NULL);
	switch (status) {
		case 1:
			printf("Payment Sucessfully !\n");
			Sleep(2000);
			return status;
		case 0:
			printf("Payment Unsucessful.\n");
			Sleep(2000);
			return status;
		case -1:
			printf("Payment Denied.\n");
			Sleep(2000);
			return status;
		default:
			printf("Error, Please contact IT adminstrator.");
			Sleep(2000);
			return 404;
	}
}

int card(float* price, char name[20]) {
	char num[17], issuer[19], input = 'N', month[3], year[3], cvv[4];
	int loop, bigLoop = 0;
	strcpy(num, "NULL");
	strcpy(month, "NO");
	do {
		do {
			do {
				do {
					input = 'N';
					strcpy(issuer, "NULL");
					title(NULL);
					printf("\tPlease provide your card details (Press 0 to return): \n");
					printf("\t\t%-13s : ", "Card Number");
					if (strcmp(num, "NULL") == 0) {
						rewind(stdin);
						scanf("%s", num);
					}
					else {
						printf("%s\n", num);
					}
					switch (num[0]) {
					case '3':
						printf("\t\t%-13s : ", "Card Issuer");
						strcpy(issuer, "AMERICAN EXPRESS");
						printf("AMERICAN EXPRESS\n");
						if (num[15] != '\0') {
							printf("Please type 15 number\n");
							input = '1';
						}
						break;
					case '4':
						printf("\t\t%-13s : ", "Card Issuer");
						strcpy(issuer, "VISA");
						printf("VISA\n");
						break;
					case '5':
						printf("\t\t%-13s : ", "Card Issuer");
						strcpy(issuer, "MASTERCARD");
						printf("MASTERCARD\n");
						break;
					case '0':
						if (num[1] == '\0') {
							strcpy(num, "NULL");
							return -1;
						}
						else {
							input = '1';
						}
						break;
					default:
						printf("We are only accepted AMERICAN EXPRESS, VISA, MASTERCARD debit/credit card, Please use an alternative payment card/methods.\n");
						printf("Do you want to continue ?\n\t1. Yes\n\t0. No(Return)\n\n");
						printf("Enter the number : ");
						rewind(stdin);
						scanf("%c", &input);
						break;
					}
					for (int i = 0; i < 16; ++i) {
						if ((int)num[i] < 48 || (int)num[i]>57 || num[16] != '\0') {
							if (i = 15 && num[15] == '\0') {
								break;
							}
							else {
								input = '1';
								break;
							}
						}
					}
					if (input != '0' && input != 'N')
						strcpy(num, "NULL");
				} while (input != '0' && input != 'N');
				if (input == '0') {
					strcpy(num, "NULL");
					return -1;
				}
				printf("\t\t%-13s : \n", "Month/Year");
				do {
				printf("\t\t\t%-15s : ", "Month");
					if (strcmp(month, "NO") == 0) {
						rewind(stdin);
						scanf("%2s", month);
					}
					else
						printf("%s\n", month);
					loop = 0;
					bigLoop = 0;
					if (month[0] == '0') {
						if ((int)month[1] < 49 || (int)month[1] > 57) {
							loop = 1;
							if (month[1] == '\0') {
								strcpy(num, "NULL");
								strcpy(month, "NO");
								bigLoop = 1;
								break;
							}
						}
					}
					else if (month[0] == '1') {
						if ((int)month[1] < 48 || (int)month[1] > 50) {
							strcpy(month, "NO");
							loop = 1;
						}
					}
					else {
						strcpy(month, "NO");
						loop = 1;
					}
				} while (loop == 1);
			} while (bigLoop == 1);
			do {
				printf("\t\t\t%-15s : ", "Year (2 digits)");
				rewind(stdin);
				scanf("%2s", year);
				loop = 0;
				bigLoop = 0;
				for (int i = 0; i < 2; ++i) {
					if ((int)year[i] < 48 || (int)year[i]>57)
						loop = 1;
					else if (strcmp(year, "0") == 0) {
						bigLoop = 2;
						strcpy(month, "NO");
						break;
					}
				}
			} while (loop == 1);
		} while (bigLoop == 2);
		printf("\t\t%-13s : %s/%s\n", "Month/Year", month, year);
		do {
			printf("\t\t%-13s : ", "CVV/CVV2");
			rewind(stdin);
			scanf("%3s", cvv);
			loop = 0;
			bigLoop = 0;
			for (int i = 0; i < 3; ++i) {
				if (strcmp(cvv, "0") == 0) {
					bigLoop = 3;
					break;
				}
				else if ((int)cvv[i] < 49 || (int)month[i] > 57) {
					loop = 1;
					break;
				}
			}
		} while (loop == 1);
	}while (bigLoop == 3);
	do {
		title();
		printf("%51s : RM%6.02f\n\n", "Total Price should payment", *price);
		printf("%51s : %s\n", "Card Holder", name);
		printf("%51s : ", "Card Number");
		int i;
		for (i = 17; num[i] != '\0'; --i);
		for (int j = 0; j < i; ++j) {
			if (j < i - 4) {
				printf("X");
			}
			else {
				printf("%c", num[j]);
			}
		}
		printf("\n");
		printf("%51s : %s\n", "Card Issuer", issuer);
		printf("\n");
		printf("Do you want to make payment with this card ?\n");
		printf("\t1. Yes, make payment with this card. (-RM%6.02f)\n\t0. No, Return to main page\n\n", *price);
		printf("Enter the number : ");
		rewind(stdin);
		scanf("%c", &input);
		switch (input) {
		case '1':
			for (int j = 3; j >= 0; --j) {
				title();
				printf("Amount of RM%6.02f has been deducted from the card ", *price);
				int i;
				for (i = 17; num[i] != '\0'; --i);
				for (int j = 0; j < i; ++j) {
					if (j < i - 4) {
						printf("X");
					}
					else {
						printf("%c", num[j]);
					}
				}
				printf("\n\nYou will be redirected to the payment status in %d second(s)", j);
				Sleep(1000);
			}
			return 1;
			break;
		case '0':
			return 0;
			break;
		}
	} while (input != '1' && input != '0');
}

int bank(float* price) {
	title();
	char input;
	struct{
		char name[27];
	}bank[33] = {"AFFIN BANK", 
			"AFFIN ISLAMIC", 
			"ARGO BANK", 
			"ALLIANCE BANK", 
			"ALLIANCE ISLAMIC BANK", 
			"AMBANK", 
			"AMBANK ISLAMIC", 
			"BANK ISLAM", 
			"BANK OF CHINA", 
			"BANK MUAMALAT", 
			"BANK RAKYAT", 
			"BSN", 
			"BNP PARIBAS", 
			"CIMB BANK", 
			"CIMB ISLAMIC", 
			"CITIBANK", 
			"DEUTCHE BANK", 
			"HONG LEONG BANK", 
			"HONG LEONG ISLAMIC BANK", 
			"HSBC", 
			"HSBC AMANAH", 
			"KUWAIT FINANCE HOUSE", 
			"MAYBANK", 
			"MAYBANK ISLAMIC", 
			"OCBC", 
			"OCBC AL-AMIN", 
			"PUBLIC BANK", 
			"PUBLIC ISLAMIC BANK",
			"RHB BANK", 
			"RHB ISLAMIC BANK", 
			"STANDARD CHARTERED", 
			"STANDARD CHARTERED SAADIQ", 
			"UOB" };
printf("%51s : RM%6.02f\n\n", "Total Price should payment", *price);
	for (int i = 0; i < 33; ++i) {
		printf("%d. %s\n", i, bank[i]);
	}
	printf("Enter the number : ");
	rewind(stdin);
	scanf("%c", &input);
}

addBooking() {
	title();
	printf("Schedules: \n"); //Integerate with schedule module
}