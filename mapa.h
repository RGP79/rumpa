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
    int **plansza;
    int x;
    int y;
    int delta_x;
    int delta_y;
    char *kierunek;
    int rozmiar_x;
    int rozmiar_y;

} Mapa;

Mapa * nowa(obszar *F);

void wypisz(Mapa *M);

void *zapisz(Mapa *M);

void *wczytaj(Mapa *M);

int check_border(Mapa *M);

Mapa * dopisz(Mapa *M);

Mapa * dopisz_N(Mapa *M);

Mapa * dopisz_E(Mapa *M);

Mapa * dopisz_S(Mapa *M);

Mapa * dopisz_W(Mapa *M);

Mapa * offset(Mapa *M);

void zwolnij_mape(Mapa *M);

#endif