#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../cJSON/cJSON.h"
#ifndef APIdecoder_h
#define APIdecoder_h

typedef struct _obszar
{
    int x;
    int y;
    char *type;
} obszar;

typedef struct _obszar3
{
    int x[3];
    int y[3];
    char *type[3];
}   obszar3;

char *info(char *token);

char *move(char *token);

char *rotate(char *token, char *direction);

char *rotatel(char *token, char *direction);

char *explore(char *token);

char *reset(char *token);

obszar *DJson(char *response);

obszar3 *DJson_explore(char *response);

#endif