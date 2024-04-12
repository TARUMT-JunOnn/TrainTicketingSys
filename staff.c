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
void staff_schedule(struct Staff* staff, struct Manager* manager);
void staff_information(struct Staff* staff, struct Manager* manager);
void staff_logout(struct Staff* staff);
// manager
void manager_menu(struct Staff* staff, struct Manager* manager);
void manager_login(struct Staff* staff, struct Manager* manager);
void manager_registration(struct Manager* manager);
void manager_main_page(struct Staff* staff, struct Manager* manager);
void delete_Acc(struct Staff* staff, struct Manager* manager);
//void modify_staffInformation(struct Staff* staff, struct Manager* manager);
void modifyEmpRestSchedule(struct Staff* staff, struct Manager* manager);
void updateManager_information(struct Staff* staff, struct Manager* manager);




// Predefined employee and manager IDs and passwords
//const char employee_id[] = "emp123";
//const char employee_password[] = "password123";
//const char manager_id[] = "mgr456";
//const char manager_password[] = "password456";
//const char staff_id[] = "staff518518";

struct schedule {
    float beginTime;
    
};

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

    system("cls");
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
        case 3:
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

// staff Menu!
void staffMenu(struct Staff* staff, struct Manager* manager)
{
    int choice;
    struct tm* hour;
    char buffer[50];
    time_t t;
    time(&t);

    system("cls");
    do {
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
    system("cls");
}

//staff registration menu
void staff_registration(struct Staff* staff) {
    char id[MAX_ID_LENGTH];
    char name[MAX_NAME_LENGTH];
    char password[MAX_PASS_LENGTH];
    char position[MAX_POSITION_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char phoneNo[MAX_PHONE_LENGTH];

    
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


    printf("\nRegistration successfully\n\n");

    staff_count++;
    system("cls"); // This make some notification can't detect.
}


// Staff Choice menu
void staff_main_page(struct Staff* staff, struct Manager* manager) {
    int choice;

    system("cls");
    do {
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
            staff_schedule(staff, manager);
            break;
        case 2:
            staff_information(staff, manager);
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
           // printf("Check in time:%x");
            break;
        case 6:
            staff_logout(staff);
            break;
        default:
            break;
        }
    } while (choice != 6);
}

//staff rest schedule 
void staff_schedule(struct Staff* staff, struct Manager* manager) {
    //coming soon!
   /* system("cls");*/
}

//staff update information
void staff_information(struct Staff* staff, struct Manager* manager) {
    //coming soon !
    system("cls");
}


//staff log out selected ****
 void staff_logout(struct Staff* staff)
{
     //SYSTEMTIME t;
     time_t current_time;
     time(&current_time);
     int ans;

    printf("---------LOG OUT------------\n");
    printf(" <1>  Break time\n");
    printf(" <2>  Off work\n ");
    scanf("%d", &ans);
        if (ans == 1)
        {
            //GetLocalTime(&t);

            printf("Break time: %s", ctime(&current_time));
            printf("you break time Already recorded\n");
        }
        else 
        {
            printf("See you tomorrow\n");
            printf("%s\n", ctime(&current_time));
        //    login time - logout time;
        //    if (working time >= 8 hour)*/
        //    {
                //                printf("You completed enough work hours today");
                //                printf("You are log out %sright now!\n", ctime(&current_time));
                //            }
                //            else {
                //
                //                printf("Comfirm?");
                //                scanf("%c", &ans);
                //                if (ans=='y' || ans=='Y')
                //                {
                //                    printf("you don't have enough working hours\n");
                //                    printf("You are log out %sright now!\n", ctime(&current_time));
                //                }
                //
                //            }

        //}
  
//               // printing result -login & logout time
//            printf("------TODAY HOURS------\n");
//            printf("\t\tTIME\t\t\n);
//            printf("Check In\t\tCheck Out\n");
//            printf("%x\t\t%x");
            }
//       
//   
//    
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
        printf("2. Remove staff\n");
        printf("3. Update information\n");
        printf("4. Log Out\n");
        printf("Enter your Choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
           /* modifyEmpRestSchedule(staff, manager);*/
            break;
        case 2:
            delete_Acc(staff, manager);
            break;
        case 3:
            //modify_staffInformation(staff, manager); --become manager update themself information
            updateManager_information(staff, manager);
            break;
        default:
            break;
        }
    } while (choice != 4);
}

// Manager registration
void manager_registration(struct Manager* manager) {
    char id[MAX_ID_LENGTH];
    char name[MAX_NAME_LENGTH];
    char password[MAX_PASS_LENGTH];
    char phone[MAX_PHONE_LENGTH];
    char email[MAX_EMAIL_LENGTH];

    
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
    system("cls");
}

//Manager delete/remove staff acc
void delete_Acc(struct Staff* staff, struct Manager* manager)
{
    char confirm;
    char answers;
    char deleteID[20];
    int done = 0;
    int memberExist = 0;
    system("cls");
    do
    {
        memberExist = 0;
        printf("You are able to delete the file\n");
        printf("\nEnter Staff ID to DELETE :");
        rewind(stdin);
        scanf("%[^\n]", deleteID);

        for (int i = 0; i < MAX_STAFF; i++) {
            if (strcmp(staff[i].staff_id, deleteID) == 0)
                memberExist++;
        }
        if (memberExist == 1) {
            for (int i = 0; i < MAX_STAFF; i++) {
                if (strcmp(staff[i].staff_id, deleteID) == 0)
                {
                    printf("\nConfirm ?\n");
                    scanf(" %c", &confirm);

                    while (confirm == 'y' || confirm == 'Y')
                    {

                        for (int i = 0; i < staff_count; i++)
                        {
                            if (strcmp(staff[i].staff_id, deleteID) == 0)
                            {
                                staff_count--;

                                for (i; i < staff_count; i++)
                                {
                                    strcpy(staff[i].staff_id, NULL);
                                    strcpy(staff[i].staff_name, NULL);
                                    strcpy(staff[i].staff_password, NULL);
                                    strcpy(staff[i].staff_email, NULL);
                                    strcpy(staff[i].staff_phone, NULL);
                                    strcpy(staff[i].staff_position, NULL);

                                    strcpy(staff[i].staff_id, staff[i + 1].staff_id);
                                    strcpy(staff[i].staff_name, staff[i + 1].staff_name);
                                    strcpy(staff[i].staff_password, staff[i + 1].staff_password);
                                    strcpy(staff[i].staff_email, staff[i + 1].staff_email);
                                    strcpy(staff[i].staff_phone, staff[i + 1].staff_phone);
                                    strcpy(staff[i].staff_position, staff[i + 1].staff_position);

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
                        printf("\nWant to delete another record (Y/N)? :");
                        scanf(" %c", &answers);
                    }

                }

            }
        }
    } while (answers == 'Y' || answers == 'y');
}



    ////manager modify particular staff / entire staff rest schedule ****
    //void modifyEmpRestSchedule(struct Staff* staff, struct Manager* manager) {
    //    //    int ans;
    ////    char id[MAX_ID_LENGTH];
    ////    double begin_time;
    ////    double rest_time;
    ////    double end_time;
    ////    char answers;
    //
    //
    ////do{
    ////        staff_count++;
    ////
    ////        printf("> Modify particular staff rest schedule\n");
    ////        printf("Staff ID:");
    ////        scanf(" %[^\n]", &id);
    ////
    ////        // Compare the product code in the array
    ////
    ////    for (int i = 0; i < MAX_STAFF; i++)
    ////    {
    ////        if (strcmp(staff[i].staff_id, id) == 0)
    ////        {
    ////            printf("%s WORKING TIME\n", staff[staff_count].staff_name);
    ////            printf("\nBEGIN:");
    ////            scanf("%lf", &begin_time);
    ////            printf("\nREST:");
    ////            scanf("%lf", &rest_time);
    ////            printf("\nEND:");
    ////            scanf("%lf", &end_time);
    ////            printf("---------------------------------------------\n");
    ////            printf("| STAFF END WORKING TIME MUST ENOUGH 8 HOUR |\n");
    ////            printf("---------------------------------------------\n");
    ////
    ////            printf("Sure to modify? Y/N : ");
    ////            scanf(" %c", &answers);
    ////            if (answers == 'Y' || answers == 'y')
    ////            {
    ////
    ////                printf("-------------------------------------------------\n");
    ////                printf("| NAME\t\tWORKING TIME\t\tREST TIME\t\tEND TIME |\n");
    ////                printf("%s\t\t%f\t\t%f\t\t%f\n");
    ////                printf("-------------------------------------------------\n");
    ////
    ////                staff_count++;
    ////                ....
    ////            }
    ////        }
    ////     } 
    ////    printf("Anymore to modify Y/N :");
    ////    scanf("%c", &answers);
    ////
    //// } while (answers == 'Y' || answers == 'y');
    ////
    //// fopen("../TrainTicketingSys/res/staff.bin", "wb");
    //// .....
    //// ---------------------------------------------------------------
    ////
    ////
    ////     reference :
    ////        for (i = 0; i < pCount; i++)
    ////        {
    ////            if (stcmp(code, p[i].product_code) == 0)
    ////            {
    ////                printf("Product code: %s\n", p[i].product_code);
    ////                printf("Expire Year: %d\n", p[i].expYr);
    ////                printf("Country : %s\n", p[i].country);
    ////
    ////                printf("Enter new expire Year:");
    ////                scanf("%d", &year);
    ////                printf("\nEnter country:");
    ////                scanf(" %[^\n]", country);
    ////
    ////                printf("Sure to modify? Y/N : ");
    ////                scanf("%c", &answers);
    ////                if (answers == 'Y' || answers == 'y')
    ////                {
    ////                    numRecModify++;
    ////                    p[i].expYr = year;
    ////                    strcpy(p[i].country, country);
    ////                }
    ////            }
    ////        }
    ////
    ////        printf("Anymore to modify Y/N :");
    ////        scanf("%c", &answers);
    ////    } while (answers == 'Y' || answers == 'y');
    ////
    ////
    ////    //copy array into file 
    ////    fp = fopen("product.dat", "ab");
    ////    if (fp == NULL)
    ////    {
    ////        printf("Can't open the file\n");
    ////    }
    ////    for (i = 0; i < pCount; i++)
    ////    {
    ////        fwrite(&p[pCount], sizeof(Product), 1, fp);
    ////
    ////    }
    ////
    ////    fclose(fp);
    //}




    //Manager update information
void updateManager_information(struct Staff* staff, struct Manager* manager) {
        char name[MAX_NAME_LENGTH];
        char email[MAX_EMAIL_LENGTH];
        char phone[MAX_PHONE_LENGTH];
        char id[MAX_ID_LENGTH];
        char stop;
        int success = 0, again = 0, choice;

        do {
            success = 0;
            again = 0;
            printf("Manager ID: ");
            scanf(" %[^\n]", id);

            for (int i = 0; i < manager_count; i++)
            {
                if (strcmp(manager[i].manager_id, id) == 0)
                {
                    // Before edit
                    printf("Name: %s\n", manager[i].manager_name);
                    printf("Phone No: %s\n", manager[i].manager_phone);
                    printf("Email:%s\n", manager[i].manager_email);

                    //ask manager to update
                    printf("Name:");
                    scanf(" %[^\n]", name);
                    printf("Phone No:");
                    scanf(" %[^\n]", phone);
                    printf("Email:");
                    scanf(" %[^\n]", email);

                    strcpy(manager[i].manager_name, "NULL");
                    strcpy(manager[i].manager_phone, "NULL");
                    strcpy(manager[i].manager_email, "NULL");

                    strcpy(manager[i].manager_name, name);
                    strcpy(manager[i].manager_phone, phone);
                    strcpy(manager[i].manager_email, email);

                    success++;
                }
            }

            if (success == 0) {
                do {
                    again = 0;
                    printf("Invalid\n");
                    printf("DO you want to enter again\n");
                    printf("1. Yes\n");
                    printf("2. No\n");
                    printf("Enter you choice: ");
                    scanf("%d", &choice);
                    if (choice == 1)
                        again++;
                    else if (choice == 2)
                        return 0;
                    else
                        again = 0;
                } while (again == 0);

            }

            //} while (stop == 'Y' || stop == 'y');
        } while (again == 1);
        
}
     

         // FILE* fstaff;
      //    fstaff = fopen("../TrainTicketingSys/res/staff.bin", "wb");
      //
      // if (fstaff == NULL) 
      // {
      //   printf("Failed Opening File\n");
      // }
      // 
    //    fclose(fstaff);
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