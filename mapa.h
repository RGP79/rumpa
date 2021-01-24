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

Mapa * tank_rot(Mapa *M, obszar *F);

Mapa * tank_move(Mapa *M, obszar *F);

Mapa * tank_exp(Mapa *M, obszar3 *F);

void wyp_inf_Map_exp(obszar3 *Fe);

void wypisz_info_Mapa(Mapa *M, obszar *F);

void wypisz(Mapa *M);

void *zapisz(Mapa *M);

Mapa *wczytaj(Mapa *M);

int check_border(Mapa *M);

Mapa * dopisz(Mapa *M);

Mapa * dopisz_N(Mapa *M);

Mapa * dopisz_E(Mapa *M);

Mapa * dopisz_S(Mapa *M);

Mapa * dopisz_W(Mapa *M);

Mapa * offset(Mapa *M, obszar *F);

void zwolnij_mape(Mapa *M);

#endif