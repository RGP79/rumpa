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

void tank_move_whole(char *token, Map *M, int a);

void tank_rot_whole(char *token, Map *M, int a, int b);

void tank_exp_whole(char *token, Map *M, int a);

Map * tank_res_whole(char *token, Map *M, int a);

Map * tank_rot(Map *M, Area *F);

Map * tank_update(Map *M, Area *F);

Map * tank_exp(Map *M, Area3 *Fe, Area *F);

void write_inf_Map_exp(Area3 *Fe, Map *M);

void write_info_Map(Map *M, Area *F);

void write(Map *M);

void *save(Map *M);

Map *load(Map *M);

int check_border(Map *M);

Map * render(Map *M);

void free_map(Map *M);

void free_area(Area *F);

#endif