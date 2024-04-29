#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
#pragma warning(disable:4996)
#pragma once
SYSTEMTIME t;

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

struct train {
	float depart;
	float arrive;
};

struct date {
	int day, month, year;
	char weekday[20];
	struct train time;
};