#ifndef logic_h
#define logic_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int getStartX(char *token);

int getStartY(char *token);

void moveToHit(char *token);

void rotL_Move(char *token);

void rotR_Move(char *token);

void rundkiL(char *token);

void rundkiR(char *token);

#endif