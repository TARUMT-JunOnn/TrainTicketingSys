#include <stdio.h>
#pragma warning ( disable : 4996 )

main() {
	FILE* fptr;
	fptr = fopen("res/staff.bin", "wb+");

		if(fptr == NULL) {
			printf("Can't open file.");
		}

		fclose(fptr);
}