#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include"task.h"
// struct customer {
//     char cname[50];
//     char caddress[100];
//     char cten[11];
//     char croom[10];
//     int croomno;
//     int cage;  
// };
int main() {
    struct customer* c;
    FILE* fp;
    int choice;
    while (1) {
        int flag=0;
        printf("Enter the NUMBER to perform the specific task:\n");
        printf("(1)--> TO ADD NEW CUSTOMER RECORD\n");
        printf("(2)--> TO UPDATE AGE OF ANY CUSTOMER RECORD\n");
        printf("(3)--> TO DISPLAY ANY CUSTOMER RECORD\n");
        printf("(4)--> CUSTOMER FEEDBACK\n");
        printf("(5)--> END\n");
        printf("Choice: ");
        scanf("%d", &choice);
        switch(choice){
            case 1:
                addcust(fp);
                break;

            case 2:
                update(fp);
                break;

            case 3:
                display(fp);
                break;

            case 4:
                custfeed(fp);
                break;

            case 5:
                flag=1;
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }if(flag==1){
            printf("End of Program...");
            break;
        }
    }
    return 0;
}
