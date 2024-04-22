#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include<string.h>
#include <ctype.h>
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



void menu(struct Staff* staff, struct Manager* manager);
void staffMenu(struct Staff* staff, struct Manager* manager);
void staff_login(struct Staff* staff, struct Manager* manager);
void staff_registration(struct Staff* staff);
void staff_main_page(struct Staff* staff, struct Manager* manager, int staffNum);
void staff_schedule(struct Staff* staff, struct Manager* manager, int staffNum);
void staff_information(struct Staff* staff, struct Manager* manager, int staffNum);
void staff_logout(struct Staff* staff, int staffNum);
// manager
void manager_menu(struct Staff* staff, struct Manager* manager);
void manager_login(struct Staff* staff, struct Manager* manager);
void manager_registration(struct Manager* manager);
void manager_main_page(struct Staff* staff, struct Manager* manager, int managerNum);
void delete_Acc(struct Staff* staff, struct Manager* manager);
//void modify_staffInformation(struct Staff* staff, struct Manager* manager);
void modifyEmpRestSchedule(struct Staff* staff, struct Manager* manager);
void updateManager_information(struct Staff* staff, struct Manager* manager, int managerNum);
void resetPassword(struct Staff* staff);
void sendValidationCode(char* email, char* code);
char* generateValidationCode();
void manager_view_schedule(struct Staff* staff, struct Manager* manager);
void manager_reset_pass(struct Staff* staff, struct Manager* manager);
void security_Ques();
void securityQues_display(int questionSelection[MAX_QUESTION_SELECTED], char questionTitle[MAX_QUESTION_SELECTED][50]);
//
double calculate_hours(time_t check_in_time, time_t check_out_time);
void dispalyAll(struct Staff* staff, struct Manager* manager, int managerNum);


// Predefined employee and manager IDs and passwords
//const char employee_id[] = "emp123";
//const char employee_password[] = "password123";
//const char manager_id[] = "mgr456";
//const char manager_password[] = "password456";
//const char staff_id[] = "staff518518";

//structure for checkin in & out time
struct Schedule {

    int begin_hour;
    int begin_minute;
    char begin_period[3]; // "a.m." or "p.m."
    int rest_time;
    int end_hour;
    int end_minute;
    char end_period[3]; // "a.m." or "p.m."
    int total_working_hours;
    int remaining_minutes;

};

struct Staff{
    char staff_id[MAX_ID_LENGTH];
    char staff_password[MAX_PASS_LENGTH];
    char staff_name[MAX_NAME_LENGTH];
    char staff_phone[MAX_PHONE_LENGTH];
    char staff_email[MAX_EMAIL_LENGTH];
    char staff_position[MAX_POSITION_LENGTH];
    struct Schedule schedule;
};

struct M_SecurityQues {
    int questionNum;
    char securityAns[50];

};

struct Manager{ 
    char manager_id[MAX_ID_LENGTH];
    char manager_password[MAX_PASS_LENGTH];
    char manager_name[MAX_NAME_LENGTH];
    char manager_phone[MAX_PHONE_LENGTH];
    char manager_email[MAX_EMAIL_LENGTH];
    char manager_position[MAX_POSITION_LENGTH];
    struct M_SecurityQues security[MAX_QUESTION_SELECTED]; //nested structure
};

int staff_count = 0;
int manager_count = 0;


main() {
    struct Staff staff[MAX_STAFF];
    struct Staff staff2;
    struct Manager manager[MAX_MANAGER];
    


    FILE* fstaff;
    fstaff = fopen("../TrainTicketingSys/res/staff.bin", "rb");

    if (fstaff == NULL) {
        printf("Error Opening File\n");
        exit(-1);
    }

    //strcpy(staff[0].staff_id, "lgw123");
    //strcpy(staff[0].staff_password, "321");
    //strcpy(staff[0].staff_phone, "01231323");
    //strcpy(staff[0].staff_email, "lee@gmail.com");
    //strcpy(staff[0].staff_position, "STAFF");

    //strcpy(manager[0].manager_id, "ALi");
    //strcpy(manager[0].manager_password, "773");
    //strcpy(manager[0].manager_phone, "12312");
    //strcpy(manager[0].manager_email, "ali@ail.com");
    //strcpy(manager[0].manager_position, "MANAGER");

    //fwrite(&staff[0], sizeof(staff), 1, fstaff);
    //fwrite(&manager[0], sizeof(manager), 1, fstaff);

     fread(&staff2, sizeof(staff2), 1, fstaff);
     while (!feof(fstaff))
     {
        if (strcmp(staff2.staff_position, "STAFF") == 0)
        {
            strcpy(staff[staff_count].staff_id, staff2.staff_id);
            strcpy(staff[staff_count].staff_password, staff2.staff_password);
            strcpy(staff[staff_count].staff_phone, staff2.staff_phone);
            strcpy(staff[staff_count].staff_email, staff2.staff_email);
            strcpy(staff[staff_count].staff_position, staff2.staff_position);

            staff_count++;
        }

        if (strcmp(staff2.staff_position, "MANAGER") == 0)
        {
            strcpy(manager[manager_count].manager_id, staff2.staff_id);
            strcpy(manager[manager_count].manager_password, staff2.staff_password);
            strcpy(manager[manager_count].manager_phone, staff2.staff_phone);
            strcpy(manager[manager_count].manager_email, staff2.staff_email);
            strcpy(manager[manager_count].manager_position, staff2.staff_position);
            manager_count++;
        }
        fread(&staff2, sizeof(staff2), 1, fstaff);
    }
     //write new information to file.
     //strcpy(staff[1].staff_id, "staff1");
     //strcpy(staff[1].staff_password, "321");
     //strcpy(staff[1].staff_phone, "01231323");
     //strcpy(staff[1].staff_email, "lee@gmail.com");
     //strcpy(staff[1].staff_position, "STAFF");
     //staff_count++;

   //test file read 
     for (int i = 0; i < staff_count; i++) {
         printf("ID: %s\n", staff[i].staff_id);
    }

     for (int i = 0; i < manager_count; i++) {
         printf("ID: %s\n", staff[i].staff_id);
     }


    fclose(fstaff);

    menu(staff, manager);

    //print all manager and staff account

    for (int i = 0; i < staff_count; i++) {
        printf("ID: %s\n", staff[i].staff_id);
    }

    for (int i = 0; i < manager_count; i++) {
        printf("ID: %s\n", staff[i].staff_id);
    }

    fstaff = fopen("../TrainTicketingSys/res/staff.bin", "wb");

    for (int i = 0; i < manager_count; i++) {
        fwrite(&manager[i], sizeof(manager), 1, fstaff);
    }

    for (int i = 0; i < staff_count; i++) {
        fwrite(&staff[i], sizeof(staff), 1, fstaff);
    }

    fclose(fstaff);
    return 0;

}


//heading all pages
void title(void) {
   // system("cls");
    printf("%10s %s %s", "Train", "Ticketing", "System");
    time_t t;
    time(&t);
    printf("%125s", ctime(&t));
    for (int i = 0; i < 155; i++) {
        printf("%s", "-");
    }
    printf("\n\n");
}


// Main menu
void menu(struct Staff* staff, struct Manager* manager) 
{
    int choice;
    struct tm* hour;
    char buffer[50];
    time_t t;
    time(&t);

    hour = localtime(&t);
    strftime(buffer, 50, "%X", hour);

    //system("cls");
    do {
        /*title();*/
        printf("------ EMPLOYEE MENU ------\n");
        printf("-------------------------\n");
        printf("1. Staff\n");
        printf("2. Manager\n");
        printf("3. Exit Program\n");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            staffMenu(staff, manager);
            break;
        case 2:
            manager_menu(staff, manager);
            break;
        case 3:
            break;
        default:
            //got error when loop
            printf("Invalid Choice!\n");
            printf("Please Select Again\n");
            //only can validate numeric answer
            //if enter character or string, it will be error
        }

    } while (choice != 3);
    printf("\nYou are Log Out %s Right Now!\n", buffer);


}

// staff Menu!
void staffMenu(struct Staff* staff, struct Manager* manager)
{
    int choice;

   //system("cls");
    do {
        /*title();*/
        printf("\n------ STAFF MENU ------\n");
        printf("-------------------------\n");
        printf("1. Login\n");
        printf("2. Registration\n");
        printf("3. Exit\n");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            staff_login(staff, manager);
            break;
        case 2:
            staff_registration(staff);
            break;
        case 3:
            printf("Exiting....\n");
            break;
        default:
            printf("Invalid Choice!\n");
            printf("Please Select Again\n");
            break;
            //only can validate numeric answer
            //if enter character or string, it will be error
        }

    } while (choice != 3);
    printf("\nYou are Exit Right Now!\n");

}


// Staff Login menu
void staff_login(struct Staff* staff, struct Manager* manager) 
{
    char id[MAX_ID_LENGTH];
    char password[MAX_PASS_LENGTH];
    int loginSuccess = 0;
    int count = 0;
    int ans;
    int again = 0;

    /*title();*/
    printf("------ STAFF Login ------\n");

    do 
    {
        printf("\nEnter your staff ID: ");
        scanf(" %[^\n]", id);
        printf("Enter your staff password: ");
        scanf(" %[^\n]", password);
        for (int i = 0; i < MAX_STAFF; i++)
        {
            if (strcmp(staff[i].staff_id, id) == 0 && strcmp(staff[i].staff_password, password) == 0)
            {
                printf("Login successful...\n");
                staff_main_page(staff, manager,i);
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
                    //system("cls");
                }
                else
                    again = 0;

            } while (again == 0);

            //
            if (count == 3)
            {
                printf("\nYou are failed to log in!\n");
                printf("\n1. RESET PASSWORD\n");
                printf("2. EXIT\n");
                printf("Do u want to reset the password ?");
                scanf("%d", &ans);

                if (ans == 1) 
                {
                    resetPassword(staff);
                }
                else
                {
                    printf("You are exit right now!\n");
                    return 0;
                }

            }


        }
    } while (again ==1);
   // system("cls");
}

//staff registration menu 
void staff_registration(struct Staff* staff) {
    char id[MAX_ID_LENGTH];
    char name[MAX_NAME_LENGTH];
    char password[MAX_PASS_LENGTH];
    char position[MAX_POSITION_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char phoneNo[MAX_PHONE_LENGTH];

    /*title();*/
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

    for (int i = 0; i < MAX_STAFF; i++) {
        if (strcmp(staff[i].staff_id, id) == 0) {
            printf("The ID %s already exits.\n", id);
            printf("Please choose a different ID.\n");
            return 0;
        }
    }

    strcpy(staff[staff_count].staff_id, id);
    strcpy(staff[staff_count].staff_name, name);
    strcpy(staff[staff_count].staff_password, password);
    strcpy(staff[staff_count].staff_phone, phoneNo);
    strcpy(staff[staff_count].staff_email, email);
    //copy email and phone
    strcpy(staff[staff_count].staff_position, "STAFF");


    //write all equal to 0 or NULL;
    
        staff[staff_count].schedule.total_working_hours = 0; ////!!!!!
    


    printf("\nRegistration successfully\n\n");

    staff_count++;
   // system("cls"); // This make some notification can't detect.
}


// Staff Choice menu //got error
void staff_main_page(struct Staff* staff, struct Manager* manager, int staffNum) {
    int choice;
    char select;

    //system("cls");
    do {
        /*title();*/
        printf("\nStaff\n");
        printf("------\n");
        printf("1. Employee working schedule\n");
        printf("2. Update Information\n");
       // printf("3. Tickets available\n");
       // printf("4. customer data\n");
        printf("5. Working Time\n"); //combination of check in and out time!
        printf("6. Log Out Staff\n");
        printf("Enter your Choice: ");
        scanf("%d", &choice);
        // maybe got loop infiniti problem

        switch (choice) {
        case 1:
            staff_schedule(staff, manager, staffNum);
            break;
        case 2:
            staff_information(staff, manager, staffNum);
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            staff_logout(staff, staffNum);
            break;
        case 6:
            printf("Exiting...\n");
            break;
        default:
            break;
        }
        if (choice == 1 || choice == 2 || choice == 3 || choice == 4 || choice == 5) {
            printf("\nSelect again? (Y||N) : ");
            scanf(" %c", &select);
        }

    } while (toupper(select) == 'Y');
}

//staff rest schedule 
void staff_schedule(struct Staff* staff, struct Manager* manager, int staffNum)
{
    
    if (staff[staffNum].schedule.total_working_hours != 0) {
        printf("\n----------------- WORKING TIME SCHEDULE -----------------|- %s -|\n", staff[staffNum].staff_name);
        printf("BEGIN TIME\tREST TIME\tEND TIME\n");
        printf("%02d:%02d %s\t%d\t%02d:%02d\t%s\n", staff[staffNum].schedule.begin_hour, staff[staffNum].schedule.begin_minute, staff[staffNum].schedule.begin_period, staff[staffNum].schedule.rest_time, staff[staffNum].schedule.end_hour, staff[staffNum].schedule.end_minute, staff[staffNum].schedule.end_period);
        printf("TOTAL WORKING TIME : %d hours %d minutes (except rest time)\n", staff[staffNum].schedule.total_working_hours, staff[staffNum].schedule.remaining_minutes);
        printf("-------------------------------------------------------------------\n");
    }
    else
        printf("Sorry,Your schedule haven't done modified yet.\n");

}


//staff update information !!Logic error
void staff_information(struct Staff* staff, struct Manager* manager, int staffNum) {
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

        /*title();*/
                /*title();*/
                // Before edit --change the versio view
                printf("---------------------------\n");
                printf("------ Before Update ------\n");
                printf("---------------------------\n");
                printf("\nName: %s\n", staff[staffNum].staff_name);
                printf("Phone No: %s\n", staff[staffNum].staff_phone);
                printf("Email:%s\n", staff[staffNum].staff_email);


                printf("\nConfirm? ");
                scanf(" %c", &confirm);

                if (confirm == 'Y' || confirm == 'y') {
                    printf("\n--------------------------\n");
                    printf("---------- UPDATE ----------\n");
                    printf("----------------------------\n");
                    printf("\nName:");
                    scanf(" %[^\n]", name);
                    printf("Phone No:");
                    scanf(" %[^\n]", phone);
                    printf("Email:");
                    scanf(" %[^\n]", email);

                    strcpy(staff[staffNum].staff_name, name);
                    strcpy(staff[staffNum].staff_phone, phone);
                    strcpy(staff[staffNum].staff_email, email);

                    success++;

                    printf("\nUpdate was done successfully!\n");

                    printf("\n---------------------------\n");
                    printf("------- After Updated -------\n");
                    printf("-----------------------------\n");
                    printf("Staff ID: %s\n", staff[staffNum].staff_id);
                    printf("\nName: %s\n", staff[staffNum].staff_name);
                    printf("Phone No: %s\n", staff[staffNum].staff_phone);
                    printf("Email:%s\n", staff[staffNum].staff_email);
                    printf("\n---------------------------\n");
                }
                else
                {
                    printf("Update unsuccessfull\n");
                }

          
        if (success == 0) {
            do {
                again = 0;

                /*title();*/
                printf("\n--------------------------\n");
                printf("ID of staff %s not found!!\n", staff[staffNum].staff_name);
                printf("DO you want to enter again?");
                printf("\n1. Yes\n");
                printf("2. No\n");
                printf("Enter you choice:");
                scanf("%d", &choice);
                printf("---------------------------\n");
                if (choice == 1)
                    again++;
                else if (choice == 2) {
                    return 0;
                    //system("cls");
                }

                else
                    again = 0;
            } while (again == 0);

        }

    } while (again == 1);
}




//combination of log out&in time selected
void staff_logout(struct Staff* staff, int staffNum) {
    int ans, choice;
    time_t check_in_time = 0;
    time_t check_out_time = 0;
    time_t break_time = 0;

    clock_t checkIn = 0, checkOut = 0;
    double elapsedTime;

    printf("\n STAFF WORKING TIME RECORDED\n");
    printf("=======================\n");
    printf("\n1. CHECK IN\n");
    printf("2. CHECK OUT\n");
    printf("Enter your choice:");
    scanf("%d", &ans);
    printf("\n======================\n");

    if (ans == 1) {
        checkIn = clock();
        // Check in
        time(&check_in_time);
        printf("---------CHECK IN------------\n");
        printf("STAFF ID:%s\tCHECK IN TIME:%s", staff[staffNum].staff_id, ctime(&check_in_time));
        printf("Check In succeed");


    }
    else if (ans == 2) {
        checkOut = clock();
        // Check out
        time(&check_out_time);
        printf("----------CHECK OUT------------\n");
        printf("STAFF ID:%s\tCHECK OUT TIME:%s", staff[staffNum].staff_id, ctime(&check_out_time));

        elapsedTime = (double)(checkOut - checkIn) / CLOCKS_PER_SEC;


        if (elapsedTime > 8 * 3600) {
            printf("You have completed 8 hours of work today.\n");
        }
        else {
            printf("You have not completed 8 hours of work today.\n");
            printf("Are you sure you want to check out? (1 for Yes, 0 for No): ");
            scanf("%d", &choice);
            if (choice == 1) {
                // Exit and return to the menu
                printf("Exiting...\n");
                // You may want to return to the main menu or exit the program here
            }
            else {
                // Return to check in and out interface
                staff_logout(staff, staffNum);
            }
        }
    }
}



// Staff reset password **
void resetPassword(struct Staff* staff)
{
    char id[MAX_ID_LENGTH];
    char phone[MAX_PHONE_LENGTH];
    int ans;
    int successfuly = 0;
    int codeReceived;
    char newPassword[MAX_PASS_LENGTH];
    char comf_newPassword[MAX_PASS_LENGTH];

    printf("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    printf("| You need to double check the data showe below |\n");
    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");


    printf("\nEnter ID:");
    scanf(" %[^\n]", id);

    for (int i = 0; i < staff_count; i++)
    {
        if (strcmp(staff[i].staff_id, id) == 0)
        {
            printf("\nName: %s\n", staff[i].staff_name);
            printf("Email:%s\n", staff[i].staff_email);
            printf("\nIs you?\n");
            printf("1. CORRECT, IS ME\n");
            printf("2. WRONG, NOT ME\n");
            scanf("%d", &ans);

            if (ans == 1)
            {
                printf("Please enter you phone number to validation\n");
                scanf(" %[^\n]", phone);
                if (strcmp(staff[i].staff_phone, phone) == 0)
                {
                    printf("Sending a validation code to your email\n");
                    //....the waiting time
                    //random()
                    //store(send) the code to email.Then compare the code staff keyin and the code in the email.
                    char* code = generateValidationCode();
                    sendValidationCode(staff[i].staff_email, code);
                    printf("\nPlease enter the validation code you receive:");
                    scanf("%d", &codeReceived);

                    /*if (strcmp(code, codeReceived) == 0)*/   //got error
                    if (atoi(code) == codeReceived)
                    {
                        printf("Able to reset the password\n");

                        successfuly = 0;
                        do {
                            printf("Enter the new password:");
                            scanf(" %[^\n]", newPassword);
                            printf("\nEnter again the same password:");
                            scanf(" %[^\n]", comf_newPassword);

                            if (strcmp(newPassword, comf_newPassword) == 0)
                            {
                                printf("Success!\n");
                                strcpy(staff[i].staff_password, comf_newPassword);
                                successfuly++;
                                return 0;
                            }
                            else {
                                printf("Failed!\n");
                                successfuly = 0;
                            }
                        } while (successfuly == 0);

                    }
                    else
                        printf("Validation code incorrect!\n");

                }

            }
            else
                printf("You phone number is incorrect!\n");
        }
        else {
            printf("Authentication failed.\n");
        }
        /* return;*/

    }
    printf("Staff ID not found.\n");
    /*return 0;*/
}

// Reference only!  
//                    if (atoi(code) == codeReceived) {
//                        printf("Able to reset the password\n");
//                        do {
//                            printf("Enter the new password:");
//                            scanf(" %[^\n]", newPassword);
//                            printf("\nEnter the new password again:");
//                            scanf(" %[^\n]", comf_newPassword);
//
//                            if (strcmp(newPassword, comf_newPassword) == 0) {
//                                printf("Password reset successful!\n");
//                                return 1; // Password reset successful
//                            }
//                            else {
//                                printf("Passwords do not match!\n");
//                            }
//                        } while (1); // Infinite loop until passwords match //this is incorrect
//                    }
//                    else {
//                        printf("Validation code incorrect!\n");
//                    }
//                }
//                else {
//                    printf("Your phone number is incorrect!\n");
//                }
//            }
//            else {
//                printf("Authentication failed.\n");
//            }
//            return 0; // Authentication failed
//        }
//    }
//    printf("Staff ID not found.\n");
//    return 0; // Staff ID not found
//}


void sendValidationCode(char* email, char* code) {
    // Implement sending the validation code to the provided email
    printf("Validation code sent to %s is: %s\n", email, code);
}

char* generateValidationCode() {
    // Generate a random validation code (simplified example)
    char* code = (char*)malloc(7 * sizeof(char)); // 6 characters + null terminator
    sprintf(code, "%06d", rand() % 1000000);
    return code;
}


// Manager menu
void manager_menu(struct Staff* staff, struct Manager* manager) 
{
    int choice;
    struct tm* hour;
    char buffer[50];
    time_t t;
    time(&t);

   // system("cls");
    do {
        /*title();*/
        printf("\n------ MANAGER MENU ------\n");
        printf("-------------------------\n");
        printf("1. Login\n");
        printf("2. Registration\n");
        printf("3. Exit\n");
        scanf("%d", &choice);


        switch (choice) {
        case 1:
            manager_login(staff, manager);
            break;
        case 2:
            manager_registration(manager);
            break;
        case 3:
            printf("Exiting....\n");
            break;
        default:
            printf("Invalid Choice!\n");
            printf("Please Select Again\n");
            //only can validate numeric answer
            //if enter character or string, it will be error
        }

    } while (choice != 3);
    printf("\nYou are Exit Right Now!\n");
}

// Manager Login menu --need to do let manager reset password!***
void manager_login(struct Staff* staff, struct Manager* manager) {
    char id[MAX_ID_LENGTH];
    char password[MAX_PASS_LENGTH];
    int loginSuccess = 0;
    int again = 0;
    int ans;
    int count = 0;
    
    /*title();*/
    printf("\n------ MANAGER Login ------\n");

    do
    {
        printf("\nEnter your manager ID: ");
        scanf(" %[^\n]", id);
        printf("Enter your manager password: ");
        scanf(" %[^\n]", password);
        for (int i = 0; i < MAX_MANAGER; i++) {
            if (strcmp(manager[i].manager_id, id) == 0 && strcmp(manager[i].manager_password, password) == 0) {
                printf("\nLogin successful...\n");
                manager_main_page(staff, manager, i);
                loginSuccess++;
            }
        }

        if (loginSuccess == 0)
        {
            do
            {
                again = 0;
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
                   // system("cls");
                }
                else {
                    again = 0;
                }
                    
                if (count == 3)
                {
                    printf("\nYou are failed to log in 3 time!\n");
                    printf("\n1. RESET PASSWORD\n");
                    printf("2. EXIT\n");
                    printf("Do u want to reset the password ? ____   ____");
                    scanf("%d", &ans);

                    if (ans == 1)
                    {
                        manager_reset_pass(staff, manager);
                        count = 0;
                        printf("%d\n", again);
                    }
                    else
                    {
                        printf("\nYou are exit right now\n");
                        return 0;
                    }

                }

            } while (again == 0);

           /* if (count == 3)
            {
                printf("\nYou are failed to log in 3 time!\n");
                printf("\n1. RESET PASSWORD\n");
                printf("2. EXIT\n");
                printf("Do u want to reset the password ? ____   ____");
                scanf("%d", &ans);

                if (ans == 1)
                {
                    manager_reset_pass(manager);
                }
                else
                {
                    printf("\nYou are exit right now\n");
                    return 0;
                }

            }*/

            //return 0;
        }
    } while (again == 1);

}

//Manager Choice menu 
void manager_main_page(struct Staff* staff, struct Manager* manager, int managerNum) {
    int choice;
    char select;
    
   // system("cls");
    do {
        /*title();*/
        printf("\nManager\n");
        printf("------\n");
        printf("1. Modify staff rest schedule\n");
        printf("2. View staff working schedule\n");
        printf("3. Remove staff\n");
        printf("4. Display All staff record\n");
        printf("5. Update information\n");
        printf("6. Log Out\n");
        printf("Enter your Choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            modifyEmpRestSchedule(staff, manager);
            break;
        case 2:
            manager_view_schedule(staff, manager);
            break;
        case 3:
            delete_Acc(staff, manager, managerNum);
            break;
        case 4:
            dispalyAll(staff, manager, managerNum);
            break;
        case 5:
            //modify_staffInformation(staff, manager); --become manager update themself information
            updateManager_information(staff, manager, managerNum);
            break;
        case 6:
            break;
        default:
            break;
        }
        printf("\nSelect again? (Y||N) : ");
        scanf(" %c", &select);

    } while (toupper(select) == 'Y');
    printf("Invalide select.");
}

// Manager registration !**** got error
void manager_registration(struct Manager* manager) {
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
    

    /*title();*/
    printf("\Manager Registration\n");
    printf("--------------------\n");
    printf("Manager ID: ");
    scanf(" %[^\n]", id);
    printf("Name: ");
    scanf(" %[^\n]", name);
    printf("Password: ");
    scanf(" %[^\n]", password);

    for (int i = 0; i < manager_count; i++) {
        if (strcmp(manager[i].manager_id, id) == 0) {
            printf("The ID %s already exits.\n", id);
            printf("Please choose a different ID.\n");
            return 0;
        }
    }

    again = 0;
    // here testing ---------------------------------------
    do {
        /*again = 0;*/
        success = 1;

        security_Ques();

        for (int i = 0; i < MAX_QUESTION_SELECTED; i++) {
            printf("%d. ", i + 1);
            scanf("%d", &questionSelection[i]);

            if (questionSelection[i] > 5 || questionSelection[i] < 1) {
                printf("Invalid Choice!\n");
                printf("Please Enter Number 1 - 5!\n");
                success = 0;
                break; // maybe can changes
            }
            if (i > 0) {
                for (int q = 0; q < i; q++) 
                {
                    if (questionSelection[i] == questionSelection[q]) {
                        printf("\nSelect the difference\n");
                        printf("Please Try Again.\n");
                        again++;
                        success = 0;
                        break;
                    }
                }
                if (again == 1)
                    break;
            }
        }
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

    strcpy(manager[manager_count].manager_id, id);
    strcpy(manager[manager_count].manager_name, name);
    strcpy(manager[manager_count].manager_password, password);
    strcpy(manager[manager_count].manager_phone, phone);
    strcpy(manager[manager_count].manager_email, email);
    strcpy(manager[staff_count].manager_position, "MANAGER");


    printf("\nRegistration successfully\n\n");

    manager_count++;
    //system("cls");
}

//Manager delete/remove staff acc 
void delete_Acc(struct Staff* staff, struct Manager* manager, int managerNum)
{
    int confirm;
    char answers;
    char deleteID[MAX_ID_LENGTH];
    int deleted = 0;
    int again = 0;
    int done = 1;
    int choice;
   // system("cls");

    do
    {
        done = 1;
        deleted = 0;
        again = 0;

        /*title();*/
        printf("you are able to delete the record\n");

        printf("\nEenter staff id to delete :");
        rewind(stdin);
        scanf("%[^\n]", deleteID);

        for (int i = 0; i < MAX_STAFF; i++)
        {
            if (strcmp(staff[i].staff_id, deleteID) == 0)
            {
                printf("\n----------- RECORD OF STAFF -----------\n");
                printf("\nStaff Name\tPhone No\tEmail\n");
                printf("%s\t%s\t%s", staff[i].staff_name, staff[i].staff_phone, staff[i].staff_email);
                printf("\n------------------------------------------\n");

                do{
                printf("\nConfirm To delete?\n");
                printf("\n1. Yes\n");
                printf("2. No\n");
                printf("Enter you choice:");
                scanf(" %d", &confirm);
                printf("\n------------------------------------------\n");

                
                    if (confirm == 1) 
                    {

                            strcpy(staff[i].staff_id, staff[i + 1].staff_id);
                            strcpy(staff[i].staff_name, staff[i + 1].staff_name);
                            strcpy(staff[i].staff_password, staff[i + 1].staff_password);
                            strcpy(staff[i].staff_email, staff[i + 1].staff_email);
                            strcpy(staff[i].staff_phone, staff[i + 1].staff_phone);
                            strcpy(staff[i].staff_position, staff[i + 1].staff_position);
                            staff_count--;

                            deleted++;

                            printf("\nDELETE SUCCESSFUL\n");
                        
                        
                    }
                       
                    else if (confirm == 2)
                    {
                        printf("\nEXIT FROM REMOVE STAFF MENU.\n");
                        return 0;
                        //system("cls");
                    }

                    else
                        done = 0;

                } while (done == 0);
                
            }
            
        }

        if (deleted == 0) {
            printf("INVALID ");
            return manager_main_page(staff, manager, managerNum);
            //got bug
            //havent done yet
        }
        if (deleted == 1) {
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
                        //system("cls");
                    }
                else
                again = 0;

            } while (again == 0);
           
        }
        
        // havent done yet

    } while (done == 1);
}


//manager modify particular staff / entire staff rest schedule !*
void modifyEmpRestSchedule(struct Staff* staff, struct Manager* manager)
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
        /*title();*/

        printf("\n------- Particular staff rest schedule -------\n");
        printf("Staff ID:");
        scanf(" %[^\n]", &id);

        for (int i = 0; i < staff_count; i++)
        {

            if (strcmp(staff[i].staff_id, id) == 0)
            {
                do { ///
                    reenter = 0;
                    printf("\nEDIT %s WORKING TIME\n", staff[i].staff_name);
                    printf("\nBEGIN (hh:mm a.m./p.m.): ");
                    if (scanf("%d:%d %s", &staff[i].schedule.begin_hour, &staff[i].schedule.begin_minute, staff[i].schedule.begin_period)!= 3) 
                    {
                        printf("Invalid input format. Please enter time in hh:mm a.m./p.m. format.\n");
                        reenter++;
                    }
                    printf("\nREST (minutes): ");
                    scanf("%d", &staff[i].schedule.rest_time);
                    printf("\nEND (hh:mm a.m./p.m.): ");
                    if (scanf("%d:%d %s", &staff[i].schedule.end_hour, &staff[i].schedule.end_minute, staff[i].schedule.end_period) != 3)
                    {
                        printf("Invalid input format. Please enter time in hh:mm a.m./p.m. format.\n");
                        reenter++;
                    }

                    
                } while (reenter != 0);

             /*   printf("\nEDIT %s WORKING TIME\n", staff[i].staff_name);
                printf("\nBEGIN (hh:mm a.m./p.m.): ");
                scanf("%d:%d %s", &staff[i].schedule.begin_hour, &staff[i].schedule.begin_minute, staff[i].schedule.begin_period);
                printf("\nREST (in minutes): ");
                scanf("%d", &staff[i].schedule.rest_time);
                printf("\nEND (hh:mm a.m./p.m.): ");
                scanf("%d:%d %s", &staff[i].schedule.end_hour, &staff[i].schedule.end_minute, staff[i].schedule.end_period);*/


                //here testing==============================
                total_begin_minutes = staff[i].schedule.begin_hour * 60 + staff[i].schedule.begin_minute;
                total_end_minutes = staff[i].schedule.end_hour * 60 + staff[i].schedule.end_minute;
                total_working_minutes = total_end_minutes - total_begin_minutes - staff[i].schedule.rest_time;

                // Adjust for overnight working(if end time is before begin time)
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

                    printf("\n---------------------------------------------\n");
                    printf("| WORKING TIME UPDATED SUCCESSFULLY |\n");
                    printf("---------------------------------------------\n");

                    printf("\n----------------- WORKING TIME SCHEDULE -----------------|- %s -|\n", staff[i].staff_name);
                    printf("BEGIN TIME\tREST TIME\tEND TIME\n");
                    printf("%02d:%02d %s\t%d\t%02d:%02d\t%s\n", staff[i].schedule.begin_hour, staff[i].schedule.begin_minute, staff[i].schedule.begin_period, staff[i].schedule.rest_time, staff[i].schedule.end_hour, staff[i].schedule.end_minute, staff[i].schedule.end_period);
                    printf("TOTAL WORKING TIME : %d hours %d minutes (exclude rest time)\n", total_working_hours, remaining_minutes);
                    printf("-------------------------------------------------------------------\n");

                    staff[i].schedule.total_working_hours = total_working_hours;
                    staff[i].schedule.remaining_minutes = remaining_minutes;
                    // system("cls");

                }
                else 
                {
                    printf("---------------------------------------------\n");
                    printf("| STAFF END WORKING TIME MUST ENOUGH 8 HOUR |\n");
                    printf("---------------------------------------------\n");
                }

                successful++;

            }

        }

        if (successful == 0) 
        {
            do
            {
                ans = 0;
                printf("Invalid -- Wrong ID --\n");
                printf("DO you want to enter again?");
                printf("\n1. Yes\n");
                printf("2. No\n");
                printf("Enter you choice:");
                scanf("%d", &choice);
                printf("---------------------------\n");
                if (choice == 1)
                    ans++;
                else if (choice == 2)
                {
                    printf("\nEXIT\n");
                    
                    return 0;
                }

                else
                    ans = 0;

            } while (ans == 0);

        }
        else
        {
            do {
                //got error 
                printf("\n1. CONTINUE\n");
                printf("2. EXIT\n");
                printf("Enter you choice:");
                scanf("%d", &choice);

                if (choice == 1)
                    again++;
                else if (choice == 2) {
                    return 0;
                   // system("cls");
                }
                else
                    again = 0;

            } while (again == 0);
        }

    } while (ans == 1);
        }


//Manager update information
void updateManager_information(struct Staff* staff, struct Manager* manager, int managerNum) {
        char name[MAX_NAME_LENGTH];
        char email[MAX_EMAIL_LENGTH];
        char phone[MAX_PHONE_LENGTH];
        char stop;
        int success = 0, again = 0, choice;

        do {
            success = 0;
            again = 0;
            /*title();*/

            //no need enter manager ID alredy pass from parameter
           
                    // Before edit
                    printf("---------------------------\n");
                    printf("------ Before Update ------\n");
                    printf("---------------------------\n");
                    printf("\nName: %s\n", manager[managerNum].manager_name);
                    printf("Phone No: %s\n", manager[managerNum].manager_phone);
                    printf("Email:%s\n", manager[managerNum].manager_email);

                    //ask manager to update
                    printf("\n--------------------------\n");
                    printf("----- UPDATE RIGHT NOW -----\n");
                    printf("----------------------------\n");
                    printf("\nName:");
                    scanf(" %[^\n]", name);
                    printf("Phone No:");
                    scanf(" %[^\n]", phone);
                    printf("Email:");
                    scanf(" %[^\n]", email);

                    strcpy(manager[managerNum].manager_name, name);
                    strcpy(manager[managerNum].manager_phone, phone);
                    strcpy(manager[managerNum].manager_email, email);

                    success++;

                    printf("\nYou are successful updated.\n");

                    printf("\n---------------------------\n");
                    printf("------- After Updated -------\n");
                    printf("-----------------------------\n");
                    printf("Manager ID: %s\n", manager[managerNum].manager_id);
                    printf("\nName: %s\n", manager[managerNum].manager_name);
                    printf("Phone No: %s\n", manager[managerNum].manager_phone);
                    printf("Email:%s\n", manager[managerNum].manager_email);
                    printf("\n---------------------------\n");

                    // system("cls");

            if (success == 0) {
                do {
                    again = 0;
                    printf("\n--------------------------\n");
                    printf("Invalid | Wrong Manager ID |\n");
                    printf("DO you want to enter again?");
                    printf("\n1. Yes\n");
                    printf("2. No\n");
                    printf("Enter you choice:");
                    scanf("%d", &choice);
                    printf("---------------------------\n");
                    if (choice == 1)
                        again++;
                    else if (choice == 2) {
                        return 0;
                        //system("cls");
                    }
                       
                    else
                        again = 0;

                } while (again == 0);

            }

        } while (again == 1);
        
}
     


// Manager reset password *****
void manager_reset_pass(struct Staff* staff, struct Manager* manager)
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
    
    do {
        again = 0;
        printf("\n--------------- RESET PASSWORD manager---------------\n");
        printf("\n|||||||||||||||||||||||||||||||||||||||||||||||\n");
        printf("| You need to double check the data showe below |\n");
        printf("|||||||||||||||||||||||||||||||||||||||||||||||||\n");

        printf("\nEnter ID:");
        scanf(" %[^\n]", id);

        for (i = 0; i < manager_count; i++)
        {
            if (strcmp(manager[i].manager_id, id) == 0)
            {
                printf("\nName: %s\n", manager[i].manager_name);
                printf("Email:%s\n", manager[i].manager_email);
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
                        scanf(" %[^\n]", manager[i].manager_password);
                        printf("Password reset successfully.\n");   
                        return;
                    }
                    else
                    {
                        printf("You failed to answer one or more security questions correctly.\n");
                        return;
                    }
                }

                else if (ans == 2) {
                    do {
                        printf("Do you want to exit?\n");
                        printf("1. Yes\n");
                        printf("2. No\n");
                        printf("Enter your choice: ");
                        scanf("%d", &choice);

                        if (choice == 1)
                            // add return back to manager menu
                            return manager_menu(staff, manager);

                        if (choice == 2) 
                            again++;
                        

                    } while (choice != 1 && choice != 2);
                }
            }
        }
        if (idExist == 0) {
            printf("\nNo manager found with the provided ID.\n");
            printf("You need to register first !\n\n");
            return manager_registration(manager);
        }
    } while (again == 1);
 }
            



// Security question 
void security_Ques() 
{

    printf("\n------------- Security Question -------------\n");
    printf("|  Choose 2 question as your security question  |\n");
    
    printf("1. What was the first name of your first pet?\n");
    printf("2. What was your childhood nickname?\n");
    printf("3. What are the favorite food as a child?\n");
    printf("4. In what city were you born?\n");
    printf("5. What is your mother's maiden name?\n");
    

    printf("-----------------------------------------------\n");

    
}


//got arrow when reset passw
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

  /*      if (questionSelection[i] == 1) 
            strcpy(questionTitle[i], "What was the first name of your first pet?");
        else if (questionSelection[i] == 2)
            strcpy(questionTitle[i], "What was your childhood nickname?");
        else if (questionSelection[i] == 3)
            strcpy(questionTitle[i], "What are the favorite food as a child?");
        else if (questionSelection[i] == 4)
            strcpy(questionTitle[i], "In what city were you born?");
        else 
            strcpy(questionTitle[i], "What is your mother's maiden name?");*/

    }
}

// Manager view staff schedule
void manager_view_schedule(struct Staff* staff, struct Manager* manager)
{
    //maybe let if the schedule did't have anythin printf("Sorry you can't see the schedule")???

    char id[MAX_ID_LENGTH];
    int success = 0;

    printf("\nEnter staff ID to view the particular staff schedule:");
    scanf(" %[^\n]", id);

    for (int i = 0; i < staff_count; i++)
    {
        if (strcmp(staff[i].staff_id, id) == 0)           
        {
            if (staff[i].schedule.total_working_hours != 0) {
                printf("\n----------------- WORKING TIME SCHEDULE -----------------|- %s -|\n", staff[i].staff_name);
                printf("BEGIN TIME\tREST TIME\tEND TIME\n");
                printf("%02d:%02d %s\t%d\t%02d:%02d\t%s\n", staff[i].schedule.begin_hour, staff[i].schedule.begin_minute, staff[i].schedule.begin_period, staff[i].schedule.rest_time, staff[i].schedule.end_hour, staff[i].schedule.end_minute, staff[i].schedule.end_period);
                printf("TOTAL WORKING TIME : %d hours %d minutes (except rest time)\n", staff[i].schedule.total_working_hours, staff[i].schedule.remaining_minutes);
                printf("-------------------------------------------------------------------\n");
            }
            else 
{
                printf("Empty\n\n");
            }

            success++;
        }

    }

    if (success == 0) {
        printf("You haven't modify the staff working schedule\n");
        //add print invalid
    }

}


//Display all staff record
void dispalyAll(struct Staff* staff, struct Manager* manager, int staffNum)
{
    
        printf("\n----------- RECORD OF STAFF -----------\n");
        printf("\nStaff Name\tPhone No\tEmail\n");

        for (int i = 0; i < staff_count; i++)
        {
        printf("%s\t%s\t%s", staff[i].staff_name, staff[i].staff_phone, staff[i].staff_email);

        }
        printf("\n------------------------------------------\n");
    
}