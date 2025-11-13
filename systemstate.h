#ifndef SYSTEMSTATE_H
#define SYSTEMSTATE_H
#include <stdbool.h>

#include "card.h"

typedef struct {
    Card* cards;
    int cardCount;
    int cardCapacity;
}
SystemState;

void initSystemstate(SystemState *s);
void freeSystemstate(SystemState *s);

#endif


