#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include<string.h>
#pragma warning (disable : 4996);

#define MAX_STAFF 40
#define MAX_MANAGER 20
#define MAX_NAME_LENGTH 50
#define MAX_ID_LENGTH 20
#define MAX_PASS_LENGTH 20
#define MAX_PHONE_LENGTH 15
#define MAX_EMAIL_LENGTH 50
#define MAX_POSITION_LENGTH 50

void menu(struct Staff* staff, struct Manager* manager);
void staffMenu(struct Staff* staff, struct Manager* manager);
//void add_staff(struct Staff* staff, struct Manager* manager);
void staff_login(struct Staff* staff, struct Manager* manager);
void staff_registration(struct Staff* staff);
void staff_main_page(struct Staff* staff, struct Manager* manager);
void manager_menu(struct Staff* staff, struct Manager* manager);
void manager_login(struct Staff* staff, struct Manager* manager);
void manager_registration(struct Manager* manager);
void manager_main_page(struct Staff* staff, struct Manager* manager);
void delete_Acc(struct Staff* staff, struct Manager* manager);
//void modify_staffInformation(struct Staff* staff, struct Manager* manager);
void staff_schedule(struct Staff* staff, struct Manager* manager);
void staff_information(struct Staff* staff, struct Manager* manager);
void modifyEmpRestSchedule(struct Staff* staff, struct Manager* manager);


//void menu();
//void add_staff(struct Difference dff);
//void login();
//void employee_Acc();
//void staff_Manager();
//void modify_staffInformation();
//void delect_ACC();


// Predefined employee and manager IDs and passwords
//const char employee_id[] = "emp123";
//const char employee_password[] = "password123";
//const char manager_id[] = "mgr456";
//const char manager_password[] = "password456";
//const char staff_id[] = "staff518518";


struct Staff{
    char staff_id[MAX_ID_LENGTH];
    char staff_password[MAX_PASS_LENGTH];
    char staff_name[MAX_NAME_LENGTH];
    char staff_phone[MAX_PHONE_LENGTH];
    char staff_email[MAX_EMAIL_LENGTH];
    char staff_position[MAX_POSITION_LENGTH];
};

struct Manager{ 
    char manager_id[MAX_ID_LENGTH];
    char manager_password[MAX_PASS_LENGTH];
    char manager_name[MAX_NAME_LENGTH];
    char manager_phone[MAX_PHONE_LENGTH];
    char manager_email[MAX_EMAIL_LENGTH];
    char manager_position[MAX_POSITION_LENGTH];
};

int staff_count = 1;
int manager_count = 1;



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
            staff_count=0;
        }

        if (strcmp(staff2.staff_position, "MANAGER") == 0)
        {
            strcpy(manager[manager_count].manager_id, staff2.staff_id);
            strcpy(manager[manager_count].manager_password, staff2.staff_password);
            strcpy(manager[manager_count].manager_phone, staff2.staff_phone);
            strcpy(manager[manager_count].manager_email, staff2.staff_email);
            strcpy(manager[manager_count].manager_position, staff2.staff_position);
            manager_count=0;
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
    printf("ID: %s\n", staff[1].staff_id);

    fclose(fstaff);

    menu(staff, manager);

    fstaff = fopen("../TrainTicketingSys/res/staff.bin", "wb");

    for (int i = 0; i < manager_count - 1; i++) {
        fwrite(&manager[i], sizeof(manager), 1, fstaff);
    }

    for (int i = 0; i < staff_count - 1; i++) {
        fwrite(&staff[i], sizeof(staff), 1, fstaff);
    }

    fclose(fstaff);
    return 0;

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
        system("cls");
        printf("------ STAFF MENU ------\n");
        printf("-------------------------\n");
        printf("1. Staff\n");
        printf("2. Manager\n");
        printf("3. Exit\n");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            staffMenu(staff, manager);
            break;
        case 2:
            manager_menu(staff, manager);
            break;
        default:
            printf("Invalid Choice!\n");
            printf("Please Select Again\n");
            //only can validate numeric answer
            //if enter character or string, it will be error
        }

    } while (choice != 2);
    printf("\nYou are Log Out %s Right Now!\n", buffer);


}

// staff Menu!
void staffMenu(struct Staff* staff, struct Manager* manager)
{
    int choice;
    struct tm* hour;
    char buffer[50];
    time_t t;
    time(&t);

    do {
        system("cls");
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
        default:
            printf("Invalid Choice!\n");
            printf("Please Select Again\n");
            //only can validate numeric answer
            //if enter character or string, it will be error
        }

    } while (choice != 3);
    printf("\nYou are Exit %s Right Now!\n", buffer);

}



// Staff Login menu
void staff_login(struct Staff* staff, struct Manager* manager) 
{
    char id[MAX_ID_LENGTH];
    char password[MAX_PASS_LENGTH];
    int loginSuccess = 0;

    system("cls");
    printf("------ STAFF Login ------\n");
    printf("\nEnter your staff ID: ");
    scanf(" %[^\n]", id);
    printf("Enter your staff password: ");
    scanf(" %[^\n]", password);
    for (int i = 0; i < MAX_STAFF; i++)
    {
        if (strcmp(staff[i].staff_id, id) == 0 && strcmp(staff[i].staff_password, password) == 0) 
        {
            printf("Login successful...\n");
            staff_main_page(staff, manager);
            loginSuccess++;
        }
    }

    if (loginSuccess == 0) 
    {
        printf("Invalid ID or Password");
        return 0;
    }
}

//staff registration menu
void staff_registration(struct Staff* staff) {
    char id[MAX_ID_LENGTH];
    char name[MAX_NAME_LENGTH];
    char password[MAX_PASS_LENGTH];
    char position[MAX_POSITION_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char phoneNo[MAX_PHONE_LENGTH];

    system("cls");
    printf("\nStaff Registration\n");
    printf("--------------------\n");
    printf("Enter your ID: ");
    rewind(stdin);
    scanf("%[^\n]", id);
    printf("Name: ");
    rewind(stdin);
    scanf("%[^\n]", name);
    printf("Enter your Password: ");
    rewind(stdin);
    scanf("%[^\n]", password);
    rewind(stdin);
    printf("Phone No: ");
    rewind(stdin);
    scanf("%[^\n]", phoneNo);
    printf("Email:");
    rewind(stdin);
    scanf("%[^\n]", email);

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


    printf("\nRegistration successfully\n\n");

    staff_count++;

}


// Staff Choice menu
void staff_main_page(struct Staff* staff, struct Manager* manager) {
    int choice;

    do {
        system("cls");
        printf("Staff\n");
        printf("------\n");
        printf("1. Employee rest schedule\n");
        printf("2. Update Information\n");
       // printf("3. Tickets available\n");
       // printf("4. customer data\n");
        printf("5. Check IN\n");
        printf("6. Log OUT\n");
        printf("Enter your Choice: ");
        scanf("%d", &choice);
        // maybe got loop infiniti problem

        switch (choice) {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        default:
            break;
        }
    } while (choice != 6);
}

//staff rest svhedule 
void staff_schedule(struct Staff* staff, struct Manager* manager) {
    //coming soon!
   /* system("cls");*/
}

//staff update information
void staff_information(struct Staff* staff, struct Manager* manager) {
    //coming soon !
    system("cls");
}


// Manager menu
void manager_menu(struct Staff* staff, struct Manager* manager) 
{
    int choice;
    struct tm* hour;
    char buffer[50];
    time_t t;
    time(&t);

    system("cls");
    do {
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
        default:
            printf("Invalid Choice!\n");
            printf("Please Select Again\n");
            //only can validate numeric answer
            //if enter character or string, it will be error
        }

    } while (choice != 3);
    printf("\nYou are Exit %s Right Now!\n", buffer);
}

// Manager Login menu
void manager_login(struct Staff* staff, struct Manager* manager) {
    char id[MAX_ID_LENGTH];
    char password[MAX_PASS_LENGTH];
    int loginSuccess = 0;

    system("cls");
    printf("\n------ MANAGER Login ------\n");
    printf("\nEnter your manager ID: ");
    scanf(" %[^\n]", id);
    printf("Enter your staff password: ");
    scanf(" %[^\n]", password);
    for (int i = 0; i < MAX_MANAGER; i++) {
        if (strcmp(manager[i].manager_id, id) == 0 && strcmp(manager[i].manager_password, password) == 0) {
            printf("\nLogin successful...\n");
            manager_main_page(staff, manager);
            loginSuccess++;
        }
    }

    if (loginSuccess == 0) {
        printf("\nInvalid ID or Password\n");
        return 0;
    }
}

//Manager Choice menu
void manager_main_page(struct Staff* staff, struct Manager* manager) {
    int choice;
    
    system("cls");
    do {
        printf("Manager\n");
        printf("------\n");
        printf("1. Employee rest schedule\n");
        //printf("2. Update information\n");
        printf("2. Delete staff record\n");
        printf("3. Log Out\n");
        printf("Enter your Choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            modifyEmpRestSchedule(staff, manager);
            break;
        case 2:
            delete_Acc(staff, manager);
            //modify_staffInformation(staff, manager); --become manager update themself information
            break;
        case 3:
            break;
        default:
            break;
        }
    } while (choice != 3);
}

// Manager registration
void manager_registration(struct Manager* manager) {
    char id[MAX_ID_LENGTH];
    char name[MAX_NAME_LENGTH];
    char password[MAX_PASS_LENGTH];
    char phone[MAX_PHONE_LENGTH];
    char email[MAX_EMAIL_LENGTH];

    system("cls");
    printf("\Manager Registration\n");
    printf("--------------------\n");
    printf("Manager ID: ");
    rewind(stdin);
    scanf("%[^\n]", id);
    printf("Name: ");
    rewind(stdin);
    scanf("%[^\n]", name);
    printf("Password: ");
    scanf(" %[^\n]", password);
    //not sure the way of store
    printf("Phone No: ");
    rewind(stdin);
    scanf("%[^\n]", phone);
    printf("Email: ");
    rewind(stdin);
    scanf("%[^\n]", email);


    for (int i = 0; i < MAX_MANAGER; i++) {
        if (strcmp(manager[i].manager_id, id) == 0) {
            printf("The ID %s already exits.\n", id);
            printf("Please choose a different ID.\n");
            return 0;
        }
    }

    strcpy(manager[manager_count].manager_id, id);
    strcpy(manager[manager_count].manager_name, name);
    strcpy(manager[manager_count].manager_password, password);
    strcpy(manager[manager_count].manager_phone, phone);
    strcpy(manager[manager_count].manager_email, email);
    strcpy(manager[staff_count].manager_position, "MANAGER");


    printf("\nRegistration successfully\n\n");

    manager_count++;
}

//Manager delete staff record
void delete_Acc(struct Staff* staff, struct Manager* manager)
{
    char confirm;
    char answers;
    char deleteID[20];
    int done =0;
    do
    {
        system("cls");
        printf("You are able to delete the file\n");
        printf("\nEnter Staff ID to DELETE :");
        rewind(stdin);
        scanf("%[^\n]", deleteID);
        for (int i = 0; i < MAX_STAFF; i++) {
            if (strcmp(staff[i].staff_id, deleteID) == 0)
            {
                printf("\nConfirm ?\n");
                scanf(" %c", &confirm);

                while (confirm == 'y' || confirm == 'Y')
                {
                    //// ...fread from binary file 
                    //printf("Enter ID to delete: ");
                    //scanf(" %[^\n]", deleteID);

                    for (int i = 0; i < staff_count; i++)
                    {
                        if (strcmp(staff[i].staff_id, deleteID) == 0)
                        {
                            staff_count--;

                            for (i; i < staff_count; i++)
                            {
                                strcpy(staff[i].staff_id, staff[i + 1].staff_id);
                                strcpy(staff[i].staff_name, staff[i + 1].staff_name);
                                strcpy(staff[i].staff_password, staff[i + 1].staff_password);
                                strcpy(staff[i].staff_email, staff[i + 1].staff_email);
                                strcpy(staff[i].staff_phone, staff[i + 1].staff_phone);
                                // no done yet

                            }

                            done++;
                        }
                    }

                    if (done == 0) {
                        printf("delete successful");
                    }
                    else
                    {
                        printf("Invalid");
                    }

                }
            }
            printf("\nWant to delete another record (Y/N)? :");
            scanf(" %c", &answers);
        }
    } while (answers == 'Y' || answers == 'y');
} 


void modifyEmpRestSchedule(struct Staff* staff, struct Manager* manager)
{
    //comming soon 
    //manager modify particular staff / entire staff rest schedule
}


// Login to Manager acc.
//void staff_Manager()
//{
//    struct Difference dff;
//    //got bugs
//    char id;
//    char password[20];
//    char select;
//
//    printf("\nPlease enter you manager ID :");
//    scanf("%d", &id);
//    printf("\nPlease enter you Manager Password:");
//    scanf(" %[^\n]", password);
//    rewind(stdin);
//    //while (fread(&dffid, sizeof(Difference), 1, fptr) == 1) 
//    if (strcmp(id, dff.employee_id)) {
//
//        if (strcmp(dff.manager_id, id) && strcmp(dff.manager_password, password) == 0) {
//            printf("Manager login successful!\n");
//            printf("Check to edit : \n");
//            printf("1. Employee rest schedule\n");
//            printf("2. Modify staff information\n");
//            printf("3. Delect staff record\n");
//            printf("4. EXIT\n");
//            rewind(stdin);
//            scanf("%c", &select);
//
//            switch (select)
//            {
//            case 1:
//                // rest_schedule();
//                break;
//            case 2:
//                modify_staffInformation();
//                break;
//            case 3:
//                delect_ACC();
//                break;
//            case 4:
//                printf("You are Log Out.");
//                menu(staff, dff);
//                break;
//            }
//        }
//
//    }
//    else
//        printf("Sorry can't found this Manager!\n");
//
//}




// Modify/ edit staff information
////void modify_staffInformation(struct Staff* staff, struct Manager* manager)
//{
//
//    int staffIDExist = 0;
//    char id[MAX_ID_LENGTH], name[MAX_NAME_LENGTH], phoneNo[MAX_PHONE_LENGTH], email[MAX_EMAIL_LENGTH], position[MAX_POSITION_LENGTH];
//    char confirm;
//    char add;
//
//    printf("Enter Staff ID:");
//    scanf(" %[^\n]", id);
//    for (int i = 0; i < MAX_STAFF; i++) {
//        if (strcmp(staff[i].staff_id, id) == 0)
//        {
//            staffIDExist++;
//            printf("\n---------BEFORE EDIT-----------\n");
//            printf("Staff ID: %s\n", staff[i].staff_id);
//            printf("Name : %s\n", staff[i].staff_name);
//            printf("Contact Number: %s\n", staff[i].staff_phone);
//            printf("Email: %s\n", staff[i].staff_email);
//            printf("Position: %s\n", staff[i].staff_position);
//
//            printf("--------------EDIT------------------\n");
//            printf("\nPlease Enter New Name: ");
//            scanf(" %[^\n]", name);
//            printf("Please enter New phone No : ");
//            scanf(" %[^\n]", phoneNo);
//            printf("Please enter New email :");
//            scanf(" %[^\n]", email);
//            printf("Please enter New position :");
//            scanf(" %[^\n]", position);
//            //maybe can let loop like when want to edit email only then just out for this edit menu.
//
//           /* printf("\n------------ADD---------------\n");
//            printf("Do you want to add phone_No? :");
//            printf(" \nY/y OR N/n : ");
//            scanf(" %c", &add);
//
//            if (add == 'Y' || add == 'y')
//            {
//
//                printf("\nEnter Phone_No: ");
//                scanf("%d", &staff.staff_phone);
//            }
//            else {
//
//                printf("Confirm? ");
//                scanf("%c", &confirm);
//                rewind(stdin);
//                if (confirm == 'Y' || confirm == 'y') {
//                    printf("\n");
//                    printf("Edit was successfully!\n");
//                }
//
//                printf("--------After edit---------------\n");
//                printf("\nName : %s\n", staff.staff_name);
//                printf("\nEmployee ID : %s\n", dff.employee_id);
//                printf("\nEmail: %s", staff.staff_email);
//                printf("Phone No :%d\n", staff.staff_phone);
//
//            }*/
//
//            printf("\nConfirm? \n");
//            scanf(" %c", &confirm);
//            if (confirm == 'Y' || confirm == 'y') {
//                strcpy(staff[i].staff_name, name);
//                strcpy(staff[i].staff_phone, phoneNo);
//                strcpy(staff[i].staff_email, email);
//                strcpy(staff[i].staff_position, position);
//                printf("\n");
//                printf("Edit was successfully!\n");
//                printf("--------After edit---------------\n");
//                printf("Staff ID : %s\n", staff[i].staff_id);
//                printf("Name : %s\n", staff[i].staff_name);
//                printf("Phone No :%s\n", staff[i].staff_phone);
//                printf("Email: %s", staff[i].staff_email);
//                printf("Position :%s\n", staff[i].staff_position);
//            }
//            else {
//                return;
//            }
//
//
//        }
//
//    }
//
//    if (staffIDExist == 0) {
//        printf("%s is unvailable!\n", id);
//        return 0;
//    }
//}