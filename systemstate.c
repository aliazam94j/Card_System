#include "systemstate.h"
#include <stdlib.h>          // ← needed for free()

void initSystemstate(SystemState *s) {
    s->cards = NULL;
    s->cardCount = 0;
    s->cardCapacity = 0;
}

void freeSystemstate(SystemState *s) {
    free(s->cards);
    s->cards = NULL;
    s->cardCount = 0;
    s->cardCount = 0;
}
