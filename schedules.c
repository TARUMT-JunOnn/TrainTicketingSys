#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#pragma warning(disable:4996)

void DisplayCurrentTime()
{
	time_t currentTime;
	char* currentTimeInString;

	// Get current system time
	currentTime = time(NULL);

	// Check if time was sucessfully retrieved
	if (currentTime == ((time_t)-1))
	{
		printf("Failed to get the current time.\n");
	}
	else
	{
		// Convert retrieved time to string
		currentTimeInString = ctime(&currentTime);

		// Check if time was successfully converted to string
		if (currentTimeInString == NULL)
		{
			printf("Failed to convert the current time.\n");
		}
		else
		{
			printf("\nCurrent time: %s", currentTimeInString);
		}
	}
}

void DisplayTrainSchedule()
{
	FILE* fp;
	char day[8], trainID[6], depart[20], destination[20];
	int seats;
	float timeFrom, timeTo;

	fp = fopen("../TrainTicketingSys/res/shcedule.txt", "r");
	if (fp == NULL)
	{
		printf("failed");
		exit(-1);
	}

	// Weekday Schedule
	printf("\nWeekday (Mon-Fri) Schedule: \n");
	printf("--------------------------------------------------------------------------------\n");
	printf("From\t To\t TrainID\t Depart From\t Destination\t Seats Available\n");
	printf("--------------------------------------------------------------------------------\n");
	while (fscanf(fp, "%s %f %f %s %[^\:]:%[^\#]#%d", &day, &timeFrom, &timeTo, trainID, depart, destination, &seats) != EOF)
	{
		if (strcmp(day, "Weekday") == 0)
		{
			printf("%.2f\t %.2f\t %-7s\t %-15s %-15s %d\n", timeFrom, timeTo, trainID, depart, destination, seats);
		}
	}
	fclose(fp);

	// Weekend Schedule
	fp = fopen("../TrainTicketingSys/res/shcedule.txt", "r");
	printf("\n\nWeekend (Sat-Sun) Schedule: \n");
	printf("--------------------------------------------------------------------------------\n");
	printf("From\t To\t TrainID\t Depart From\t Destination\t Seats Available\n");
	printf("--------------------------------------------------------------------------------\n");
	while (fscanf(fp, "%s %f %f %s %[^\:]:%[^\#]#%d", &day, &timeFrom, &timeTo, trainID, depart, destination, &seats) != EOF)
	{
		if (strcmp(day, "Weekend") == 0)
		{
			printf("%.2f\t %.2f\t %-7s\t %-15s %-15s %d\n", timeFrom, timeTo, trainID, depart, destination, seats);
		}
	}
	fclose(fp);
}

void SearchTrainSchedule()
{
	time_t now;
	struct tm* cur_time;
	char s[100];
	char dayOfWeek[8];

	time(&now);
	cur_time = localtime(&now);
	strftime(s, 100, "%A", cur_time);
	printf("\nToday's date: %d-%02d-%02d\n", cur_time->tm_year + 1900, cur_time->tm_mon + 1, cur_time->tm_mday);
	printf("%s\n\n", s);

	// Begin searching
	struct tm future_date = {0};

	rewind(stdin);
	printf("Enter the date you want to search by following sequence.\n");
	printf("1. Year : ");
	scanf("%d", &future_date.tm_year);
	printf("2. Month: ");
	rewind(stdin);
	scanf("%d", &future_date.tm_mon);
	printf("3. Day  : ");
	rewind(stdin);
	scanf("%d", &future_date.tm_mday);

	// for checking purpose (remember delete lol)
	printf("%d/%d/%d", future_date.tm_year, future_date.tm_mon, future_date.tm_mday);
	future_date.tm_year -= 1900;
	future_date.tm_mon -= 1;
	future_date.tm_mday += 1;

	// Convert to time_t;
	time_t future_time = mktime(&future_date);

	// Calculate the differences (in seconds)
	double difference_seconds = difftime(future_time, now);

	// Convert it
	int difference_days = difference_seconds / (60 * 60 * 24);

	// Output the difference
	printf("\nDifference between today and future date: %d days\n", difference_days);
}

void ModifyTrainSchedule()
{

}

main() 
{
	DisplayCurrentTime();
	DisplayTrainSchedule();
	SearchTrainSchedule();
	system("pause");
}