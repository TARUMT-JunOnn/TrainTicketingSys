#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#pragma warning(disable:4996)
#define STRUCTCOUNT 100
#define THISYEAR 2024

typedef struct
{
	float departureTime, arrivalTime;
}DeptArr;

typedef struct
{
	char day[20], trainID[6], departureFrom[13], destination[13];
	DeptArr deptArr;
	int seats;
}Schedule;
Schedule schedule[STRUCTCOUNT];

void month_day(int year, int yearday, int* pmonth, int* pday);
void DisplaySchedule(void);
void ModifySchedule(void);
void AddSchedule(void);
void SearchSchedule(void);

main()
{
	int menuChoice;
	time_t currentTime;
	char* currentTimeInString;

	currentTime = time(NULL);

	// Read text file into array
	rewind(stdin);
	FILE* fp;
	fp = fopen("../TrainTicketingSys/res/schedule.txt", "r");
	while (fp == NULL)
	{
		printf("Failed to read the file");
		exit(-1);
	}
	int i = 0;
	while (fscanf(fp, "%s %f %f %[^|]|%[^|]|%[^|]|%d\n", schedule[i].day, &schedule[i].deptArr.departureTime, &schedule[i].deptArr.arrivalTime, schedule[i].trainID, schedule[i].departureFrom, schedule[i].destination, &schedule[i].seats) != EOF)
	{
		i++;
	}
	fclose(fp);


	do
	{
		system("cls");
		if (currentTime == ((time_t)-1))
		{
			printf("Failed to get the current time.\n");
		}
		else
		{
			currentTimeInString = ctime(&currentTime);
			if (currentTimeInString == NULL)
			{
				printf("Failed to convert the current time.\n");
			}
			else
			{
				printf("Current time: %s", currentTimeInString);
			}
		}
		printf("-----------------------------------------------------------------------------------------\n");
		printf("SCHEDULE: \n");
		printf("-----------------------------------------------------------------------------------------\n");
		printf("\nWhat you want to do? \n");
		printf("1. | Display Schedule\n");
		printf("2. | Modify Schedule\n");
		printf("3. | Add Schedule\n");
		printf("4. | Search Schedule\n");
		printf("5. | Return to Main Menu\n");
		printf("Choose One > ");
		rewind(stdin);
		scanf("%d", &menuChoice);

		switch (menuChoice)
		{
		case 1:
			DisplaySchedule();
			break;

		case 2:
			ModifySchedule(currentTime);
			break;

		case 3:
			AddSchedule();
			break;

		case 4:
			SearchSchedule();
			break;

		case 5:
			printf("Returning to Main Menu\n");
			break;

		default:
			system("cls");
			printf("Invalid value.\n");
			printf("Enter Again.\n\n");
			Sleep(1000);
		}
	} while (menuChoice != 5);
}

// Display schedule module
void DisplaySchedule(void)
{
	int counter = 0;
	int choice;
	time_t timer;
	struct tm* now;
	char s[80];
	int month, day;

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
			time(&timer);
			now = localtime(&timer);
			system("cls");
			// All Schedule
			printf("-------------------------------------------------------------------------------------------------------\n");
			printf("This Week Schedule: \n");
			printf("-------------------------------------------------------------------------------------------------------\n");
			month_day(THISYEAR, (now->tm_yday), &month, &day);
			printf("Date: %d/%d/%d\n", day, month, THISYEAR);
			now->tm_mday = day;
			now->tm_mon = month - 1;
			now->tm_year = THISYEAR - 1900;
			mktime(now);
			strftime(s, 80, "%A", now);
			printf("%s:\n", s);
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
			for (counter = 0; counter < STRUCTCOUNT; counter++)
			{
				if (strcmp(schedule[counter].day, s) == 0)
				{
					printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[counter].deptArr.departureTime, schedule[counter].deptArr.arrivalTime, schedule[counter].trainID, schedule[counter].departureFrom, schedule[counter].destination, schedule[counter].seats);
				}
			}
			printf("\n-------------------------------------------------------------------------------------------------------\n");
			for (int j = 0; j < 6; j++)
			{
				month_day(THISYEAR, (now->tm_yday) + 1, &month, &day);
				printf("Date: %d/%d/%d\n", day, month, THISYEAR);
				now->tm_mday = day;
				now->tm_mon = month - 1;
				now->tm_year = THISYEAR - 1900;
				mktime(now);
				strftime(s, 80, "%A", now);
				printf("%s:\n", s);
				printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
				printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
				for (counter = 0; counter < STRUCTCOUNT; counter++)
				{
					if (strcmp(schedule[counter].day, s) == 0)
					{
						printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[counter].deptArr.departureTime, schedule[counter].deptArr.arrivalTime, schedule[counter].trainID, schedule[counter].departureFrom, schedule[counter].destination, schedule[counter].seats);
					}
				}
				printf("\n-------------------------------------------------------------------------------------------------------\n");
			}

			printf("Next Week Schedule: \n");
			printf("-------------------------------------------------------------------------------------------------------\n");
			for (int j = 0; j < 7; j++)
			{
				month_day(THISYEAR, (now->tm_yday) + 1, &month, &day);
				printf("Date: %d/%d/%d\n", day, month, THISYEAR);
				now->tm_mday = day;
				now->tm_mon = month - 1;
				now->tm_year = THISYEAR - 1900;
				mktime(now);
				strftime(s, 80, "%A", now);
				if (strcmp(s, "Monday") == 0)
				{
					strcpy(s, "NextMonday");
					printf("Next Monday:\n");
				}
				else if (strcmp(s, "Tuesday") == 0)
				{
					strcpy(s, "NextTuesday");
					printf("Next Tueday:\n");
				}
				else if (strcmp(s, "Wednesday") == 0)
				{
					strcpy(s, "NextWednesday");
					printf("Next Wednesday:\n");
				}
				else if (strcmp(s, "Thursday") == 0)
				{
					strcpy(s, "NextThursday");
					printf("Next Thursday:\n");
				}
				else if (strcmp(s, "Friday") == 0)
				{
					strcpy(s, "NextFriday");
					printf("Next Friday:\n");
				}
				else if (strcmp(s, "Saturday") == 0)
				{
					strcpy(s, "NextSaturday");
					printf("Next Saturday:\n");
				}
				else if (strcmp(s, "Sunday") == 0)
				{
					strcpy(s, "NextSunday");
					printf("Next Sunday:\n");
				}
				printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
				printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
				for (counter = 0; counter < STRUCTCOUNT; counter++)
				{
					if (strcmp(schedule[counter].day, s) == 0)
					{
						printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[counter].deptArr.departureTime, schedule[counter].deptArr.arrivalTime, schedule[counter].trainID, schedule[counter].departureFrom, schedule[counter].destination, schedule[counter].seats);
					}
				}
				printf("\n-------------------------------------------------------------------------------------------------------\n");
			}
			break;

		case 1:
			// Monday
			time(&timer);
			now = localtime(&timer);
			system("cls");
			printf("-------------------------------------------------------------------------------------------------------\n");
			month_day(THISYEAR, (now->tm_yday), &month, &day);
			now->tm_mday = day;
			now->tm_mon = month - 1;
			now->tm_year = THISYEAR - 1900;
			mktime(now);
			strftime(s, 80, "%A", now);
			if (strcmp(s, "Monday") == 0)
			{
				printf("Date:%d/%d/%d\n", day, month, THISYEAR);
				printf("%s:\n", s);
			}
			else
			{
				for (int j = 0; j < 6; j++)
				{
					month_day(THISYEAR, (now->tm_yday) + 1, &month, &day);
					now->tm_mday = day;
					now->tm_mon = month - 1;
					now->tm_year = THISYEAR - 1900;
					mktime(now);
					strftime(s, 80, "%A", now);
					if (strcmp(s, "Monday") == 0)
					{
						printf("Date:%d/%d/%d\n", day, month, THISYEAR);
						printf("%s:\n", s);
					}
				}
			}
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
			for (counter = 0; counter < STRUCTCOUNT; counter++)
			{
				if (strcmp(schedule[counter].day, s) == 0)
				{
					printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[counter].deptArr.departureTime, schedule[counter].deptArr.arrivalTime, schedule[counter].trainID, schedule[counter].departureFrom, schedule[counter].destination, schedule[counter].seats);
				}
			}
			printf("\n");
			for (int j = 0; j < 7; j++)
			{
				month_day(THISYEAR, (now->tm_yday) + 1, &month, &day);
				now->tm_mday = day;
				now->tm_mon = month - 1;
				now->tm_year = THISYEAR - 1900;
				mktime(now);
				strftime(s, 80, "%A", now);
				if (strcmp(s, "Monday") == 0)
				{
					printf("Date:%d/%d/%d\n", day, month, THISYEAR);
					printf("Next Monday:\n");
					strcpy(s, "NextMonday");
				}
			}
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
			for (counter = 0; counter < STRUCTCOUNT; counter++)
			{
				if (strcmp(schedule[counter].day, s) == 0)
				{
					printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[counter].deptArr.departureTime, schedule[counter].deptArr.arrivalTime, schedule[counter].trainID, schedule[counter].departureFrom, schedule[counter].destination, schedule[counter].seats);
				}
			}
			printf("-------------------------------------------------------------------------------------------------------\n");
			break;

		case 2:
			// Tuesday
			time(&timer);
			now = localtime(&timer);
			system("cls");
			printf("-------------------------------------------------------------------------------------------------------\n");
			month_day(THISYEAR, (now->tm_yday), &month, &day);
			now->tm_mday = day;
			now->tm_mon = month - 1;
			now->tm_year = THISYEAR - 1900;
			mktime(now);
			strftime(s, 80, "%A", now);
			if (strcmp(s, "Tuesday") == 0)
			{
				printf("Date: %d/%d/%d\n", day, month, THISYEAR);
				printf("%s:\n", s);
			}
			else
			{
				for (int j = 0; j < 6; j++)
				{
					month_day(THISYEAR, (now->tm_yday) + 1, &month, &day);
					now->tm_mday = day;
					now->tm_mon = month - 1;
					now->tm_year = THISYEAR - 1900;
					mktime(now);
					strftime(s, 80, "%A", now);
					if (strcmp(s, "Tuesday") == 0)
					{
						printf("Date:%d/%d/%d\n", day, month, THISYEAR);
						printf("%s:\n", s);
					}
				}
			}
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
			for (counter = 0; counter < STRUCTCOUNT; counter++)
			{
				if (strcmp(schedule[counter].day, "Tuesday") == 0)
				{
					printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[counter].deptArr.departureTime, schedule[counter].deptArr.arrivalTime, schedule[counter].trainID, schedule[counter].departureFrom, schedule[counter].destination, schedule[counter].seats);
				}
			}
			printf("\n");
			for (int j = 0; j < 7; j++)
			{
				month_day(THISYEAR, (now->tm_yday) + 1, &month, &day);
				now->tm_mday = day;
				now->tm_mon = month - 1;
				now->tm_year = THISYEAR - 1900;
				mktime(now);
				strftime(s, 80, "%A", now);
				if (strcmp(s, "Tuesday") == 0)
				{
					printf("Date:%d/%d/%d\n", day, month, THISYEAR);
					printf("Next Tuesday:\n");
					strcpy(s, "NextTuesday");
				}
			}
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
			for (counter = 0; counter < STRUCTCOUNT; counter++)
			{
				if (strcmp(schedule[counter].day, "NextTuesday") == 0)
				{
					printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[counter].deptArr.departureTime, schedule[counter].deptArr.arrivalTime, schedule[counter].trainID, schedule[counter].departureFrom, schedule[counter].destination, schedule[counter].seats);
				}
			}
			printf("-------------------------------------------------------------------------------------------------------\n");
			break;

		case 3:
			// Wednesday
			time(&timer);
			now = localtime(&timer);
			system("cls");
			printf("-------------------------------------------------------------------------------------------------------\n");
			month_day(THISYEAR, (now->tm_yday), &month, &day);
			now->tm_mday = day;
			now->tm_mon = month - 1;
			now->tm_year = THISYEAR - 1900;
			mktime(now);
			strftime(s, 80, "%A", now);
			if (strcmp(s, "Wednesday") == 0)
			{
				printf("Date: %d/%d/%d\n", day, month, THISYEAR);
				printf("%s:\n", s);
			}
			else
			{
				for (int j = 0; j < 6; j++)
				{
					month_day(THISYEAR, (now->tm_yday) + 1, &month, &day);
					now->tm_mday = day;
					now->tm_mon = month - 1;
					now->tm_year = THISYEAR - 1900;
					mktime(now);
					strftime(s, 80, "%A", now);
					if (strcmp(s, "Wednesday") == 0)
					{
						printf("Date:%d/%d/%d\n", day, month, THISYEAR);
						printf("%s:\n", s);
					}
				}
			}
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
			for (counter = 0; counter < STRUCTCOUNT; counter++)
			{
				if (strcmp(schedule[counter].day, "Wednesday") == 0)
				{
					printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[counter].deptArr.departureTime, schedule[counter].deptArr.arrivalTime, schedule[counter].trainID, schedule[counter].departureFrom, schedule[counter].destination, schedule[counter].seats);
				}
			}
			printf("\n");
			for (int j = 0; j < 7; j++)
			{
				month_day(THISYEAR, (now->tm_yday) + 1, &month, &day);
				now->tm_mday = day;
				now->tm_mon = month - 1;
				now->tm_year = THISYEAR - 1900;
				mktime(now);
				strftime(s, 80, "%A", now);
				if (strcmp(s, "Wednesday") == 0)
				{
					printf("Date:%d/%d/%d\n", day, month, THISYEAR);
					printf("Next Wednesday:\n");
					strcpy(s, "NextWednesday");
				}
			}
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
			for (counter = 0; counter < STRUCTCOUNT; counter++)
			{
				if (strcmp(schedule[counter].day, "NextWednesday") == 0)
				{
					printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[counter].deptArr.departureTime, schedule[counter].deptArr.arrivalTime, schedule[counter].trainID, schedule[counter].departureFrom, schedule[counter].destination, schedule[counter].seats);
				}
			}
			printf("-------------------------------------------------------------------------------------------------------\n");
			break;

		case 4:
			// Thursday
			time(&timer);
			now = localtime(&timer);
			system("cls");
			printf("-------------------------------------------------------------------------------------------------------\n");
			month_day(THISYEAR, (now->tm_yday), &month, &day);
			now->tm_mday = day;
			now->tm_mon = month - 1;
			now->tm_year = THISYEAR - 1900;
			mktime(now);
			strftime(s, 80, "%A", now);
			if (strcmp(s, "Thursday") == 0)
			{
				printf("Date: %d/%d/%d\n", day, month, THISYEAR);
				printf("%s:\n", s);
			}
			else
			{
				for (int j = 0; j < 6; j++)
				{
					month_day(THISYEAR, (now->tm_yday) + 1, &month, &day);
					now->tm_mday = day;
					now->tm_mon = month - 1;
					now->tm_year = THISYEAR - 1900;
					mktime(now);
					strftime(s, 80, "%A", now);
					if (strcmp(s, "Thursday") == 0)
					{
						printf("Date:%d/%d/%d\n", day, month, THISYEAR);
						printf("%s:\n", s);
					}
				}
			}
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
			for (counter = 0; counter < STRUCTCOUNT; counter++)
			{
				if (strcmp(schedule[counter].day, "Thursday") == 0)
				{
					printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[counter].deptArr.departureTime, schedule[counter].deptArr.arrivalTime, schedule[counter].trainID, schedule[counter].departureFrom, schedule[counter].destination, schedule[counter].seats);
				}
			}
			printf("\n");
			for (int j = 0; j < 7; j++)
			{
				month_day(THISYEAR, (now->tm_yday) + 1, &month, &day);
				now->tm_mday = day;
				now->tm_mon = month - 1;
				now->tm_year = THISYEAR - 1900;
				mktime(now);
				strftime(s, 80, "%A", now);
				if (strcmp(s, "Thursday") == 0)
				{
					printf("Date:%d/%d/%d\n", day, month, THISYEAR);
					printf("Next Thursday:\n");
					strcpy(s, "NextThursday");
				}
			}
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
			for (counter = 0; counter < STRUCTCOUNT; counter++)
			{
				if (strcmp(schedule[counter].day, "NextThursday") == 0)
				{
					printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[counter].deptArr.departureTime, schedule[counter].deptArr.arrivalTime, schedule[counter].trainID, schedule[counter].departureFrom, schedule[counter].destination, schedule[counter].seats);
				}
			}
			printf("-------------------------------------------------------------------------------------------------------\n");
			break;

		case 5:
			// Friday
			time(&timer);
			now = localtime(&timer);
			system("cls");
			printf("-------------------------------------------------------------------------------------------------------\n");
			month_day(THISYEAR, (now->tm_yday), &month, &day);
			now->tm_mday = day;
			now->tm_mon = month - 1;
			now->tm_year = THISYEAR - 1900;
			mktime(now);
			strftime(s, 80, "%A", now);
			if (strcmp(s, "Friday") == 0)
			{
				printf("Date: %d/%d/%d\n", day, month, THISYEAR);
				printf("%s:\n", s);
			}
			else
			{
				for (int j = 0; j < 6; j++)
				{
					month_day(THISYEAR, (now->tm_yday) + 1, &month, &day);
					now->tm_mday = day;
					now->tm_mon = month - 1;
					now->tm_year = THISYEAR - 1900;
					mktime(now);
					strftime(s, 80, "%A", now);
					if (strcmp(s, "Friday") == 0)
					{
						printf("Date:%d/%d/%d\n", day, month, THISYEAR);
						printf("%s:\n", s);
					}
				}
			}
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
			for (counter = 0; counter < STRUCTCOUNT; counter++)
			{
				if (strcmp(schedule[counter].day, "Friday") == 0)
				{
					printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[counter].deptArr.departureTime, schedule[counter].deptArr.arrivalTime, schedule[counter].trainID, schedule[counter].departureFrom, schedule[counter].destination, schedule[counter].seats);
				}
			}
			printf("\n");
			for (int j = 0; j < 7; j++)
			{
				month_day(THISYEAR, (now->tm_yday) + 1, &month, &day);
				now->tm_mday = day;
				now->tm_mon = month - 1;
				now->tm_year = THISYEAR - 1900;
				mktime(now);
				strftime(s, 80, "%A", now);
				if (strcmp(s, "Friday") == 0)
				{
					printf("Date:%d/%d/%d\n", day, month, THISYEAR);
					printf("Next Friday:\n");
					strcpy(s, "NextFriday");
				}
			}
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
			for (counter = 0; counter < STRUCTCOUNT; counter++)
			{
				if (strcmp(schedule[counter].day, "NextFriday") == 0)
				{
					printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[counter].deptArr.departureTime, schedule[counter].deptArr.arrivalTime, schedule[counter].trainID, schedule[counter].departureFrom, schedule[counter].destination, schedule[counter].seats);
				}
			}
			printf("-------------------------------------------------------------------------------------------------------\n");
			break;

		case 6:
			// Saturday
			time(&timer);
			now = localtime(&timer);
			system("cls");
			printf("-------------------------------------------------------------------------------------------------------\n");
			month_day(THISYEAR, (now->tm_yday), &month, &day);
			now->tm_mday = day;
			now->tm_mon = month - 1;
			now->tm_year = THISYEAR - 1900;
			mktime(now);
			strftime(s, 80, "%A", now);
			if (strcmp(s, "Saturday") == 0)
			{
				printf("Date: %d/%d/%d\n", day, month, THISYEAR);
				printf("%s:\n", s);
			}
			else
			{
				for (int j = 0; j < 6; j++)
				{
					month_day(THISYEAR, (now->tm_yday) + 1, &month, &day);
					now->tm_mday = day;
					now->tm_mon = month - 1;
					now->tm_year = THISYEAR - 1900;
					mktime(now);
					strftime(s, 80, "%A", now);
					if (strcmp(s, "Saturday") == 0)
					{
						printf("Date:%d/%d/%d\n", day, month, THISYEAR);
						printf("%s:\n", s);
					}
				}
			}
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
			for (counter = 0; counter < STRUCTCOUNT; counter++)
			{
				if (strcmp(schedule[counter].day, "Saturday") == 0)
				{
					printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[counter].deptArr.departureTime, schedule[counter].deptArr.arrivalTime, schedule[counter].trainID, schedule[counter].departureFrom, schedule[counter].destination, schedule[counter].seats);
				}
			}
			printf("\n");
			for (int j = 0; j < 7; j++)
			{
				month_day(THISYEAR, (now->tm_yday) + 1, &month, &day);
				now->tm_mday = day;
				now->tm_mon = month - 1;
				now->tm_year = THISYEAR - 1900;
				mktime(now);
				strftime(s, 80, "%A", now);
				if (strcmp(s, "Saturday") == 0)
				{
					printf("Date:%d/%d/%d\n", day, month, THISYEAR);
					printf("Next Saturday:\n");
					strcpy(s, "NextSaturday");
				}
			}
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
			for (counter = 0; counter < STRUCTCOUNT; counter++)
			{
				if (strcmp(schedule[counter].day, "NextSaturday") == 0)
				{
					printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[counter].deptArr.departureTime, schedule[counter].deptArr.arrivalTime, schedule[counter].trainID, schedule[counter].departureFrom, schedule[counter].destination, schedule[counter].seats);
				}
			}
			printf("-------------------------------------------------------------------------------------------------------\n");
			break;

		case 7:
			// Sunday
			time(&timer);
			now = localtime(&timer);
			system("cls");
			printf("-------------------------------------------------------------------------------------------------------\n");
			month_day(THISYEAR, (now->tm_yday), &month, &day);
			now->tm_mday = day;
			now->tm_mon = month - 1;
			now->tm_year = THISYEAR - 1900;
			mktime(now);
			strftime(s, 80, "%A", now);
			if (strcmp(s, "Sunday") == 0)
			{
				printf("Date:%d/%d/%d\n", day, month, THISYEAR);
				printf("%s:\n", s);
			}
			else
			{
				for (int j = 0; j < 6; j++)
				{
					month_day(THISYEAR, (now->tm_yday) + 1, &month, &day);
					now->tm_mday = day;
					now->tm_mon = month - 1;
					now->tm_year = THISYEAR - 1900;
					mktime(now);
					strftime(s, 80, "%A", now);
					if (strcmp(s, "Sunday") == 0)
					{
						printf("Date:%d/%d/%d\n", day, month, THISYEAR);
						printf("%s:\n", s);
					}
				}
			}
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
			for (counter = 0; counter < STRUCTCOUNT; counter++)
			{
				if (strcmp(schedule[counter].day, "Sunday") == 0)
				{
					printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[counter].deptArr.departureTime, schedule[counter].deptArr.arrivalTime, schedule[counter].trainID, schedule[counter].departureFrom, schedule[counter].destination, schedule[counter].seats);
				}
			}
			printf("\n");
			for (int j = 0; j < 7; j++)
			{
				month_day(THISYEAR, (now->tm_yday) + 1, &month, &day);
				now->tm_mday = day;
				now->tm_mon = month - 1;
				now->tm_year = THISYEAR - 1900;
				mktime(now);
				strftime(s, 80, "%A", now);
				if (strcmp(s, "Sunday") == 0)
				{
					printf("Date:%d/%d/%d\n", day, month, THISYEAR);
					printf("Next Sunday:\n");
					strcpy(s, "NextSunday");
				}
			}
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
			for (counter = 0; counter < STRUCTCOUNT; counter++)
			{
				if (strcmp(schedule[counter].day, "NextSunday") == 0)
				{
					printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[counter].deptArr.departureTime, schedule[counter].deptArr.arrivalTime, schedule[counter].trainID, schedule[counter].departureFrom, schedule[counter].destination, schedule[counter].seats);
				}
			}
			printf("-------------------------------------------------------------------------------------------------------\n");
			break;

		case 8:
			printf("\nReturn to schedule menu.\n");
			break;

		default:
			printf("Invalid value. Enter again! \n\n");
		}
	} while (choice != 8);
}

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
						default:
							system("cls");
							printf("Invalid day. Again.\n");
							break;
						}
					} while (dayChoice1 != 1 && dayChoice1 != 2 && dayChoice1 != 3 && dayChoice1 != 4 && dayChoice1 != 5 && dayChoice1 != 6 && dayChoice1 != 7);

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
								schedule[j].deptArr.departureTime = newTime1;
								schedule[j].deptArr.arrivalTime = newTime2;
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
						default:
							system("cls");
							printf("Invalid day. Again.\n");
							break;
						}
					} while (dayChoice2 != 1 && dayChoice2 != 2 && dayChoice2 != 3 && dayChoice2 != 4 && dayChoice2 != 5 && dayChoice2 != 6 && dayChoice2 != 7);

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
								schedule[k].deptArr.departureTime = newTime3;
								schedule[k].deptArr.arrivalTime = newTime4;
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

// Convert date to day
void month_day(int year, int yearday, int* pmonth, int* pday)
{
	int i;
	int leap = 0;
	int month[2][13] = { { 31,28,31,30,31,30,31,31,30,31,30,31 }, { 31,28,31,30,31,30,31,31,30,31,30,31 } };
	if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0) {
		leap = 1;
	}
	for (i = 0; yearday > month[leap][i]; ++i) {
		yearday -= month[leap][i];
	}
	*pmonth = i + 1;
	*pday = yearday;
	return 0;
}

// Add schedule module
void AddSchedule(void)
{
	printf("[Add Schedule Tool]\n");
	printf("-------------------\n");

}

// Search schedule module
void SearchSchedule(void)
{
	int choice, choice2;
	system("cls");
	do
	{
		printf("[Schedule Searching Tool]\n");
		printf("-------------------------\n");
		printf("1. | This week schedule\n");
		printf("2. | Next week schedule\n");
		printf("3. | Return to schedule menu.\n");
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
					printf("\n\nMonday");
					printf("\n-------------------------------------------------------------------------------------------------------\n");
					printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
					printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
					for (int i = 0; i < STRUCTCOUNT; i++)
					{
						if (strcmp(schedule[i].day, "Monday") == 0)
						{
							printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[i].deptArr.departureTime, schedule[i].deptArr.arrivalTime, schedule[i].trainID, schedule[i].departureFrom, schedule[i].destination, schedule[i].seats);
						}
					}
					printf("\n\n");
					break;
				case 2:
					system("cls");
					printf("\n\nTuesday");
					printf("\n-------------------------------------------------------------------------------------------------------\n");
					printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
					printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
					for (int i = 0; i < STRUCTCOUNT; i++)
					{
						if (strcmp(schedule[i].day, "Tuesday") == 0)
						{
							printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[i].deptArr.departureTime, schedule[i].deptArr.arrivalTime, schedule[i].trainID, schedule[i].departureFrom, schedule[i].destination, schedule[i].seats);
						}
					}
					printf("\n\n");
					break;
				case 3:
					system("cls");
					printf("\n\nWednesday");
					printf("\n-------------------------------------------------------------------------------------------------------\n");
					printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
					printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
					for (int i = 0; i < STRUCTCOUNT; i++)
					{
						if (strcmp(schedule[i].day, "Wednesday") == 0)
						{
							printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[i].deptArr.departureTime, schedule[i].deptArr.arrivalTime, schedule[i].trainID, schedule[i].departureFrom, schedule[i].destination, schedule[i].seats);
						}
					}
					printf("\n\n");
					break;
				case 4:
					system("cls");
					printf("\n\nThursday");
					printf("\n-------------------------------------------------------------------------------------------------------\n");
					printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
					printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
					for (int i = 0; i < STRUCTCOUNT; i++)
					{
						if (strcmp(schedule[i].day, "Thursday") == 0)
						{
							printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[i].deptArr.departureTime, schedule[i].deptArr.arrivalTime, schedule[i].trainID, schedule[i].departureFrom, schedule[i].destination, schedule[i].seats);
						}
					}
					printf("\n\n");
					break;
				case 5:
					system("cls");
					printf("\n\nFriday");
					printf("\n-------------------------------------------------------------------------------------------------------\n");
					printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
					printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
					for (int i = 0; i < STRUCTCOUNT; i++)
					{
						if (strcmp(schedule[i].day, "Friday") == 0)
						{
							printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[i].deptArr.departureTime, schedule[i].deptArr.arrivalTime, schedule[i].trainID, schedule[i].departureFrom, schedule[i].destination, schedule[i].seats);
						}
					}
					printf("\n\n");
					break;
				case 6:
					system("cls");
					printf("\n\nSaturday");
					printf("\n-------------------------------------------------------------------------------------------------------\n");
					printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
					printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
					for (int i = 0; i < STRUCTCOUNT; i++)
					{
						if (strcmp(schedule[i].day, "Saturday") == 0)
						{
							printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[i].deptArr.departureTime, schedule[i].deptArr.arrivalTime, schedule[i].trainID, schedule[i].departureFrom, schedule[i].destination, schedule[i].seats);
						}
					}
					printf("\n\n");
					break;
				case 7:
					system("cls");
					printf("\n\nSunday");
					printf("\n-------------------------------------------------------------------------------------------------------\n");
					printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
					printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
					for (int i = 0; i < STRUCTCOUNT; i++)
					{
						if (strcmp(schedule[i].day, "Sunday") == 0)
						{
							printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[i].deptArr.departureTime, schedule[i].deptArr.arrivalTime, schedule[i].trainID, schedule[i].departureFrom, schedule[i].destination, schedule[i].seats);
						}
					}
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
					printf("\n\nNext Monday");
					printf("\n-------------------------------------------------------------------------------------------------------\n");
					printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
					printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
					for (int i = 0; i < STRUCTCOUNT; i++)
					{
						if (strcmp(schedule[i].day, "NextMonday") == 0)
						{
							printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[i].deptArr.departureTime, schedule[i].deptArr.arrivalTime, schedule[i].trainID, schedule[i].departureFrom, schedule[i].destination, schedule[i].seats);
						}
					}
					printf("\n\n");
					break;
				case 2:
					system("cls");
					printf("\n\nNext Tuesday");
					printf("\n-------------------------------------------------------------------------------------------------------\n");
					printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
					printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
					for (int i = 0; i < STRUCTCOUNT; i++)
					{
						if (strcmp(schedule[i].day, "NextTuesday") == 0)
						{
							printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[i].deptArr.departureTime, schedule[i].deptArr.arrivalTime, schedule[i].trainID, schedule[i].departureFrom, schedule[i].destination, schedule[i].seats);
						}
					}
					printf("\n\n");
					break;
				case 3:
					system("cls");
					printf("\n\nNext Wednesday");
					printf("\n-------------------------------------------------------------------------------------------------------\n");
					printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
					printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
					for (int i = 0; i < STRUCTCOUNT; i++)
					{
						if (strcmp(schedule[i].day, "NextWednesday") == 0)
						{
							printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[i].deptArr.departureTime, schedule[i].deptArr.arrivalTime, schedule[i].trainID, schedule[i].departureFrom, schedule[i].destination, schedule[i].seats);
						}
					}
					printf("\n\n");
					break;
				case 4:
					system("cls");
					printf("\n\nNext Thursday");
					printf("\n-------------------------------------------------------------------------------------------------------\n");
					printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
					printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
					for (int i = 0; i < STRUCTCOUNT; i++)
					{
						if (strcmp(schedule[i].day, "NextThursday") == 0)
						{
							printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[i].deptArr.departureTime, schedule[i].deptArr.arrivalTime, schedule[i].trainID, schedule[i].departureFrom, schedule[i].destination, schedule[i].seats);
						}
					}
					printf("\n\n");
					break;
				case 5:
					system("cls");
					printf("\n\nNext Friday");
					printf("\n-------------------------------------------------------------------------------------------------------\n");
					printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
					printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
					for (int i = 0; i < STRUCTCOUNT; i++)
					{
						if (strcmp(schedule[i].day, "NextFriday") == 0)
						{
							printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[i].deptArr.departureTime, schedule[i].deptArr.arrivalTime, schedule[i].trainID, schedule[i].departureFrom, schedule[i].destination, schedule[i].seats);
						}
					}
					printf("\n\n");
					break;
				case 6:
					system("cls");
					printf("\n\nNext Saturday");
					printf("\n-------------------------------------------------------------------------------------------------------\n");
					printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
					printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
					for (int i = 0; i < STRUCTCOUNT; i++)
					{
						if (strcmp(schedule[i].day, "NextSaturday") == 0)
						{
							printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[i].deptArr.departureTime, schedule[i].deptArr.arrivalTime, schedule[i].trainID, schedule[i].departureFrom, schedule[i].destination, schedule[i].seats);
						}
					}
					printf("\n\n");
					break;
				case 7:
					system("cls");
					printf("\n\nNext Sunday");
					printf("\n-------------------------------------------------------------------------------------------------------\n");
					printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
					printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
					for (int i = 0; i < STRUCTCOUNT; i++)
					{
						if (strcmp(schedule[i].day, "NextSunday") == 0)
						{
							printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[i].deptArr.departureTime, schedule[i].deptArr.arrivalTime, schedule[i].trainID, schedule[i].departureFrom, schedule[i].destination, schedule[i].seats);
						}
					}
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
			printf("Returning to schedule menu...\n");
			Sleep(1000);
			break;
		default:
			break;
		}
	} while (choice != 3);
}