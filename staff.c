#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include<string.h>
#include <ctype.h>
#include <Windows.h>
#define USE_TITLE
#include "common.c"
#pragma warning (disable : 4996);

#define MAX_STAFF 40
#define MAX_MANAGER 20
#define MAX_NAME_LENGTH 50
#define MAX_ID_LENGTH 20
#define MAX_PASS_LENGTH 20
#define MAX_PHONE_LENGTH 15
#define MAX_EMAIL_LENGTH 50
#define MAX_POSITION_LENGTH 50
#define MAX_QUESTION_SELECTED 2




//structure for checkin in & out time
struct ScheduleStaff {

    int begin_hour;
    int begin_minute;
    int rest_time;
    int end_hour;
    int end_minute;
    int total_working_hours;
    int remaining_minutes;

};

typedef struct {
    char id[MAX_ID_LENGTH];
    char password[MAX_PASS_LENGTH];
    char name[MAX_NAME_LENGTH];
    char phone[MAX_PHONE_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char position[MAX_POSITION_LENGTH];
}Table;

struct Staff {
    Table table;
    struct ScheduleStaff schedule;
    time_t check_in_time; //time staff
    time_t check_out_time;
};

struct M_SecurityQues {
    int questionNum;
    char securityAns[50];
};

struct Manager {
    Table table;
    struct M_SecurityQues security[MAX_QUESTION_SELECTED]; //nested structure
};


struct Staff staff[MAX_STAFF];

struct Manager manager[MAX_MANAGER];
int staff_count = 0;
int manager_count = 0;
int employeeNum[2];




int readStaffFile(FILE** fstaff) {
    Table staff2;

    fread(&staff2, sizeof(Table), 1, *fstaff);

    while (!feof(*fstaff))
    {
        if (strcmp(staff2.position, "STAFF") == 0)
        {
            fseek(*fstaff, sizeof(Table) * -1, SEEK_CUR);
            fread(&staff[staff_count], sizeof(struct Staff), 1, *fstaff);
            staff_count++;
        }

        if (strcmp(staff2.position, "MANAGER") == 0)
        {
            fseek(*fstaff, sizeof(Table) * -1, SEEK_CUR);
            fread(&manager[manager_count], sizeof(struct Manager), 1, *fstaff);
            manager_count++;
        }
        fread(&staff2, sizeof(Table), 1, *fstaff);
    }

}

int writeStaffFile(FILE** fstaff) {
    for (int i = 0; i < manager_count; i++) {
        fwrite(&manager[i], sizeof(struct Manager), 1, *fstaff);
    }

    for (int i = 0; i < staff_count; i++) {
        fwrite(&staff[i], sizeof(struct Staff), 1, *fstaff);
    }
}

//main() {
//    struct Staff staff[MAX_STAFF];
//    Table staff2;
//    struct Manager manager[MAX_MANAGER];
//
//
//
//    FILE* fstaff;
//    fstaff = fopen("../TrainTicketingSys/res/staff.bin", "rb");
//
//    if (fstaff == NULL) {
//        printf("Error Opening File\n");
//        exit(-1);
//    }
//
//    //strcpy(staff[0].table.id, "lgw123");
//    //strcpy(staff[0].table.password, "321");
//    //strcpy(staff[0].table.phone, "01231323");
//    //strcpy(staff[0].table.email, "lee@gmail.com");
//    //strcpy(staff[0].table.position, "STAFF");
//
//    //strcpy(manager[0].table.id, "ALi");
//    //strcpy(manager[0].table.password, "773");
//    //strcpy(manager[0].table.phone, "12312");
//    //strcpy(manager[0].table.email, "ali@ail.com");
//    //strcpy(manager[0].table.position, "MANAGER");
//
//    //fwrite(&staff[0], sizeof(staff), 1, fstaff);
//    //fwrite(&manager[0], sizeof(manager), 1, fstaff);
//    fread(&staff2, sizeof(Table), 1, fstaff);
//
//    while (!feof(fstaff))
//    {
//        if (strcmp(staff2.position, "STAFF") == 0)
//        {
//            fseek(fstaff, sizeof(Table) * -1, SEEK_CUR);
//            fread(&staff[staff_count], sizeof(struct Staff), 1, fstaff);
//            staff_count++;
//        }
//
//        if (strcmp(staff2.position, "MANAGER") == 0)
//        {
//            fseek(fstaff, sizeof(Table) * -1, SEEK_CUR);
//            fread(&manager[manager_count], sizeof(struct Manager), 1, fstaff);
//            manager_count++;
//        }
//        fread(&staff2, sizeof(Table), 1, fstaff);
//    }
//
//    //write new information to file.
//    //strcpy(staff[1].table.id, "staff1");
//    //strcpy(staff[1].table.password, "321");
//    //strcpy(staff[1].table.phone, "01231323");
//    //strcpy(staff[1].table.email, "lee@gmail.com");
//    //strcpy(staff[1].staff[i], "STAFF");
//    //staff_count++;
//
//  //test file read 
//    for (int i = 0; i < staff_count; i++) {
//        printf("ID: %s\n", staff[i].table.id);
//    }
//
//    for (int i = 0; i < manager_count; i++) {
//        printf("ID: %s\n", manager[i].table.id);
//    }
//
//
//    fclose(fstaff);
//
//    menu();
//
//    //print all manager and staff account
//
//    for (int i = 0; i < staff_count; i++) {
//        printf("ID: %s\n", staff[i].table.id);
//    }
//
//    for (int i = 0; i < manager_count; i++) {
//        printf("ID: %s\n", manager[i].table.id);
//    }
//    //------------------------------------------------
//
//    fstaff = fopen("../TrainTicketingSys/res/staff.bin", "wb");
//
//    for (int i = 0; i < manager_count; i++) {
//        fwrite(&manager[i], sizeof(struct Manager), 1, fstaff);
//    }
//
////    for (int i = 0; i < staff_count; i++) {
////        fwrite(&staff[i], sizeof(struct Staff), 1, fstaff);
////    }
//
//
//
//
//    fclose(fstaff);
//    return 0;
//
//}

// Main menu
int employeeMenu()
{
    char choice;
    int choiceInt;
    struct tm* hour;
    char buffer[50];
    time_t t;
    time(&t);

    hour = localtime(&t);
    strftime(buffer, 50, "%X", hour);

    //system("cls");
    do {
        title();
        printf(" ------ EMPLOYEE MENU ------\n");
        printf("------------------------------\n");
        printf("1. Staff\n");
        printf("2. Manager\n");
        printf("3. Exit\n");
        scanf(" %c", &choice);
        switch (choice) {
        case '1':
            return choice - 48;
            break;
        case '2':
            return choice - 48;
            break;
        case '3':
            printf("\nYou are Log Out %s Right Now!\n", buffer);
            system("pause");
            return 0;
            break;
        default:
            //got error when loop
            printf("Invalid Choice!\n");
            printf("Please Select Again...\n");
            Sleep(1000);
            break;
            //only can validate numeric answer
            //if enter character or string, it will be error
        }
    } while (choice != '1' && choice != '2' && choice != 3);

}

// Staff menu
int staffMenu()
{
    int choice, status = 1;
    do {
        status = 1;
        title();
        printf("------ STAFF MENU ------\n");
        printf("-------------------------\n");
        printf("1. Login\n");
        printf("2. Registration\n");
        printf("3. Exit\n");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
        case 2:
            return choice;
            break;
        case 3:
            printf("Exiting....\n");
            Sleep(600);
            break;
        default:
            printf("Invalid Choice!\n");
            printf("Please Select Again\n");
            Sleep(600);
            break;
        }
    } while (choice != 1 && choice != 2 && choice != 3);
    printf("\nYou are Exit Right Now!\n");
    Sleep(600);
    return 0;
}


// Staff Login menu
int staff_login()
{
    char id[MAX_ID_LENGTH];
    char password[MAX_PASS_LENGTH];
    int loginSuccess = 0;
    int count = 0;
    int ans, status = -1;
    int again = 0;

    title();
    printf("------ STAFF LOGIN ------\n");

    do
    {

        loginSuccess = 0;
        printf("\nEnter your staff ID: ");
        scanf(" %[^\n]", id);
        printf("Enter your staff password: ");
        scanf(" %[^\n]", password);
        for (int i = 0; i < MAX_STAFF; i++)
        {
            if (strcmp(staff[i].table.id, id) == 0 && strcmp(staff[i].table.password, password) == 0)
            {
                printf("Login successful...\n");
                Sleep(600);
                employeeNum[0] = i;
                return 1;
                loginSuccess++;
            }
        }

        if (loginSuccess == 0)
        {
            do {
                again = 0;
                printf("\nInvalid ID or Password\n");
                printf("\nDo you want to try again?");
                printf("\n1. Yes\n");
                printf("2. No\n");
                printf("Enter you choice:");
                scanf("%d", &ans);
                printf("---------------------------\n");
                if (ans == 1) {
                    again++;
                    count++;
                }
                else if (ans == 2) {
                    return 0;
                    system("cls");
                }
                else
                    again = 0;

            } while (again == 0);

            if (count == 3)
            {
                printf("\nYou are failed to log in 3 time!\n");
                Sleep(600);
                do {
                    printf("\n1. RESET PASSWORD\n");
                    printf("2. EXIT\n");
                    printf("Do u want to reset the password ?");
                    scanf("%d", &ans);

                    if (ans == 1)
                    {
                        resetPassword(staff);
                        return 0;
                        count = 0;
                    }
                    else if (ans == 2)
                    {

                        printf("You are exit right now!\n");
                        Sleep(600);
                        return 0;
                    }
                    else
                    {
                        printf("Select again.\n");
                    }
                } while (ans != 1 && ans != 2);
            }
        }
    } while (again == 1 && loginSuccess == 0);
    // system("cls");
}

//staff registration menu 
void staff_registration() {
    char id[MAX_ID_LENGTH];
    char name[MAX_NAME_LENGTH];
    char password[MAX_PASS_LENGTH];
    char position[MAX_POSITION_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char phoneNo[MAX_PHONE_LENGTH];

    title();
    printf("\nStaff Registration\n");
    printf("--------------------\n");
    printf("Enter your ID: ");
    scanf(" %[^\n]", id);
    printf("Name: ");
    scanf(" %[^\n]", name);
    printf("Enter your Password: ");
    scanf(" %[^\n]", password);
    printf("Phone No: ");
    scanf(" %[^\n]", phoneNo);
    printf("Email:");
    scanf(" %[^\n]", email);


    for (int i = 0; i < staff_count; i++) {
        if (strcmp(staff[i].table.id, id) == 0) {
            title();
            printf("The ID %s already exits.\n", id);
            printf("Please choose a different ID.\n");
            Sleep(600);
            return 0;
        }
    }

    strcpy(staff[staff_count].table.id, id);
    strcpy(staff[staff_count].table.name, name);
    strcpy(staff[staff_count].table.password, password);
    strcpy(staff[staff_count].table.phone, phoneNo);
    strcpy(staff[staff_count].table.email, email);
    //copy email and phone
    strcpy(staff[staff_count].table.position, "STAFF");

    //write all equal to 0 or NULL;

    staff[staff_count].schedule.total_working_hours = 0;



    printf("\nRegistration successfully\n");
    Sleep(600);

    staff_count++;

}


//staff working schedule 
void staff_schedule()
{
    title();
    if (staff[employeeNum[0]].schedule.total_working_hours != 0) { //
        printf("\n----------------- WORKING TIME SCHEDULE -----------------|- %s -|\n", staff[employeeNum[0]].table.name);
        printf("BEGIN TIME\t\tREST TIME\t\tEND TIME\n");
        printf("%02d:%02d\t\t\t %d\t\t\t  %02d:%02d\t\n", staff[employeeNum[0]].schedule.begin_hour, staff[employeeNum[0]].schedule.begin_minute, staff[employeeNum[0]].schedule.rest_time, staff[employeeNum[0]].schedule.end_hour, staff[employeeNum[0]].schedule.end_minute);
        printf("TOTAL WORKING TIME : %d hours %d minutes (except rest time)\n", staff[employeeNum[0]].schedule.total_working_hours, staff[employeeNum[0]].schedule.remaining_minutes);
        printf("-------------------------------------------------------------------\n");
        system("pause");
    }
    else
        printf("Sorry,Your schedule haven't done modified yet.\n");
    Sleep(600);

}


//staff update information 
void staff_information() {
    char name[MAX_NAME_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char phone[MAX_PHONE_LENGTH];
    char id[MAX_ID_LENGTH];
    char stop;
    int success = 0, again = 0, choice;
    char confirm;

    do {
        success = 0;
        again = 0;

        title();

        // Before edit --change the versio view
        printf("---------------------------\n");
        printf("------ Before Update ------\n");
        printf("---------------------------\n");
        printf("\nName: %s\n", staff[employeeNum[0]].table.name);
        printf("Phone No: %s\n", staff[employeeNum[0]].table.phone);
        printf("Email:%s\n", staff[employeeNum[0]].table.email);


        printf("\nConfirm to update?(Y/N): ");
        scanf(" %c", &confirm);

        if (confirm == 'Y' || confirm == 'y') {
            title();
            printf("\n--------------------------------------\n");
            printf("---------- UPDATE RIGHT NOW ---------\n");
            printf("--------------------------------------\n");
            printf("\nNew Name:");
            scanf(" %[^\n]", name);
            printf("New Phone No:");
            scanf(" %[^\n]", phone);
            printf("New Email:");
            scanf(" %[^\n]", email);
            printf("----------------------------\n");

            strcpy(staff[employeeNum[0]].table.name, name);
            strcpy(staff[employeeNum[0]].table.phone, phone);
            strcpy(staff[employeeNum[0]].table.email, email);

            success++;

            printf("\nUpdate was done successfully!\n");
            Sleep(800);

            title();
            printf("\n-----------------------------\n");
            printf("------- After Updated -------\n");
            printf("-----------------------------\n");
            printf("Staff ID: %s\n", staff[employeeNum[0]].table.id);
            printf("\nName: %s\n", staff[employeeNum[0]].table.name);
            printf("Phone No: %s\n", staff[employeeNum[0]].table.phone);
            printf("Email:%s\n", staff[employeeNum[0]].table.email);
            printf("\n-----------------------------\n");
            system("pause");
        }
        else
        {
            printf("Update unsuccessfull\n");
            Sleep(500);
        }


        if (success == 0) {
            do {
                again = 0;

                title();
                printf("\n--------------------------\n");
                printf("Do you want to update again?");
                printf("\n1. Yes\n");
                printf("2. No\n");
                printf("Enter you choice:");
                scanf("%d", &choice);
                printf("---------------------------\n");
                Sleep(600);
                if (choice == 1)
                    again++;
                else if (choice == 2) {
                    return 0;

                }

                else
                    again = 0;
            } while (again == 0);

        }

    } while (again == 1);
}


//combination of log out&in time selected
int staff_logout() {
    int ans, choice;
    time_t check_in_time = 0;
    time_t check_out_time = 0;

    clock_t checkIn = 0, checkOut = 0;
    double elapsedTime;


    do {
        title();
        printf("\nSTAFF WORKING TIME RECORDED\n");
        printf("=================================\n\n");
        printf("1. CHECK IN\n");
        printf("2. CHECK OUT\n");
        printf("Enter your choice:");
        scanf("%d", &ans);
        printf("==================================\n\n");
    } while (ans != 1 && ans != 2);

    if (ans == 1) {
        checkIn = clock();
        // Check in
        title();
        time(&staff[employeeNum[0]].check_in_time);
        printf("---------------------------- CHECK IN ----------------------------\n");
        printf("STAFF ID:%s\tCHECK IN TIME:%s", staff[employeeNum[0]].table.id, ctime(&staff[employeeNum[0]].check_in_time));
        printf("Check In succeed\n");
        printf("-------------------------------------------------------------------\n");
        Sleep(1000);


    }
    else if (ans == 2) {
        checkOut = clock();
        // Check out
        title();
        time(&staff[employeeNum[0]].check_out_time);
        printf("----------------------------- CHECK OUT ---------------------------\n");
        printf("STAFF ID:%s\tCHECK OUT TIME:%s", staff[employeeNum[0]].table.id, ctime(&staff[employeeNum[0]].check_out_time));
        printf("-------------------------------------------------------------------\n");

        elapsedTime = (double)(checkOut - checkIn) / CLOCKS_PER_SEC;


        if (elapsedTime > 8 * 3600) {
            printf("\nThis is your check in time %s and you are check out right now.\n", ctime(&staff[employeeNum[0]].check_in_time));
            printf("You have completed 8 hours of work today.\n");
            Sleep(600);
        }
        else {

            printf("--------------------- Time Overall situation ----------------------\n");
            printf("-------------------------------------------------------------------\n");
            printf(" | CHECK IN TIME  | %s |\n", ctime(&staff[employeeNum[0]].check_in_time));
            printf(" | CHECK OUT TIME | %s |\n", ctime(&staff[employeeNum[0]].check_out_time));
            printf("-------------------------------------------------------------------\n");

            printf("---------- You have not completed 8 hours of work today. ----------\n");
            Sleep(600);

            do {
                printf("\nAre you sure you want to check out? (1 for Yes, 0 for No): ");
                scanf("%d", &choice);
                if (choice == 1) {
                    // Exit and return to the menu
                    printf("\nExiting...\n");
                    Sleep(600);
                    return 1;
                    // You may want to return to the main menu or exit the program here
                }
                else if (choice == 0)
                {
                    // Return to staff menu
                    return 0;
                }
                else
                {
                    title();
                    printf("\nFailed to select...\n");
                    printf("Please select again!\n");
                    Sleep(600);
                }

            } while (choice != 1 && choice != 2);
        }
    }
    return 0;
}

void sendValidationCode(char* email, char* code) {
    // Implement sending the validation code to the provided email
    title();
    printf("Validation code sent to %s is: %s\n", email, code);
}

char* generateValidationCode() {
    // Generate a random validation code (simplified example)
    char* code = (char*)malloc(7 * sizeof(char)); // 6 characters + null terminator
    sprintf(code, "%06d", rand() % 1000000);
    return code;
}

// Staff reset password 
int resetPassword()
{
    char id[MAX_ID_LENGTH];
    char phone[MAX_PHONE_LENGTH];
    int ans;
    int successfuly = 0;
    int codeReceived;
    char newPassword[MAX_PASS_LENGTH];
    char comf_newPassword[MAX_PASS_LENGTH];
    char choice;

    title();
    printf("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    printf("| You need to double check the data showe below |\n");
    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    Sleep(600);

    printf("\nEnter ID:");
    scanf(" %[^\n]", id);

    for (int i = 0; i < staff_count; i++)
    {
        if (strcmp(staff[i].table.id, id) == 0)
        {

            printf("%-20s%-20s\n", "STAFF NAME", "EMAIL");
            printf("%-20s%-20s\n", staff[i].table.name, staff[i].table.email);
            do {
                printf("\nIs you?\n");
                printf("1. CORRECT, IS ME\n");
                printf("2. WRONG, NOT ME\n");
                scanf("%d", &ans);

                if (ans == 1)
                {
                    do {
                        title();
                        printf("\nPlease enter you phone number to validation\n");
                        scanf(" %[^\n]", phone);
                        if (strcmp(staff[i].table.phone, phone) == 0)
                        {
                            printf("Sending a validation code to your email\n");
                            printf("\nWaiting time....\n");
                            Sleep(800);
                            //random()
                            //store(send) the code to email.Then compare the code staff keyin and the code in the email.
                            char* code = generateValidationCode();
                            sendValidationCode(staff[i].table.email, code);
                            printf("\nPlease enter the validation code you receive:");
                            scanf("%d", &codeReceived);


                            if (atoi(code) == codeReceived)
                            {
                                printf("\nAble to reset the password\n");
                                Sleep(600);

                                successfuly = 0;
                                do {
                                    title();
                                    printf("Enter the new password:");
                                    scanf(" %[^\n]", newPassword);
                                    printf("\nEnter again the same password:");
                                    scanf(" %[^\n]", comf_newPassword);

                                    if (strcmp(newPassword, comf_newPassword) == 0)
                                    {
                                        printf("Success!\n");
                                        Sleep(600);
                                        strcpy(staff[i].table.password, comf_newPassword);
                                        successfuly++;
                                        return 0;
                                    }
                                    else {
                                        printf("Failed, Password didn't same with the password you key in!\n\n");
                                        successfuly = 0;
                                    }
                                } while (successfuly == 0);

                            }
                            else
                                printf("Validation code incorrect!\n");
                            Sleep(600);

                        }
                        else

                            printf("You phone number is incorrect!\n");
                        do {
                            printf("\nDo you want to try again?(Y/N)");
                            Sleep(600);
                            scanf(" %c", &choice);
                            if (toupper(choice) == 'N') {
                                printf("EXIT");
                                Sleep(600);
                                return 0;
                            }
                            else if (toupper(choice) != 'Y') {
                                printf("Invalid select.\n");
                            }
                        } while (toupper(choice) != 'Y' && toupper(choice) != 'N');

                    } while (toupper(choice) == 'Y');

                }
                else if (ans != 1 && ans != 2)
                    printf("Invalid select.\n");
                Sleep(600);

            } while (ans != 1 && ans != 2);

        }
        else {
            printf("Authentication failed.\n");
            printf("You need to register first !\n\n");
            Sleep(600);
            return 0;
        }

    }
    printf("Staff ID not found.\n");
    printf("You need to register first !\n\n");
    Sleep(600);
    return 0;
}

// Manager menu
int manager_menu()
{
    int choice;
    struct tm* hour;
    char buffer[50];
    time_t t;
    time(&t);


    do {
        title();

        printf("\n ------ MANAGER MENU ------\n");
        printf("-------------------------------\n");
        printf("1. Login\n");
        printf("2. Registration\n");
        printf("3. Exit\n");
        scanf("%d", &choice);


        switch (choice) {
        case 1:
        case 2:
            return choice;
            break;

        case 3:
            printf("\nYou are Exit Right Now!\n");
            Sleep(600);
            break;
        default:
            printf("\nInvalid Choice!\n");
            printf("Please Select Again\n");
            Sleep(600);
            //only can validate numeric answer
            //if enter character or string, it will be error
        }
    } while (choice != 3);
    return 0;
}

void securityQues_display(int questionSelection[MAX_QUESTION_SELECTED], char questionTitle[MAX_QUESTION_SELECTED][50])
{
    for (int i = 0; i < 2; i++) {
        switch (questionSelection[i])
        {
        case 1:
            strcpy(questionTitle[i], "What was the first name of your first pet?");
            break;
        case 2:
            strcpy(questionTitle[i], "What was your childhood nickname?");
            break;
        case 3:
            strcpy(questionTitle[i], "What are the favorite food as a child?");
            break;
        case 4:
            strcpy(questionTitle[i], "In what city were you born?");
            break;
        case 5:
            strcpy(questionTitle[i], "What is your mother's maiden name?");
            break;
        }

    }
}

// Security question 
void security_Ques()
{
    title();
    printf("\n------------- Security Question -------------\n");
    printf("|  Choose 2 question as your security question  |\n");

    printf("1. What was the first name of your first pet?\n");
    printf("2. What was your childhood nickname?\n");
    printf("3. What are the favorite food as a child?\n");
    printf("4. In what city were you born?\n");
    printf("5. What is your mother's maiden name?\n");


    printf("-----------------------------------------------\n");


}

// Manager registration 
void manager_registration()
{
    char id[MAX_ID_LENGTH];
    char name[MAX_NAME_LENGTH];
    char password[MAX_PASS_LENGTH];
    char phone[MAX_PHONE_LENGTH];
    char email[MAX_EMAIL_LENGTH];

    int again = 0;
    int success = 0;
    char answer[MAX_QUESTION_SELECTED][50];
    char question[MAX_QUESTION_SELECTED][50];
    int questionSelection[MAX_QUESTION_SELECTED];


    title();
    printf("\Manager Registration\n");
    printf("--------------------\n");
    printf("Manager ID: ");
    scanf(" %[^\n]", id);
    printf("Name: ");
    scanf(" %[^\n]", name);
    printf("Password: ");
    scanf(" %[^\n]", password);

    for (int i = 0; i < manager_count; i++)
    {
        if (strcmp(manager[i].table.id, id) == 0)
        {
            title();
            printf("The ID %s already exits.\n", id);
            printf("Please choose a different ID.\n");
            Sleep(600);
            return 0;
        }
    }

    again = 0;
    //  ---------------------------------------
    do
    {

        do {

            security_Ques();

            for (int i = 0; i < MAX_QUESTION_SELECTED; i++)
            {
                do
                {
                    success = 1;
                    again = 0;

                    printf("%d. ", i + 1);
                    scanf("%d", &questionSelection[i]);


                    if (questionSelection[i] > 5 || questionSelection[i] < 1)
                    {
                        printf("Invalid Choice!\n");
                        printf("Please Enter Number 1 - 5!\n");
                        Sleep(600);
                        success = 0;
                        //break; //got bugg looping bug
                    }
                } while (questionSelection[i] > 5 || questionSelection[i] < 1);


                if (i > 0)
                {
                    for (int q = 0; q < i; q++)
                    {
                        if (questionSelection[i] == questionSelection[q])
                        {
                            printf("\nSelect the difference security question\n");
                            printf("Please Try Again.\n");
                            Sleep(600);
                            again++;
                            success = 0;

                        }
                    }

                }

            }
        } while (again == 1);
    } while (success != 1);

    // copy into structure
    for (int i = 0; i < 2; i++)
    {
        manager[manager_count].security[i].questionNum = questionSelection[i];
    }

    securityQues_display(questionSelection, question);

    for (int i = 0; i < MAX_QUESTION_SELECTED; i++) {
        printf("%s\n", question[i]);
        printf("Answer: ");
        scanf(" %[^\n]", answer[i]);
        strcpy(manager[manager_count].security[i].securityAns, answer[i]);
    }
    // ----------------------------------------------

    printf("Phone No: ");
    rewind(stdin);
    scanf("%[^\n]", phone);
    printf("Email: ");
    rewind(stdin);
    scanf("%[^\n]", email);

    strcpy(manager[manager_count].table.id, id);
    strcpy(manager[manager_count].table.name, name);
    strcpy(manager[manager_count].table.password, password);
    strcpy(manager[manager_count].table.phone, phone);
    strcpy(manager[manager_count].table.email, email);
    strcpy(manager[manager_count].table.position, "MANAGER");


    printf("\nRegistration successfully\n\n");
    system("pause");


    manager_count++;
}


//Manager delete/remove staff acc 
int delete_Acc()
{
    int confirm;
    char answers;
    char deleteID[MAX_ID_LENGTH];
    int deleted = 0;
    int again = 0;
    int done = 1;
    int choice;


    do
    {
        done = 1;
        deleted = 0;
        again = 0;

        title();
        printf("you are able to delete the record\n");
        Sleep(600);
        title();

        printf("\nEenter staff id to delete :");
        Sleep(600);
        rewind(stdin);
        scanf("%[^\n]", deleteID);

        for (int i = 0; i < MAX_STAFF; i++)
        {
            if (strcmp(staff[i].table.id, deleteID) == 0)
            {
                title();
                printf("\n----------- RECORD OF STAFF -----------\n");
                printf("\nStaff Name\tPhone No\tEmail\n");
                printf("%s\t%s\t%s", staff[i].table.name, staff[i].table.phone, staff[i].table.email);
                printf("\n------------------------------------------\n");

                do {
                    done = 1;
                    printf("\nConfirm To delete?\n");
                    printf("\n1. Yes\n");
                    printf("2. No\n");
                    printf("Enter you choice:");
                    scanf(" %d", &confirm);
                    printf("\n------------------------------------------\n");


                    if (confirm == 1)
                    {

                        strcpy(staff[i].table.id, staff[i + 1].table.id);
                        strcpy(staff[i].table.name, staff[i + 1].table.name);
                        strcpy(staff[i].table.password, staff[i + 1].table.password);
                        strcpy(staff[i].table.email, staff[i + 1].table.email);
                        strcpy(staff[i].table.phone, staff[i + 1].table.phone);
                        strcpy(staff[i].table.position, staff[i + 1].table.position);
                        staff_count--;

                        deleted++;

                        printf("\nDELETE SUCCESSFUL\n");
                        Sleep(600);

                    }

                    else if (confirm == 2)
                    {
                        printf("\nEXIT FROM REMOVE STAFF MENU.\n");
                        Sleep(600);
                        return 0;
                        //system("cls");
                    }

                    else
                        done = 0;

                } while (done == 0);

            }

        }

        if (deleted == 0) {
            printf("\nINVALID - STAFF ID NOT FOUND\n");
            Sleep(600);
            return 0;

        }
        if (deleted == 1) {
            title();
            do {
                printf("Do you want to continue");
                printf("\n1. Yes\n");
                printf("2. No\n");
                printf("Enter you choice:");
                scanf("%d", &choice);

                if (choice == 1)
                    again++;
                else if (choice == 2) {
                    return 0;

                }
                else
                    again = 0;

            } while (again == 0);

        }



    } while (done == 1);
}


//manager modify particular staff / entire staff rest schedule 
void modifyEmpRestSchedule()
{
    char id[MAX_ID_LENGTH];
    int ans = 0;
    int successful = 0;
    int choice;
    int again = 0;
    int total_end_minutes = 0;
    int total_working_minutes = 0;
    int total_begin_minutes = 0;
    int total_working_hours = 0;
    int remaining_minutes = 0;
    int reenter = 0;

    do
    {
        ans = 0;
        successful = 0;
        again = 0;
        reenter = 0;
        title();

        printf("\n-------- Particular staff rest schedule --------\n");
        printf("\nStaff ID:");
        scanf(" %[^\n]", &id);

        for (int i = 0; i < staff_count; i++)
        {

            if (strcmp(staff[i].table.id, id) == 0)
            {

                do { ///
                    reenter = 0;
                    printf("\n----------- EDIT STAFF WORKING TIME ------------\n");
                    printf("--------------------------------------------------\n");
                    printf("\nSTAFF NAME : %s\n", staff[i].table.name);
                    printf("\nBEGIN (hh:mm - 24H format): ");

                    if (scanf("%d:%d", &staff[i].schedule.begin_hour, &staff[i].schedule.begin_minute) != 2)
                    {
                        printf("Invalid input format. Please enter time in hh:mm - 24H format.\n");
                        reenter++;
                        Sleep(600);
                    }
                    if (reenter == 0) {
                        printf("\nREST (minutes): ");
                        scanf("%d", &staff[i].schedule.rest_time);


                        do {
                            printf("\nEND (hh:mm - 24H format): ");

                            if (scanf("%d:%d", &staff[i].schedule.end_hour, &staff[i].schedule.end_minute) != 2)
                            {
                                printf("Invalid input format. Please enter time in hh:mm - 24H format.\n");
                                reenter++;
                            }

                            total_begin_minutes = staff[i].schedule.begin_hour * 60 + staff[i].schedule.begin_minute;
                            total_end_minutes = staff[i].schedule.end_hour * 60 + staff[i].schedule.end_minute;


                            if (staff[i].schedule.begin_hour >= 16 && staff[i].schedule.end_hour < staff[i].schedule.begin_hour) {
                                total_end_minutes = total_end_minutes + 1440;
                            }
                            total_working_minutes = total_end_minutes - total_begin_minutes - staff[i].schedule.rest_time;

                        } while (total_working_minutes < 480);


                    }




                } while (reenter != 0);


                if (total_end_minutes < total_begin_minutes) {
                    total_working_minutes = (24 * 60 - total_begin_minutes) + total_end_minutes;
                }
                else {
                    total_working_minutes = total_end_minutes - total_begin_minutes;
                }

                if (total_working_minutes >= 8 * 60) {

                    // Calculate total working hours and minutes
                    total_working_hours = total_working_minutes / 60;
                    remaining_minutes = total_working_minutes % 60;

                    title();
                    printf("\n---------------------------------------------\n");
                    printf("| WORKING TIME UPDATED SUCCESSFULLY |\n");
                    printf("---------------------------------------------\n");
                    Sleep(1000);

                    title();

                    printf("\n----------------- WORKING TIME SCHEDULE -----------------|- %s -|\n", staff[i].table.name);
                    printf("BEGIN TIME\t\tREST TIME\t\tEND TIME\n");
                    printf("%02d:%02d\t\t\t  %d\t\t\t  %02d:%02d\n", staff[i].schedule.begin_hour, staff[i].schedule.begin_minute, staff[i].schedule.rest_time, staff[i].schedule.end_hour, staff[i].schedule.end_minute);
                    printf("TOTAL WORKING TIME : %d hours %d minutes (exclude rest time)\n", total_working_hours, remaining_minutes);
                    printf("-------------------------------------------------------------------\n");
                    system("pause");

                    staff[i].schedule.total_working_hours = total_working_hours;
                    staff[i].schedule.remaining_minutes = remaining_minutes;
                    title();

                }
                else
                {
                    Sleep(600);
                    printf("---------------------------------------------\n");
                    printf("| STAFF END WORKING TIME MUST ENOUGH 8 HOUR |\n");
                    printf("---------------------------------------------\n");
                    Sleep(1000);
                }


                successful++;

            }

        }

        if (successful == 0 && ans == 0)
        {
            do
            {
                title();
                ans = 0;
                printf("|------------------------------|\n");
                printf("| Invalid ---- Wrong ID  ----  |\n");
                printf("|------------------------------|\n");
                printf("| Do you want to enter again?  |");
                printf("\n| 1. Yes                       |\n");
                printf("| 2. No                        |\n");
                printf("|------------------------------|\n\n");
                printf("Enter you choice:");
                scanf("%d", &choice);
                printf("|-----------------------------|\n");
                Sleep(500);
                if (choice == 1)
                    ans++;
                else if (choice == 2)
                {
                    printf("\nEXIT\n");
                    Sleep(300);
                    return 0;
                }

                else
                    ans = 0;

            } while (ans == 0);

        }
        else
        {
            do {
                title();
                printf("Enter 1 to 'Countinue' modify staff schedules Or Enter 2 to 'Exit' the staff schedules\n");
                printf("Enter you choice:");
                scanf("%d", &choice);

                if (choice == 1) {
                    again++;
                    ans++;
                }
                else if (choice == 2) {
                    return 0;
                }
                else
                    again = 0;

            } while (again == 0);
        }

    } while (ans == 1);
}


//Manager update information
void updateManager_information() {
    char name[MAX_NAME_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char phone[MAX_PHONE_LENGTH];
    char stop;
    int success = 0, again = 0, choice;
    char confirm;

    do {
        success = 0;
        again = 0;
        title();

        //no need enter manager ID alredy pass from parameter

        // Before edit
        printf("---------------------------------------------------\n");
        printf("================== Before Update ==================\n");
        printf("---------------------------------------------------\n");
        printf("%-20s%-20s%-20s\n", "Name", "Phone No", "Email");
        printf("%-20s%-20s%-20s\n", manager[employeeNum[1]].table.name, manager[employeeNum[1]].table.phone, manager[employeeNum[1]].table.email);
        printf("---------------------------------------------------\n");

        printf("\nConfirm to update?(Y/N): ");
        scanf(" %c", &confirm);

        //ask manager to update
        if (confirm == 'Y' || confirm == 'y') {
            title();
            printf("--------------------------------------------------\n");
            printf("================ UPDATE RIGHT NOW ================\n");
            printf("--------------------------------------------------\n"); //don't know
            printf("New Name:");
            scanf(" %[^\n]", name);
            printf("New Phone Number:");
            scanf(" %[^\n]", phone);
            printf("New Email:");
            scanf(" %[^\n]", email);

            strcpy(manager[employeeNum[1]].table.name, name);
            strcpy(manager[employeeNum[1]].table.phone, phone);
            strcpy(manager[employeeNum[1]].table.email, email);

            success++;

            printf("\nYou are successful updated.\n");

            title();

            printf("---------------------------------------------------\n");
            printf("================== After Updated ==================\n");
            printf("---------------------------------------------------\n");
            printf("%-20s%-20s%-20s\n", "Manager ID", "Name", "Phone No", "Email");
            printf("%-20s%-20s%-20s\n", manager[employeeNum[1]].table.id, manager[employeeNum[1]].table.name, manager[employeeNum[1]].table.phone, manager[employeeNum[1]].table.email);
            printf("\n--------------------------------------------------\n");
            system("pause");
        }
        else
        {
            printf("Update unsuccessfull\n");
            Sleep(600);
        }


        if (success == 0) {
            do {
                title();
                again = 0;
                printf("Do you want to update again?");
                printf("\n1. Yes\n");
                printf("2. No\n");
                printf("Enter you choice:");
                scanf("%d", &choice);
                printf("---------------------------\n");
                if (choice == 1)
                    again++;
                else if (choice == 2) {
                    return 0;

                }

                else
                    again = 0;

            } while (again == 0);

        }

    } while (again == 1);

}

// Manager reset password 
void manager_reset_pass()
{

    char id[MAX_ID_LENGTH];
    int i, j;
    int ans;
    int correctAns = 0;
    char answer[50][2];
    char question[MAX_QUESTION_SELECTED][50];
    int idExist = 0;
    int choice;
    int again = 0;
    int questionNum[MAX_QUESTION_SELECTED];
    char enterAgain;

    do {

        again = 0;
        title();
        printf("\n--------------- RESET PASSWORD MANAGER---------------\n");
        printf("\n|||||||||||||||||||||||||||||||||||||||||||||||\n");
        printf("| You need to double check the data showe below |\n");
        printf("|||||||||||||||||||||||||||||||||||||||||||||||||\n");
        printf("\n------------------------------------------------------\n");
        printf("\nEnter ID:");
        scanf(" %[^\n]", id);

        for (i = 0; i < manager_count; i++)
        {
            if (strcmp(manager[i].table.id, id) == 0)
            {
                printf("\nName: %s\n", manager[i].table.name);
                printf("Email:%s\n", manager[i].table.email);
                do {
                    printf("\nIs you?\n");
                    printf("1. CORRECT, IS ME\n");
                    printf("2. WRONG, NOT ME\n");
                    scanf("%d", &ans);
                    idExist++;
                    if (ans == 1)
                    {
                        correctAns = 0;

                        for (int j = 0; j < MAX_QUESTION_SELECTED; j++)
                            questionNum[j] = manager[i].security[j].questionNum;


                        securityQues_display(questionNum, question);

                        do {

                            for (int j = 0; j < MAX_QUESTION_SELECTED; j++) {
                                printf("\n%s:", question[j]);
                                printf("\nAnswers:");
                                scanf(" %[^\n]", answer[j]);
                            }

                            for (int j = 0; j < MAX_QUESTION_SELECTED; j++) {
                                if (strcmp(answer[j], manager[i].security[j].securityAns) == 0) {
                                    correctAns++;
                                }
                            }


                            if (correctAns == MAX_QUESTION_SELECTED) {
                                printf("Please enter your new password: ");
                                scanf(" %[^\n]", manager[i].table.password);
                                printf("Password reset successfully.\n");
                                return;
                            }
                            else
                            {
                                do {
                                    printf("You failed to answer one or more security questions correctly.\n");
                                    Sleep(600);
                                    printf("Do u want to enter the answers for security password again?(Y/N):\n");
                                    scanf(" %c", &enterAgain);
                                    if (toupper(enterAgain) != 'N' && toupper(enterAgain) != 'Y')
                                    {
                                        printf("\nInvalid selection - Answers in Y/N only\n\n");
                                    }

                                } while (toupper(enterAgain) != 'N' && toupper(enterAgain) != 'Y');


                            }
                        } while (enterAgain == 'Y' || enterAgain == 'y');
                    }

                    else if (ans == 2) {
                        do {
                            title();
                            printf("Do you want to exit?\n");
                            printf("1. Yes\n");
                            printf("2. No\n");
                            printf("Enter your choice: ");
                            scanf("%d", &choice);

                            if (choice == 1)
                                // return back to manager menu
                                return 0;

                            if (choice == 2)
                                again++;


                        } while (choice != 1 && choice != 2);
                    }
                    else {
                        printf("Invalid select.\n");
                        Sleep(600);
                    }
                } while (ans != 1 && ans != 2);
            }
        }

        if (idExist == 0) {
            printf("\nNo manager found with the provided ID.\n");
            printf("You need to register first !\n\n");
            Sleep(600);
            return 0;
        }
    } while (again == 1);
}


// Manager Login menu --need to do let manager reset password!***
int manager_login() {
    char id[MAX_ID_LENGTH];
    char password[MAX_PASS_LENGTH];
    int loginSuccess = 0;
    int again = 0;
    int ans;
    int count = 0;

    title();
    printf("\n------ MANAGER LOGIN ------\n");

    do
    {
        loginSuccess = 0;
        printf("\nEnter your manager ID: ");
        scanf(" %[^\n]", id);
        printf("Enter your manager password: ");
        scanf(" %[^\n]", password);
        for (int i = 0; i < MAX_MANAGER; i++) {
            if (strcmp(manager[i].table.id, id) == 0 && strcmp(manager[i].table.password, password) == 0) {
                printf("\nLogin successful...\n");
                Sleep(600);
                employeeNum[1] = i;
                return 1;
                loginSuccess++;
            }
        }

        if (loginSuccess == 0)
        {
            do



            {
                again = 0;
                title();
                printf("\nInvalid ID or Password\n");
                printf("Do you want to try again?");
                printf("\n1. Yes\n");
                printf("2. No\n");
                printf("Enter you choice:");
                scanf("%d", &ans);
                printf("---------------------------\n");
                if (ans == 1) {
                    again++;
                    count++;
                }
                else if (ans == 2) {
                    return 0;
                }
                else {
                    again = 0;
                }
            } while (again == 0);

            if (count == 3)
            {

                printf("\nYou are failed to log in 3 time!\n");

                title();
                do {
                    printf("\n1. RESET PASSWORD\n");
                    printf("2. EXIT\n");
                    printf("Do u want to reset the password ?");
                    scanf("%d", &ans);

                    if (ans == 1)
                    {
                        manager_reset_pass();
                        count = 0;
                        return 0;
                    }
                    else if (ans == 2)
                    {
                        printf("\nYou are exit right now\n");
                        Sleep(600);
                        return 0;
                    }
                    else {
                        printf("Select again.\n");
                    }
                } while (ans != 1 && ans != 2);
            }

        }
    } while (again == 1 && loginSuccess == 0);

}



// Manager view staff schedule
void manager_view_schedule()
{


    char id[MAX_ID_LENGTH];
    int success = 0;
    int choice;
    title();
    do {
        printf("\n\n1. View all staff working schedules\n");
        printf("2. View particular staff working schedule\n");
        printf("Enter you choice:");
        scanf("%d", &choice);

        if (choice == 1)
        {
            for (int i = 0; i < staff_count; i++)
            {
                if (staff[i].schedule.total_working_hours != 0) {
                    printf("\n----------------- WORKING TIME SCHEDULE -----------------|- %s -|\n", staff[i].table.name);
                    printf("BEGIN TIME\t\tREST TIME\t\tEND TIME\n");
                    printf("%02d:%02d\t\t\t %d\t\t\t  %02d:%02d\n", staff[i].schedule.begin_hour, staff[i].schedule.begin_minute, staff[i].schedule.rest_time, staff[i].schedule.end_hour, staff[i].schedule.end_minute);
                    printf("TOTAL WORKING TIME : %d hours %d minutes (except rest time)\n", staff[i].schedule.total_working_hours, staff[i].schedule.remaining_minutes);
                    printf("-------------------------------------------------------------------\n");
                    system("pause");
                }
                else
                {
                    printf("\nSTAFF %s SCHEDULE IS Empty\n\n", staff[i].table.name);
                    Sleep(600);
                }
            }
        }
        else if (choice == 2)
        {
            printf("\nEnter staff ID to view the particular staff schedule:");
            scanf(" %[^\n]", id);

            for (int i = 0; i < staff_count; i++)
            {
                if (strcmp(staff[i].table.id, id) == 0)
                {
                    if (staff[i].schedule.total_working_hours != 0) {
                        title();
                        printf("\n----------------- WORKING TIME SCHEDULE -----------------|- %s -|\n", staff[i].table.name);
                        printf("BEGIN TIME\t\tREST TIME\t\tEND TIME\n");
                        printf("%02d:%02d\t\t\t %d\t\t\t  %02d:%02d\n", staff[i].schedule.begin_hour, staff[i].schedule.begin_minute, staff[i].schedule.rest_time, staff[i].schedule.end_hour, staff[i].schedule.end_minute);
                        printf("TOTAL WORKING TIME : %d hours %d minutes (except rest time)\n", staff[i].schedule.total_working_hours, staff[i].schedule.remaining_minutes);
                        printf("-------------------------------------------------------------------\n");
                    }
                    else
                    {
                        printf("Empty\n\n");
                        Sleep(600);
                    }

                    success++;
                }

            }

            if (success == 0) {
                printf("You haven't modify the staff working schedule\n");
                Sleep(600);
            }
        }
    } while (choice != 1 && choice != 2);
}


//Display all staff record
void dispalyAll()
{
    int counter = 0;
    title();
    printf("\n----------- RECORD OF ALL STAFF ----------------------------------\n");
    printf("\n|  %-20s  |  %-20s  |  %-20s  |\n", "Staff Name", "Phone No", "Email");

    for (int i = 0; i < staff_count; i++)
    {
        printf("|  %-20s  |  %-20s  |  %-20s  |\n", staff[i].table.name, staff[i].table.phone, staff[i].table.email);
        counter++;

    }
    printf("\nTOTAL STAFF RECORD FOUNDED --- %d ", counter);
    printf("\n------------------------------------------------------------------\n");
    system("pause");
}

// Staff Choice menu 
int staff_main_page() {
    int choice;
    int status = 0;

    do {
        title();
        printf("\nStaff\n");
        printf("-------\n");
        printf("1. Employee working schedule\n");
        printf("2. Update Information\n");
        printf("3. Train Schedules\n");
        printf("4. Search Member Information\n");
        printf("5. Working Time\n"); //combination of check in and out time!
        printf("6. Add Booking\n");
        printf("0. Log Out Staff\n"); //got log out bug
        printf("Enter your Choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            staff_schedule();
            break;
        case 2:
            staff_information();
            break;
        case 3:
        case 4:
        case 6:
            return choice;
            break;
        case 5:
            status = staff_logout();
            break;
        case 0:
            printf("Exiting...\n");
            Sleep(600);
            return 0;
            break;
        default:
            printf("\nPlease try again\n");
            Sleep(600);
            break;
        }
        if (status == 1) {
            return 0;
        }
    } while (choice != '0');
}

//Manager Choice menu 
int manager_main_page() {
    int choice;
    int status = 1;

    do {
        title();
        alert();
        printf("\nManager\n");
        printf("------\n");
        printf("1. Modify staff working schedule\n");
        printf("2. View staff working schedule\n");
        printf("3. Remove staff\n");
        printf("4. Display All staff record\n");
        printf("5. Update information\n");
        printf("6. Train Schedules\n");
        printf("7. Member Login History\n");
        printf("0. Log Out\n"); //can't directly log out! 
        printf("Enter your Choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            modifyEmpRestSchedule();
            break;
        case 2:
            manager_view_schedule();
            break;
        case 3:
            status = delete_Acc();
            break;
        case 4:
            dispalyAll();
            break;
        case 5:
            updateManager_information();
            break;
        case 6:
        case 7:
        case 0:
            return choice;
            break;
        default:
            printf("\nPlease try again\n");
            Sleep(600);
            break;
        }
    } while (choice != 0);

}