#ifndef task_h
#define task_h
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
struct customer {
    char cname[50];
    char caddress[100];
    char cten[11];
    char croom[10];
    int croomno;
    int cage;  
};
int fileExists(const char* filename);
void addcust(FILE *fp);
void update(FILE *fp);
void display(FILE *fp);
void custfeed(FILE *fp);
int fileExists(const char* filename) {
    return access(filename, F_OK) != -1;
}

void addcust(FILE *fp) {
    struct customer* c = malloc(sizeof(struct customer));

    while (1) {
        printf("Enter the NAME of the new customer: ");
        scanf(" %49[^\n]", c->cname);

        if (fileExists(c->cname)) {
            char ans;
            printf("The file by this name already exists, do you want to overwrite it? (y/n): ");
            scanf(" %c", &ans);

            if (ans == 'n') {
                free(c);
                continue;
            }
        }break;
    }

    fp = fopen(c->cname, "w");

    printf("Enter the ADDRESS of the new customer: ");
    scanf(" %99[^\n]", c->caddress);

    printf("Enter the 10-digit customer ID: ");
    scanf(" %10s", c->cten);

    while (1) {
        printf("Enter the number for the TYPE OF ROOM:\n");
        printf("(1) -> Deluxe\n");
        printf("(2) -> Standard\n");
        printf("(3) -> Suite\n");
        printf("(4) -> Family\n");
        printf("Choice: ");

        int check,flag=0;
        scanf("%d", &check);

        switch (check) {
            case 1:
                strcpy(c->croom, "Deluxe");
                break;
            case 2:
                strcpy(c->croom, "Standard");
                break;
            case 3:
                strcpy(c->croom, "Suite");
                break;
            case 4:
                strcpy(c->croom, "Family");
                break;
            default:
                printf("Invalid room type. Please enter again.\n");
                flag=1;
                break;
        }

        if(flag==0){
            break;
        }
    }
    printf("Enter the 4-digit ROOM NUMBER: ");
    scanf("%d", &(c->croomno));

    printf("Enter the AGE of the new customer: ");
    scanf("%d", &(c->cage));

    fprintf(fp, "NAME:%s\nADDRESS:%s\nAGE:%d\nCUST_ID:%s\nROOM_NO:%d\nROOMTYPE:%s",
            c->cname, c->caddress, c->cage, c->cten, c->croomno, c->croom);

    printf("Customer record added successfully...\n");
    fclose(fp);
    free(c);
}
void update(FILE *fp) {
    int found = 0,new=0;
    FILE *tempfp;
    char fname[50], tempfilename[50], line[150], c,naam[50];
    printf("Enter the File Name to be updated: ");
    scanf(" %49[^\n]", fname);
    strcpy(tempfilename, "temp.txt");
    while (1) {
        int flag = 0;
        printf("Enter the number for the value you wish to update:\n");
        printf("(1) -> NAME\n");
        printf("(2) -> ADDRESS\n");
        printf("(3) -> CUSTOMER_ID\n");
        printf("(4) -> ROOM_TYPE\n");
        printf("(5) -> ROOM_NO.\n");
        printf("(6) -> AGE\n");
        printf("Choice: ");

        char change;
        scanf(" %c", &change);

        switch (change) {
            case '1':
                new=1;
                fp = fopen(fname, "r");
                tempfp = fopen(tempfilename, "w");
                printf("Enter the New name: ");
                char name[50];
                strcpy(name,naam);
                scanf(" %49[^\n]", name);
                while (fgets(line, sizeof(line), fp) != NULL) {
                    if (strstr(line, "NAME:") != NULL) {
                        fprintf(tempfp, "NAME:%s\n", name);
                        found = 1;
                    } else {
                        fputs(line, tempfp);
                    }
                }
                fclose(fp);
                fclose(tempfp);
                remove(fname);
                rename(tempfilename, fname);
                break;

            case '2':
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

            case '3':
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

            case '4':
                fp = fopen(fname, "r");
                tempfp = fopen(tempfilename, "w");
                printf("Enter the new room type:\n");
                printf("(1) -> Deluxe\n");
                printf("(2) -> Standard\n");
                printf("(3) -> Suite\n");
                printf("(4) -> Family\n");
                printf("Choice: ");

                int roomType;
                scanf("%d", &roomType);

                char croom[10];
                switch (roomType) {
                    case 1:
                        strcpy(croom, "Deluxe");
                        break;
                    case 2:
                        strcpy(croom, "Standard");
                        break;
                    case 3:
                        strcpy(croom, "Suite");
                        break;
                    case 4:
                        strcpy(croom, "Family");
                        break;
                    default:
                        printf("Invalid room type. Please enter again.\n");
                        continue;
                }

                while (fgets(line, sizeof(line), fp) != NULL) {
                    if (strstr(line, "ROOMTYPE:") != NULL) {
                        fprintf(tempfp, "ROOMTYPE:%s\n", croom);
                        found = 1;
                    } else {
                        fputs(line, tempfp);
                    }
                }fclose(fp);
                fclose(tempfp);
                remove(fname);
                rename(tempfilename, fname);
                break;

            case '5':
                fp = fopen(fname, "r");
                tempfp = fopen(tempfilename, "w");
                printf("Enter the new Room Number: ");
                int room_no;
                scanf("%d", &room_no);

                while (fgets(line, sizeof(line), fp) != NULL) {
                    if (strstr(line, "ROOM_NO:") != NULL) {
                        fprintf(tempfp, "ROOM_NO:%d\n", room_no);
                        found = 1;
                    } else {
                        fputs(line, tempfp);
                    }
                }fclose(fp);
                fclose(tempfp);
                remove(fname);
                rename(tempfilename, fname);
                break;

            case '6':
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
    char c,fname[50];
    printf("Enter the filename to display the contents of the file: ");
    scanf(" %[^\n]", fname);
    fp = fopen(fname, "r");
    while((c=getc(fp)) != EOF){
        printf("%c", c);
    }
    fclose(fp);
}void custfeed(FILE *fp){
    printf("CUSTOMER FEEDBACK: ");
    char c,fname[50];
    printf("Enter the name of the customer that wants to give feedback: ");
    scanf(" %[^\n]", &fname);
    fp=fopen(fname, "a");
    fprintf(fp,"CUSTOMER FEEDBACK:\n");
    while((c=getchar()!=EOF)){
        putc(c,fp);
    }
    fclose(fp);
}
#endif 
