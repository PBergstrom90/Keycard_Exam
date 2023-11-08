#include <stdio.h>
#include "remotedoor.h"
#include "safeinput.h"

    void remoteDoor() {
        
        int openDoor = 0;
        printf("\nDo you wish to open the door? \n1. Yes\n2. No\n");
        GetInputInt("\nEnter: ", &openDoor);
        if(openDoor == 1){
            printf("\nDoor is opening...\n");
            printf("Currently the lamp is: ");
            printf("\033[1;32m"); 
            printf("GREEN\n"); 
            printf("\033[0m");

        } else if (openDoor == 2){
            printf("\nDoor is locked...\n");
            printf("Currently the lamp is: ");
            printf("\033[1;31m"); 
            printf("RED\n"); 
            printf("\033[0m");
        } else {
            printf("\nAn error has occured. Please try again.\n");
        }
    }