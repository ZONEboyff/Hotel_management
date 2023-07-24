#ifndef task_h
#define task_h
struct customer {
    char cname[50];
    int cage;
    char caddress[100];
    char cten[11];
    int cpnum;
    int Deluxe; 
    int Standard; 
    int Family;
    int Suite;
      
};
int fileExists(const char* filename);
void addcust(FILE *fp);
void update(FILE *fp);
void display(FILE *fp);
void custfeed(FILE *fp);
// void roomtype(FILE *fp);
int fileExists(const char* filename) {//fucntion used to check if file exists
    return access(filename, F_OK) != -1;
}
void formatFileName(char* fileName) {//This function is used to make a single filename which removes spaces and adds .txt
    int length = strlen(fileName);
    for (int i = 0; i < length; i++) {
        if (fileName[i] == ' ') {
            fileName[i] = '_';//replacing spaces with '_'
        }
    }
    strcat(fileName, ".txt");//concatenating .txt 
}    
void addcust(FILE *fp) {
    char fname[100];//To store the filname
    system("clear");
    int deluxe, standard, family, suite;//To store the current number of rooms from the file roomtype.txt file
    FILE *tempfp = fopen("roomtype.txt", "r+");
    if (tempfp == NULL) {//to check if the file exists 
        printf("Error opening the file.\n");
        return;
    }
    fscanf(tempfp, "Deluxe:%d\n", &deluxe);//used to put the values into each variable
    fscanf(tempfp, "Standard:%d\n", &standard);
    fscanf(tempfp, "Family:%d\n", &family);
    fscanf(tempfp, "Suite:%d\n", &suite);
    fclose(tempfp);

    struct customer *c = malloc(sizeof(struct customer));//Dynamically allocate space for a single customer variable
    c->Deluxe=0, c->Standard=0, c->Family=0, c->Suite=0;//iniatlixe the roomtype members to 0
    
    while (1) {//runs till a unique name is generated
        printf("Enter the NAME of the new customer: ");
        scanf(" %49[^\n]", c->cname);
        strcpy(fname, c->cname);//copy the name of the customer to create a filname by formating it
        formatFileName(fname);
        if (fileExists(fname)) {//checks if file exist,if it is prompts the user to write the same name with some changes
            printf("THE FILE BY THIS NAME ALREADY EXISTS/nENTER THE NAME AGAIN WITH SLIGHT CHANGES\n");
            continue;
        }
        break;
    }
    //storing all the respective values in the appropriate structure members
    printf("Enter the AGE of the new customer: ");
    scanf("%d", &(c->cage));

    printf("Enter the ADDRESS of the new customer: ");
    scanf(" %99[^\n]", c->caddress);

    printf("Enter the customer ID: ");
    scanf(" %10s", c->cten);

    printf("Enter the number of people: ");
    scanf(" %d", &(c->cpnum));

    int temp = c->cpnum;//stores the number of people

    while (1) {//infinite loop till the roomtype and number of people for each loop is decided
        printf("Enter the number for the TYPE OF ROOM:\n");
        printf("(1) -> Deluxe (Max PEOPLE:10)(Price: 7000 per day or night)\n");
        printf("(2) -> Standard (MAX PEOPLE:2)(Price: 6000 per day or night)\n");
        printf("(3) -> Suite (MAX PEOPLE:1)(Price: 9000 per day or night)\n");
        printf("(4) -> Family (MAX PEOPLE:5)(Price: 8000 per day or night)\n");
        printf("Choice: ");

        int check, flag = 0;
        scanf("%d", &check);
        //The main premise is that each roomtype has limit to number of people
        //So for each roomtype that user chooses if the number of people they
        //entered before exceeds maximum limit then the user is asked again for a different room
        //there also limited number of rooms for each type whose data is stored in Roomtype.txt
        //If there are no rooms available the user is prompted to choose a different room type
        switch (check) {
            case 1:
                if (deluxe == 0) {
                    printf("The Deluxe Rooms are currently full! Kindly choose some other room.\n");
                    continue;
                }
                c->Deluxe++;//Increases the number of rooms that the user has taken for the specific room type
                deluxe--;//decrements from the remaining rooms available for the specific room type
                if (temp > 10) {
                    printf("Room limit exceeds, choose one more room.\n");
                    temp /= 2;
                    continue;
                }
                break;

            case 2:
                if (standard == 0) {
                    printf("The Standard Rooms are currently full! Kindly choose some other room.\n");
                    continue;
                }
                c->Standard++;
                standard--;
                if (temp > 2) {
                    printf("Room limit exceeds, choose one more room.\n");
                    temp /= 2;
                    continue;
                }
                break;

            case 3:
                if (suite == 0) {
                    printf("The Suite Rooms are currently full! Kindly choose some other room.\n");
                    continue;
                }
                c->Suite++;
                suite--;
                if (temp > 1) {
                    printf("Room limit exceeds, choose one more room.\n");
                    temp /= 2;
                    continue;
                }
                break;

            case 4:
                if (family == 0) {
                    printf("The Family Rooms are currently full! Kindly choose some other room.\n");
                    continue;
                }
                c->Family++;
                family--;
                if (temp > 5) {
                    printf("Room limit exceeds, choose one more room.\n");
                    temp /= 2;
                    continue;
                }
                break;

            default:
                printf("Invalid room type. Please enter again.\n");
                flag = 1;
                break;
        }

        if (flag == 0) {
            break;
        }
    }

    tempfp = fopen("roomtype.txt", "w");//The roomtpe.txt file is opened for writing the new date which are the number of rooms remaining
    if (tempfp == NULL) {
        printf("Error opening the file.\n");
        free(c);
        return;
    }
    fprintf(tempfp, "Deluxe:%d\n", deluxe);
    fprintf(tempfp, "Standard:%d\n", standard);
    fprintf(tempfp, "Family:%d\n", family);
    fprintf(tempfp, "Suite:%d\n", suite);
    fclose(tempfp);

    fp = fopen(fname, "w");//file named by the user is opened to enter the details of the customer
    if (fp == NULL) {
        printf("Error opening the file.\n");
        free(c);
        return;
    }
    fprintf(fp, "NAME:%s\nAGE:%d\nADDRESS:%s\nCUST_ID:%s\nNUMBER_OF_PEOPLE:%d\nDELUXE:%d\nSTANDARD:%d\nFAMILY:%d\nSUITE:%d\n",
            c->cname, c->cage, c->caddress, c->cten, c->cpnum, c->Deluxe, c->Standard, c->Family, c->Suite);
    fclose(fp);
    printf("Customer record added successfully.\n");
    free(c);
}
void update(FILE *fp) {//used to update the customer file
    system("clear");
    int found = 0,new=0;//checks if the value needs to be updated is found
    FILE *tempfp;
    char fname[50], tempfilename[50], line[150], c,naam[50];//tempory file is created to store the updated records,
    //line[150] is a string which will make sense later
    printf("Enter the File Name to be updated: ");
    scanf(" %99[^\n]", fname);
    strcpy(tempfilename, "temp.txt");
    while (1) {
        int flag = 0;//to check is proper number for updation of value is entered by the user
        printf("Enter the number for the value you wish to update:\n");
        printf("(1) -> NAME\n");
        printf("(2) -> AGE\n");
        printf("(3) -> ADDRESS\n");
        printf("(4) -> CUSTOMER_ID\n");
        printf("Choice: ");

        char change;
        scanf(" %c", &change);

        switch (change) {
            case '1':
                new=1;
                fp = fopen(fname, "r");//open the filename entered by the user
                tempfp = fopen(tempfilename, "w");//open a temporery file named tempfilename
                printf("Enter the New name: ");//Enter the new value for the chosen parameter
                char name[50];
                strcpy(name,naam);
                scanf(" %49[^\n]", name);
                while (fgets(line, sizeof(line), fp) != NULL) {//fgets function returns line till it
                // reaches end of file,the line is stored in line[]array
                    if (strstr(line, "NAME:") != NULL) {//using strstr function we check if the substring is present in the line
                    //the substring being the value to be updated
                        fprintf(tempfp, "NAME:%s\n", name);//if found enters it into the temporary file
                        found = 1;
                    } else {
                        fputs(line, tempfp);//other wise normally fputs()function is used to put the lines without change
                    }
                }
                //now the temporary file has all the records of original file with the uodated values
                fclose(fp);
                fclose(tempfp);
                remove(fname);//original file is deleted
                rename(tempfilename, fname);//Temporary file is renamed to the original file
                //This procedure is done for all the updatable parameters
                break;

            case '2':
                fp = fopen(fname, "r");
                tempfp = fopen(tempfilename, "w");
                printf("Enter the new Age: ");
                int age;
                scanf("%d", &age);

                while (fgets(line, sizeof(line), fp) != NULL) {
                    if (strstr(line, "AGE:") != NULL) {
                        fprintf(tempfp, "AGE:%d\n", age);
                        found = 1;
                    } else {
                        fputs(line, tempfp);
                    }
                }fclose(fp);
                fclose(tempfp);
                remove(fname);
                rename(tempfilename, fname);
                break;
                

            case '3':
                fp = fopen(fname, "r");
                tempfp = fopen(tempfilename, "w");
                printf("Enter the new address: ");
                char address[100];
                scanf(" %99[^\n]", address);

                while (fgets(line, sizeof(line), fp) != NULL) {
                    if (strstr(line, "ADDRESS:") != NULL) {
                        fprintf(tempfp, "ADDRESS:%s\n", address);
                        found = 1;
                    } else {
                        fputs(line, tempfp);
                    }
                }fclose(fp);
                fclose(tempfp);
                remove(fname);
                rename(tempfilename, fname);
                break;
                

            case '4':
                fp = fopen(fname, "r");
                tempfp = fopen(tempfilename, "w");
                printf("Enter the new customer ID: ");
                char custId[11];
                scanf(" %10s", custId);

                while (fgets(line, sizeof(line), fp) != NULL) {
                    if (strstr(line, "CUST_ID:") != NULL) {
                        fprintf(tempfp, "CUST_ID:%s\n", custId);
                        found = 1;
                    } else {
                        fputs(line, tempfp);
                    }
                }fclose(fp);
                fclose(tempfp);
                remove(fname);
                rename(tempfilename, fname);
                break;
                
            default:
                printf("Improper Input, please try again\n");
                flag = 1;
                break;
        }
        printf("Do you want to update more values? (y/n): ");
        char check;
        scanf(" %c", &check);
        if (flag == 0 && check == 'n') {
            break;
        }
    }
    if(new==1){
        rename(fname,naam);
    }
    printf("Customer information updated successfully.\n");
    printf("Updated File: %s\n", fname);
    fp = fopen(fname, "r");
    while ((c = getc(fp)) != EOF) {
        printf("%c", c);
    }
    fclose(fp);
}
void display(FILE *fp){
    system("clear");
    char c,fname[50];
    printf("Enter the Filename to display the contents of the file: ");
    scanf(" %49[^\n]", fname);
    fp = fopen(fname, "r");
    while((c=getc(fp)) != EOF){
        printf("%c", c);
    }
    fclose(fp);
}void custfeed(FILE *fp) {
    system("clear");
    char c, fname[50];
    printf("Enter the Filename of the customer that wants to give feedback: ");
    scanf(" %49[^\n]", fname);
    printf("Write the Feedback(TO end press (Enter + CTRL Z + Enter): \n");
    fp = fopen(fname, "a");
    fprintf(fp, "CUSTOMER FEEDBACK:");
    int i=0;
    while((c=getchar())!=EOF){
        putc(c,fp);
    }
    fclose(fp);
}void checkout(FILE *fp) {
    int deluxe,standard,suite,family;
    system("clear");
    char n[50];
    printf("Enter the Filename of the customer that wants to checkout: ");
    scanf(" %49[^\n]", n);
    int r[4], bill[4] = {0, 0, 0, 0};
    float total_bill = 0;
    FILE *tempfp;
    tempfp = fopen("Roomtype.txt", "r+");
    fscanf(tempfp, "Deluxe:%d\n", &deluxe);
    fscanf(tempfp, "Standard:%d\n", &standard);
    fscanf(tempfp, "Family:%d\n", &family);
    fscanf(tempfp, "Suite:%d\n", &suite);
    fprintf(tempfp, "Deluxe:%d\n", deluxe+r[0]);
    fprintf(tempfp, "Standard:%d\n", standard+r[1]);
    fprintf(tempfp, "Family:%d\n", family+r[2]);
    fprintf(tempfp, "Suite:%d\n", suite+r[3]);
    fclose(tempfp);
    FILE *customerFile = fopen(n, "r");
    if (customerFile == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    char line[100];
    while (fgets(line, sizeof(line), customerFile)) {
        if (strstr(line, "DELUXE:") != NULL) {
            sscanf(line, "DELUXE:%d", &r[0]);
        } else if (strstr(line, "STANDARD:") != NULL) {
            sscanf(line, "STANDARD:%d", &r[1]);
        } else if (strstr(line, "FAMILY:") != NULL) {
            sscanf(line, "FAMILY:%d", &r[2]);
        } else if (strstr(line, "SUITE:") != NULL) {
            sscanf(line, "SUITE:%d", &r[3]);
        }
    }

    fclose(customerFile);

    for (int i = 0; i < 4; i++) {
        if (r[i] != 0) {
            int billt = 0;
            switch (i) {
                case 0:
                    printf("For the Deluxe room(s):\n");
                    for (int j = 1; j <= r[i]; j++) {
                        int serv, dn;
                        printf("For room %d:\n", j);
                        printf("  Enter the Services Cost (foods, beverages, and transportation): ");
                        scanf("%d", &serv);
                        printf("  Enter the total number of days and nights: ");
                        scanf("%d", &dn);
                        billt += (dn * 7000 + serv);
                    }
                    bill[i] = billt;
                    break;
                case 1:
                    printf("For the Standard room(s):\n");
                    for (int j = 1; j <= r[i]; j++) {
                        int serv, dn;
                        printf("For room %d:\n", j);
                        printf("  Enter the Services Cost (foods, beverages, and transportation): ");
                        scanf("%d", &serv);
                        printf("  Enter the total number of days and nights: ");
                        scanf("%d", &dn);
                        billt += (dn * 6000 + serv);
                    }
                    bill[i] = billt;
                    break;
                case 2:
                    printf("For the Family room(s):\n");
                    for (int j = 1; j <= r[i]; j++) {
                        int serv, dn;
                        printf("For room %d:\n", j);
                        printf("  Enter the Services Cost (foods, beverages, and transportation): ");
                        scanf("%d", &serv);
                        printf("  Enter the total number of days and nights: ");
                        scanf("%d", &dn);
                        billt += (dn * 8000 + serv);
                    }
                    bill[i] = billt;
                    break;
                case 3:
                    printf("For the Suite room(s):\n");
                    for (int j = 1; j <= r[i]; j++) {
                        int serv, dn;
                        printf("For room %d:\n", j);
                        printf("  Enter the Services Cost (foods, beverages, and transportation): ");
                        scanf("%d", &serv);
                        printf("  Enter the total number of days and nights: ");
                        scanf("%d", &dn);
                        billt += (dn * 9000 + serv);
                    }
                    bill[i] = billt;
                    break;
            }
        }
    }

    for (int i = 0; i < 4; i++) {
        total_bill += bill[i];
    }
    total_bill += total_bill * 0.40;
    printf("The total bill is: Rs %.2f/-\n", total_bill);

    customerFile = fopen(n, "a+");
    if (customerFile == NULL) {
        printf("Error opening the file to append the bill.\n");
        return;
    }
    fprintf(customerFile, "TOTAL_BILL: Rs %.2f/-\n", total_bill);
    fclose(customerFile);
}

#endif
