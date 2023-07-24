#include <stdio.h>//standard library header file
#include <string.h>//string handling header file
#include <stdlib.h>//standard library header file to use DMA
#include <unistd.h>//to use the access fucntion
#include <windows.h>//to use system("cls")
#include "task.h"//custom header files containing functions to execute this program
int main() {
    struct customer* c;
    FILE* fp;
    int choice;
    while (1) {
        int flag = 0;//Used for ending the manu
        printf("*************************************************************\n");
        printf("*  Enter the NUMBER to perform the specific task:           *\n");
        printf("*  (1)--> TO ADD NEW CUSTOMER RECORD                        *\n");
        printf("*  (2)--> TO UPDATE AGE OF ANY CUSTOMER RECORD              *\n");
        printf("*  (3)--> TO DISPLAY ANY CUSTOMER RECORD                    *\n");
        printf("*  (4)--> CHECKING OUT                                      *\n");
        printf("*  (5)--> CUSTOMER FEEDBACK                                 *\n");
        printf("*  (6)--> END                                               *\n");
        printf("*************************************************************\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
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
                checkout(fp);
                break;

            case 5:
                custfeed(fp);
                break;

            case 6:
                flag = 1;
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
        
        if (flag == 1) {//checks if flag==1 which is only possible when user selects (6) or end
            printf("End of Program...\n");
            break;
        }
    }
    
    return 0;
}
