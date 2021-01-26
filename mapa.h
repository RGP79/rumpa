#ifndef mapa_h
#define mapa_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "APIdecoder.h"
#define N 5

typedef struct _Map
{
    int **plansza;
    int x;
    int y;
    int delta_x;
    int delta_y;
    char *kierunek;
    int rozmiar_x;
    int rozmiar_y;

} Map;

Map * new_map(Area *F);

Map * tank_rot(Map *M, Area *F);

Map * tank_move(Map *M, Area *F);

// Map * tank_reset(Map *M, Area *F);

Map * tank_exp(Map *M, Area3 *Fe, Area *F);

void write_inf_Map_exp(Area3 *Fe, Map *M);

void write_info_Map(Map *M, Area *F);

void write(Map *M);

void *save(Map *M);

Map *load(Map *M);

int check_border(Map *M);

Map * render(Map *M);

Map * render_N(Map *M);

Map * render_E(Map *M);

Map * render_S(Map *M);

Map * render_W(Map *M);

Map * offset(Map *M, Area *F);

void free_map(Map *M);

void free_area(Area *F);

#endif