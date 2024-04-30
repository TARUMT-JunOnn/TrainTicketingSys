#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
#pragma warning(disable:4996)
#pragma once
#define MAX_PAX 10
#define MAX_RECORDS 5000
SYSTEMTIME t;

#ifdef USE_TITLE
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

#ifdef USE_STRUCT
struct train {
	float depart;
	float arrive;
};

struct date {
	int day, month, year;
	char weekday[20];
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
	char status;
	Info trainInfo;
}records[MAX_RECORDS];
#endif