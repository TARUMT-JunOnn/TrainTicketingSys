#include<stdio.h>
#include<string.h>
#pragma warning (disable:4996)
#define _CRT_SECURE_NO_WARNINGS
#pragma once

/*Common used function and structure that used in Train Ticketing System
If you want to disable this file, undefine all defined constants as shown below to ensure that the module works properly in the module file
USE_TITLE
USE_STRUCT
USE_GW_FUNCTION
*/


#ifdef USE_TITLE
#include<Windows.h>
#include<string.h>
extern SYSTEMTIME t;
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
#define MAX_PAX 10
#define MAX_RECORDS 5000
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

#ifdef USE_GW_FUNCTION
#include <stdbool.h>
#include <conio.h>
#include <string.h>
char passwordStore(char password[]) {
	int i = 0;
	char ch;
	do{
		ch = _getch();

		if (ch == 8) {
			if (i > 0) {
				i--;
				password[i] = '\0';
				printf("\b \b");
			}
		}
		else {
			if (ch != 13) {
				password[i] = ch;
				i++;
				printf("*");
			}
		}
	} while (ch != 13);
	password[i] = '\0';

	return password;
}

bool verify_password(char* pass) {
	int length = strlen(pass);
	bool hasUpper = false;
	bool hasLower = false;
	bool hasDigit = false;
	bool hasSymbol = false;

	if (length < 8)
		return false;

	for (int i = 0; i < length; i++) {
		if (isupper(pass[i]))
			hasUpper = true;
		if (islower(pass[i]))
			hasLower = true;
		if (isdigit(pass[i]))
			hasDigit = true;
		if (ispunct(pass[i]))
			hasSymbol = true;
	}

	if (!hasUpper) return false;
	if (!hasLower) return false;
	if (!hasDigit) return false;
	if (!hasSymbol) return false;

	return true;

}

bool verify_email(char* email) {
	int count = 0;

	for (int i = 0; i < strlen(email); i++) {
		if (email[i] == '@')
			count++;


		if (email[i] == ' ' || email[i] == '/' || email[i] == ':' || email[i] == ';'
			|| email[i] == '[' || email[i] == ']' || email[i] == '<' || email[i] == '>'
			|| email[i] == ',')
			return false;
	}

	if (count == 1) {
		if (email[0] != '@') {
			char* dot = strchr(email, '.');

			if (dot != NULL && dot > strchr(email, '@'))
				return true;

		}
	}

	return false;
}

bool verify_phone_no(char* phoneNo) {
	int length = strlen(phoneNo);

	if (length != 11 && length != 12)
		return false;

	if (phoneNo[0] != '0' || phoneNo[1] != '1')
		return false;

	for (int i = 0; i < 3; i++) {

		if (!isdigit(phoneNo[i]))
			return false;
	}

	for (int i = 4; i < length; i++) {
		if (!isdigit(phoneNo[i]))
			return false;
	}

	if (phoneNo[3] != '-')
		return false;

	return true;

}

bool verify_IC(char* gender, char* ic) {
	if (strlen(ic) != 14)
		return false;

	if (ic[6] != '-' || ic[9] != '-')
		return false;

	if (strcmp(gender, "M") == 0) {
		if (ic[13] != '1' && ic[13] != '3' && ic[13] != '5' && ic[13] != '7' && ic[13] != '9')
			return false;
	}
	else if (strcmp(gender, "F") == 0) {
		if (ic[13] != '0' && ic[13] != '2' && ic[13] != '4' && ic[13] != '6' && ic[13] != '8')
			return false;
	}
	else
		return false;

	for (int i = 0; i < 6; i++) {
		if (!isdigit(ic[i]))
			return false;
	}

	for (int i = 7; i < 9; i++) {
		if (!isdigit(ic[i]))
			return false;
	}

	for (int i = 10; i < 14; i++) {
		if (!isdigit(ic[i]))
			return false;
	}

	return true;
}
#endif

#ifdef USE_DATE_FUNCTION
#include<time.h>
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
#endif