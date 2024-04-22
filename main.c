#include<stdio.h>
#pragma warning(disable:4996);

int main(void) {
	FILE* fptr[4];
	bookingMain(readfile(&fptr[3]));
	writefile(&fptr[3]);
	fclose(fptr[3]);
}