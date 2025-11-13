#include <stdio.h>
#include <string.h>
#include "card.h"


// When you write the name of the card like A, that same letter has to be before the . in the code
void printCard(Card A){
    // Print the cardnumber, A.card(lower case) Number(uppercase) ->(can be written differently)
    printf("CardNumber -> %d\n", A.cardNumber); 
    // Print the Access
    printf("Access Status -> %s\n",A.hasAccess ? "Granted" : "Denied" ); 
    //Print the date when the card was added
    printf("The Added Date -> %s\n",A.dateAdded);


}

