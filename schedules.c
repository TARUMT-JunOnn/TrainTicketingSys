#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#pragma warning(disable:4996)
#define STRUCTCOUNT 100


typedef struct
{
	char day[20], trainID[6], departureFrom[13], destination[13];
	float departureTime, arrivalTime;
	int seats;
}Schedule;
Schedule schedule[STRUCTCOUNT];

void DisplaySchedule(void);
void ModifySchedule(time_t currentTime);
void AddSchedule(void);
void SearchSchedule(void);

main()
{
	int menuChoice;
	time_t currentTime;
	char* currentTimeInString;

	currentTime = time(NULL);


	/*
	struct tm* cur_time = localtime(&currentTime);
	cur_time->tm_mday = cur_time->tm_mday + 1;
	time_t new_time = mktime(cur_time);
	printf("now: %ld\n", currentTime);
	printf("new time: %ld\n", new_time);

	int differences = new_time - currentTime;
	printf("Diff: %ld\n", differences);
	*/

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
	while (fscanf(fp, "%s %f %f %[^|]|%[^|]|%[^|]|%d\n", schedule[i].day, &schedule[i].departureTime, &schedule[i].arrivalTime, schedule[i].trainID, schedule[i].departureFrom, schedule[i].destination, &schedule[i].seats) != EOF)
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
			printf("Invalid value.\n");
			printf("Enter Again.\n\n");
		}
	} while (menuChoice != 5);
}

// Display schedule module
void DisplaySchedule(void)
{
	int counter = 0;
	int choice;

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
			// Monday
			printf("-------------------------------------------------------------------------------------------------------\n");
			printf("This Weekday Schedule: \n");
			printf("-------------------------------------------------------------------------------------------------------\n");
			printf("Monday: \n");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
			for (counter = 0; counter < STRUCTCOUNT; counter++)
			{
				if (strcmp(schedule[counter].day, "Monday") == 0)
				{
					printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[counter].departureTime, schedule[counter].arrivalTime, schedule[counter].trainID, schedule[counter].departureFrom, schedule[counter].destination, schedule[counter].seats);
				}
			}
			// Tuesday
			printf("\nTuesday: \n");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
			for (counter = 0; counter < STRUCTCOUNT; counter++)
			{
				if (strcmp(schedule[counter].day, "Tuesday") == 0)
				{
					printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[counter].departureTime, schedule[counter].arrivalTime, schedule[counter].trainID, schedule[counter].departureFrom, schedule[counter].destination, schedule[counter].seats);
				}
			}
			// Wednesday
			printf("\nWednesday: \n");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
			for (counter = 0; counter < STRUCTCOUNT; counter++)
			{
				if (strcmp(schedule[counter].day, "Wednesday") == 0)
				{
					printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[counter].departureTime, schedule[counter].arrivalTime, schedule[counter].trainID, schedule[counter].departureFrom, schedule[counter].destination, schedule[counter].seats);
				}
			}
			// Thursday
			printf("\nThursday: \n");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
			rewind(stdin);
			for (counter = 0; counter < STRUCTCOUNT; counter++)
			{
				if (strcmp(schedule[counter].day, "Thursday") == 0)
				{
					printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[counter].departureTime, schedule[counter].arrivalTime, schedule[counter].trainID, schedule[counter].departureFrom, schedule[counter].destination, schedule[counter].seats);
				}
			}
			// Friday
			printf("\nFriday: \n");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
			rewind(stdin);
			for (counter = 0; counter < STRUCTCOUNT; counter++)
			{
				if (strcmp(schedule[counter].day, "Friday") == 0)
				{
					printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[counter].departureTime, schedule[counter].arrivalTime, schedule[counter].trainID, schedule[counter].departureFrom, schedule[counter].destination, schedule[counter].seats);
				}
			}
			printf("-------------------------------------------------------------------------------------------------------\n");
			printf("This Weekend Schedule: \n");
			printf("-------------------------------------------------------------------------------------------------------\n");
			// Saturday
			printf("Saturday: \n");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
			rewind(stdin);
			for (counter = 0; counter < STRUCTCOUNT; counter++)
			{
				if (strcmp(schedule[counter].day, "Saturday") == 0)
				{
					printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[counter].departureTime, schedule[counter].arrivalTime, schedule[counter].trainID, schedule[counter].departureFrom, schedule[counter].destination, schedule[counter].seats);
				}
			}
			// Sunday
			printf("\nSunday: \n");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
			rewind(stdin);
			for (counter = 0; counter < STRUCTCOUNT; counter++)
			{
				if (strcmp(schedule[counter].day, "Sunday") == 0)
				{
					printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[counter].departureTime, schedule[counter].arrivalTime, schedule[counter].trainID, schedule[counter].departureFrom, schedule[counter].destination, schedule[counter].seats);
				}
			}

			// Next Week
			printf("\n-------------------------------------------------------------------------------------------------------\n");
			printf("Next Weekday Schedule: \n");
			printf("-------------------------------------------------------------------------------------------------------\n");
			printf("Monday: \n");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
			for (counter = 0; counter < STRUCTCOUNT; counter++)
			{
				if (strcmp(schedule[counter].day, "NextMonday") == 0)
				{
					printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[counter].departureTime, schedule[counter].arrivalTime, schedule[counter].trainID, schedule[counter].departureFrom, schedule[counter].destination, schedule[counter].seats);
				}
			}
			// Tuesday
			printf("\nTuesday: \n");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
			for (counter = 0; counter < STRUCTCOUNT; counter++)
			{
				if (strcmp(schedule[counter].day, "NextTuesday") == 0)
				{
					printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[counter].departureTime, schedule[counter].arrivalTime, schedule[counter].trainID, schedule[counter].departureFrom, schedule[counter].destination, schedule[counter].seats);
				}
			}
			// Wednesday
			printf("\nWednesday: \n");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
			for (counter = 0; counter < STRUCTCOUNT; counter++)
			{
				if (strcmp(schedule[counter].day, "NextWednesday") == 0)
				{
					printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[counter].departureTime, schedule[counter].arrivalTime, schedule[counter].trainID, schedule[counter].departureFrom, schedule[counter].destination, schedule[counter].seats);
				}
			}
			// Thursday
			printf("\nThursday: \n");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
			rewind(stdin);
			for (counter = 0; counter < STRUCTCOUNT; counter++)
			{
				if (strcmp(schedule[counter].day, "NextThursday") == 0)
				{
					printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[counter].departureTime, schedule[counter].arrivalTime, schedule[counter].trainID, schedule[counter].departureFrom, schedule[counter].destination, schedule[counter].seats);
				}
			}
			// Friday
			printf("\nFriday: \n");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
			rewind(stdin);
			for (counter = 0; counter < STRUCTCOUNT; counter++)
			{
				if (strcmp(schedule[counter].day, "NextFriday") == 0)
				{
					printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[counter].departureTime, schedule[counter].arrivalTime, schedule[counter].trainID, schedule[counter].departureFrom, schedule[counter].destination, schedule[counter].seats);
				}
			}
			printf("-------------------------------------------------------------------------------------------------------\n");
			printf("Next Weekend Schedule: \n");
			printf("-------------------------------------------------------------------------------------------------------\n");
			// Saturday
			printf("Saturday: \n");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
			rewind(stdin);
			for (counter = 0; counter < STRUCTCOUNT; counter++)
			{
				if (strcmp(schedule[counter].day, "NextSaturday") == 0)
				{
					printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[counter].departureTime, schedule[counter].arrivalTime, schedule[counter].trainID, schedule[counter].departureFrom, schedule[counter].destination, schedule[counter].seats);
				}
			}
			// Sunday
			printf("\nSunday: \n");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
			rewind(stdin);
			for (counter = 0; counter < STRUCTCOUNT; counter++)
			{
				if (strcmp(schedule[counter].day, "NextSunday") == 0)
				{
					printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[counter].departureTime, schedule[counter].arrivalTime, schedule[counter].trainID, schedule[counter].departureFrom, schedule[counter].destination, schedule[counter].seats);
				}
			}
			break;

		case 1:
			// Monday
			printf("-------------------------------------------------------------------------------------------------------\n");
			printf("This Monday: \n");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
			for (counter = 0; counter < 50; counter++)
			{
				if (strcmp(schedule[counter].day, "Monday") == 0)
				{
					printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[counter].departureTime, schedule[counter].arrivalTime, schedule[counter].trainID, schedule[counter].departureFrom, schedule[counter].destination, schedule[counter].seats);
				}
			}
			printf("\nNext Monday: \n");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
			for (counter = 0; counter < 50; counter++)
			{
				if (strcmp(schedule[counter].day, "NextMonday") == 0)
				{
					printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[counter].departureTime, schedule[counter].arrivalTime, schedule[counter].trainID, schedule[counter].departureFrom, schedule[counter].destination, schedule[counter].seats);
				}
			}
			printf("-------------------------------------------------------------------------------------------------------\n");
			break;

		case 2:
			// Tuesday
			printf("-------------------------------------------------------------------------------------------------------\n");
			printf("This Tuesday: \n");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
			for (counter = 0; counter < STRUCTCOUNT; counter++)
			{
				if (strcmp(schedule[counter].day, "Tuesday") == 0)
				{
					printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[counter].departureTime, schedule[counter].arrivalTime, schedule[counter].trainID, schedule[counter].departureFrom, schedule[counter].destination, schedule[counter].seats);
				}
			}
			printf("\nNext Tuesday: \n");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
			for (counter = 0; counter < STRUCTCOUNT; counter++)
			{
				if (strcmp(schedule[counter].day, "NextTuesday") == 0)
				{
					printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[counter].departureTime, schedule[counter].arrivalTime, schedule[counter].trainID, schedule[counter].departureFrom, schedule[counter].destination, schedule[counter].seats);
				}
			}
			printf("-------------------------------------------------------------------------------------------------------\n");
			break;

		case 3:
			// Wednesday
			printf("-------------------------------------------------------------------------------------------------------\n");
			printf("This Wednesday: \n");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
			for (counter = 0; counter < STRUCTCOUNT; counter++)
			{
				if (strcmp(schedule[counter].day, "Wednesday") == 0)
				{
					printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[counter].departureTime, schedule[counter].arrivalTime, schedule[counter].trainID, schedule[counter].departureFrom, schedule[counter].destination, schedule[counter].seats);
				}
			}
			printf("\nNext Wednesday: \n");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
			for (counter = 0; counter < STRUCTCOUNT; counter++)
			{
				if (strcmp(schedule[counter].day, "NextWednesday") == 0)
				{
					printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[counter].departureTime, schedule[counter].arrivalTime, schedule[counter].trainID, schedule[counter].departureFrom, schedule[counter].destination, schedule[counter].seats);
				}
			}
			printf("-------------------------------------------------------------------------------------------------------\n");
			break;

		case 4:
			// Thursday
			printf("-------------------------------------------------------------------------------------------------------\n");
			printf("This Thursday: \n");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
			rewind(stdin);
			for (counter = 0; counter < STRUCTCOUNT; counter++)
			{
				if (strcmp(schedule[counter].day, "Thursday") == 0)
				{
					printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[counter].departureTime, schedule[counter].arrivalTime, schedule[counter].trainID, schedule[counter].departureFrom, schedule[counter].destination, schedule[counter].seats);
				}
			}
			printf("\nNext Thursday: \n");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
			rewind(stdin);
			for (counter = 0; counter < STRUCTCOUNT; counter++)
			{
				if (strcmp(schedule[counter].day, "NextThursday") == 0)
				{
					printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[counter].departureTime, schedule[counter].arrivalTime, schedule[counter].trainID, schedule[counter].departureFrom, schedule[counter].destination, schedule[counter].seats);
				}
			}
			printf("-------------------------------------------------------------------------------------------------------\n");
			break;

		case 5:
			// Friday
			printf("-------------------------------------------------------------------------------------------------------\n");
			printf("This Friday: \n");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
			rewind(stdin);
			for (counter = 0; counter < STRUCTCOUNT; counter++)
			{
				if (strcmp(schedule[counter].day, "Friday") == 0)
				{
					printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[counter].departureTime, schedule[counter].arrivalTime, schedule[counter].trainID, schedule[counter].departureFrom, schedule[counter].destination, schedule[counter].seats);
				}
			}
			printf("\nNext Friday: \n");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
			rewind(stdin);
			for (counter = 0; counter < STRUCTCOUNT; counter++)
			{
				if (strcmp(schedule[counter].day, "NextFriday") == 0)
				{
					printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[counter].departureTime, schedule[counter].arrivalTime, schedule[counter].trainID, schedule[counter].departureFrom, schedule[counter].destination, schedule[counter].seats);
				}
			}
			printf("-------------------------------------------------------------------------------------------------------\n");
			break;

		case 6:
			// Saturday
			printf("-------------------------------------------------------------------------------------------------------\n");
			printf("Saturday: \n");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
			rewind(stdin);
			for (counter = 0; counter < STRUCTCOUNT; counter++)
			{
				if (strcmp(schedule[counter].day, "Saturday") == 0)
				{
					printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[counter].departureTime, schedule[counter].arrivalTime, schedule[counter].trainID, schedule[counter].departureFrom, schedule[counter].destination, schedule[counter].seats);
				}
			}
			printf("\nNext Saturday: \n");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
			rewind(stdin);
			for (counter = 0; counter < STRUCTCOUNT; counter++)
			{
				if (strcmp(schedule[counter].day, "NextSaturday") == 0)
				{
					printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[counter].departureTime, schedule[counter].arrivalTime, schedule[counter].trainID, schedule[counter].departureFrom, schedule[counter].destination, schedule[counter].seats);
				}
			}
			printf("-------------------------------------------------------------------------------------------------------\n");
			break;

		case 7:
			// Sunday
			printf("-------------------------------------------------------------------------------------------------------\n");
			printf("Sunday: \n");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
			rewind(stdin);
			for (counter = 0; counter < STRUCTCOUNT; counter++)
			{
				if (strcmp(schedule[counter].day, "Sunday") == 0)
				{
					printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[counter].departureTime, schedule[counter].arrivalTime, schedule[counter].trainID, schedule[counter].departureFrom, schedule[counter].destination, schedule[counter].seats);
				}
			}
			printf("\nNext Sunday: \n");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "Departure Time", "Arrival Time", "Train ID", "Depart From", "Destination", "Seats Left");
			printf("%-15s %-15s %-10s %-15s %-15s %s\n", "==============", "============", "========", "===========", "===========", "==========");
			rewind(stdin);
			for (counter = 0; counter < STRUCTCOUNT; counter++)
			{
				if (strcmp(schedule[counter].day, "NextSunday") == 0)
				{
					printf("%-15.2f %-15.2f %-10s %-15s %-15s %d\n", schedule[counter].departureTime, schedule[counter].arrivalTime, schedule[counter].trainID, schedule[counter].departureFrom, schedule[counter].destination, schedule[counter].seats);
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
	}while (choice != 8);
}

// Modify schedule module
void ModifySchedule(time_t currentTime) 
{
	int modifyChoice, modifyChoice1;
	char modifyDay[20], modTrainID[6];
	float newTime1, newTime2, newTime3, newTime4;
	char confirmation, confirmation2, continues;
	char continues2;

	system("cls");
	printf("[Schedule Modifier]\n");
	printf("-------------------\n");
	printf("Do you want: \n");
	printf("1. | Modify by entering day\n");
	printf("2. | Modify by entering date\n");
	printf("3. | Return to schedule menu.\n");
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
		printf(">");
		rewind(stdin);
		scanf("%d", &modifyChoice1);
		// Nested switch
		switch (modifyChoice1)
		{
		case 1:
			do
			{
				printf("Enter day: ");
				rewind(stdin);
				scanf("%[^\n]", modifyDay);
				printf("Train ID: \n");
				printf("T1001 T1002 T1003 T1004\n");
				printf("Select a Train ID for schedule you want to modify for: ");
				rewind(stdin);
				scanf("%[^\n]", modTrainID);

				for (int j = 0; j < STRUCTCOUNT; j++)
				{
					if (strcmp(modifyDay, schedule[j].day) == 0 && strcmp(modTrainID, schedule[j].trainID) == 0)
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
							printf("\nEnter new depart time(24h format): ");
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
								printf("\nEnter new depart time(24h format): ");
								rewind(stdin);
								scanf("%f", &newTime2);
							}
						}
						printf("Confirm?(Y/N) : ");
						rewind(stdin);
						scanf("%c", &confirmation);
						if (confirmation == 'Y' || confirmation == 'y')
						{
							schedule[j].departureTime = newTime1;
							schedule[j].arrivalTime = newTime2;
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
			}while (continues == 'y' || continues == 'Y');
			break;

		case 2:
			do
			{
				printf("Enter day: ");
				rewind(stdin);
				scanf("%[^\n]", modifyDay);
				
				// Converting to next week day
				if (strcmp(modifyDay, "Monday"))
				{
					strcpy(modifyDay, "nextMonday");
				}

				else if (strcmp(modifyDay, "Tuesday"))
				{
					strcpy(modifyDay, "nextTuesday");
				}

				else if (strcmp(modifyDay, "Wednesday"))
				{
					strcpy(modifyDay, "nextWednesday");
				}

				else if (strcmp(modifyDay, "Thursday"))
				{
					strcpy(modifyDay, "nextThursday");
				}

				else if (strcmp(modifyDay, "Friday"))
				{
					strcpy(modifyDay, "nextFriday");
				}

				else if (strcmp(modifyDay, "Saturday"))
				{
					strcpy(modifyDay, "nextSaturday");
				}

				else if (strcmp(modifyDay, "Sunday"))
				{
					strcpy(modifyDay, "nextSunday");
				}

				printf("Train ID: \n");
				printf("T1001 T1002 T1003 T1004\n");
				printf("Select a Train ID for schedule you want to modify for: ");
				rewind(stdin);
				scanf("%[^\n]", modTrainID);

				for (int k = 0; k < STRUCTCOUNT; k++)
				{
					if (strcmp(modifyDay, schedule[k].day) == 0 && strcmp(modTrainID, schedule[k].trainID) == 0)
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
							printf("\nEnter new depart time(24h format): ");
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
								printf("\nEnter new depart time(24h format): ");
								rewind(stdin);
								scanf("%f", &newTime4);
							}
						}
						printf("Confirm?(Y/N) : ");
						rewind(stdin);
						scanf("%c", &confirmation2);
						if (confirmation2 == 'Y' || confirmation2 == 'y')
						{
							schedule[k].departureTime = newTime3;
							schedule[k].arrivalTime = newTime4;
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
			}while (continues2 == 'y' || continues2 == 'Y');
			break;

		default:
			break;
		} // End Nested switch
		break;

	case 2:
		printf("Enter a date you would like to modify for.\n");
		printf("Notes: You can only modify for schedules for upcoming two weeks.");
		break;

	case 3:
		printf("Returning to schedule menu.\n");
	default:
		printf("Invalid value.\n");
		break;
	}
}

// Add schedule module
void AddSchedule(void)
{

}


void SearchSchedule(void)
{

}