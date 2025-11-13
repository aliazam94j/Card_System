#ifndef CARDFUNCTIONS_H
#define CARDFUNCTIONS_H
#include <stdbool.h>
#include "systemstate.h"

void remoteOpenDoor(const SystemState *s);
void listAllCards(const SystemState *s);
void fakeCardScan(const SystemState *s);
bool addRemoveAccess(SystemState *s);

bool SaveDaFile(const SystemState *s, const char *path);
bool LoadDaFile(SystemState *s, const char *path);
#endif