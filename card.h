#ifndef CARD_H
#define CARD_H
#include <stdbool.h>


typedef struct {

    int cardNumber; // card id
    bool hasAccess; // Access status of the card
    char dateAdded[11]; // date format when the card was added, 11 is how many characters there are. 
} Card;

void printCard(Card A);

#endif

