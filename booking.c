#include <stdio.h>
#include<time.h>
#pragma warning(disable:4996)

void showTime(void) {
	system("cls");
	time_t t;
	time(&t);
	printf("%110s", ctime(&t));
}

int main(void) {
	showTime(NULL);
	FILE* fptr;
	fptr = fopen("res/booking.txt", "w+");
	fprintf(fptr, "Hello,world");
	fclose(fptr);
}