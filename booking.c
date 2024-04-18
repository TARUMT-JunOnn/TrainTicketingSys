#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<windows.h>
#include<conio.h>
#include<ctype.h>
#pragma warning(disable:4996)
#define MAX_PAX 10
#define MAX_TRIP 2
#define MAX_RECORDS 5000

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

struct {
	char refNum[10];
	char ID[20];
	char date[11];
	int amount;
	Info trainInfo;
}records[MAX_RECORDS];

//Global Variable

//Function Declaration
int addBooking(Info(*userChoice)[MAX_TRIP][MAX_PAX],const int);
int bookingHistory();
int searchBooking();
void modifyBooking();
int allBooking();
void cancelBooking();
void produceList();
void createDate(int,int,int, char (*date)[MAX_TRIP][11], int);
void calcPax(Info (*userChoice)[MAX_TRIP][MAX_PAX], int (*pax)[2]);
float calcFare(Info (*userChoice)[MAX_TRIP][MAX_PAX], char (*)[MAX_TRIP][11], int (*pax)[2], int);
float calcTax(int, float);
char userAction();
void editPax(Info(*userChoice)[MAX_TRIP][MAX_PAX], char(*)[MAX_TRIP][11], int(*pax)[2]);
int payment(float*, Info(*userChoice)[MAX_TRIP][MAX_PAX], char(*)[MAX_TRIP][11], int(*pax)[2], char (*)[9]);
int card(float*, char *name[20]);
int bank(float*);
int eWallet(float*, char* name[20]);
void showBooking(Info(*userChoice)[MAX_TRIP][MAX_PAX], char(*)[MAX_TRIP][11], int(*pax)[2], float, char (*name)[20], char (*)[9], const int);
int bookingbyDate(char*);
int bookingbyString(char*, char);
int bookingbyTime(char*, int);

//Reset all userChoice
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

//Same with all module
void title(void) {
	system("cls");
	printf("%10s %s %s", "Train", "Ticketing", "System");
	SYSTEMTIME t;
	GetLocalTime(&t);
	const char day[7][10] = { {"Sunday"} , {"Monday"} ,{"Tuesday"} ,{"Wednesday"} ,{"Thursday"} ,{"Friday"} ,{"Saturday"}};
	const char month[12][10] = { {"January"}, {"February"}, {"March"}, {"April"}, {"May"}, {"June"}, {"July"}, {"August"}, {"September"}, {"October"}, {"November"}, {"December"}};
	printf("%104s %02d %s %d %02d:%02d:%02d", day[t.wDayOfWeek], t.wDay, month[t.wMonth - 1], t.wYear, t.wHour, t.wMinute, t.wSecond);
	printf("\n");
	for (int i = 0; i < 155; i++) {
		printf("%s", "-");
	}
	printf("\n\n");
}

int readfile(FILE** fptr) {
	int i = 0;
	while (fscanf(fptr, "%[^|]|", records[i].refNum) != EOF) {
		fscanf(fptr, "%[^|]|", records[i].ID);
		fscanf(fptr, "%[^|]|", records[i].date);
		fscanf(fptr, "%[^|]|", records[i].trainInfo.trainId);
		fscanf(fptr, "%d|", &records[i].amount);
		fscanf(fptr, "%f|", &records[i].trainInfo.prefer.time.depart);
		fscanf(fptr, "%f|", &records[i].trainInfo.prefer.time.arrive);
		fscanf(fptr, "%[^|]|", records[i].trainInfo.departFrom);
		fscanf(fptr, "%[^\n]\n", records[i].trainInfo.destination);
		++i;
	}
	return i;
}

int writefile(FILE** fptr) {
	int i = 0;
	while (strcmp(records[i].date, "") != 0) {
		fprintf(fptr, "%s|%s|%s|%s|%d|%.02f|%.02f|%s|%s\n", records[i].refNum, records[i].ID, records[i].date, records[i].trainInfo.trainId, records[i].amount, records[i].trainInfo.prefer.time.depart, records[i].trainInfo.prefer.time.arrive, records[i].trainInfo.departFrom, records[i].trainInfo.destination);
		++i;
	}
}

//Main Function
int main(void) {
	Info userChoice[MAX_TRIP][MAX_PAX];
	char input;
	int statAdd;
	FILE* fptr;
	fptr = fopen("../TrainTicketingSys/res/booking.txt", "r");
	const int recordQty = readfile(fptr);
	fclose(fptr);
	reset(userChoice);
	do{
	title(NULL);
	printf("What action you would like to perform ?\n");
	printf("\t1. Add booking\n\t2. Booking History\n\t3. Modify Booking\n\t4. Cancel booking\n\t5. Produce List\n\n");
		printf("Enter the number : ");
		rewind(stdin);
		scanf("%c", &input);
		switch (input) {
		case '1':
			statAdd = addBooking(userChoice, recordQty);
			break;
		case '2':
			input = bookingHistory("Wong");
			break;
		case '3':
			//modifyBooking();
			break;
		case '4':
			//allBooking();
			break;
		case '5':
			//cancelBooking();
			break;
		case '6':
			//produceList();
			break;
		}
	} while (!(input == '1' || input == '2' || input == '3' || input == '4' || input == '5' || input == '6'));
	fptr = fopen("../TrainTicketingSys/res/booking.txt", "w");
	writefile(fptr);
	fclose(fptr);
}

int addBooking(Info (*userChoice)[MAX_TRIP][MAX_PAX], const int recordQty) {
	char memName[20];
	char memID[20];
	strcpy(memID, "Wong");
	strcpy(memName, "Marco");
	char dateAdd[MAX_TRIP][11], action = '2', paymentTime[9], input;
	int pax[2] = {0, 0}, status = 0, j;
	float fare;
	(*userChoice)[0][0] = (Info){ "T1001", "KL Sentral",  "Kampar", 50, { 5, 4, 2024,{ 9, 13} } };
	(*userChoice)[1][0] = (Info){ "T1004", "Kampar", "KL Sentral", 25, { 6, 4, 2024,{ 5, 8} } };
	do{
		do {
			for (int j = 0; j < MAX_TRIP; ++j) {
				for (int i = 0; i < MAX_PAX; ++i) {
					if ((*userChoice)[j][i].prefer.day != NULL && (*userChoice)[j][i].prefer.month != NULL && (*userChoice)[j][i].prefer.year != NULL) 
						createDate((*userChoice)[j][i].prefer.day, (*userChoice)[j][i].prefer.month, (*userChoice)[j][i].prefer.year, dateAdd, j);
				}
			}
			if (action == '2') {
				j = 0;
				editPax(*userChoice, dateAdd, pax);
				calcPax(*userChoice, pax);
				for (int i = 0; i < 2 ; ++i) {
					if (pax[i] == 0) {
						++j;
					}
				}
				if (j == 2) {
					return 1;
				}
			}
			do {
				fare = calcFare(*userChoice, dateAdd, pax, status);
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
				fare = calcFare(*userChoice, dateAdd, pax, status);
				status = payment(&fare, *userChoice, dateAdd, pax, paymentTime, memName, memID);
				break;
			case '0':
				return 0;
		}
		if (status == 1) {
			do {
				showBooking(*userChoice, dateAdd, pax, fare, memName, paymentTime, recordQty, memID);
				printf("Press 1 for exit");
				scanf("%c", &input);
			} while (input != '1');
		}
	} while (status != 1);
	return 0;
}

void createDate(int day, int month, int year, char(*date)[MAX_TRIP][11], int j) {
	char takeDay[2][3];
	char takeYear[5];
		itoa(day, takeDay[0], 10);
		itoa(month, takeDay[1], 10);
		itoa(year, takeYear, 10);
		strcpy((*date)[j], takeDay[0]);
		if (day >= 1 && day <= 9) {
			(*date)[j][0] = '0';
			strcat((*date)[j], takeDay[0]);
		}
		strcat((*date)[j], "/");
		strcat((*date)[j], takeDay[1]);
		if (month >= 1 && month <= 9) {
			(*date)[j][3] = '0';
			strcat((*date)[j], takeDay[1]);
		}
		strcat((*date)[j], "/");
		strcat((*date)[j], takeYear);
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

float calcFare(Info (*userChoice)[MAX_TRIP][MAX_PAX], char (*date)[MAX_TRIP][11], int (*pax)[2], int status) {
	float totalPrice[10], sumPrice = 0, adj = 0, tax = 0,  negative;
	int sumPriceint;
	//print price list
	title(NULL);
	for (int i = 0; i < 115; i++) {
		printf("-");
	}
	printf("\n");
	printf("%-11s\t %-5s\t %-5s\t %-5s\t \%-10s\t %-10s\t %-2s\t %-13s\t %-10s\n", "Date", "From", "To", "TrainID", "Departure", "Destination", "Pax", "Price per Pax", "Net Price");
	for (int i = 0; i < 115; i++) {
		printf("-");
	}
	printf("\n");
	for (int i = 0; i < MAX_TRIP; ++i) {
		if ((*pax)[i] != 0 && (*date)[i][2] == '/') {
			totalPrice[0] = (*userChoice)[i][0].price * (float)(*pax)[i];
			printf("%s\t %.2f\t %.2f\t %-7s\t %-15s %-15s %d\t RM %-10.02f\t RM %.02f\n", (*date)[i], (*userChoice)[i][0].prefer.time.depart, (*userChoice)[i][0].prefer.time.arrive, (*userChoice)[i][0].trainId, (*userChoice)[i][0].departFrom, (*userChoice)[i][0].destination, (*pax)[i], (*userChoice)[i][0].price, totalPrice[0]);
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

void editPax(Info(*userChoice)[MAX_TRIP][MAX_PAX], char(*date)[MAX_TRIP][11], int(*pax)[2]) {
	char paxInC[3];
	int paxInD = 0, j = 0;
	do{
		title(NULL);
		for (int i = 0; i < 92; i++) {
			printf("-");
		}
		printf("\n");
		printf("%-11s\t %-5s\t %-5s\t %-5s\t \%-10s\t %-10s\t %-2s\n", "Date", "From", "To", "TrainID", "Departure", "Destination", "Pax (1-10)");
		for (int i = 0; i < 92; i++) {
			printf("-");
		}
		printf("\n");
		while (j < MAX_TRIP) {
			if ((*date)[j][2] == '/') {
				printf("%s\t %.2f\t %.2f\t %-7s\t %-15s %-15s ", (*date)[j], (*userChoice)[j][0].prefer.time.depart, (*userChoice)[j][0].prefer.time.arrive, (*userChoice)[j][0].trainId, (*userChoice)[j][0].departFrom, (*userChoice)[j][0].destination);
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
							(*date)[j][l] = '\0';
						}
					}
				}
			}
			++j;
		}
	} while (paxInD < 0 || paxInD > 10 );
}

int payment(float* price, Info(*userChoice)[MAX_TRIP][MAX_PAX], char(*date)[MAX_TRIP][11], int(*pax)[2], char(*time)[9], char memName[20], char memID[20]) {
	int mem_point;
	mem_point = 10000;
	char input;
	int status = 0;
	float redeem, temporary = *price;
	printf("Member Name : %s\tRemaining Member Points : %d pts\n", memID, mem_point);
	do {
		if (mem_point > 0) {
			printf("You can redeem up to %d pts points as cashback !\n", mem_point);
			if ((float)mem_point / 100 < *price)
				redeem = (float)mem_point / 100;
			else
				redeem = *price;
			printf("Would you like to redeem? \n\n\t1. Yes(-%d pts)\n\t2. No\n\t0. Return\n\n", (int)(redeem*100));
			printf("Enter the number : ");
			rewind(stdin);
			scanf("%c", &input);
		}
		switch (input) {
		case '1':
			mem_point -= (int)(redeem * 100);
			temporary -= redeem;
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
		printf("%102s : RM%6.02f\n", "Total Price should payment", temporary);
	}
	if (temporary != 0) {
		printf("Payments method :\n\t1. Credit/Debit Card\n\t2. Online Banking\n\t3. E-Wallet\n\t0. Cancel Payment (Return)\n\n");
		printf("Enter the number : ");
		rewind(stdin);
		scanf("%c", &input);
	}
	else {
		printf("Would you like to proceed to payment ? (RM 0.00)\n\t1. Yes\n\t0. No, Return\n\n");
		printf("Enter the number : ");
		rewind(stdin);
		scanf("%c", &input);
		switch (input) {
		case '1':
			input = '9';
			status = 1;
			break;
		}
	}
	switch (input) {
	case '1':
		status = card(&temporary, memName);
		break;
	case '2':
		status = bank(&temporary);
		break;
	case '3':
		status = eWallet(&temporary, memName);
		break;
	case '0':
		return 0;
		break;
	case '9':
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
			char month[20], day[20];
			SYSTEMTIME t;
			GetLocalTime(&t);
			itoa(t.wYear, (*time), 10);
			for (int i = 0; i < 3; ++i) {
				(*time)[i] = (*time)[i + 2];
			}
			itoa(t.wMonth, month, 10);
			itoa(t.wDay, day, 10);
			if (t.wMonth >= 1 && t.wMonth <= 9) 
				strcat((*time), "0");
			strcat((*time), month);
			if (t.wDay >= 1 && t.wDay <= 9)
				strcat((*time), "0");
			strcat((*time), day);
			*price = temporary;
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
				printf("\n\nYou will be redirected to the merchant page in %d second(s)", j);
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
	char input[3], name[50], pin[100], input1;
	int num;
	struct {
		char name[27];
	}bank[33] = { "AFFIN BANK",
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
	do {
		do {
			do {
				title();
				printf("%29s : RM%6.02f\n\n", "Total Price should payment", *price);
				printf("Type 0 to return\n");
				printf("Please choose the bank you prefered :\n\n");
				printf("Page (1/2)\n");
				for (int i = 0; i < 17; ++i) {
					printf("%d. %s\n", i + 1, bank[i].name);
				}
				printf(".\n.\n.\n");
				printf("Enter the number (Press Enter for next page) : ");
				rewind(stdin);
				if ((int)input[0] < 48 || (int)input[0] >57 || (int)input[1] < 48 && input[1] != '\0' || (int)input[1] >57) {
					if (scanf("%[^\n]", input) == 0) {
						title();
						printf("%29s : RM%6.02f\n\n", "Total Price should payment", *price);
						printf("Please choose the bank you prefered :\n\n");
						printf("Page (2/2)\n");
						for (int i = 17; i < 33; ++i) {
							printf("%d. %s\n", i + 1, bank[i].name);
						}
						printf("Enter the number (Press Enter for previous page) : ");
						rewind(stdin);
						if (scanf("%[^\n]", input) == 0) {
							input[1] = 'A';
						}
					}
					else if (input[0] == '3' && (int)input[1] > 51) {
						input[1] == 'A';
					}
					else if (strcmp(input, "0") == 0) {
						return -1;
					}
				}
			} while ((int)input[0] < 48 || (int)input[0] >57 || (int)input[1] < 48 && input[1] != '\0' || (int)input[1] >57);
			num = atoi(input) - 1;
			title();
			printf("%s\n\n", bank[num].name);
			printf("Type 0 to return\n");
			printf("Type your username : ");
			rewind(stdin);
			scanf("%s", name);
			if (strcmp(name, "0") == 0)
				input[1] = 'A';
		} while (strcmp(name, "0") == 0);
		printf("Type your password : ");
		int j = 0;
		do {
			++j;
			pin[j] = getch();
		} while (pin[j] != '\r');
	} while (pin[1] == '0' && pin[2] == '\r');
	title();
	printf("%29s : RM%6.02f\n\n", "Total Price should payment", *price);
	printf("%s\n", bank[num].name);
	srand(time(NULL));
	printf("Username : %s\n", name);
	int acc = rand() % (9999999999 - 1000000000 + 1) + 1000000000;
	printf("Account Number : %d\n", acc);
	float balance = ((100000 - 1000) * ((float)rand() / RAND_MAX)) + 1000;
	printf("Remaining Balance : RM%.02f\n\n", balance);
	printf("Do you want to make payment with this account number ?\n");
	printf("\t1. Yes, make payment with this account number. (-RM%6.02f)\n\t0. No, Return to main page\n\n", *price);
	printf("Enter the number : ");
	rewind(stdin);
	scanf("%c", &input1);
	switch (input1) {
	case '1':
		for (int j = 3; j >= 0; --j) {
			title();
			printf("Amount of RM%6.02f has been deducted from the account ", *price);
			int i;
			printf("\n\nYou will be redirected to the merchant page in %d second(s)", j);
			Sleep(1000);
		}
		return 1;
		break;
	case '0':
		return 0;
		break;
	}
}

int eWallet(float *price, char* name[20]) {
	char phone[15], pin[6];
	char input;
	int loop = 0, i;
	do {
		do {
			title(NULL);
			loop = 0;
			printf("Touch N Go E Wallet\n");
			printf("Type 0 to return\n\n");
			printf("Enter your phone number : +60 ");
			rewind(stdin);
			scanf("%s", phone);
			if (strcmp(phone, "0") == 0)
				return -1;
		} while (strlen(phone) < 9 || strlen(phone) > 11);
		printf("Type your 6 Number PIN : ");
		for (i = 0; i < 6; ++i) {
			pin[i] = getch();
			if ((int)pin[i] >= 48 && (int)pin[i] <= 57) 
				printf("%c", 250);
			else if (pin[1] == '\r' && pin[0] == '0') {
				loop = 1;
				break;
			}
			else {
				--i;
			}
		}
	} while (loop == 1);
	do{
		title();
		printf("Touch N Go E Wallet\n\n");
		printf("Account username : %s\n", name);
		printf("%29s : RM%6.02f\n\n", "Total Price should payment", *price);
		printf("Do you want to pay ?\n");
		printf("\t1. Yes, make payment with this e-Wallet account. (-RM%6.02f)\n\t0. No, Return to main page\n\n", *price);
		printf("Enter the number : ");
		rewind(stdin);
		scanf("%c", &input);
		switch (input) {
		case '1':
			for (int j = 3; j >= 0; --j) {
				title();
				printf("Amount of RM%6.02f has been deducted from the TnG E-Wallet account ", *price);
				printf("\n\nYou will be redirected to the merchant page in %d second(s)", j);
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

void showBooking(Info(*userChoice)[MAX_TRIP][MAX_PAX], char(*date)[MAX_TRIP][11], int(*pax)[2], float fare, char (*name)[20], char (*paymentTime)[10], const int recordQty, char ID[20]) {
	char random[20];
	int i;
	srand(time(NULL));
	char refNum[10];
	static int j = 0;
	strcpy(refNum, (*paymentTime));
	itoa(rand() % (999 - 100 + 1) + 100, random, 10);
	strcat(refNum, random);
	title();
	printf("Reference Number : %s\n", refNum);
	printf("Name : %s\n\n", *name);
	printf("Booking Details :\n\n");
	for (i = 0; i < MAX_TRIP && strcmp((*date)[i], "NULL") != 0; ++i) {
		if (strcmp((*date)[0], "") != 0 && strcmp((*date)[1], "") != 0) {
			switch (i) {
			case 0:
				printf("Departure\n");
				printf("------------\n");
				break;
			case 1:
				printf("Return\n");
				printf("--------\n");
				break;
			}
		}
		if (strcmp((*date)[i], "") != 0) {
			printf("Date : %s\n", (*date)[i]);
			printf("Train ID : %s\n", (*userChoice)[i][0].trainId);
			printf("Pax : %d\n", (*pax)[i]);
			printf("Time : %.02f - %.02f\n", (*userChoice)[i][0].prefer.time.depart, (*userChoice)[i][0].prefer.time.arrive);
			printf("Departure : %s\n", (*userChoice)[i][0].departFrom);
			printf("Destination : %s\n", (*userChoice)[i][0].destination);
			printf("\n\n");
			strcpy(records[recordQty + i + j].refNum, refNum);
			strcpy(records[recordQty + i + j].ID, ID);
			strcpy(records[recordQty + i + j].date, (*date)[i]);
			strcpy(records[recordQty + i + j].trainInfo.trainId, (*userChoice)[i][0].trainId);
			records[recordQty + i + j].amount = (*pax)[i];
			records[recordQty + i + j].trainInfo.prefer.time.depart = (*userChoice)[i][0].prefer.time.depart;
			records[recordQty + i + j].trainInfo.prefer.time.arrive = (*userChoice)[i][0].prefer.time.arrive;
			strcpy(records[recordQty + i + j].trainInfo.departFrom, (*userChoice)[i][0].departFrom);
			strcpy(records[recordQty + i + j].trainInfo.destination, (*userChoice)[i][0].destination);
		}
	}
	j = i + 1 + recordQty;
}

int bookingHistory(char id[20]) {
	char input;
	int loop;
	do{
		title();
		printf("Booking history :\n\n");
		int recordsNum = allBooking(id);
		printf("< %d records found >\n", recordsNum);
		if (recordsNum == 0) {
			title();
			printf("No records found.\n");
			printf("Press any key to return.\n");
			rewind(stdin);
			getch();
			return 1;
		}
		else {
			do {
				printf("What action you would like to perform ?\n");
				printf("\t1. Search particular booking\n\t0. Return\n\n");
				printf("Enter the number : ");
				rewind(stdin);
				scanf("%c", &input);
			} while (input != '1' && input != '0');
			switch (input) {
			case '1':
				loop = searchBooking(id);
				break;
			case '0':
				return 1;
				break;
			}
		}
	} while (loop == 0);
	return 1;
}

int allBooking(char id[20]) {
	int j = 0;
	for (int i = 0; i < 115; i++) {
		printf("-");
	}
	printf("\n");
	printf("%-13s\t %-11s\t %-5s\t %-5s\t %-5s\t \%-10s\t %-10s\t %-2s\n","Reference No", "Date", "From", "To", "TrainID", "Departure", "Destination", "Pax");
	for (int i = 0; i < 115; i++) {
		printf("-");
	}
	printf("\n");
	for (int i = 0; strcmp(records[i].date, "") != 0; ++i) {
		if (strcmp(records[i].ID, id) == 0) {
			printf("%-13s\t %s\t %.2f\t %.2f\t %-7s\t %-15s %-15s %d\n", records[i].refNum, records[i].date, records[i].trainInfo.prefer.time.depart, records[i].trainInfo.prefer.time.arrive, records[i].trainInfo.trainId, records[i].trainInfo.departFrom, records[i].trainInfo.destination, records[i].amount);
			++j;
		}
	}
	for (int i = 0; i < 115; i++) {
		printf("-");
	}
	printf("\n");
	return j;
}

int searchBooking(char id[20]) {
	char input;
	int check = 1;
	do {
		title();
		printf("What action you would like to perform ?\n");
		printf("Search by :\n");
		printf("\t1. Date\n\t2. Train ID\n\t3. Time\n\t4. Destination\n\t5. Departure\n\t0. Return\n\n");
		printf("Enter the number : ");
		rewind(stdin);
		scanf("%c", &input);
		switch (input) {
		case '1':
			bookingbyDate(id);
			break;
		case '2':
		case '4':
		case '5':
			bookingbyString(id, input);
			break;
		case '3':
			do {
				do {
					title();
					printf("What action you would like to perform ?\n");
					printf("\t1. Search by Departure Time\n\t2. Search by Arrival Time\n\t3. Search by Departure and Arrival Time\n\t0. Return\n\n");
					printf("Enter the number : ");
					rewind(stdin);
					scanf("%c", &input);
				} while (input != '1' && input != '2' && input != '3' && input != '0');
				if (input == '0')
					input = '1';
				else
					check = bookingbyTime(id, input);
			} while (check == 0 && input != '1');
		}
	} while (input != '0');
	return 0;
}

int bookingbyDate(char id[20]) {
	char input[5], date[1][11];
	int day, month, year;
	int j = 0, loop = 0;
	do {
		do {
			do {
				j = 0;
				title();
				printf("Press 0 for return.\n\n");
				do {
					if (loop == 2)
						printf("Type the year : %d\n", year);
					else {
						printf("Type the year : ");
						rewind(stdin);
						scanf("%s", input);
						year = atoi(input);
						if ((year < 2000 || year > 2099) && strcmp(input, "0") != 0)
							printf("Error, please try again.\n");
						else if (strcmp(input, "0") == 0)
							return 0;
					}
				} while (year == 0 || year < 2000 || year > 2099);
				do {
					loop = 0;
					printf("Type the month : ");
					rewind(stdin);
					scanf("%s", input);
					month = atoi(input);
					if ((month < 1 || month >12) && strcmp(input, "0") != 0)
						printf("Error, please try again.\n");
				} while ((month < 1 || month >12) && strcmp(input, "0") != 0);
				if (strcmp(input, "0") == 0)
					loop = 1;
			} while (loop == 1);
			do {
				printf("Type the day : ");
				rewind(stdin);
				scanf("%s", input);
				day = atoi(input);
				if (month % 2 != 0 || month == 8) {
					if ((day <= 0 || day > 31) && strcmp(input, "0") != 0)
						day = 0;
				}
				else {
					if ((day <= 0 || day > 31) && strcmp(input, "0") != 0)
						day = 0;
				}
			} while (day == 0 && strcmp(input, "0") != 0);
			if (strcmp(input, "0") == 0)
				loop = 2;
		} while (loop == 2);
		createDate(day, month, year, date, 0);
		for (int i = 0; i < 115; i++) {
			printf("-");
		}
		printf("\n");
		printf("%-13s\t %-11s\t %-5s\t %-5s\t %-5s\t \%-10s\t %-10s\t %-2s\n", "Reference No", "Date", "From", "To", "TrainID", "Departure", "Destination", "Pax");
		for (int i = 0; i < 115; i++) {
			printf("-");
		}
		printf("\n");
		for (int i = 0; i < MAX_RECORDS; ++i) {
			if (strcmp(records[i].date, date) == 0 && strcmp(records[i].ID, id) == 0) {
				printf("%-13s\t %s\t %.2f\t %.2f\t %-7s\t %-15s %-15s %d\n", records[i].refNum, records[i].date, records[i].trainInfo.prefer.time.depart, records[i].trainInfo.prefer.time.arrive, records[i].trainInfo.trainId, records[i].trainInfo.departFrom, records[i].trainInfo.destination, records[i].amount);
				++j;
			}
		}
		for (int i = 0; i < 115; i++) {
			printf("-");
		}
		printf("\n");
		if (j == 0) {
			title();
			printf("No records found.\n");
		}
		printf("Press any key to continue .......\n");
		rewind(stdin);
		getch();
	} while (strcmp(input, "0") != 0);
}

int bookingbyString(char id[20], char prmt) {
	char input[3][50];
	int j = 0;
	strcpy(input[0], "NULL");
	strcpy(input[1], "NULL");
	strcpy(input[2], "NULL");
	title();
	do {
		j = 0;
		switch (prmt) {
		case '2':
			printf("Press 0 for return.\n\n");
			printf("Type the ID : ");
			rewind(stdin);
			scanf("%s", input[0]);
			break;
		case '4':
			printf("What destination you would like to search ?\n");
			printf("\t1. KL Sentral\n\t2. Kampar\n\t0. Return\n\n");
			printf("Enter the number : ");
			rewind(stdin);
			scanf("%c", &input[1][0]);
			switch (input[1][0]) {
			case '1':
				strcpy(input[1], "KL Sentral");
				break;
			case '2':
				strcpy(input[1], "Kampar");
				break;
			case '0':
				return 1;
				break;
			}
			break;
		case '5':
			printf("What departure you would like to search ?\n");
			printf("\t1. KL Sentral\n\t2. Kampar\n\t0. Return\n\n");
			printf("Enter the number : ");
			rewind(stdin);
			scanf("%c", &input[2][0]);
			switch (input[2][0]) {
			case '1':
				strcpy(input[2], "KL Sentral");
				break;
			case '2':
				strcpy(input[2], "Kampar");
				break;
			case '0':
				return 1;
				break;
			}
		}
		for (int i = 0; i < 115; i++) {
			printf("-");
		}
		printf("\n");
		printf("%-13s\t %-11s\t %-5s\t %-5s\t %-5s\t \%-10s\t %-10s\t %-2s\n", "Reference No", "Date", "From", "To", "TrainID", "Departure", "Destination", "Pax");
		for (int i = 0; i < 115; i++) {
			printf("-");
		}
		printf("\n");
		for (int i = 0; i < MAX_RECORDS; ++i) {
			if ((stricmp(records[i].trainInfo.trainId, input[0]) == 0 || stricmp(records[i].trainInfo.departFrom, input[2]) == 0 || stricmp(records[i].trainInfo.destination, input[1]) == 0) && strcmp(records[i].ID, id) == 0) {
				printf("%-13s\t %s\t %.2f\t %.2f\t %-7s\t %-15s %-15s %d\n", records[i].refNum, records[i].date, records[i].trainInfo.prefer.time.depart, records[i].trainInfo.prefer.time.arrive, records[i].trainInfo.trainId, records[i].trainInfo.departFrom, records[i].trainInfo.destination, records[i].amount);
				++j;
			}
		}
		for (int i = 0; i < 115; i++) {
			printf("-");
		}
		printf("\n");
		if (j == 0) {
			title();
			printf("No records found.\n");
			printf("Press any key to return.\n");
			rewind(stdin);
			getch();
			return 1;
		}
	} while (strcmp(input[0], "0") != 0 && strcmp(input[1], "0") != 0 && strcmp(input[2], "0") != 0);
}

int bookingbyTime(char id[20], char prmt) {
	char input[3];
	float time[2][2] = { {0,0} ,{0,0} };
	int ampm[2] = {0, 0};
	int loop = 0;
	int j = 0;
	switch (prmt) {
	case '1':
		do {
			do {
				do {
					j = 0;
					title();
					printf("Press 0 for return.\n\n");
					if (loop == 1) {
						strcpy(input, "1");
						if (time[0][0] > 12)
							time[0][0] -= 12;
						else if (time[0][0] == 0)
							time[0][0] += 12;
						printf("Type the Departure Time (in hours) (1 - 12) : %d\n", (int)time[0][0]);
					}
					else {
						printf("Type the Departure Time (in hours) (1 - 12) : ");
						rewind(stdin);
						scanf("%s", input);
						time[0][0] = atoi(input);
					}
				} while ((time[0][0] < 1 || time[0][0] > 12) && strcmp(input, "0") != 0);
				if (strcmp(input, "0") == 0)
					return 0;
				do {
					loop = 0;
					printf("\t1. in a.m.\n\t2. in p.m.\n\n");
					printf("Enter the number : ");
					rewind(stdin);
					scanf("%s", input);
				} while (strcmp(input, "1") != 0 && strcmp(input, "2") != 0 && strcmp(input, "0") != 0);
			} while (strcmp(input, "0") == 0);
			if (strcmp(input, "2") == 0 && time[0][0] != 12) {
				time[0][0] += 12;
			}
			else if (strcmp(input, "1") == 0 && time[0][0] == 12) {
				time[0][0] -= 12;
			}
			do {
				printf("Type the Departure Time (in minutes) (00 - 59): ");
				rewind(stdin);
				scanf("%s", input);
				time[0][1] = atoi(input);
			} while ((time[0][1] < 0 || time[0][1] > 59) && strcmp(input, "0") != 0);
			if (strcmp(input, "0") == 0)
				loop = 1;
		} while (strcmp(input, "0") == 0);
		time[0][0] += time[0][1] / 100;
		for (int i = 0; i < 115; i++) {
			printf("-");
		}
		printf("\n");
		printf("%-13s\t %-11s\t %-5s\t %-5s\t %-5s\t \%-10s\t %-10s\t %-2s\n", "Reference No", "Date", "From", "To", "TrainID", "Departure", "Destination", "Pax");
		for (int i = 0; i < 115; i++) {
			printf("-");
		}
		printf("\n");
		for (int i = 0; i < MAX_RECORDS; ++i) {
			if (records[i].trainInfo.prefer.time.depart == time[0][0] && strcmp(records[i].ID, id) == 0) {
				printf("%-13s\t %s\t %.2f\t %.2f\t %-7s\t %-15s %-15s %d\n", records[i].refNum, records[i].date, records[i].trainInfo.prefer.time.depart, records[i].trainInfo.prefer.time.arrive, records[i].trainInfo.trainId, records[i].trainInfo.departFrom, records[i].trainInfo.destination, records[i].amount);
				++j;
			}
		}
		for (int i = 0; i < 115; i++) {
			printf("-");
		}
		printf("\n");
		if (j == 0) {
			title();
			printf("No records found.\n");
		}
		printf("Press any key to return.\n");
		rewind(stdin);
		getch();
		break;
	case '2':
		do {
			do {
				do {
					j = 0;
					title();
					printf("Press 0 for return.\n\n");
					if (loop == 1) {
						strcpy(input, "1");
						if (time[1][0] > 12)
							time[1][0] -= 12;
						else if (time == 0)
							time[1][0] += 12;
						printf("Arrival Time (in hours) (0 - 24) : %d", (int)time[1][0]);
					}
					else {
						printf("Type the Arrival Time (in hours) (1 - 12) : ");
						rewind(stdin);
						scanf("%s", input);
						time[1][0] = atoi(input);
					}
				} while ((time[1][0] < 1 || time[1][0] > 12) && strcmp(input, "0") != 0);
				if (strcmp(input, "0") == 0)
					return 0;
				do {
					loop = 0;
					printf("\t1. in a.m.\n\t2. in p.m.\n\n");
					printf("Enter the number : ");
					rewind(stdin);
					scanf("%s", &input);
				} while (strcmp(input, "1") != 0 && strcmp(input, "2") != 0 && strcmp(input, "0") != 0);
			} while (strcmp(input, "0") == 0);
			if (strcmp(input, "2") == 0 && time[1][0] != 12)
				time[1][0] += 12;
			else if (strcmp(input, "1") == 0 && time[1][0] == 12)
				time[1][0] -= 12;
			do {
				printf("Type the Arrival Time (in minutes) (00 - 59): ");
				rewind(stdin);
				scanf("%s", input);
				time[1][1] = atoi(input);
			} while ((time[1][1] < 0 || time[1][1] > 59) && strcmp(input, "0") != 0);
			if (strcmp(input, "0") == 0)
				loop = 1;
		} while (strcmp(input, "0") == 0);
		time[1][0] += time[1][1] / 100;
		for (int i = 0; i < 115; i++) {
			printf("-");
		}
		printf("\n");
		printf("%-13s\t %-11s\t %-5s\t %-5s\t %-5s\t \%-10s\t %-10s\t %-2s\n", "Reference No", "Date", "From", "To", "TrainID", "Departure", "Destination", "Pax");
		for (int i = 0; i < 115; i++) {
			printf("-");
		}
		printf("\n");
		for (int i = 0; i < MAX_RECORDS; ++i) {
			if (records[i].trainInfo.prefer.time.arrive == time[1][0] && strcmp(records[i].ID, id) == 0) {
				printf("%-13s\t %s\t %.2f\t %.2f\t %-7s\t %-15s %-15s %d\n", records[i].refNum, records[i].date, records[i].trainInfo.prefer.time.depart, records[i].trainInfo.prefer.time.arrive, records[i].trainInfo.trainId, records[i].trainInfo.departFrom, records[i].trainInfo.destination, records[i].amount);
				++j;
			}
		}
		for (int i = 0; i < 115; i++) {
			printf("-");
		}
		printf("\n");
		if (j == 0) {
			title();
			printf("No records found.\n");
		}
		printf("Press any key to return.\n");
		rewind(stdin);
		getch();
		break;

	case '3':
		do {
			do {
				do {
					do {
						do {
							do {
								j = 0;
								title();
								printf("Press 0 for return.\n\n");
								if (loop == 1 || loop == 2 || loop == 3 || loop == 4) {
									strcpy(input, "1");
									if (time[0][0] > 12)
										time[0][0] -= 12;
									else if (time[0][0] == 0)
										time[0][0] += 12;
									printf("Type the Departure Time (in hours) (1 - 12) : %d\n", (int)(time[0][0] - time[0][1] / 100));
								}
								else {
									printf("Type the Departure Time (in hours) (1 - 12) : ");
									rewind(stdin);
									scanf("%s", input);
									time[0][0] = atoi(input);
								}
							} while ((time[0][0] < 1 || time[0][0] > 12) && strcmp(input, "0") != 0);
							if (strcmp(input, "0") == 0)
								return 0;
							else if (ampm[0] == 1) 
								time[0][0] -= 12;
							else if(ampm[1] == 1)
								time[0][0] += 12;
							do {
								ampm[0] = 0;
								ampm[1] = 0;
								printf("\t1. in a.m.\n\t2. in p.m.\n\n");
								printf("Enter the number : ");
								if (loop == 2 || loop == 3 || loop == 4) {
									if (ampm[0] == 1 || time[0][0] < 12)
										printf("1\n");
									else
										printf("2\n");
								}
								else {
									loop = 0;
									rewind(stdin);
									scanf("%s", input);
								}
							} while (strcmp(input, "1") != 0 && strcmp(input, "2") != 0 && strcmp(input, "0") != 0);
							if (strcmp(input, "0") == 0)
								time[0][1] = 0;
						} while (strcmp(input, "0") == 0);
						if (strcmp(input, "2") == 0 && time[0][0] != 12) {
							time[0][0] += 12;
							ampm[1] = 1;
						}
						else if (strcmp(input, "1") == 0 && time[0][0] == 12) {
							time[0][0] -= 12;
							ampm[0] = 1;
						}
						do {
							printf("Type the Departure Time (in minutes) (00 - 59) : ");
							if (loop == 3 || loop == 4) {
								printf("%02d\n", (int)time[0][1]);
							}
							else {
								loop = 0;
								time[0][0] -= time[0][1] / 100;
								rewind(stdin);
								scanf("%s", input);
								time[0][1] = atoi(input);
							}
						} while ((time[0][1] < 0 || time[0][1] > 59) && strcmp(input, "0") != 0);
						if (strcmp(input, "0") == 0)
							loop = 1;
					} while (strcmp(input, "0") == 0);
					time[0][0] += time[0][1] / 100;
					do {
						if (loop == 4) {
							strcpy(input, "1");
							if (time[1][0] > 12)
								time[1][0] -= 12;
							else if (time == 0)
								time[1][0] += 12;
							printf("Arrival Time (in hours) (0 - 24) : %d\n", (int)time[1][0]);
						}
						else {
							loop = 0;
							printf("Type the Arrival Time (in hours) (1 - 12) : ");
							rewind(stdin);
							scanf("%s", input);
							time[1][0] = atoi(input);
						}
					} while ((time[1][0] < 1 || time[1][0] > 12) && strcmp(input, "0") != 0);
					if (strcmp(input, "0") == 0)
						loop = 2;
				} while (strcmp(input, "0") == 0);
				do {
					loop = 0;
					printf("\t1. in a.m.\n\t2. in p.m.\n\n");
					printf("Enter the number : ");
					rewind(stdin);
					scanf("%s", &input);
				} while (strcmp(input, "1") != 0 && strcmp(input, "2") != 0 && strcmp(input, "0") != 0);
				if (strcmp(input, "0") == 0)
					loop = 3;
			} while (strcmp(input, "0") == 0);
			if (strcmp(input, "2") == 0 && time[1][0] != 12)
				time[1][0] += 12;
			else if (strcmp(input, "1") == 0 && time[1][0] == 12)
				time[1][0] -= 12;
			do {
				printf("Type the Arrival Time (in minutes) (00 - 59): ");
				rewind(stdin);
				scanf("%s", input);
				time[1][1] = atoi(input);
			} while ((time[1][1] < 0 || time[1][1] > 59) && strcmp(input, "0") != 0);
			if (strcmp(input, "0") == 0)
				loop = 4;
		} while (strcmp(input, "0") == 0);
		time[1][0] += time[1][1] / 100;
		for (int i = 0; i < 115; i++) {
			printf("-");
		}
		printf("\n");
		printf("%-13s\t %-11s\t %-5s\t %-5s\t %-5s\t \%-10s\t %-10s\t %-2s\n", "Reference No", "Date", "From", "To", "TrainID", "Departure", "Destination", "Pax");
		for (int i = 0; i < 115; i++) {
			printf("-");
		}
		printf("\n");
		for (int i = 0; i < MAX_RECORDS; ++i) {
			if (records[i].trainInfo.prefer.time.arrive == time[1][0] && records[i].trainInfo.prefer.time.depart == time[0][0] && strcmp(records[i].ID, id) == 0) {
				printf("%-13s\t %s\t %.2f\t %.2f\t %-7s\t %-15s %-15s %d\n", records[i].refNum, records[i].date, records[i].trainInfo.prefer.time.depart, records[i].trainInfo.prefer.time.arrive, records[i].trainInfo.trainId, records[i].trainInfo.departFrom, records[i].trainInfo.destination, records[i].amount);
				++j;
			}
		}
		for (int i = 0; i < 115; i++) {
			printf("-");
		}
		printf("\n");
		if (j == 0) {
			title();
			printf("No records found.\n");
		}
		printf("Press any key to return.\n");
		rewind(stdin);
		getch();
		break;
	}
	return 0;
}
