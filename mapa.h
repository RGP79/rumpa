#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "APIdecoder.h"
#define N 5
#ifndef mapa_h
#define mapa_h

typedef struct _Mapa
{
    char **plansza;
    int x;
    int y;
    int delta_x;
    int delta_y;
    char *kierunek;
    int rozmiar_x;
    int rozmiar_y;
    struct _obszar mapa;
    struct _obszar3 mapa2;

} Mapa;

Mapa * nowa(Mapa* M);

void wypisz(Mapa *M);

#endif