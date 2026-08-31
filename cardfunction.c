#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "card.h"
#include <string.h>
#include <stdbool.h>

#include "systemstate.h"
#include "safeinput.h"
#include "cardfunction.h"
#ifdef _WIN32
    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
    #endif
    #include <windows.h>
#endif


static int findCardIndex(const SystemState *s, int number){
    for(int input =0; input < s->cardCount; ++input){
        if(s->cards[input].cardNumber == number) return input;
    }
    return -1;
}



 void remoteOpenDoor(const SystemState *s) {
    (void)s;
    printf("Door opened remotely!\n");
    puts("CURRENTLY LAMP IS:GREEN");
#ifdef _WIN32
    Sleep(3000);
#else
    struct timespec ts ={3, 0};
    nanosleep(&ts, NULL);
#endif
puts("CURRENTLY LAMP IS:RED");
}

void listAllCards(const SystemState *s){
    if (s->cardCount == 0) {
        puts("No CARDS in system.");
        return;
    }

    for (int i = 0; i < s->cardCount; ++i) {
        printf("Card index %d:\n", i);
        printCard(s->cards[i]);   // uses dateAdded inside
        puts("");                 // blank line between cards
    }

}

void fakeCardScan(const SystemState *s){
    int number;
    if(!GetInputInt("Fake Scan - Enter da Card Number: ", &number)){
        puts("Failed Input! ");
        return;
    }

    int index = findCardIndex(s,number);
    if(index == -1) {
        puts("Card not FOUND. CURRENTLY LAMP IS: RED");
        return;
    }

    if (s->cards[index].hasAccess){
        puts("card has ACCESS. CURRENTLY LAMP IS: GREEN");
    }else{
        puts("card has NO ACCESS! CURRENTLY LAMP IS: RED");
    }
    
}

// To add or remove cards

static bool growCards(SystemState *s){
    if(s -> cardCount < s->cardCapacity){
        return true;
    }
    int newCap;
    if (s->cardCapacity == 0){ // -> points to capacity
        newCap = 10;
    }
    else{
        newCap = s->cardCapacity * 2;
    }
    Card *newBrick = realloc (s ->cards,(size_t)newCap* sizeof *newBrick );
    if(!newBrick){
        printf("ERROR: COULD NOT GROW CARD LIST.\n ");
        return false;
    }

    s->cards = newBrick;
    s->cardCapacity = newCap;
    return true;
    }

    static void setToday(char *buf, size_t size) {
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    if (!tm_info) {
        if (size > 0) buf[0] = '\0';
        return;
    }
    /* writes "YYYY-MM-DD" into buf */
    strftime(buf, size, "%Y-%m-%d", tm_info);
}


bool addRemoveAccess(SystemState *s) {
    int number;


    // Ask for a card nr
    if(!GetInputInt("Enter The Card Here!: ", &number)){
        puts("Not valid input. ");
        return false;
}
if (number <=0){
    puts("Card must be positive. ");
    return false;
}

    // check if it exists
    int position=findCardIndex(s,number);
    if(position != -1){
    printf("Card %d exists.(access:%s)\n",
        number,
        s->cards[position].hasAccess ? "GRANTED" : "DENIED!");
    puts("Chose: [g]rant, [d]eny, [x]delete");
    

    char choice;
    if(!GetInputChar(">", &choice)){
        puts("NO INPUT! ");
        return false;
    }


    if(choice == 'g'|| choice == 'G'){
        s->cards[position].hasAccess=true;
        puts("Access GRANTED For da card. ");
        return true;
    }else if (choice == 'd'|| choice == 'D'){
        s->cards[position].hasAccess=false;
        puts("Access DENIED For da card. ");
        return true;
    }else if(choice == 'x'|| choice == 'X'){
        s->cards[position] = s->cards[s->cardCount -1];
        s->cardCount --;
        puts("Da CARD deleted from the system ");
        return true;
    }else{
        puts("UNKNOWN choice. ");
        return false;
    }
    }


    // Making sure there is space and that it can grow if needed.
    if(!growCards(s)){
        return false;
    }


    // Add a new card at the end.
    Card *c = &s->cards[s->cardCount];
    c->cardNumber = number;
    c->hasAccess  = true;
    setToday(c->dateAdded, sizeof c->dateAdded);

    s->cardCount++; // we have now added 1 more card


    printf("Card %d ADDED! Total cards: %d\n", number, s->cardCount);
    return true;
}

bool SaveDaFile(const SystemState *s, const char *path){
    FILE *f =fopen(path,"wb");
    if(!f){
        puts("Could not open Da file for writing. ");
        return false;
    }

    // write how many cards we have
    if(fwrite(&s-> cardCount, sizeof s-> cardCount, 1, f) !=1){
        puts("FAILED to input the card count");
        fclose(f);
        return false;
    }

    // write the actual cards (if we have any)
    if(s-> cardCount > 0){
        if(fwrite(s->cards, sizeof s -> cards[0], (size_t) s->cardCount, f)
            !=(size_t) s -> cardCount){
            puts("FAILED TO write da Cards");
            fclose(f);
            return false;
        }
    }
    fclose(f);
    return true;
}

bool LoadDaFile(SystemState *s, const char *path){
    FILE *f =fopen(path,"rb");
    if(!f){
        return false;
    }

    int n= 0;
    if (fread(&n, sizeof n, 1, f) !=1 || n <0) {
        puts("Failed to display ammounts of card");
        fclose(f);
        return false;
    }

    Card *arr = NULL;
    if (n>0){
        arr= (Card *)malloc((size_t) n* sizeof *arr);
        if(!arr) {
            puts("No memory while loading ");
            fclose(f);
            return false;
        }
        if(fread(arr, sizeof *arr,(size_t)n,f)!=(size_t)n){
            puts("Failed to read cards. ");
            free(arr);
            fclose(f);
            return false;
        }
    }
    fclose(f);

    free (s->cards);
    s->cards       = arr;
    s->cardCount   = n;
    s->cardCapacity= n; 

    return true;
}