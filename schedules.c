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

void ModifyTrainSchedule()
{

}

main() 
{
	DisplayCurrentTime();
	DisplayTrainSchedule();
	system("pause");
}