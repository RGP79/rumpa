#ifndef APIdecoder_h
#define APIdecoder_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../cJSON/cJSON.h"

typedef struct _Area
{
    int x;
    int y;
    char *type;
    char *dir;
} Area;

typedef struct _Area3
{
    int x[3];
    int y[3];
    char *type[3];
}   Area3;

char *info(char *token, int a);

char *move(char *token);

char *rotate(char *token, char *direction);

char *rotatel(char *token, char *direction);

char *explore(char *token);

char *reset(char *token);

Area *DJson_info(char *response);

Area3 *DJson_explore(char *response);

#endif