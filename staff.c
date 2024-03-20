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
void modify_staffInformation(struct Staff* staff, struct Manager* manager);

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


struct Staff {
    char staff_id[MAX_ID_LENGTH];
    char staff_password[MAX_PASS_LENGTH];
    char staff_name[MAX_NAME_LENGTH];
    char staff_phone[MAX_PHONE_LENGTH];
    char staff_email[MAX_EMAIL_LENGTH];
    char staff_position[MAX_POSITION_LENGTH];
};

struct Manager {
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
    struct Manager manager[MAX_MANAGER];

    strcpy(staff[0].staff_id, "staff1");
    strcpy(staff[0].staff_password, "123456");
    strcpy(staff[0].staff_name, "Ali");
    strcpy(staff[0].staff_phone, "011-1234567");
    strcpy(staff[0].staff_email, "ali@gmail.com");
    strcpy(staff[0].staff_position, "Cleaner");

    strcpy(manager[0].manager_id, "manager1");
    strcpy(manager[0].manager_password, "654321");
    strcpy(manager[0].manager_name, "Abu");
    strcpy(manager[0].manager_phone, "010-9876543");
    strcpy(manager[0].manager_email, "abuManager@gmail.com");
    strcpy(manager[0].manager_position, "CEO");

    menu(staff, manager);

    return 0;

}

void menu(struct Staff* staff, struct Manager* manager) {
    int choice;
    struct tm* hour;
    char buffer[50];
    time_t t;
    time(&t);

    hour = localtime(&t);
    strftime(buffer, 50, "%X", hour);


    do {
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

    } while (choice != 3);
    printf("\nYou are Log Out %s Right Now!\n", buffer);


}


void staffMenu(struct Staff* staff, struct Manager* manager)
{
    int choice;
    struct tm* hour;
    char buffer[50];
    time_t t;
    time(&t);

    do {
        printf("------ STAFF MENU ------\n");
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
//Staff create new acc
//void add_staff(struct Staff* staff, struct Manager* manager)
//{
//    char choice;
//    char id[MAX_ID_LENGTH];
//    char password[MAX_PASS_LENGTH];
//
//    if (staff_count >= MAX_STAFF) {
//        printf("Already full! No more staff can be add.\n");
//
//        printf("Do you want to delete staff acc?\n");
//        rewind(stdin);
//        scanf("%c", &choice);
//        if (choice == 'Y' || choice == 'y')
//        {
//            deleteAcc();
//
//            /*printf("Only MANAGER can access!\n");
//            printf("Enter Manager ID:");
//            rewind(stdin);
//            scanf("%s", id);
//            printf("\nEnter password to access:");
//            rewind(stdin);
//            scanf("%[^\n]", password);
//
//            for (int i = 0; i < MAX_MANAGER; i++) {
//                if (strcmp(manager[i].manager_id, id) == 0 && strcmp(manager[i].manager_password, password) == 0)
//                {
//                    deleteAcc();
//                }
//            }*/
//        }
//        return 0;
//    }
//
//    printf("Enter your name：");
//    rewind(stdin);
//    scanf(" %[^\n]", staff[staff_count].staff_name);
//
//    printf("Enter your ID：");
//    scanf(" %s", &staff[staff_count].staff_id);
//
//    printf("Enter your phone number：");
//    scanf("%d", &staff[staff_count].staff_phone);
//
//    printf("Enter your email：");
//    rewind(stdin);
//    scanf("%[^\n]", staff[staff_count].staff_email);
//
//    printf("Enter your position：");
//    scanf(" %s", &staff[staff_count].staff_position);
//
//    staff_count++;
//    printf("Employee information has been added.\n");
//}

void staff_login(struct Staff* staff, struct Manager* manager) {
    char id[MAX_ID_LENGTH];
    char password[MAX_PASS_LENGTH];
    int loginSuccess = 0;
    printf("------ STAFF Login ------\n");
    printf("\nEnter your staff ID: ");
    scanf(" %[^\n]", id);
    printf("Enter your staff password: ");
    scanf(" %[^\n]", password);
    for (int i = 0; i < MAX_STAFF; i++) {
        if (strcmp(staff[i].staff_id, id) == 0 && strcmp(staff[i].staff_password, password) == 0) {
            printf("Login successful...\n");
            staff_main_page(staff, manager);
            loginSuccess++;
        }
    }

    if (loginSuccess == 0) {
        printf("Invalid ID or Password");
        return 0;
    }
}

void staff_registration(struct Staff* staff) {
    char id[MAX_ID_LENGTH];
    char password[MAX_PASS_LENGTH];
    printf("\nStaff Registration\n");
    printf("--------------------\n");
    printf("Enter your ID: ");
    scanf(" %[^\n]", id);
    printf("Enter your Password: ");
    scanf(" %[^\n]", password);

    for (int i = 0; i < MAX_STAFF; i++) {
        if (strcmp(staff[i].staff_id, id) == 0) {
            printf("The ID %s already exits.\n", id);
            printf("Please choose a different ID.\n");
            return 0;
        }
    }

    strcpy(staff[staff_count].staff_id, id);
    strcpy(staff[staff_count].staff_password, password);

    printf("\nRegistration successfully\n\n");

    staff_count++;

}

void staff_main_page(struct Staff* staff, struct Manager* manager) {
    int choice;
    do {
        printf("Staff\n");
        printf("------\n");
        printf("1. Employee rest schedule\n");
        printf("2. Employe Information\n");
        printf("3. Check IN\n");
        printf("4. Log OUT\n");
        printf("Enter your Choice: ");
        scanf("%d", &choice);

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
    } while (choice != 4);
}

void manager_menu(struct Staff* staff, struct Manager* manager) {
    int choice;
    struct tm* hour;
    char buffer[50];
    time_t t;
    time(&t);
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

void manager_login(struct Staff* staff, struct Manager* manager) {
    char id[MAX_ID_LENGTH];
    char password[MAX_PASS_LENGTH];
    int loginSuccess = 0;
    printf("\n------ MANAGER Login ------\n");
    printf("\nEnter your manager ID: ");
    scanf(" %[^\n]", id);
    printf("Enter your staff password: ");
    scanf(" %[^\n]", password);
    for (int i = 0; i < MAX_MANAGER; i++) {
        if (strcmp(manager[i].manager_id, id) == 0 && strcmp(manager[i].manager_password, password) == 0) {
            printf("Login successful...\n");
            manager_main_page(staff, manager);
            loginSuccess++;
        }
    }

    if (loginSuccess == 0) {
        printf("Invalid ID or Password\n");
        return 0;
    }
}

void manager_main_page(struct Staff* staff, struct Manager* manager) {
    int choice;
    do {
        printf("Manager\n");
        printf("------\n");
        printf("1. Employee rest schedule\n");
        printf("2. Modify staff information\n");
        printf("3. Delete staff record\n");
        printf("Enter your Choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            break;
        case 2:
            modify_staffInformation(staff, manager);
            break;
        case 3:
            delete_Acc(staff, manager);
            break;
        default:
            break;
        }
    } while (choice != 5);
}

void manager_registration(struct Manager* manager) {
    char id[MAX_ID_LENGTH];
    char password[MAX_PASS_LENGTH];
    printf("\Manager Registration\n");
    printf("--------------------\n");
    printf("Enter your ID: ");
    scanf(" %[^\n]", id);
    printf("Enter your Password: ");
    scanf(" %[^\n]", password);

    for (int i = 0; i < MAX_MANAGER; i++) {
        if (strcmp(manager[i].manager_id, id) == 0) {
            printf("The ID %s already exits.\n", id);
            printf("Please choose a different ID.\n");
            return 0;
        }
    }

    strcpy(manager[manager_count].manager_id, id);
    strcpy(manager[manager_count].manager_password, password);

    printf("\nRegistration successfully\n\n");

    manager_count++;
}

void delete_Acc(struct Staff* staff, struct Manager* manager)
{
    char id[MAX_ID_LENGTH];
    char confirm;
    char answers;

    printf("You are able to delete the file\n");
    printf("\nEnter Employee Name to DELETE :");
    rewind(stdin);
    scanf("%[^\n]", id);
    for (int i = 0; i < MAX_STAFF; i++) {
        if (strcmp(staff[i].staff_id, id) == 0) {
            printf("\nConfirm ?\n");
            scanf(" %c", &confirm);

            while (confirm == 'y' || confirm == 'Y')
            {
                // ...fread from binary file 
            }
            printf("\nWant to delete another"
                " record (Y/N) :");
            rewind(stdin);
            scanf(" %c", &answers);
        }
    }
    //printf("\nConfirm ?\n");
    //scanf(" %c", &confirm);

    //while (confirm == 'y' || confirm == 'Y')
    //{
    //    // ...fread from binary file 
    //}
    //printf("\nWant to delete another"
    //    " record (Y/N) :");
    //rewind(stdin);
    //scanf(" %c", &answers);
    // .......

    //fprintf(save) to binary file 


}


// Staff Login Acc
//void login(struct Staff staff, struct Employee employee, struct Manager manager) {
//    char id[MAX_ID_LENGTH];
//    char choice;
//    int wrong_password = 0;
//
//    printf("------ ONLY for STAFF Login ------\n");
//    printf("\nEnter your staff ID: ");
//    scanf("%s", id);
//    if (strcmp(staff.staff_id, id) == 0)
//    {
//        printf("Welcome %s", staff.staff_name);
//        printf("\nLogin to Employee Acc (S/s) OR Manager Acc (M/m): ");
//        scanf(" %c", &choice);
//
//        if (choice == 'M' || choice == 'm') {
//            printf("You are logged in as an manager.\n");
//            staff_Manager();
//        }
//        else if (choice == 'S' || choice == 's') {
//            printf("You are logged in as an Employee.\n");
//            employee_Acc();
//        }
//        else {		// Checking if login failed 3 time logout directly
//            printf("\nFailed to Login.\n");
//            wrong_password++;
//
//            if (wrong_password >= 3) {
//                printf("Incorrect password 3 times, Log Out!");
//                return;
//            }
//        }
//    }
//    printf("Can't founed the staff in system.\n");
//}


//Staff menu 
//void staffMenu(struct Staff staff, struct Manager manager) {
//    int choice;
//    struct tm* hour;
//    char buffer[50];
//    time_t t;
//    time(&t);
//
//    hour = localtime(&t);
//    strftime(buffer, 50, "%X", hour);
//
//
//    do {
//        printf("------ STAFF MENU ------\n");
//        printf("-------------------------\n");
//        printf("1. Sign In Acc\n");
//        printf("2. Log In Acc\n");
//        printf("3. Exit\n");
//        scanf("%d", &choice);
//        if (choice != 1 && choice != 2 && choice != 3)
//            printf("Please select again:\n");
//
//        switch (choice) {
//        case 1:
//            add_staff(staff);
//            break;
//        case 2:
//            login(staff, employee, manager);
//            break;
//        case 3:
//            printf("\nYou are Log Out %s Right Now!\n", buffer);
//            break;
//        }
//
//    } while (choice != 1 && choice != 2 && choice != 3);
//
//}


// Login to emp acc
//void employee_Acc()
//{
//    char password[20];
//    char id;
//    char select;
//
//    struct tm* hour;
//    char buffer[50];
//    time_t t;
//    time(&t);
//
//    hour = localtime(&t);
//    strftime(buffer, 50, "%X", hour);
//
//    //Let emp define id and password (all is difference ID and password) - read form binary file
//    printf("Enter your Emp.ID :");
//    rewind(stdin);
//    scanf(" %s", &id);
//    printf("Please enter your password:");
//    rewind(stdin);
//    scanf("%[^\n]", password);
//    if (strcmp(dff.employee_password, password) == 0) {
//        printf("Your are sucessful login Acc");
//        printf("Check to see :\n");
//        printf("1. Employee rest schedule\n");
//        printf("2. Employe Information\n");
//        printf("3. Check IN\n");
//        printf("4. Log OUT\n");
//        scanf(" %c", &select);
//        switch (select)
//        {
//        case 1:
//            // rest_schedule();
//            break;
//        case 2:
//            //log in to ourselfe record then edit only.
//            modify_staffInformation();
//            break;
//        case 3:
//            // after check in ,store check in & out time show to employee see when log out acc.
//            printf("\nYou are Check IN %s Right Now!\n", buffer);
//            break;
//        case 4:
//            printf("You are Log Out.");
//            menu();
//            break;
//        }
//    }
//    else
//        printf("Wrong Password!\n");
//}



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
void modify_staffInformation(struct Staff* staff, struct Manager* manager)
{

    int staffIDExist = 0;
    char id[MAX_ID_LENGTH], name[MAX_NAME_LENGTH], phoneNo[MAX_PHONE_LENGTH], email[MAX_EMAIL_LENGTH], position[MAX_POSITION_LENGTH];
    char confirm;
    char add;

    printf("Enter Staff ID:");
    scanf(" %[^\n]", id);
    for (int i = 0; i < MAX_STAFF; i++) {
        if (strcmp(staff[i].staff_id, id) == 0)
        {
            staffIDExist++;
            printf("\n---------BEFORE EDIT-----------\n");
            printf("Staff ID: %s\n", staff[i].staff_id);
            printf("Name : %s\n", staff[i].staff_name);
            printf("Contact Number: %s\n", staff[i].staff_phone);
            printf("Email: %s\n", staff[i].staff_email);
            printf("Position: %s\n", staff[i].staff_position);


            printf("Please Enter New Name: ");
            scanf(" %[^\n]", name);
            printf("Please enter New phone No : ");
            scanf(" %[^\n]", phoneNo);
            printf("Please enter New email :");
            scanf(" %[^\n]", email);
            printf("Please enter New position :");
            scanf(" %[^\n]", position);

            //maybe can let loop like when want to edit email only then just out for this edit menu.

           /* printf("\n------------ADD---------------\n");
            printf("Do you want to add phone_No? :");
            printf(" \nY/y OR N/n : ");
            scanf(" %c", &add);

            if (add == 'Y' || add == 'y')
            {

                printf("\nEnter Phone_No: ");
                scanf("%d", &staff.staff_phone);
            }
            else {

                printf("Confirm? ");
                scanf("%c", &confirm);
                rewind(stdin);
                if (confirm == 'Y' || confirm == 'y') {
                    printf("\n");
                    printf("Edit was successfully!\n");
                }

                printf("--------After edit---------------\n");
                printf("\nName : %s\n", staff.staff_name);
                printf("\nEmployee ID : %s\n", dff.employee_id);
                printf("\nEmail: %s", staff.staff_email);
                printf("Phone No :%d\n", staff.staff_phone);

            }*/

            printf("Confirm? ");
            scanf(" %c", &confirm);
            if (confirm == 'Y' || confirm == 'y') {
                strcpy(staff[i].staff_name, name);
                strcpy(staff[i].staff_phone, phoneNo);
                strcpy(staff[i].staff_email, email);
                strcpy(staff[i].staff_position, position);
                printf("\n");
                printf("Edit was successfully!\n");
                printf("--------After edit---------------\n");
                printf("Staff ID : %s\n", staff[i].staff_id);
                printf("Name : %s\n", staff[i].staff_name);
                printf("Phone No :%s\n", staff[i].staff_phone);
                printf("Email: %s", staff[i].staff_email);
                printf("Position :%s\n", staff[i].staff_position);
            }
            else {
                return;
            }


        }

    }

    if (staffIDExist == 0) {
        printf("%s is unvailable!\n", id);
        return 0;
    }
}