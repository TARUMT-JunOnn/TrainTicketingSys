#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include<string.h>
#include <ctype.h>
#include <Windows.h>
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
int staff_login(struct Staff* staff, struct Manager* manager);
void staff_registration(struct Staff* staff);
int staff_main_page(struct Staff* staff, struct Manager* manager, int staffNum);
void staff_schedule(struct Staff* staff, struct Manager* manager, int staffNum);
void staff_information(struct Staff* staff, struct Manager* manager, int staffNum);
int staff_logout(struct Staff* staff, int staffNum, struct Manager* manager);
int resetPassword(struct Staff* staff);
void sendValidationCode(char* email, char* code);
char* generateValidationCode();
// manager
void manager_menu(struct Staff* staff, struct Manager* manager);
void manager_login(struct Staff* staff, struct Manager* manager);
void manager_registration(struct Manager* manager);
void manager_main_page(struct Staff* staff, struct Manager* manager, int managerNum);
void delete_Acc(struct Staff* staff, struct Manager* manager);
void modifyEmpRestSchedule(struct Staff* staff, struct Manager* manager);
void updateManager_information(struct Staff* staff, struct Manager* manager, int managerNum);
void manager_view_schedule(struct Staff* staff, struct Manager* manager);
void manager_reset_pass(struct Staff* staff, struct Manager* manager);
void security_Ques();
void securityQues_display(int questionSelection[MAX_QUESTION_SELECTED], char questionTitle[MAX_QUESTION_SELECTED][50]);
void dispalyAll(struct Staff* staff, struct Manager* manager, int managerNum);
void title(void);



//structure for checkin in & out time
struct Schedule {

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
    struct Schedule schedule;
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

int staff_count = 0;
int manager_count = 0;


main() {
    struct Staff staff[MAX_STAFF];
    Table staff2;
    struct Manager manager[MAX_MANAGER];



    FILE* fstaff;
    fstaff = fopen("../TrainTicketingSys/res/staff.bin", "rb");

    if (fstaff == NULL) {
        printf("Error Opening File\n");
        exit(-1);
    }

    //strcpy(staff[0].table.id, "lgw123");
    //strcpy(staff[0].table.password, "321");
    //strcpy(staff[0].table.phone, "01231323");
    //strcpy(staff[0].table.email, "lee@gmail.com");
    //strcpy(staff[0].table.position, "STAFF");

    //strcpy(manager[0].table.id, "ALi");
    //strcpy(manager[0].table.password, "773");
    //strcpy(manager[0].table.phone, "12312");
    //strcpy(manager[0].table.email, "ali@ail.com");
    //strcpy(manager[0].table.position, "MANAGER");

    //fwrite(&staff[0], sizeof(staff), 1, fstaff);
    //fwrite(&manager[0], sizeof(manager), 1, fstaff);
    fread(&staff2, sizeof(Table), 1, fstaff);

    while (!feof(fstaff))
    {
        if (strcmp(staff2.position, "STAFF") == 0)
        {
            fseek(fstaff, sizeof(Table) * -1, SEEK_CUR);
            fread(&staff[staff_count], sizeof(struct Staff), 1, fstaff);
            staff_count++;
        }

        if (strcmp(staff2.position, "MANAGER") == 0)
        {
            fseek(fstaff, sizeof(Table) * -1, SEEK_CUR);
            fread(&manager[manager_count], sizeof(struct Manager), 1, fstaff);
            manager_count++;
        }
        fread(&staff2, sizeof(Table), 1, fstaff);
    }

    //write new information to file.
    //strcpy(staff[1].table.id, "staff1");
    //strcpy(staff[1].table.password, "321");
    //strcpy(staff[1].table.phone, "01231323");
    //strcpy(staff[1].table.email, "lee@gmail.com");
    //strcpy(staff[1].staff[i], "STAFF");
    //staff_count++;

  //test file read 
    for (int i = 0; i < staff_count; i++) {
        printf("ID: %s\n", staff[i].table.id);
    }

    for (int i = 0; i < manager_count; i++) {
        printf("ID: %s\n", manager[i].table.id);
    }


    fclose(fstaff);

    menu(staff, manager);

    //print all manager and staff account

    for (int i = 0; i < staff_count; i++) {
        printf("ID: %s\n", staff[i].table.id);
    }

    for (int i = 0; i < manager_count; i++) {
        printf("ID: %s\n", manager[i].table.id);
    }
    //------------------------------------------------

    fstaff = fopen("../TrainTicketingSys/res/staff.bin", "wb");

    for (int i = 0; i < manager_count; i++) {
        fwrite(&manager[i], sizeof(struct Manager), 1, fstaff);
    }

    for (int i = 0; i < staff_count; i++) {
        fwrite(&staff[i], sizeof(struct Staff), 1, fstaff);
    }




    fclose(fstaff);
    return 0;

}


//heading all pages
void title(void) {
    system("cls");
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


    do {
        title();
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
            
            printf("Invalid Choice!\n");
            printf("Please Select Again...\n");
            Sleep(1000);
            //only can validate numeric answer
        }

    } while (choice != 3);
    printf("\nYou are Log Out %s Right Now!\n", buffer);


}

// Staff menu
void staffMenu(struct Staff* staff, struct Manager* manager)
{
    int choice, status = 1;
    char select;

   
    do{
        do {
            select = 'N';
            status = 1;
            title();
            printf("\n------ STAFF MENU ------\n");
            printf("-------------------------\n");
            printf("1. Login\n");
            printf("2. Registration\n");
            printf("3. Exit\n");
            scanf("%d", &choice);

            switch (choice) {
            case 1:
                status = staff_login(staff, manager);
                break;
            case 2:
                staff_registration(staff);
                break;
            case 3:
                printf("Exiting....\n");
                select = 'N';
                Sleep(1000);
                break;
            default:
                printf("Invalid Choice!\n");
                printf("Please Select Again\n");
                Sleep(1000);
                break;
                //only can validate numeric answer
                //if enter character or string, it will be error
            }
        } while ((choice != 1 && choice != 2 && choice != 3) || status == 0);
    } while (choice != 3);
    if (select == 'N') {
        
        printf("\nYou are Exit Right Now!\n");
        Sleep(1000);

    }
   
}


// Staff Login menu
int staff_login(struct Staff* staff, struct Manager* manager)
{
    char id[MAX_ID_LENGTH];
    char password[MAX_PASS_LENGTH];
    int loginSuccess = 0;
    int count = 0;
    int ans, status;
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
                Sleep(1000);
                status = staff_main_page(staff, manager, i);
                loginSuccess++;
            }
            if (status = 0) {
                return status;
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

            //
            if (count == 3)
            {
                int std;
                printf("\nYou are failed to log in 3 time!\n");
                Sleep(1000);
                printf("\n1. RESET PASSWORD\n");
                printf("2. EXIT\n");
                printf("Do u want to reset the password ?");
                scanf("%d", &ans);

                if (ans == 1)
                {
                    std = resetPassword(staff);
                    if (std == 0) {
                        return 0;
                    }
                    count = 0;
                }
                else
                {
                   
                    printf("You are exit right now!\n");
                    Sleep(1000);
                    return 0;
                }

            }


        }
    } while (again == 1 && loginSuccess ==0 );
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

    
    for (int i = 0; i < MAX_STAFF; i++) {
        if (strcmp(staff[i].table.id, id) == 0) {
            title();
            printf("The ID %s already exits.\n", id);
            printf("Please choose a different ID.\n");
            Sleep(1000);
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
    Sleep(1000);

    staff_count++;

}


// Staff Choice menu 
int staff_main_page(struct Staff* staff, struct Manager* manager, int staffNum) {
    int choice;
    int status = 1;
    char select;

    do {
        select = 'Y';
        title();
        printf("\nStaff\n");
        printf("-------\n");
        printf("1. Employee working schedule\n");
        printf("2. Update Information\n");
        // printf("3. Tickets available\n");
        // printf("4. customer data\n");
        printf("5. Working Time\n"); //combination of check in and out time!
        printf("6. Log Out Staff\n"); //got log out bug
        printf("Enter your Choice: ");
        scanf("%d", &choice);

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
            status = staff_logout(staff, staffNum, manager);
            break;
        case 6:
            printf("Exiting...\n");
            Sleep(1000);
            select = 'N';
            break;
        default:
            select = 'Y';
            printf("\nPlease try again\n");
            Sleep(1000);
            break;
        }
        if (status == 0) {
            return status;
        }
        if (choice == 1 || choice == 2 || choice == 3 || choice == 4 || choice == 5) {
            do {
                title();
                printf("\nCountinue select ? (Y||N) : ");
                scanf(" %c", &select);

                if (toupper(select) != 'Y' && toupper(select) != 'N')
                {
                    printf("Invalide select.");
                    Sleep(1000);
                }

            } while (toupper(select) != 'Y' && toupper(select) != 'N');

        }

    } while (toupper(select) == 'Y');
}

//staff working schedule 
void staff_schedule(struct Staff* staff, struct Manager* manager, int staffNum)
{
    title();
    if (staff[staffNum].schedule.total_working_hours != 0) { //
        printf("\n----------------- WORKING TIME SCHEDULE -----------------|- %s -|\n", staff[staffNum].table.name);
        printf("BEGIN TIME\tREST TIME\tEND TIME\n");
        printf("%02d:%02d\t%d\t%02d:%02d\t\n", staff[staffNum].schedule.begin_hour, staff[staffNum].schedule.begin_minute, staff[staffNum].schedule.rest_time, staff[staffNum].schedule.end_hour, staff[staffNum].schedule.end_minute);
        printf("TOTAL WORKING TIME : %d hours %d minutes (except rest time)\n", staff[staffNum].schedule.total_working_hours, staff[staffNum].schedule.remaining_minutes);
        printf("-------------------------------------------------------------------\n");
    }
    else
        printf("Sorry,Your schedule haven't done modified yet.\n");
    Sleep(1000);

}


//staff update information 
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

        title();

                // Before edit --change the versio view
        printf("---------------------------\n");
        printf("------ Before Update ------\n");
        printf("---------------------------\n");
        printf("\nName: %s\n", staff[staffNum].table.name);
        printf("Phone No: %s\n", staff[staffNum].table.phone);
        printf("Email:%s\n", staff[staffNum].table.email);


        printf("\nConfirm to update?(Y/N): ");
        scanf(" %c", &confirm);

        if (confirm == 'Y' || confirm == 'y') {
            title();
            printf("\n--------------------------\n");
            printf("---------- UPDATE ----------\n");
            printf("----------------------------\n");
            printf("\nName:");
            scanf(" %[^\n]", name);
            printf("Phone No:");
            scanf(" %[^\n]", phone);
            printf("Email:");
            scanf(" %[^\n]", email);

            strcpy(staff[staffNum].table.name, name);
            strcpy(staff[staffNum].table.phone, phone);
            strcpy(staff[staffNum].table.email, email);

            success++;

            printf("\nUpdate was done successfully!\n");

            printf("\n---------------------------\n");
            printf("------- After Updated -------\n");
            printf("-----------------------------\n");
            printf("Staff ID: %s\n", staff[staffNum].table.id);
            printf("\nName: %s\n", staff[staffNum].table.name);
            printf("Phone No: %s\n", staff[staffNum].table.phone);
            printf("Email:%s\n", staff[staffNum].table.email);
            printf("\n---------------------------\n");
        }
        else
        {
            printf("Update unsuccessfull\n");
            system("pause");
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
                Sleep(1000);
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
int staff_logout(struct Staff* staff, int staffNum, struct Manager* manager) {
    int ans, choice;
    time_t check_in_time = 0;
    time_t check_out_time = 0;

    clock_t checkIn = 0, checkOut = 0;
    double elapsedTime;

    title();
    printf("\nSTAFF WORKING TIME RECORDED\n");
    printf("=================================\n\n");
    printf("1. CHECK IN\n");
    printf("2. CHECK OUT\n");
    printf("Enter your choice:");
    scanf("%d", &ans);
    printf("==================================\n\n");

    if (ans == 1) {
        checkIn = clock();
        // Check in
        title();
        time(&staff[staffNum].check_in_time);
        printf("---------------------------- CHECK IN ----------------------------\n");
        printf("STAFF ID:%s\tCHECK IN TIME:%s", staff[staffNum].table.id, ctime(&staff[staffNum].check_in_time));
        printf("Check In succeed\n");
        printf("-------------------------------------------------------------------\n");
        Sleep(1000);


    }
    else if (ans == 2) {
        checkOut = clock();
        // Check out
        title();
        time(&staff[staffNum].check_out_time);
        printf("----------------------------- CHECK OUT ---------------------------\n");
        printf("STAFF ID:%s\tCHECK OUT TIME:%s", staff[staffNum].table.id, ctime(&staff[staffNum].check_out_time));
        printf("-------------------------------------------------------------------\n");

        elapsedTime = (double)(checkOut - checkIn) / CLOCKS_PER_SEC;


        if (elapsedTime > 8 * 3600) {
            printf("\nThis is your check in time %s and you are check out right now.\n", ctime(&staff[staffNum].check_in_time));
            printf("You have completed 8 hours of work today.\n");
            Sleep(1000);
        }
        else {
  
            printf("--------------------- Time Overall situation ----------------------\n");
            printf("-------------------------------------------------------------------\n");
            printf(" | CHECK IN TIME  | %s |\n", ctime(&staff[staffNum].check_in_time));
            printf(" | CHECK OUT TIME | %s |\n", ctime(&staff[staffNum].check_out_time));
            printf("-------------------------------------------------------------------\n");

            printf("---------- You have not completed 8 hours of work today. ----------\n");
            Sleep(1000);

            do {
                printf("\nAre you sure you want to check out? (1 for Yes, 0 for No): ");
                scanf("%d", &choice);
                if (choice == 1) {
                    // Exit and return to the menu
                    printf("Exiting...\n");
                    Sleep(1000);
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
                    Sleep(1000);
                }

            } while (choice != 1 && choice != 2);
        }
    }
    return 1;
}

// Staff reset password 
int resetPassword(struct Staff* staff)
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
    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    Sleep(1000);

    printf("\nEnter ID:");
    scanf(" %[^\n]", id);

    for (int i = 0; i < staff_count; i++)
    {
        if (strcmp(staff[i].table.id, id) == 0)
        {
            
            printf("\nName: %s\n", staff[i].table.name);
            printf("Email:%s\n", staff[i].table.email);
            do {
                printf("\nIs you?\n");
                printf("1. CORRECT, IS ME\n");
                printf("2. WRONG, NOT ME\n");
                scanf("%d", &ans);

                if (ans == 1)
                {
                    do {
                        printf("Please enter you phone number to validation\n");
                        scanf(" %[^\n]", phone);
                        if (strcmp(staff[i].table.phone, phone) == 0)
                        {
                            printf("Sending a validation code to your email\n");
                            printf("Waiting time....\n");
                            Sleep(1000);
                            //random()
                            //store(send) the code to email.Then compare the code staff keyin and the code in the email.
                            char* code = generateValidationCode();
                            sendValidationCode(staff[i].table.email, code);
                            printf("\nPlease enter the validation code you receive:");
                            scanf("%d", &codeReceived);

                            
                            if (atoi(code) == codeReceived)
                            {
                                printf("Able to reset the password\n");
                                Sleep(1000);

                                successfuly = 0;
                                do {
                                    printf("Enter the new password:");
                                    scanf(" %[^\n]", newPassword);
                                    printf("\nEnter again the same password:");
                                    scanf(" %[^\n]", comf_newPassword);

                                    if (strcmp(newPassword, comf_newPassword) == 0)
                                    {
                                        printf("Success!\n");
                                        Sleep(1000);
                                        strcpy(staff[i].table.password, comf_newPassword);
                                        successfuly++;
                                        return 0;
                                    }
                                    else {
                                        printf("Failed!\n");
                                        Sleep(1000);
                                        successfuly = 0;
                                    }
                                } while (successfuly == 0);

                            }
                            else
                                printf("Validation code incorrect!\n");
                            Sleep(1000);

                        }
                        else

                            printf("You phone number is incorrect!\n");
                        do {
                            printf("Do u want to try again?(Y/N)");
                            Sleep(1000);
                            scanf(" %c", &choice);
                            if (toupper(choice) == 'N') {
                                printf("EXIT");
                                Sleep(1000);
                                return 0;
                            }
                            else if (toupper(choice) != 'Y') {
                                printf("Invalid select.\n");
                            }
                        } while(toupper(choice) != 'Y' && toupper(choice) != 'N');
                       
                    } while (toupper(choice) == 'Y');

                }
                else if (ans != 1 && ans != 2)
                    printf("Invalid select.\n");
                Sleep(1000);

            } while (ans != 1 && ans != 2);
            
        }
        else {
            printf("Authentication failed.\n");
            printf("You need to register first !\n\n");
            Sleep(1000);
            return 0;
        }
        

    }
    printf("Staff ID not found.\n");
    printf("You need to register first !\n\n");
    Sleep(1000);
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



// Manager menu
void manager_menu(struct Staff* staff, struct Manager* manager)
{
    int choice;
    struct tm* hour;
    char buffer[50];
    time_t t;
    time(&t);

    
    do {
        title();

        printf("\n------ MANAGER MENU ------\n");
        printf("----------------------------\n");
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
            Sleep(1000);
            break;
        default:
            printf("\nInvalid Choice!\n");
            printf("Please Select Again\n");
            Sleep(1000);
            //only can validate numeric answer
            //if enter character or string, it will be error
        }

    } while (choice != 3);
    printf("\nYou are Exit Right Now!\n");
    Sleep(1000);
}


// Manager Login menu --need to do let manager reset password!***
void manager_login(struct Staff* staff, struct Manager* manager) {
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
                Sleep(1000);
                manager_main_page(staff, manager, i);
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
                    printf("\n1. RESET PASSWORD\n");
                    printf("2. EXIT\n");
                    printf("Do u want to reset the password ?");
                    scanf("%d", &ans);

                    if (ans == 1)
                    {
                        manager_reset_pass(staff, manager);
                        count = 0;
                        return 0;
                    }
                    else
                    {
                        printf("\nYou are exit right now\n");
                        Sleep(1000);
                        return 0;
                    }

                }

        }
    } while (again == 1 && loginSuccess ==0);

}


//Manager Choice menu 
void manager_main_page(struct Staff* staff, struct Manager* manager, int managerNum) {
    int choice;
    char select;


    do {
        title();
        printf("\nManager\n");
        printf("------\n");
        printf("1. Modify staff working schedule\n");
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
            updateManager_information(staff, manager, managerNum);
            break;
        case 6:
            select = 'N';
            break;
        default:
            select = 'Y';
            printf("\nPlease try again\n");
            Sleep(1000);
            break;
        }
        if (choice == 1 || choice == 2 || choice == 3 || choice == 4 || choice == 5) {
            do{
                printf("\nContinue Select? (Y||N) : ");
                scanf(" %c", &select);

                if(toupper(select) != 'Y' && toupper(select) != 'N')
                {
                    printf("Invalide select.");
                    Sleep(1000);
                }

            } while (toupper(select) != 'Y' && toupper(select) != 'N');
            
        }

    } while (toupper(select) == 'Y');
    
}


// Manager registration 
void manager_registration(struct Manager* manager)
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
            Sleep(1000);
            return 0;
        }
    }

    again = 0;
    //  ---------------------------------------
    do 
    {     
            
        do {
            success = 1;
            again = 0;
            security_Ques();

            for (int i = 0; i < MAX_QUESTION_SELECTED; i++)
            {
                printf("%d. ", i + 1);
                scanf("%d", &questionSelection[i]);

                do
                {
                    if (questionSelection[i] > 5 || questionSelection[i] < 1)
                    {
                        printf("Invalid Choice!\n");
                        printf("Please Enter Number 1 - 5!\n");
                        Sleep(1000);
                        success = 0;
                        //break; 
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
                            Sleep(1000);
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
void delete_Acc(struct Staff* staff, struct Manager* manager, int managerNum)
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
        Sleep(1000);

        printf("\nEenter staff id to delete :");
        Sleep(1000);
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
                        Sleep(1000);

                    }

                    else if (confirm == 2)
                    {
                        printf("\nEXIT FROM REMOVE STAFF MENU.\n");
                        Sleep(1000);
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
            return manager_main_page(staff, manager, managerNum);
            
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
                    printf("------------------------------------------------\n");
                    printf("\nSTAFF NAME : %s\n", staff[i].table.name);
                    printf("\nBEGIN (hh:mm - 24H format): ");
                 
                    if (scanf("%d:%d", &staff[i].schedule.begin_hour, &staff[i].schedule.begin_minute) != 2)
                    {
                        printf("Invalid input format. Please enter time in hh:mm - 24H format.\n");
                        reenter++;
                        Sleep(1000);
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
                            
                        } while (total_working_minutes < 480 );
                        
                        
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

                    printf("\n----------------- WORKING TIME SCHEDULE -----------------|- %s -|\n", staff[i].table.name);
                    printf("BEGIN TIME\t\tREST TIME\t\tEND TIME\n");
                    printf("%02d:%02d\t\t\t  %d\t\t\t  %02d:%02d\n", staff[i].schedule.begin_hour, staff[i].schedule.begin_minute, staff[i].schedule.rest_time, staff[i].schedule.end_hour, staff[i].schedule.end_minute);
                    printf("TOTAL WORKING TIME : %d hours %d minutes (exclude rest time)\n", total_working_hours, remaining_minutes);
                    printf("-------------------------------------------------------------------\n");

                    staff[i].schedule.total_working_hours = total_working_hours;
                    staff[i].schedule.remaining_minutes = remaining_minutes;
                    title();

                }
                else
                {
                    Sleep(1000);
                    printf("---------------------------------------------\n");
                    printf("| STAFF END WORKING TIME MUST ENOUGH 8 HOUR |\n");
                    printf("---------------------------------------------\n");
                    
                }


                successful++;

            }

        }

        if (successful == 0 && ans == 0)
        {
            do
            {
                ans = 0;
                printf("| Invalid ---- Wrong ID  ---- |\n");
                printf("------------------------------|\n");
                printf("| Do you want to enter again? |");
                printf("\n| 1. Yes                      |\n");
                printf("| 2. No                       |\n");
                printf("Enter you choice:             |");
                scanf("%d", &choice);
                printf("|-----------------------------|\n");
                Sleep(800);
                if (choice == 1)
                    ans++;
                else if (choice == 2)
                {
                    printf("\nEXIT\n");
                    Sleep(1000);
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
                printf("\n1. CONTINUE\n");
                printf("2. EXIT\n");
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
void updateManager_information(struct Staff* staff, struct Manager* manager, int managerNum) {
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
        printf("---------------------------\n");
        printf("------ Before Update ------\n");
        printf("---------------------------\n");
        printf("\nName: %s\n", manager[managerNum].table.name);
        printf("Phone No: %s\n", manager[managerNum].table.phone);
        printf("Email:%s\n", manager[managerNum].table.email);

        printf("\nConfirm to update?(Y/N): ");
        scanf(" %c", &confirm);

        //ask manager to update
        if (confirm == 'Y' || confirm == 'y') {
            title();
            printf("\n--------------------------\n");
            printf("----- UPDATE RIGHT NOW -----\n");
            printf("----------------------------\n");
            printf("\nName:");
            scanf(" %[^\n]", name);
            printf("Phone No:");
            scanf(" %[^\n]", phone);
            printf("Email:");
            scanf(" %[^\n]", email);

            strcpy(manager[managerNum].table.name, name);
            strcpy(manager[managerNum].table.phone, phone);
            strcpy(manager[managerNum].table.email, email);

            success++;

            printf("\nYou are successful updated.\n");

            printf("\n---------------------------\n");
            printf("------- After Updated -------\n");
            printf("-----------------------------\n");
            printf("Manager ID: %s\n", manager[managerNum].table.id);
            printf("\nName: %s\n", manager[managerNum].table.name);
            printf("Phone No: %s\n", manager[managerNum].table.phone);
            printf("Email:%s\n", manager[managerNum].table.email);
            printf("\n---------------------------\n");
        }
        else
        {
            printf("Update unsuccessfull\n");
            Sleep(1000);
        }


        if (success == 0) {
            do {
                title();
                again = 0;
                printf("\n--------------------------\n");
               // printf("Invalid | Wrong Manager ID |\n");
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
                   
                }

                else
                    again = 0;

            } while (again == 0);

        }

    } while (again == 1);

}



// Manager reset password 
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
    char enterAgain;

    do {
        
        again = 0;
        title();
        printf("\n--------------- RESET PASSWORD manager---------------\n");
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
                                    printf("Do u want to enter the answers for security password again?(Y/N):\n");
                                    scanf(" %c", &enterAgain);
                                    if (toupper(enterAgain) != 'N' && toupper(enterAgain) != 'Y')
                                    {
                                        printf("\nInvalid selection - Answers in Y/N only\n\n");
                                    }
                                    else {
                                        printf("------------------------------------------------------------\n");

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
                                return manager_menu(staff, manager);

                            if (choice == 2)
                                again++;


                        } while (choice != 1 && choice != 2);
                    }
                    else {
                        printf("Invalid select.\n");
                        Sleep(1000);
                    }
                } while (ans != 1 && ans != 2);
            }
        }

        if (idExist == 0) {
            printf("\nNo manager found with the provided ID.\n");
            printf("You need to register first !\n\n");
            Sleep(1000);
            return manager_registration(manager);
        }
    } while (again == 1);
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


// Manager view staff schedule
void manager_view_schedule(struct Staff* staff, struct Manager* manager)
{
   

    char id[MAX_ID_LENGTH];
    int success = 0;
    title();
    printf("\nEnter staff ID to view the particular staff schedule:");
    scanf(" %[^\n]", id);

    for (int i = 0; i < staff_count; i++)
    {
        if (strcmp(staff[i].table.id, id) == 0)
        {
            if (staff[i].schedule.total_working_hours != 0) {
                title();
                printf("\n----------------- WORKING TIME SCHEDULE -----------------|- %s -|\n", staff[i].table.name);
                printf("BEGIN TIME\tREST TIME\tEND TIME\n");
                printf("%02d:%02d\t%d\t%02d:%02d\n", staff[i].schedule.begin_hour, staff[i].schedule.begin_minute, staff[i].schedule.rest_time, staff[i].schedule.end_hour, staff[i].schedule.end_minute);
                printf("TOTAL WORKING TIME : %d hours %d minutes (except rest time)\n", staff[i].schedule.total_working_hours, staff[i].schedule.remaining_minutes);
                printf("-------------------------------------------------------------------\n");
            }
            else
            {
                printf("Empty\n\n");
                Sleep(1000);
            }

            success++;
        }

    }

    if (success == 0) {
        printf("You haven't modify the staff working schedule\n");
        Sleep(1000);
    }

}


//Display all staff record
void dispalyAll(struct Staff* staff, struct Manager* manager, int staffNum)
{
    title();
    printf("\n----------- RECORD OF STAFF ------------\n");
    printf("\nStaff Name\tPhone No\tEmail\n");

    for (int i = 0; i < staff_count; i++)
    {
        printf("%s\t%s\t%s", staff[i].table.name, staff[i].table.phone, staff[i].table.email);

    }
    printf("\n------------------------------------------\n");

}