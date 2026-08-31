#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "menu.h"
#include "cardfunction.h"
#include "safeinput.h"
#include "card.h"
#include "systemstate.h"

int main(void){
    SystemState state;
    initSystemstate(&state);

    if(LoadDaFile(&state, "cards.dat")){
        printf("Loaded %d cards from file.\n", state.cardCount);
    }else{
        puts("no previous cards file can be found(starting empty).");
    }


    while (true) {
        printMenu();
        int option;
if (!GetInputInt("Select option: ", &option)) {
    printf("Wrong input. Try again.\n");
    continue;
}

        switch (option) {
            case 1:
                remoteOpenDoor(&state);
                break;
            case 2:
                listAllCards(&state);
                break;
            case 3:
               addRemoveAccess(&state);  
                break;
            case 4:
                if(!SaveDaFile(&state, "cards.dat")){
                    puts("Warning: FAILED to save cardfile.");
                }
                freeSystemstate(&state);
                printf("Exiting...\n");
                return 0;
            case 9:
                fakeCardScan(&state);
                break;
            default:
                printf("Invalid option. Try again.\n");
        }
    } 
}   


