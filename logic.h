#ifndef logic_h
#define logic_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"
#include "APIdecoder.h"

int getStartX(char *token);

int getStartY(char *token);

Map * moveToHit(char *token, Map *M);

Map * rotL_Move(char *token, Map *M);

Map * rotR_Move(char *token, Map *M);

Map * roundsL(char *token, Map *M);

#endif