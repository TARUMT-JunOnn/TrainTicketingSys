#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#pragma warning(disable:4996)
#define STRUCTCOUNT 100
#define MAX_DAY 14
#define USE_TITLE

#ifndef USE_TITLE
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

typedef struct
{
	char day[20], trainID[6], departureFrom[13], destination[13];
	struct date deptArr;
	int seats;
	float price;
}Schedule;
Schedule schedule[STRUCTCOUNT];
struct date toMaxWeek[14];

// Modify schedule module
void ModifySchedule(void)
{
	int modifyChoice, modifyChoice1, dayChoice1, idChoice1, dayChoice2, idChoice2;
	char modifyDay[20], modTrainID[6];
	float newTime1, newTime2, newTime3, newTime4;
	char confirmation, confirmation2, continues;
	char continues2;
	do
	{
		system("cls");
		printf("[Schedule Modifier]\n");
		printf("-------------------\n");
		printf("Do you want: \n");
		printf("1. | Modify by entering day\n");
		printf("2. | Return to schedule menu.\n");
		printf("Choose one > ");
		rewind(stdin);
		scanf("%d", &modifyChoice);

		switch (modifyChoice)
		{
		case 1:
			system("cls");
			printf("Would you like to modify\n");
			printf("1. | This week schedule\n");
			printf("2. | Next week schedule\n");
			printf("Notes: You can only modify for schedules for upcoming two weeks.\n");
			printf("Choose one >");
			rewind(stdin);
			scanf("%d", &modifyChoice1);
			// Nested switch
			switch (modifyChoice1)
			{
			case 1:
				do
				{
					system("cls");

					do
					{
						printf("Select a day to modify:\n");
						printf("1. | Monday\n");
						printf("2. | Tuesday\n");
						printf("3. | Wednesday\n");
						printf("4. | Thursday\n");
						printf("5. | Friday\n");
						printf("6. | Saturday\n");
						printf("7. | Sunday\n");
						printf("Your choice > ");
						rewind(stdin);
						scanf("%d", &dayChoice1);
						switch (dayChoice1)
						{
						case 1:
							strcpy(modifyDay, "Monday");
							break;
						case 2:
							strcpy(modifyDay, "Tuesday");
							break;
						case 3:
							strcpy(modifyDay, "Wednesday");
							break;
						case 4:
							strcpy(modifyDay, "Thursday");
							break;
						case 5:
							strcpy(modifyDay, "Friday");
							break;
						case 6:
							strcpy(modifyDay, "Saturday");
							break;
						case 7:
							strcpy(modifyDay, "Sunday");
							break;
						case 0:
							continues = 'N';
							break;
						default:
							system("cls");
							printf("Invalid day. Again.\n");
							break;
						}
					} while (dayChoice1 != 1 && dayChoice1 != 2 && dayChoice1 != 3 && dayChoice1 != 4 && dayChoice1 != 5 && dayChoice1 != 6 && dayChoice1 != 7 && dayChoice1 != 0);
					if (dayChoice1 != 0) {
						do
						{
							printf("Select a train ID to modify.\n");
							printf("1. | T1001\n");
							printf("2. | T1002\n");
							printf("3. | T1003\n");
							printf("4. | T1004\n");
							printf("Your choice > ");
							rewind(stdin);
							scanf("%d", &idChoice1);
							switch (idChoice1)
							{
							case 1:
								strcpy(modTrainID, "T1001");
								break;
							case 2:
								strcpy(modTrainID, "T1002");
								break;
							case 3:
								strcpy(modTrainID, "T1003");
								break;
							case 4:
								strcpy(modTrainID, "T1004");
								break;
							default:
								system("cls");
								printf("Invalid Train ID. Again.\n");
								break;
							}
						} while (idChoice1 != 1 && idChoice1 != 2 && idChoice1 != 3 && idChoice1 != 4);

						for (int j = 0; j < STRUCTCOUNT; j++)
						{
							if (stricmp(modifyDay, schedule[j].day) == 0 && stricmp(modTrainID, schedule[j].trainID) == 0)
							{
								printf("\nEnter new depart time(24h format): ");
								rewind(stdin);
								scanf("%f", &newTime1);
								while (newTime1 > 24)
								{
									printf("Invalid time. Try again.\n");
									printf("\nEnter new depart time(24h format): ");
									rewind(stdin);
									scanf("%f", &newTime1);
								}
								printf("Enter new arrival time(24h format): ");
								rewind(stdin);
								scanf("%f", &newTime2);
								while (newTime2 > 24)
								{
									printf("Invalid time. Try again.\n");
									printf("\nEnter new arrival time(24h format): ");
									rewind(stdin);
									scanf("%f", &newTime2);
								}
								while (newTime2 <= newTime1 || newTime2 < newTime1 + 4)
								{
									if (newTime2 <= newTime1)
									{
										printf("Error: Your arrival time is earlier than your departure time!\n");
									}
									else if (newTime2 < newTime1 + 4)
									{
										printf("Error: The train need at least 4 hours to travel between two destination!\n");
									}
									// Try again
									printf("\nEnter new depart time(24h format): ");
									rewind(stdin);
									scanf("%f", &newTime1);
									while (newTime1 > 24)
									{
										printf("Invalid time. Try again.\n");
										printf("\nEnter new depart time(24h format): ");
										rewind(stdin);
										scanf("%f", &newTime1);
									}
									printf("Enter new arrival time(24h format): ");
									rewind(stdin);
									scanf("%f", &newTime2);
									while (newTime2 > 24)
									{
										printf("Invalid time. Try again.\n");
										printf("\nEnter new arrival time(24h format): ");
										rewind(stdin);
										scanf("%f", &newTime2);
									}
								}
								printf("Confirm?(Y/N) : ");
								rewind(stdin);
								scanf("%c", &confirmation);
								if (confirmation == 'Y' || confirmation == 'y')
								{
									schedule[j].deptArr.time.depart = newTime1;
									schedule[j].deptArr.time.arrive = newTime2;
									printf("\nSchedule modified.\n");
								}
								else if (confirmation == 'N' || confirmation == 'n')
								{
									printf("\nChange ignore.\n");
								}
								else
								{
									printf("Invalid command. Change ignore.\n");
								}
								printf("Do you wish to continue?\n");
								printf("(Y/N) > ");
								rewind(stdin);
								scanf("%c", &continues);
							}
						}
					}
				} while (continues == 'y' || continues == 'Y');
				break;

			case 2:
				do
				{
					system("cls");

					do
					{
						printf("Select a day to modify:\n");
						printf("1. | Monday\n");
						printf("2. | Tuesday\n");
						printf("3. | Wednesday\n");
						printf("4. | Thursday\n");
						printf("5. | Friday\n");
						printf("6. | Saturday\n");
						printf("7. | Sunday\n");
						printf("Your choice > ");
						rewind(stdin);
						scanf("%d", &dayChoice2);
						switch (dayChoice2)
						{
						case 1:
							strcpy(modifyDay, "NextMonday");
							break;
						case 2:
							strcpy(modifyDay, "NextTuesday");
							break;
						case 3:
							strcpy(modifyDay, "NextWednesday");
							break;
						case 4:
							strcpy(modifyDay, "NextThursday");
							break;
						case 5:
							strcpy(modifyDay, "NextFriday");
							break;
						case 6:
							strcpy(modifyDay, "NextSaturday");
							break;
						case 7:
							strcpy(modifyDay, "NextSunday");
							break;
						case 0:
							continues2 = 'N';
							break;
						default:
							system("cls");
							printf("Invalid day. Again.\n");
							break;
						}
					} while (dayChoice2 != 1 && dayChoice2 != 2 && dayChoice2 != 3 && dayChoice2 != 4 && dayChoice2 != 5 && dayChoice2 != 6 && dayChoice2 != 7 && dayChoice2 != 0);

					if (dayChoice2 != 0) {
						do
						{
							printf("Select a train ID to modify.\n");
							printf("1. | T1001\n");
							printf("2. | T1002\n");
							printf("3. | T1003\n");
							printf("4. | T1004\n");
							printf("Your choice > ");
							rewind(stdin);
							scanf("%d", &idChoice2);
							switch (idChoice2)
							{
							case 1:
								strcpy(modTrainID, "T1001");
								break;
							case 2:
								strcpy(modTrainID, "T1002");
								break;
							case 3:
								strcpy(modTrainID, "T1003");
								break;
							case 4:
								strcpy(modTrainID, "T1004");
								break;
							default:
								system("cls");
								printf("Invalid Train ID. Again.\n");
								break;
							}
						} while (idChoice2 != 1 && idChoice2 != 2 && idChoice2 != 3 && idChoice2 != 4);


						for (int k = 0; k < STRUCTCOUNT; k++)
						{
							if (stricmp(modifyDay, schedule[k].day) == 0 && stricmp(modTrainID, schedule[k].trainID) == 0)
							{
								printf("\nEnter new depart time(24h format): ");
								rewind(stdin);
								scanf("%f", &newTime3);
								while (newTime3 > 24)
								{
									printf("Invalid time. Try again.\n");
									printf("\nEnter new depart time(24h format): ");
									rewind(stdin);
									scanf("%f", &newTime3);
								}
								printf("Enter new arrival time(24h format): ");
								rewind(stdin);
								scanf("%f", &newTime4);
								while (newTime4 > 24)
								{
									printf("Invalid time. Try again.\n");
									printf("\nEnter new arrival time(24h format): ");
									rewind(stdin);
									scanf("%f", &newTime4);
								}
								while (newTime4 <= newTime3 || newTime4 < newTime3 + 4)
								{
									if (newTime4 <= newTime3)
									{
										printf("Error: Your arrival time is earlier than your departure time!\n");
									}
									else if (newTime4 < newTime3 + 4)
									{
										printf("Error: The train need at least 4 hours to travel between two destination!\n");
									}
									// Try again
									printf("\nEnter new depart time(24h format): ");
									rewind(stdin);
									scanf("%f", &newTime3);
									while (newTime3 > 24)
									{
										printf("Invalid time. Try again.\n");
										printf("\nEnter new depart time(24h format): ");
										rewind(stdin);
										scanf("%f", &newTime3);
									}
									printf("Enter new arrival time(24h format): ");
									rewind(stdin);
									scanf("%f", &newTime4);
									while (newTime4 > 24)
									{
										printf("Invalid time. Try again.\n");
										printf("\nEnter new arrival time(24h format): ");
										rewind(stdin);
										scanf("%f", &newTime4);
									}
								}
								printf("Confirm?(Y/N) : ");
								rewind(stdin);
								scanf("%c", &confirmation2);
								if (confirmation2 == 'Y' || confirmation2 == 'y')
								{
									schedule[k].deptArr.time.depart = newTime3;
									schedule[k].deptArr.time.arrive = newTime4;
									printf("\nSchedule modified.\n");
								}
								else if (confirmation2 == 'N' || confirmation2 == 'n')
								{
									printf("\nChange ignore.\n");
								}
								else
								{
									printf("Invalid command. Change ignore.\n");
								}
								printf("Do you wish to continue?\n");
								printf("(Y/N) > ");
								rewind(stdin);
								scanf("%c", &continues2);
							}
						}
					}
				} while (continues2 == 'y' || continues2 == 'Y');
				break;
			default:
				break;
			} // End Nested switch
			break;

		case 2:
			system("cls");
			printf("Returning to schedule menu...\n");
			Sleep(1500);
			break;

		default:
			system("cls");
			printf("Invalid value. Enter again\n\n");
			Sleep(1000);
			break;
		}
	} while (modifyChoice != 2);
}

// Reset Schedule Module Part II Weekday
void ResetScheduleIIWeekday(char resetDayII[15])
{
	int j = 0, k;
	// Reset added schedule
	for (int i = 48; i < STRUCTCOUNT; i++) {
		if (strcmp(schedule[i].day, resetDayII) == 0)
			j++;
	}
	for (j; j > 0; j--) {
		for (k = 48; strcmp(schedule[k].day, resetDayII) != 0; k++);
		for (int i = k; k < STRUCTCOUNT; k++) {
			schedule[k] = schedule[k + 1];
		}
	}

	// Reset passed schedule
	for (int j = 0; j < STRUCTCOUNT; j++)
	{
		if (strcmp(schedule[j].day, resetDayII) == 0)
		{
			schedule[j].seats = 100;
			if (strcmp(schedule[j].trainID, "T1001") == 0)
			{
				schedule[j].deptArr.time.depart = 9;
				schedule[j].deptArr.time.arrive = 13;
			}
			else if (strcmp(schedule[j].trainID, "T1002") == 0)
			{
				schedule[j].deptArr.time.depart = 9;
				schedule[j].deptArr.time.arrive = 13;
			}
			else if (strcmp(schedule[j].trainID, "T1003") == 0)
			{
				schedule[j].deptArr.time.depart = 16;
				schedule[j].deptArr.time.arrive = 20;
			}
			else if (strcmp(schedule[j].trainID, "T1004") == 0)
			{
				schedule[j].deptArr.time.depart = 16;
				schedule[j].deptArr.time.arrive = 20;
			}
		}
	}
	for (int i = 0; i < 3; ++i) {
		system("cls");
		printf("Resetting Schedule");
		for (int j = 0; j < 3; ++j) {
			Sleep(200);
			printf(".");
			Sleep(200);
		}
	}
	system("cls");
	printf("\nSchedule reset completed.\n\n");
	Sleep(1500);
}
void ResetScheduleIIWeekend(char resetDayII[15])
{
	int j = 0, k;
	// Reset added schedule
	for (int i = 48; i < STRUCTCOUNT; i++) {
		if (strcmp(schedule[i].day, resetDayII) == 0)
			j++;
	}
	for (j; j > 0; j--) {
		for (k = 48; strcmp(schedule[k].day, resetDayII) != 0; k++);
		for (int i = k; k < STRUCTCOUNT; k++) {
			schedule[k] = schedule[k + 1];
		}
	}

	// Reset passed schedule
	for (int j = 0; j < STRUCTCOUNT; j++)
	{
		if (strcmp(schedule[j].day, resetDayII) == 0)
		{
			schedule[j].seats = 100;
			if (strcmp(schedule[j].trainID, "T1001") == 0)
			{
				schedule[j].deptArr.time.depart = 15;
				schedule[j].deptArr.time.arrive = 19;
			}
			else if (strcmp(schedule[j].trainID, "T1002") == 0)
			{
				schedule[j].deptArr.time.depart = 15;
				schedule[j].deptArr.time.arrive = 19;
			}
		}
	}
	for (int i = 0; i < 3; ++i) {
		system("cls");
		printf("Resetting Schedule");
		for (int j = 0; j < 3; ++j) {
			Sleep(200);
			printf(".");
			Sleep(200);
		}
	}
	system("cls");
	printf("\nSchedule reset completed.\n\n");
	Sleep(1500);
}

void countDate(int followingNum, int* day, int* month, int* year, char(*dayOW)[80]) {
	time_t timer;
	struct tm* now;
	int status;
	time(&timer);
	now = localtime(&timer);
	int thisyear = now->tm_year + 1900;
	do {
		status = month_day(thisyear, now->tm_yday + followingNum, &(*month), &(*day));
		if (status == 0) {
			followingNum -= 365;
			thisyear++;
		}
		else if (status == 1) {
			followingNum -= 366;
			thisyear++;
		}
	} while (status != 2);
	*year = thisyear;
	now->tm_mday = *day;
	now->tm_mon = *month - 1;
	now->tm_year = thisyear - 1900;
	mktime(now);
	strftime((*dayOW), 80, "%A", now);
}


int readScheduleFile(FILE** fp) {
	*fp = fopen("../TrainTicketingSys/res/schedule.txt", "r");
	while (*fp == NULL)
	{
		return -1;
	}
	int i = 0;
	while (fscanf(*fp, "%s %f %f %[^|]|%[^|]|%[^|]|%d|%f\n", schedule[i].day, &schedule[i].deptArr.time.depart, &schedule[i].deptArr.time.arrive, schedule[i].trainID, schedule[i].departureFrom, schedule[i].destination, &schedule[i].seats, &schedule[i].price) != EOF)
	{
		i++;
	}
	for (int i = 0; i < 14; i++) {
				countDate(i, &toMaxWeek[i].day, &toMaxWeek[i].month, &toMaxWeek[i].year, &toMaxWeek[i].weekday);
			}
	fclose(*fp);
}

int writeScheduleFile(FILE** fp2) {
	for (int i = 0; i < STRUCTCOUNT; i++)
	{
		if (strcmp(schedule[i].day, "") != 0)
		{
			fprintf(*fp2, "%s %.2f %.2f %s|%s|%s|%d|%.02f\n", schedule[i].day, schedule[i].deptArr.time.depart, schedule[i].deptArr.time.arrive, schedule[i].trainID, schedule[i].departureFrom, schedule[i].destination, schedule[i].seats, schedule[i].price);
		}
	}
}

void alert() {
	time_t timer;
	struct tm* now;
	char day[10];
	time(&timer);
	now = localtime(&timer);
	dayOfWeek(now->tm_wday, &day);
	if (schedule[48].deptArr.time.depart > 0 && schedule[48].deptArr.time.arrive > 0)
	{
		printf("Alert ! The schedule has remaining customised schedule that haven't deleted ! \n");
	}
	for (int i = 48; i < STRUCTCOUNT; i++) {
		printf("%-20s %s\n", schedule[i].day, schedule[i].destination);
	}
}

void parSchedule(int week, int day, int month, int year, char weekday[80], int* matched) {
	char s[80];
	int qty = 0;
	if (week > 1) {
		strcpy(s, "Next");
		strcat(s, weekday);
		if (day != 0 && month != 0 && year != 0)
			printf("Date: %d/%d/%d\n", day, month, year);
		printf("Next %s:\n", weekday);
	}
	else {
		strcpy(s, weekday);
		if (day != 0 && month != 0 && year != 0)
			printf("Date: %d/%d/%d\n", day, month, year);
			printf("%s:\n", weekday);
	}
	printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
	printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
	for (int counter = 0; counter < STRUCTCOUNT; counter++)
	{
		if (strcmp(schedule[counter].day, s) == 0)
		{
			printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[counter].deptArr.time.depart, schedule[counter].deptArr.time.arrive, schedule[counter].trainID, schedule[counter].departureFrom, schedule[counter].destination, schedule[counter].seats);
			*(matched + qty) = counter;
			qty++;
		}
	}
	printf("\n");
}

void allSchedule() {
	int records[STRUCTCOUNT];
	printf("-------------------------------------------------------------------------------------------------------\n");
	printf("This Week Schedule: \n");
	printf("-------------------------------------------------------------------------------------------------------\n");
	for (int i = 0; i < 14; i++)
		countDate(i, &toMaxWeek[i].day, &toMaxWeek[i].month, &toMaxWeek[i].year, &toMaxWeek[i].weekday);
	for (int j = 0; j < 14; j++) {
		if (j == 7) {
			printf("\n");
			printf("-------------------------------------------------------------------------------------------------------\n");
			printf("Next Week Schedule: \n");
			printf("-------------------------------------------------------------------------------------------------------\n");
		}
		if (j < 7)
			parSchedule(1, toMaxWeek[j].day, toMaxWeek[j].month, toMaxWeek[j].year, toMaxWeek[j].weekday, &records);
		else
			parSchedule(2, toMaxWeek[j].day, toMaxWeek[j].month, toMaxWeek[j].year, toMaxWeek[j].weekday, &records);
	}
	printf("-------------------------------------------------------------------------------------------------------\n");
}

// Add schedule part II
void AddSchedulePartII(char dayHolder[20])
{
	float deptTime, arrTime;
	int destinationChoice;
	char trainID[6], deptfrom[30], destination[30];
	int idLength;
	int i;
	int trainSeats;
	char confirmation;

	printf("Enter a trainID (Maximum 5 characters): ");
	rewind(stdin);
	scanf("%[^\n]", trainID);
	idLength = strlen(trainID);
	while (idLength > 5)
	{
		system("cls");
		printf("Train ID (%s) exceed 5 characters.Try again.\n", trainID);
		printf("Enter a train ID (Maximum 5 characters): ");
		rewind(stdin);
		scanf("%[^\n]", trainID);
		idLength = strlen(trainID);
	}
	while (idLength < 2)
	{
		system("cls");
		printf("Invalid train ID. Try again.\n", trainID);
		printf("Enter a train ID (Maximum 5 characters): ");
		rewind(stdin);
		scanf("%[^\n]", trainID);
		idLength = strlen(trainID);
	}
	do
	{
		printf("Select a depart train station\n");
		printf("1. | KL Sentral\n");
		printf("2. | Kampar\n");
		printf("Choice > ");
		rewind(stdin);
		scanf("%d", &destinationChoice);
		switch (destinationChoice)
		{
		case 1:
			strcpy(deptfrom, "KL Sentral");
			printf("\nAuto assign destination to Kampar.\n");
			strcpy(destination, "Kampar");
			break;
		case 2:
			strcpy(deptfrom, "Kampar");
			printf("\nAuto assign destination to KL Sentral.\n");
			strcpy(destination, "KL Sentral");
			break;
		default:
			system("cls");
			printf("Invalid command. Try again.\n");
			break;
		}
	} while (destinationChoice != 1 && destinationChoice != 2);

	printf("Enter train depart time: ");
	rewind(stdin);
	scanf("%f", &deptTime);

	// Check valid, valid for midnight haven't **
	while (deptTime < 0 || deptTime > 24)
	{
		printf("\nInvalid time. Again.\n");
		printf("Enter train depart time: ");
		rewind(stdin);
		scanf("%f", &deptTime);
	}

	printf("\n");
	printf("Enter train arrive time: ");
	rewind(stdin);
	scanf("%f", &arrTime);
	while (arrTime < 0 || arrTime > 24)
	{
		printf("\nInvalid time. Again.\n");
		printf("Enter train depart time: ");
		rewind(stdin);
		scanf("%f", &arrTime);
	}
	printf("Enter total seats available: ");
	rewind(stdin);
	scanf("%d", &trainSeats);

	printf("Confirm(Y/N) ? >");
	rewind(stdin);
	scanf("%c", &confirmation);

	while (confirmation != 'Y' && confirmation != 'y' && confirmation != 'n' && confirmation != 'N')
	{
		system("cls");
		printf("Invalid command. Try again.\n");
		printf("Confirm(Y/N) ? >");
		rewind(stdin);
		scanf("%c", &confirmation);
	}

	if (confirmation == 'Y' || confirmation == 'y')
	{
		for (i = 0; strcmp(schedule[i].day, "") != 0; i++);
		strcpy(schedule[i].day, dayHolder);
		schedule[i].deptArr.time.depart = deptTime;
		schedule[i].deptArr.time.arrive = arrTime;
		strcpy(schedule[i].trainID, trainID);
		strcpy(schedule[i].departureFrom, deptfrom);
		strcpy(schedule[i].destination, destination);
		schedule[i].seats = trainSeats;

		system("cls");
		printf("Schedule Added.\n\n");
		Sleep(1000);
		system("cls");
	}
	else if (confirmation == 'n' || confirmation == 'N')
	{
		system("cls");
		printf("Change ignore.\n\n");
		printf("Returning to last page...");
		Sleep(1000);
		system("cls");
	}
}

// Display schedule module
int DisplaySchedule()
{
	struct date toMaxWeek[MAX_DAY];
	int records[STRUCTCOUNT];
	for (int i = 0; i < 14; i++)
		countDate(i, &toMaxWeek[i].day, &toMaxWeek[i].month, &toMaxWeek[i].year, &toMaxWeek[i].weekday);
	int counter = 0;
	int choice;
	int k;
	char s[14][80];
	char weekday[10];
	for (int i = 0; i < 14; i++) {
		if (i < 7)
			strcpy(s[i], (*(toMaxWeek + i)).weekday);
		else {
			strcpy(s[i], "Next ");
			strcat(s[i], (*(toMaxWeek + i)).weekday);
		}
	}

	system("cls");
	// Weekday Schedule
	printf("Select the schedule you want to display. \n");
	do
	{
		printf("\n0. | Display all\n");
		printf("1. | Monday Schedule\n");
		printf("2. | Tuesday Schedule\n");
		printf("3. | Wednesday Schedule\n");
		printf("4. | Thursday Schedule\n");
		printf("5. | Friday Schedule\n");
		printf("6. | Saturday Schedule\n");
		printf("7. | Sunday Schedule\n");
		printf("8. | Return to schedule menu.\n");
		printf("\nYour choice > ");
		rewind(stdin);
		scanf("%d", &choice);
		switch (choice)
		{
		case 0:
			allSchedule();
			break;
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
			system("cls");
			printf("-------------------------------------------------------------------------------------------------------\n");
			dayOfWeek(choice, &weekday);
			if (choice == 7)
				dayOfWeek(0, &weekday);
			for (k = 0; k < 7; k++) {
				if (strcmp(toMaxWeek[k].weekday, weekday) == 0)
					parSchedule(1, toMaxWeek[k].day, toMaxWeek[k].month, toMaxWeek[k].year, toMaxWeek[k].weekday, &records);
			}
			printf("\n");
			for (k = 7; k < 14; k++)
			{
				if (strcmp(toMaxWeek[k].weekday, weekday) == 0)
					parSchedule(2, toMaxWeek[k].day, toMaxWeek[k].month, toMaxWeek[k].year, toMaxWeek[k].weekday, &records);
			}
			printf("-------------------------------------------------------------------------------------------------------\n");
			break;

		case 8:
			printf("\nReturn to schedule menu.\n");
			return 8;
			break;

		default:
			printf("Invalid value. Enter again! \n\n");
		}
	} while (choice != 8);
}

// Convert date to day
int month_day(int year, int yearday, int* pmonth, int* pday)
{
	int i;
	int leap = 0;
	int month[2][12] = { { 31,28,31,30,31,30,31,31,30,31,30,31 }, { 31,28,31,30,31,30,31,31,30,31,30,31 } };
	if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0) {
		leap = 1;
	}
	for (i = 0; yearday > month[leap][i]; ++i) {
		if (i >= 12)
			return leap;
		yearday -= month[leap][i];
	}
	*pmonth = i + 1;
	*pday = yearday;
	return 2;
}

// Add schedule module
void AddSchedule(void)
{
	int choice, selectDay;
	char tempDayHolder[20];

	do
	{
		system("cls");
		printf("[Add Schedule Tool]\n");
		printf("-------------------\n");
		printf("Do you want to add schedule for:\n");
		printf("1. | This week\n");
		printf("2. | Next week\n");
		printf("3. | Return to schedule menu\n");
		printf("Your choice > \n");
		scanf("%d", &choice);

		system("cls");

		switch (choice)
		{
		case 1:
			do
			{
				printf("[Add Schedule Tool]\n");
				printf("-------------------\n");
				printf("Select a day for this week.\n");
				selectDay = daySelection();

				system("cls");

				switch (selectDay)
				{
				case 1:
					printf("Adding schedule for Monday\n");
					strcpy(tempDayHolder, "Monday");
					AddSchedulePartII(tempDayHolder);
					break;
				case 2:
					printf("Adding schedule for Tuesday\n");
					strcpy(tempDayHolder, "Tuesday");
					AddSchedulePartII(tempDayHolder);
					break;
				case 3:
					printf("Adding schedule for Wednesday\n");
					strcpy(tempDayHolder, "Wednesday");
					AddSchedulePartII(tempDayHolder);
					break;
				case 4:
					printf("Adding schedule for Thursday\n");
					strcpy(tempDayHolder, "Thursday");
					AddSchedulePartII(tempDayHolder);
					break;
				case 5:
					printf("Adding schedule for Friday\n");
					strcpy(tempDayHolder, "Friday");
					AddSchedulePartII(tempDayHolder);
					break;
				case 6:
					printf("Adding schedule for Saturday\n");
					strcpy(tempDayHolder, "Saturday");
					AddSchedulePartII(tempDayHolder);
					break;
				case 7:
					printf("Adding schedule for Sunday\n");
					strcpy(tempDayHolder, "Sunday");
					AddSchedulePartII(tempDayHolder);
					break;
				case 8:
					system("cls");
					printf("Returning to last page...\n");
					Sleep(1000);
					break;
				default:
					system("cls");
					printf("Invalid value. Try again.\n");
					break;
				}
			} while (selectDay != 8);
			break;

		case 2:
			do
			{
				printf("[Add Schedule Tool]\n");
				printf("-------------------\n");
				printf("Select a day for next week.\n");
				selectDay = daySelection();

				system("cls");

				switch (selectDay)
				{
				case 1:
					printf("Adding schedule for Next Monday\n");
					strcpy(tempDayHolder, "NextMonday");
					AddSchedulePartII(tempDayHolder);
					break;
				case 2:
					printf("Adding schedule for Tuesday\n");
					strcpy(tempDayHolder, "NextTuesday");
					AddSchedulePartII(tempDayHolder);
					break;
				case 3:
					printf("Adding schedule for Wednesday\n");
					strcpy(tempDayHolder, "NextWednesday");
					AddSchedulePartII(tempDayHolder);
					break;
				case 4:
					printf("Adding schedule for Thursday\n");
					strcpy(tempDayHolder, "NextThursday");
					AddSchedulePartII(tempDayHolder);
					break;
				case 5:
					printf("Adding schedule for Friday\n");
					strcpy(tempDayHolder, "NextFriday");
					AddSchedulePartII(tempDayHolder);
					break;
				case 6:
					printf("Adding schedule for Saturday\n");
					strcpy(tempDayHolder, "NextSaturday");
					AddSchedulePartII(tempDayHolder);
					break;
				case 7:
					printf("Adding schedule for Sunday\n");
					strcpy(tempDayHolder, "NextSunday");
					AddSchedulePartII(tempDayHolder);
					break;
				case 8:
					system("cls");
					printf("Returning to last page...\n");
					Sleep(1000);
					break;
				default:
					system("cls");
					printf("Invalid value. Try again.\n");
					break;
				}
			} while (selectDay != 8);
			break;
		case 3:
			system("cls");
			printf("Returning to schedule menu...\n");
			Sleep(1500);
			break;
		default:
			system("cls");
			printf("Invalid command. Try again.\n");
			Sleep(1000);
			break;
		}
	} while (choice != 3);
}

// Search module part II
void SearchScheduleII(char destination[20], int* records)
{
	int j = 0;
	printf("\n");
	printf("%-20s %-10s %-20s %-20s %-20s\n", "=================", "========", "==============", "============", "==========");
	printf("%-20s %-10s %-20s %-20s %-20s\n", "       Day       ", "Train ID", "Departure Time", "Arrival Time", "Seats Left");
	printf("%-20s %-10s %-20s %-20s %-20s\n", "=================", "========", "==============", "============", "==========");
	for (int i = 0; i < STRUCTCOUNT; i++)
	{
		if (strcmp(schedule[i].destination, destination) == 0)
		{
			printf("%-20s %-10s %-20.2f %-20.2f %-20d\n\n", schedule[i].day, schedule[i].trainID, schedule[i].deptArr.time.depart, schedule[i].deptArr.time.arrive, schedule[i].seats);
			*(records + j) = i;
			j++;
		}
	}
	printf("------------------------------------------------------------------------------------------------------\n\n");
}

// Search schedule module
void SearchSchedule(void)
{
	int mainChoice, choice, choice2, choice3;
	int date, todays, diffDays;
	int searchDay, searchMonth, searchYear;
	time_t dateNow, compare;
	struct tm* searchDate, * compareStruct;
	char nextWeekResult[20], searchDestination[20], searchResult[80];
	char confirmation;
	int records[STRUCTCOUNT];


	system("cls");

	do
	{
		printf("[Schedule Searching Tool]\n");
		printf("-------------------------\n");
		printf("Do you wish to search by\n");
		printf("1. | Day\n");
		printf("2. | Date\n");
		printf("3. | Destination\n");
		printf("4. | Return to schedule menu.\n");
		printf("Choice > ");
		rewind(stdin);
		scanf("%d", &mainChoice);

		system("cls");
		switch (mainChoice)
		{
			// By day
		case 1:
			do
			{
				system("cls");
				printf("[Schedule Searching Tool]\n");
				printf("-------------------------\n");
				printf("1. | This week schedule\n");
				printf("2. | Next week schedule\n");
				printf("3. | Return to last page.\n");
				printf("Choice > ");
				rewind(stdin);
				scanf("%d", &choice);
				system("cls");
				switch (choice)
				{
				case 1:
					do
					{
						printf("You are searching for this week schedule\n");
						printf("1. | Monday Schedule\n");
						printf("2. | Tuesday Schedule\n");
						printf("3. | Wednesday Schedule\n");
						printf("4. | Thursday Schedule\n");
						printf("5. | Friday Schedule\n");
						printf("6. | Saturday Schedule\n");
						printf("7. | Sunday Schedule\n");
						printf("8. | Return to last page.\n");
						rewind(stdin);
						scanf("%d", &choice2);
						switch (choice2)
						{
						case 1:
							system("cls");
							parSchedule(1, 0, 0, 0, "Monday", &records);
							printf("\n\n");
							break;
						case 2:
							system("cls");
							parSchedule(1, 0, 0, 0, "Tuesday", &records);
							break;
						case 3:
							system("cls");
							parSchedule(1, 0, 0, 0, "Wednesday", &records);
							printf("\n\n");
							break;
						case 4:
							system("cls");
							parSchedule(1, 0, 0, 0, "Thursday", &records);
							printf("\n\n");
							break;
						case 5:
							system("cls");
							parSchedule(1, 0, 0, 0, "Friday", &records);
							break;
						case 6:
							system("cls");
							parSchedule(1, 0, 0, 0, "Saturday", &records);
							break;
						case 7:
							system("cls");
							parSchedule(1, 0, 0, 0, "Sunday", &records);
							printf("\n\n");
							break;
						case 8:
							system("cls");
							printf("Returning to last page...\n");
							Sleep(1000);
							break;
						default:
							system("cls");
							printf("Invalid value. Again.\n");
							break;
						}
					} while (choice2 != 8);
					break;
				case 2:
					do
					{
						printf("You are searching for next week schedule\n");
						printf("1. | Monday Schedule\n");
						printf("2. | Tuesday Schedule\n");
						printf("3. | Wednesday Schedule\n");
						printf("4. | Thursday Schedule\n");
						printf("5. | Friday Schedule\n");
						printf("6. | Saturday Schedule\n");
						printf("7. | Sunday Schedule\n");
						printf("8. | Return to last page.\n");
						rewind(stdin);
						scanf("%d", &choice2);
						switch (choice2)
						{
						case 1:
							system("cls");
							parSchedule(2, 0, 0, 0, "Monday", &records);
							printf("\n\n");
							break;
						case 2:
							system("cls");
							system("cls");
							parSchedule(2, 0, 0, 0, "Tuesday", &records);
							printf("\n\n");
							break;
						case 3:
							system("cls");
							system("cls");
							parSchedule(2, 0, 0, 0, "Wednesday", &records);
							printf("\n\n");
							break;
						case 4:
							system("cls");
							parSchedule(2, 0, 0, 0, "Thursday", &records);
							printf("\n\n");
							break;
						case 5:
							system("cls");
							parSchedule(2, 0, 0, 0, "Friday", &records);
							printf("\n\n");
							break;
						case 6:
							system("cls");
							parSchedule(2, 0, 0, 0, "Saturday", &records);
							printf("\n\n");
							break;
						case 7:
							system("cls");
							parSchedule(2, 0, 0, 0, "Sunday", &records);
							printf("\n\n");
							break;
						case 8:
							system("cls");
							printf("Returning to last page...\n");
							Sleep(1000);
							break;
						default:
							system("cls");
							printf("Invalid value. Again.\n");
							break;
						}
					} while (choice2 != 8);
					break;
				case 3:
					system("cls");
					printf("Returning to last page...\n");
					Sleep(1000);
					break;
				default:
					break;
				}
			} while (choice != 3);
			break;

			// By date
		case 2:
			do
			{
				time(&dateNow);
				searchDate = localtime(&dateNow);
				system("cls");

				printf("Enter the date you wish to search for by: \n");
				printf("Day  : ");
				rewind(stdin);
				scanf("%d", &searchDay);
				printf("Month: ");
				rewind(stdin);
				scanf("%d", &searchMonth);
				printf("Year : ");
				rewind(stdin);
				scanf("%d", &searchYear);

				searchDate->tm_mday = searchDay;
				searchDate->tm_mon = searchMonth - 1;
				searchDate->tm_year = searchYear - 1900;

				mktime(searchDate);
				date = searchDate->tm_yday;
				strftime(searchResult, 80, "%A", searchDate);

				time(&compare);
				compareStruct = localtime(&compare);

				compareStruct->tm_mday = compareStruct->tm_mday;
				compareStruct->tm_mon = compareStruct->tm_mon - 1;
				compareStruct->tm_year = compareStruct->tm_year - 1900;

				mktime(compareStruct);
				todays = compareStruct->tm_yday;

				diffDays = date - todays;

				if (diffDays > 0 && diffDays < 7)
				{
					system("cls");
					parSchedule(0, searchDay, searchMonth, searchYear, searchResult, &records);
					printf("\n\n");
				}

				else if (diffDays >= 7 && diffDays < 14)
				{
					system("cls");
					parSchedule(1, searchDay, searchMonth, searchYear, searchResult, &records);
					printf("\n\n");
				}
				else
				{
					system("cls");
					printf("Sorry. System are only able to show up to two weeks schedules from now.\n");
				}
				printf("Continue? (Y/N) > ");
				rewind(stdin);
				scanf("%c", &confirmation);
			} while (confirmation == 'y' || confirmation == 'Y');
			break;

			// By destination
		case 3:
			system("cls");
			do
			{
				printf("Select your route to begin searching.\n");
				printf("1. | KL Sentral to Kampar\n");
				printf("2. | Kampar to KL Sentral\n");
				printf("3. | Return to last page.\n");
				printf("Choice > ");
				rewind(stdin);
				scanf("%d", &choice3);
				switch (choice3)
				{
				case 1:
					printf("\n===========================================\n");
					printf("Showing Schedule From Kampar to KL Sentral.\n");
					printf("===========================================\n");
					strcpy(searchDestination, "Kl Sentral");
					SearchScheduleII(searchDestination, &records);
					break;
				case 2:
					printf("\n===========================================\n");
					printf("Showing Schedule From KL Sentral to Kampar.\n");
					printf("===========================================\n");
					strcpy(searchDestination, "Kampar");
					SearchScheduleII(searchDestination, &records);
					break;
				case 3:
					system("cls");
					printf("Returning to last page.\n");
					Sleep(1000);
					break;
				default:
					system("cls");
					printf("Invalid value. Try again. \n");
					break;
				}
			} while (choice3 != 3);
			break;

		case 4:
			system("cls");
			printf("Returning to schedule menu...\n");
			Sleep(1500);
			break;

		default:
			printf("Invalid value. Try again.\n");
			break;
		}

	} while (mainChoice != 4);
}

int daySelection(void)
{
	int select;
	printf("1. | Monday\n");
	printf("2. | Tuesday\n");
	printf("3. | Wednesday\n");
	printf("4. | Thursday\n");
	printf("5. | Friday\n");
	printf("6. | Saturday\n");
	printf("7. | Sunday\n");
	printf("8. | Return to last page.\n");
	printf("Your Choice > ");
	rewind(stdin);
	scanf("%d", &select);
	return select;
}

// Delete module
void DeleteSchedule(void)
{
	int i;
	char deleteTrainID[10];
	char confirmation;
	int checkValid, continueOrNo;

	// Maybe administrator password again here?
	// scanf("%s", administratorPassword);
	// if(strcmp() == 0) ... 
	
	do
	{
		system("cls");
		printf("[Delete Schedule System]\n");
		printf("========================\n");
		printf("You're entering Schedule Deleting System.\n");
		printf("Notes: You're only able to delete the schedule that you've add before.\n\n");
		printf("1. | Continue\n");
		printf("2. | Return to last page\n");
		rewind(stdin);
		scanf("%d", &continueOrNo);
		switch (continueOrNo)
		{
		case 1:
			system("cls");
			printf("[Delete Schedule System]\n");
			printf("========================\n");
			printf("You're entering Schedule Deleting System.\n");
			printf("Notes: You're only able to delete the schedule that you've add before.\n\n");
			printf("The schedule you've add before:\n");
			printf("%-10s %-20s %-20s %-20s %-15s %-15s\n", "Train ID", "Day             ", "Depart From", "Destination", "Depart Time", "Arrive Time");
			printf("%-10s %-20s %-20s %-20s %-15s %-15s\n", "========", "================", "===========", "===========", "===========", "===========");

			for (i = 0; i < STRUCTCOUNT; i++)
			{
				if (i >= 48 && strcmp(schedule[i].day, "") != 0)
				{
					printf("%-10s %-20s %-20s %-20s %-15.2f %-15.2f\n", schedule[i].trainID, schedule[i].day, schedule[i].departureFrom, schedule[i].destination, schedule[i].deptArr.time.depart, schedule[i].deptArr.time.arrive);
				}
			}
			
				printf("Enter a train ID to delete that schedule(if there is no schedule to delete, XXX to exit): ");
				rewind(stdin);
				scanf("%s", deleteTrainID);

				if (strcmp(deleteTrainID, "XXX") != 0 && strcmp(deleteTrainID, "xxx") != 0)
				{
					checkValid = checkTrainIDValid(deleteTrainID);

					while (checkValid != 1)
					{
						printf("\nInvalid trainID, refer to table above.\n");
						printf("Enter a train ID to delete that schedule: ");
						rewind(stdin);
						scanf("%s", deleteTrainID);
						checkValid = checkTrainIDValid(deleteTrainID);
					}

					for (i = 0; i < STRUCTCOUNT; i++)
					{
						if (strcmp(schedule[i].trainID, deleteTrainID) == 0)
						{
							printf("Confirm? (Y/N) > ");
							rewind(stdin);
							scanf("%c", &confirmation);
							while (confirmation != 'Y' && confirmation != 'y' && confirmation != 'N' && confirmation != 'n')
							{
								system("cls");
								printf("Invalid Action. Try again.\n");
								printf("Confirm? (Y/N) > ");
								rewind(stdin);
								scanf("%c", &confirmation);
							}
							if (confirmation == 'Y' || confirmation == 'y')
							{
								for (int j = i; j < STRUCTCOUNT; j++)
								{
									{
										schedule[j] = schedule[j + 1];
									}
								}
								system("cls");
								printf("Schedule successfully deleted.\n");
								Sleep(1000);
							}
							else if (confirmation == 'N' || confirmation == 'n')
							{
								system("cls");
								printf("Action Discard.\n");
								printf("Returning back...\n");
								Sleep(1500);
							}
						}
					}
				}
			break;

		case 2:
			system("cls");
			printf("Returning to last page...");
			Sleep(600);
			break;
		default:
			system("cls");
			printf("Invalid value. Try again.\n");
			Sleep(600);
			break;
		}
	} while (continueOrNo != 2);
}

// Check Valid ID for delete
int checkTrainIDValid(char deleteID[10])
{
	for (int i = 0; i < STRUCTCOUNT; i++)
	{
		if (strcmp(schedule[i].trainID, deleteID) == 0)
			return 1;
	}
}

// Reset module
void ResetSchedule(void)
{
	int selection;
	char resetConfirmation;
	char resetDay[15];

	system("cls");
	printf("[Schedule Reset System]\n");
	printf("=======================\n");
	// Admin Enter Password ?

	do
	{
		printf("\nSelect a day to reset the schedule.\n");
		printf("Notes: Keep in mind that only reset for the day that've passed.\n");
		selection = daySelection();
		system("cls");
		switch (selection)
		{
		case 1:
			printf("\n\nYou're about to reset schedule for Monday.\n");
			printf("Confirm? (Y/N) > ");
			rewind(stdin);
			scanf("%c", &resetConfirmation);
			while (resetConfirmation != 'Y' && resetConfirmation != 'y' && resetConfirmation != 'N' && resetConfirmation != 'n')
			{
				printf("Invalid command. Try Again.\n");
				printf("\n\nYou're about to reset schedule for Monday.\n");
				printf("Confirm? (Y/N) > ");
				rewind(stdin);
				scanf("%c", &resetConfirmation);
			}
			if (resetConfirmation == 'y' || resetConfirmation == 'Y')
			{
				strcpy(resetDay, "Monday");
				ResetScheduleIIWeekday(resetDay);
			}
			else if (resetConfirmation == 'n' || resetConfirmation == 'N')
			{
				system("cls");
				printf("Change Discard.\n");
				Sleep(1000);
			}
			break;
		case 2:
			printf("You're about to reset schedule for Tuesday.\n");
			printf("\n\nYou're about to reset schedule for Tuesday.\n");
			printf("Confirm? (Y/N) > ");
			rewind(stdin);
			scanf("%c", &resetConfirmation);
			while (resetConfirmation != 'Y' && resetConfirmation != 'y' && resetConfirmation != 'N' && resetConfirmation != 'n')
			{
				printf("Invalid command. Try Again.\n");
				printf("\n\nYou're about to reset schedule for Tuesday.\n");
				printf("Confirm? (Y/N) > ");
				rewind(stdin);
				scanf("%c", &resetConfirmation);
			}
			if (resetConfirmation == 'y' || resetConfirmation == 'Y')
			{
				strcpy(resetDay, "Tuesday");
				ResetScheduleIIWeekday(resetDay);
			}
			else if (resetConfirmation == 'n' || resetConfirmation == 'N')
			{
				system("cls");
				printf("Change Discard.\n");
				Sleep(1000);
			}
			break;
		case 3:
			printf("You're about to reset schedule for Wednesday.\n");
			printf("\n\nYou're about to reset schedule for Wednesday.\n");
			printf("Confirm? (Y/N) > ");
			rewind(stdin);
			scanf("%c", &resetConfirmation);
			while (resetConfirmation != 'Y' && resetConfirmation != 'y' && resetConfirmation != 'N' && resetConfirmation != 'n')
			{
				printf("Invalid command. Try Again.\n");
				printf("\n\nYou're about to reset schedule for Wednesday.\n");
				printf("Confirm? (Y/N) > ");
				rewind(stdin);
				scanf("%c", &resetConfirmation);
			}
			if (resetConfirmation == 'y' || resetConfirmation == 'Y')
			{
				strcpy(resetDay, "Wednesday");
				ResetScheduleIIWeekday(resetDay);
			}
			else if (resetConfirmation == 'n' || resetConfirmation == 'N')
			{
				system("cls");
				printf("Change Discard.\n");
				Sleep(1000);
			}
			break;
		case 4:
			printf("You're about to reset schedule for Thursday.\n");
			printf("\n\nYou're about to reset schedule for Thursday.\n");
			printf("Confirm? (Y/N) > ");
			rewind(stdin);
			scanf("%c", &resetConfirmation);
			while (resetConfirmation != 'Y' && resetConfirmation != 'y' && resetConfirmation != 'N' && resetConfirmation != 'n')
			{
				printf("Invalid command. Try Again.\n");
				printf("\n\nYou're about to reset schedule for Thursday.\n");
				printf("Confirm? (Y/N) > ");
				rewind(stdin);
				scanf("%c", &resetConfirmation);
			}
			if (resetConfirmation == 'y' || resetConfirmation == 'Y')
			{
				strcpy(resetDay, "Thursday");
				ResetScheduleIIWeekday(resetDay);
			}
			else if (resetConfirmation == 'n' || resetConfirmation == 'N')
			{
				system("cls");
				printf("Change Discard.\n");
				Sleep(1000);
			}
			break;
		case 5:
			printf("You're about to reset schedule for Friday.\n");
			printf("\n\nYou're about to reset schedule for Friday.\n");
			printf("Confirm? (Y/N) > ");
			rewind(stdin);
			scanf("%c", &resetConfirmation);
			while (resetConfirmation != 'Y' && resetConfirmation != 'y' && resetConfirmation != 'N' && resetConfirmation != 'n')
			{
				printf("Invalid command. Try Again.\n");
				printf("\n\nYou're about to reset schedule for Friday.\n");
				printf("Confirm? (Y/N) > ");
				rewind(stdin);
				scanf("%c", &resetConfirmation);
			}
			if (resetConfirmation == 'y' || resetConfirmation == 'Y')
			{
				strcpy(resetDay, "Friday");
				ResetScheduleIIWeekday(resetDay);
			}
			else if (resetConfirmation == 'n' || resetConfirmation == 'N')
			{
				system("cls");
				printf("Change Discard.\n");
				Sleep(1000);
			}
			break;
		case 6:
			printf("You're about to reset schedule for Saturday.\n");
			printf("\n\nYou're about to reset schedule for Saturday.\n");
			printf("Confirm? (Y/N) > ");
			rewind(stdin);
			scanf("%c", &resetConfirmation);
			while (resetConfirmation != 'Y' && resetConfirmation != 'y' && resetConfirmation != 'N' && resetConfirmation != 'n')
			{
				printf("Invalid command. Try Again.\n");
				printf("\n\nYou're about to reset schedule for Saturday.\n");
				printf("Confirm? (Y/N) > ");
				rewind(stdin);
				scanf("%c", &resetConfirmation);
			}
			if (resetConfirmation == 'y' || resetConfirmation == 'Y')
			{
				strcpy(resetDay, "Saturday");
				ResetScheduleIIWeekend(resetDay);
			}
			else if (resetConfirmation == 'n' || resetConfirmation == 'N')
			{
				system("cls");
				printf("Change Discard.\n");
				Sleep(1000);
			}
			break;
		case 7:
			printf("You're about to reset schedule for Sunday.\n");
			printf("\n\nYou're about to reset schedule for Sunday.\n");
			printf("Confirm? (Y/N) > ");
			rewind(stdin);
			scanf("%c", &resetConfirmation);
			while (resetConfirmation != 'Y' && resetConfirmation != 'y' && resetConfirmation != 'N' && resetConfirmation != 'n')
			{
				printf("Invalid command. Try Again.\n");
				printf("\n\nYou're about to reset schedule for Sunday.\n");
				printf("Confirm? (Y/N) > ");
				rewind(stdin);
				scanf("%c", &resetConfirmation);
			}
			if (resetConfirmation == 'y' || resetConfirmation == 'Y')
			{
				strcpy(resetDay, "Sunday");
				ResetScheduleIIWeekend(resetDay);
			}
			else if (resetConfirmation == 'n' || resetConfirmation == 'N')
			{
				system("cls");
				printf("Change Discard.\n");
				Sleep(1000);
			}
			break;
		case 8:
			system("cls");
			printf("Returning to last page");
			Sleep(1000);
			break;
		default:
			system("cls");
			printf("Invalid value. Try Again.\n\n");
			break;
		}
	} while (selection != 8);
}

void destinationDepartAvailable(char(*destination)[20]) {
	int k = 0;
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 2; j++) {
			strcpy(*(destination + i * 2 + j), "NULL");
		}
	}
	for (int i = 0; i < STRUCTCOUNT; i++) {
			for (int j = 0; strcmp(schedule[i].destination, *(destination + j * 2 + 1)) != 0 && strcmp(schedule[i].departureFrom, *(destination + j * 2)) != 0; j++) {
				if (strcmp(*(destination + j * 2 + 1), "NULL") == 0 && strcmp(schedule[i].destination, "") != 0 && strcmp(*(destination + j * 2), "NULL") == 0 && strcmp(schedule[i].departureFrom, "") != 0) {
					strcpy(*(destination + j * 2), schedule[i].departureFrom);
					strcpy(*(destination + j *2 + 1), schedule[i].destination);
					k++;
					break;
			}
		}
	}
}

int typeDate(int* day, int* month, int* year) {
	char choice[5];
	printf("Type the year : ");
	rewind(stdin);
	scanf("%s", choice);
	*year = atoi(choice);
	do {
		printf("Type the month : ");
		rewind(stdin);
		scanf("%s", choice);
		*month = atoi(choice);
		if ((*month < 1 || *month >12) && strcmp(choice, "0") != 0)
			printf("Error, please try again.\n");
	} while ((*month < 1 || *month >12) && strcmp(choice, "0") != 0);
	do {
		printf("Type the day : ");
		rewind(stdin);
		scanf("%s", choice);
		*day = atoi(choice);
		if (*month % 2 != 0 || *month == 8) {
			if ((*day <= 0 || *day > 31) && strcmp(choice, "0") != 0)
				*day = 0;
		}
		else {
			if ((*day <= 0 || *day > 31) && strcmp(choice, "0") != 0)
				*day = 0;
		}
	} while (*day == 0);

}

int chooseTime(Info* results,  int seatleft[2]) {
	struct date temporary;
	char fromto[100][2][20], choice[2], day[2][80];
	char destination[2][20][20];
	int userChoice[2], j, k[2] = { 0, 0 }, date[2][3], followingDate[3], records[2][4][STRUCTCOUNT], timeChoice[2], trip;
	for (int k = 0; k < 2; k++) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < STRUCTCOUNT; j++) {
				records[k][i][j] = STRUCTCOUNT - 1;
			}
		}
	}
	do {
		k[0] = 0;
		printf("Select a destination\n\n");
		destinationDepartAvailable(&fromto);
		do {
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 20; j++) {
					strcpy(destination[i][j], "NULL");
				}
			}
			for (int i = 0; strcmp(fromto[i][1], "NULL") != 0; i++) {
				for (int j = 0; strcmp(destination[0][j], fromto[i][1]) != 0; j++) {
					if (strcmp(destination[0][j], "NULL") == 0) {
						printf("\t%d. %s\n", k[0] + 1, fromto[i][1]);
						strcpy(destination[0][j], fromto[i][1]);
						k[0]++;
						break;
					}
				}
			}
			printf("\t0. Return\n");
			printf("Your Choice > ");
			rewind(stdin);
			scanf("%s", choice);
		} while ((choice[0] != '0' && atoi(choice) == 0) || atoi(choice) > k[0] + 1);
		if (choice[0] == '0')
			return 0;
		userChoice[0] = atoi(choice) - 1;
		do {
			printf("Select departion : \n\n");
			k[1] = 0;
			for (int i = 0; strcmp(fromto[i][0], "NULL") != 0; i++) {
				for (int j = 0; strcmp(destination[1][j], fromto[i][0]) != 0; j++) {
					if (strcmp(destination[1][j], "NULL") == 0) {
						if (strcmp(destination[0][userChoice[0]], fromto[i][1]) == 0) {
							printf("\t%d. %s\n", k[1] + 1, fromto[i][0]);
							strcpy(destination[1][j], fromto[i][0]);
							k[1]++;
						}
						break;
					}
				}
			}
			printf("\t0. Return\n");
			printf("Your Choice > ");
			rewind(stdin);
			scanf("%s", choice);
		} while ((choice[0] != '0' && atoi(choice) == 0) || atoi(choice) > k[1] + 1);
		if (choice[0] == '0')
			return 0;
		userChoice[1] = atoi(choice) - 1;
		do {
			printf("\n\t1. One-Way.\n\t2. Round-Trip\n\n");
			printf("Your Choice > ");
			rewind(stdin);
			scanf("%s", choice);
		} while (strcmp(choice, "1") != 0 && strcmp(choice, "2") != 0);
		trip = atoi(choice);
		for (int m = 0; m < trip; m++) {
			do {
				title();
				printf("Please type the ");
					switch (m) {
					case 0:
						printf("Depart Date\n");
						break;
					case 1:
						printf("Return Date\n");
						break;
					}
				printf("============================\n\n");
				typeDate(&date[m][0], &date[m][1], &date[m][2]);
				for (j = 0; j < 14; j++) {
					countDate(j, &followingDate[0], &followingDate[1], &followingDate[2], &day[m]);
					if (followingDate[0] == date[m][0] && followingDate[1] == date[m][1] && followingDate[2] == date[m][2])
						break;
				}
				if (j == 14) {
					printf("Sorry. System are only able to show up to two weeks schedules from now.\n");
					system("pause");
				}
			} while (j == 14);
			if (j < 7)
				parSchedule(1, date[m][0], date[m][1], date[m][2], day[m], &records[m][0]);
			else
				parSchedule(2, date[m][0], date[m][1], date[m][2], day[m], &records[m][0]);
			SearchScheduleII(destination[m][userChoice[m]], &records[m][1]);
			for (int i = 0; i < 14; i++) {
				if (toMaxWeek[i].day == date[m][0] && toMaxWeek[i].month == date[m][1] && toMaxWeek[i].year == date[m][2])
					temporary = toMaxWeek[i];
			}
			title();
			printf("%-5s %-15s %-15s %-10s %-15s %-15s %s\n", "No.", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
			printf("%-5s %-15s %-15s %-10s %-15s %-15s %s\n", "===", "==============", "============", "========", "===========", "===========", "==========");
			j = 1;
			for (int k = 0; schedule[records[m][0][k]].deptArr.time.depart > 0; k++) {
				for (int l = 0; schedule[records[m][1][l]].deptArr.time.depart > 0; l++) {
					if (records[m][0][k] == records[m][1][l]) {
						temporary.time.depart = schedule[records[m][0][k]].deptArr.time.depart;
						temporary.time.arrive = schedule[records[m][0][k]].deptArr.time.arrive;
						seatleft[m] = countVacancy(schedule[records[m][0][k]].trainID, temporary, &records[m][3]);
						seatleft[m] = schedule[records[m][0][k]].seats - seatleft[m];
						int isTrue = 0;
						if (temporary.day == t.wDay && temporary.month == t.wMonth && temporary.year == t.wYear) {
							if ((int)temporary.time.depart > t.wHour) {
								if ((int)(temporary.time.depart * 100) % 100 - 30 > 0)
									isTrue = 1;
								else {
									if ((60 - (int)(temporary.time.depart * 100) % 100 - 30) > t.wMinute)
										isTrue = 1;
								}
							}
							else if ((int)temporary.time.depart == t.wHour) {
								if((int)(temporary.time.depart * 100) % 100 - 30 > t.wMinute)
									isTrue = 1;
							}
							else if ((int)temporary.time.depart == 0) {
							}
							if (((int)(temporary.time.depart * 100) % 100 - 30 > t.wMinute && temporary.time.depart == t.wHour) || ((int)temporary.time.depart == 0 && (int)(temporary.time.depart * 100) % 100 - 30 < 0 && t.wHour == 23 && 60 - (int)(temporary.time.depart * 100) % 100 - 30 > t.wMinute)) {
								isTrue = 1;
							}
						}
						else {
							isTrue = 1;
						}
						if (seatleft[m] > 0 && isTrue == 1) {
							printf("%-5d %-15.2f %-15.2f %-10s %-15s %-15s ", j, schedule[records[m][0][k]].deptArr.time.depart, schedule[records[m][0][k]].deptArr.time.arrive, schedule[records[m][0][k]].trainID, schedule[records[m][0][k]].departureFrom, schedule[records[m][0][k]].destination);
							printf("%d\n", seatleft[m]);
							records[m][3][j - 1] = records[m][0][k];
							j++;
						}
					}
				}
			}
			printf("\n\n");
			if (j == 1) {
					title();
					printf("Train towards %s are not available in %0d/%02d/%d. Please choose again.\n", destination[m][userChoice[m]], date[m][0], date[m][1], date[m][2]);
					system("pause");
			}
			else {
				do {
					printf("Which time you are prefered ? \n");
					printf("Your Choice > ");
					scanf("%s", choice);
				} while (atoi(choice) >= j || atoi(choice) == 0);
				timeChoice[m] = atoi(choice) - 1;
				strcpy((*(results + m * MAX_PAX)).departFrom, schedule[records[m][3][timeChoice[m]]].departureFrom);
				strcpy((*(results + m * MAX_PAX)).destination, schedule[records[m][3][timeChoice[m]]].destination);
				strcpy((*(results + m * MAX_PAX)).trainId, schedule[records[m][3][timeChoice[m]]].trainID);
				strcpy((*(results + m * MAX_PAX)).prefer.weekday, day[m]);
				(*(results + m * MAX_PAX)).prefer.day = date[m][0];
				(*(results + m * MAX_PAX)).prefer.month = date[m][1];
				(*(results + m * MAX_PAX)).prefer.year = date[m][2];
				(*(results + m * MAX_PAX)).price = schedule[records[m][3][timeChoice[m]]].price;
				(*(results + m * MAX_PAX)).prefer.time.depart = schedule[records[m][3][timeChoice[m]]].deptArr.time.depart;
				(*(results + m * MAX_PAX)).prefer.time.arrive = schedule[records[m][3][timeChoice[m]]].deptArr.time.arrive;
			}
		}
		} while (j == 1);
		return trip;
}

int scheduleMain(int identity) {

	char menuChoice;
	do {
		title();
		if (identity == 1)
			alert();
		printf("-----------------------------------------------------------------------------------------\n");
		printf("SCHEDULE: \n");
		printf("-----------------------------------------------------------------------------------------\n");
		printf("\nWhat you want to do? \n");
		printf("1. | Display Schedule\n");
		printf("2. | Search Schedule\n");
		if (identity == 1) {
			printf("3. | Add Schedule\n");
			printf("4. | Modify Schedule\n");
			printf("5. | Delete Schedule\n");
		}
		printf("0. | Return to Main Menu\n");
		printf("Choose One > ");
		rewind(stdin);
		scanf("%c", &menuChoice);

		switch (menuChoice)
		{
		case '1':
			DisplaySchedule();
			break;
		case '2':
			SearchSchedule();
			break;

		case '0':
			printf("Returning to Main Menu\n");
			return;
			break;

		default:
			if (identity != 1) {
				system("cls");
				printf("Invalid value.\n");
				printf("Enter Again.\n\n");
				Sleep(1000);
			}
		}
		if (identity == 1) {
			switch (menuChoice)
			{
			case '3':
				AddSchedule();
				break;
			case '4':
				ModifySchedule();
				break;
			case '5':
				DeleteSchedule();
				break;
			default:
				system("cls");
				printf("Invalid value.\n");
				printf("Enter Again.\n\n");
				Sleep(1000);
			}
		}

	} while (menuChoice != '0');
}
// End. Scheduling Module By Lee Ka Qin