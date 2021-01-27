#include "map.h"
//nie działa check border po dopisaniu na połódniu.
Map * new_map(Area *F){
    int i, j;
    Map *M;
    M = (Map*) malloc(sizeof(Map));
    M->rozmiar_x = N;
    M->rozmiar_y = N;
    M->delta_x = 1;
    M->delta_y = 1;
    M->kierunek = (char*) malloc(sizeof(char) * strlen((F->dir) + 1));
    strcpy(M->kierunek, F->dir);
    M->plansza = (int**) calloc(M->rozmiar_y, sizeof(int*));
    for(i=0; i<M->rozmiar_y; i++)
    {
        M->plansza[i] = (int*) calloc(M->rozmiar_x, sizeof(int));
        for(j=0;j<M->rozmiar_x;j++)
        {
            M->plansza[i][j]=' ';
        }
    }
    return M;
}

void tank_move_whole(char *token, Map *M, int a)
{
    char *response;
    response=move(token);
    Area *field = DJson_info(response, 0);
    
    M = tank_update(M, field);
    if(a == 1)
        write_info_Map(M, field);
    write(M);
    free_area(field);
    free(response);
}

void tank_rot_whole(char *token, Map *M, int a, int b)
{
    char *response;
    if(b == 1)
        response=rotatel(token, "left");
    else if(b == 2)
        response=rotate(token, "right");
    Area *field = DJson_info(response, 1);
    free(response);
    M = tank_rot(M, field);
    if(a == 1)
        write_info_Map(M, field);
    write(M);
    free_area(field);
}

void tank_exp_whole(char *token, Map *M, int a)
{
    char *response;
    char *response1;
    response=explore(token);
    Area3 *fielde = DJson_explore(response);
    
    response1 = info(token, 0);
    Area *F = DJson_info(response1, 0);

    M = tank_exp(M, fielde, F);
    if(a == 1)
        write_inf_Map_exp(fielde, M);
    write(M);
    for(int i=0;i<3;i++)
        free(fielde->type[i]);
    free(fielde);
    free_area(F);
    free(response);
    free(response1);
}

Map * tank_res_whole(char *token, Map *M, int a)
{
    char *response;
    free_map(M);
    response=reset(token);
    Area *field = DJson_info(response, 0);
    free(response);
    M = new_map(field);
    M = tank_update(M, field);
    if(a == 0)
        write_info_Map(M, field);
    write(M);
    free_area(field);
    return M;
}

Map * tank_rot(Map *M, Area *F)
{
    Map *New = M;
    // New->kierunek = (char*) malloc(sizeof(char) * strlen((F->dir) + 1));
    // strcpy(New->kierunek, F->dir);
    New->kierunek = F->dir;
    // free(M->kierunek);
    New->x = F->x + M->delta_x;
    New->y = F->y + M->delta_y;
    return New;
}

Map * tank_update(Map *M, Area *F)
{   
    Map *New = M;
    New->x = F->x + M->delta_x;
    New->y = F->y + M->delta_y;
    if(strcmp(F->type, "grass")==0)
        New->plansza[New->y][New->x]='G';
    if(strcmp(F->type, "sand")==0)
        New->plansza[New->y][New->x]='S';
    if(strcmp(F->type, "wall")==0)
        New->plansza[New->y][New->x]='W';
    return New;
}

Map * tank_exp(Map *M, Area3 *Fe, Area *F)
{    
    // printf("M->x: %d\n", M->x);
    for (int i = 0; i<3; i++){
        if(strcmp(Fe->type[i], "grass")==0)
        M->plansza[M->delta_y + Fe->y[i]][M->delta_x + Fe->x[i]]='G';
        if(strcmp(Fe->type[i], "sand")==0)
        M->plansza[M->delta_y + Fe->y[i]][M->delta_x + Fe->x[i]]='S';
        if(strcmp(Fe->type[i], "wall")==0)
        M->plansza[M->delta_y + Fe->y[i]][M->delta_x + Fe->x[i]]='W';
    }
    M->x = F->x + M->delta_x;
    M->y = F->y + M->delta_y;
    return M;
}

void write_inf_Map_exp(Area3 *Fe, Map *M)
{
    printf("x 3: %d\n",(M->delta_x + Fe->x[0]));
    printf("y 3: %d\n",(M->delta_y + Fe->y[0]));
    printf("Type of field 3: %s\n",Fe->type[0]);
    printf("x 2: %d\n",(M->delta_x + Fe->x[1]));
    printf("y 2: %d\n",(M->delta_y + Fe->y[1]));
    printf("Type of field 2: %s\n",Fe->type[1]);
    printf("x 1: %d\n",(M->delta_x + Fe->x[2]));
    printf("y 1: %d\n",(M->delta_y + Fe->y[2]));
    printf("Type of field 1: %s\n",Fe->type[2]);
}

void write_info_Map(Map *M, Area *F)
{
    // printf("M->rozmiar_x: %d\n", M->rozmiar_x);
    // printf("M->rozmiar_y: %d\n", M->rozmiar_y);
    printf("Direction: %s\n",M->kierunek);
    printf("x: %d\n",M->x);
    printf("y: %d\n",M->y);
    printf("Field type: %s\n",F->type);
}

int check_border(Map *M)
{
    // printf("M->x: %d\n", M->x);
    // printf("M->y: %d\n", M->y);
    // printf("M->delta_y: %d\n", M->delta_y);
    // printf("M->delta_y: %d\n", M->delta_y);
    // printf("warunek N: %d = %d\n", (M->rozmiar_y - M->delta_y - M->y), 0);
    // printf("warunek E: %d = %d\n", (M->delta_x + M->x), (M->rozmiar_x));
    // printf("warunek S: %d = %d\n", (M->rozmiar_y - M->delta_y - M->y), (M->rozmiar_y-1));
    // printf("warunek W: %d = %d\n", (M->delta_x + M->x), 0);
    if((M->rozmiar_y - M->delta_y - M->y) == 0 || (M->delta_x + M->x) == (M->rozmiar_x) || (M->rozmiar_y - M->delta_y - M->y) == (M->rozmiar_y-1) || (M->delta_x + M->x) == (0)){
        // printf("zwracam 0\n");
        return 0;
    }
    else
    {
        return -1;
    }
}

Map * render(Map *M)
{    
    int i, j;
    Map *New;    
    New = (Map*) malloc(sizeof(Map)); 
    if(strcmp(M->kierunek, "N")==0)
    {
        New->rozmiar_x = M->rozmiar_x;
        New->rozmiar_y = M->rozmiar_y*2;
        New->plansza = (int**) calloc(New->rozmiar_y , sizeof(int*));
        for(i=0; i<New->rozmiar_y; i++){ 
            New->plansza[i] = (int*) calloc(New->rozmiar_x, sizeof(int));
            for(j=0;j<New->rozmiar_x;j++)
            {            
                if(i < M->rozmiar_y){
                    New->plansza[i][j] = M->plansza[i][j];
                }
                if(i >= M->rozmiar_y){
                    New->plansza[i][j]=' ';
                }
            }
        }
        New->delta_x = M->delta_x;
        New->delta_y = M->delta_y;
        New->x = M->x;
        New->y = M->y;
    }
    else if(strcmp(M->kierunek, "E")==0)
    {
        New->rozmiar_x = M->rozmiar_x*2;
        New->rozmiar_y = M->rozmiar_y;  
        New->plansza = (int**) calloc(New->rozmiar_y , sizeof(int*));
        for(i=0; i<New->rozmiar_y; i++){ 
            New->plansza[i] = (int*) calloc(New->rozmiar_x, sizeof(int));
            for(j=0;j<New->rozmiar_x;j++)
            {            
                if(j < M->rozmiar_x){
                    New->plansza[i][j] = M->plansza[i][j];
                }
                if(j >= M->rozmiar_x){
                    New->plansza[i][j]=' ';
                }            
            }        
        }
        New->delta_x = M->delta_x;
        New->delta_y = M->delta_y;
        New->x = M->x;
        New->y = M->y;
    }
    else if(strcmp(M->kierunek, "S")==0)
    {
        New->rozmiar_x = M->rozmiar_x;
        New->rozmiar_y = M->rozmiar_y*2;  
        New->plansza = (int**) calloc(New->rozmiar_y , sizeof(int*));
        for(i=0; i<New->rozmiar_y; i++){ 
            New->plansza[i] = (int*) calloc(New->rozmiar_x, sizeof(int));
            for(j=0;j<New->rozmiar_x;j++)
            {            
                if(i < M->rozmiar_y){
                    New->plansza[i][j]=' ';
                }
                if(i >= M->rozmiar_y){
                    New->plansza[i][j] = M->plansza[i - M->rozmiar_y][j];
                }            
            }        
        }
        New->delta_x = M->delta_x;
        New->delta_y = M->delta_y + M->rozmiar_y;
        New->x = M->x;
        New->y = M->y + New->delta_y;
    }
    else if(strcmp(M->kierunek, "W")==0)
    {
        New->rozmiar_x = M->rozmiar_x*2;
        New->rozmiar_y = M->rozmiar_y;  
        New->plansza = (int**) calloc(New->rozmiar_y , sizeof(int*));
        for(i=0; i<New->rozmiar_y; i++){ 
            New->plansza[i] = (int*) calloc(New->rozmiar_x, sizeof(int));
            for(j=0;j<New->rozmiar_x;j++)
            {            
                if(j < M->rozmiar_x){
                    New->plansza[i][j]=' ';
                }
                if(j >= M->rozmiar_x){
                    New->plansza[i][j] = M->plansza[i][j - M->rozmiar_x];
                }                
            }
        }
        New->delta_x = M->delta_x + M->rozmiar_x;
        New->delta_y = M->delta_y;
        New->x = M->x + New->delta_x;
        New->y = M->y;
    }
    else
    {
        printf("Error of funcion render[mapa.c].\n");
    }
    New->kierunek = (char*) malloc(sizeof(char) * strlen((M->kierunek) + 1));
    strcpy(New->kierunek, M->kierunek);
    free_map(M);
    return New;
}

void write(Map *M){
    int i, j, a;
    for(i=0;i<M->rozmiar_x;i++)
        printf("+ - ");
    printf("+\n");

    for(i=0;i<M->rozmiar_y;i++){
        for(j=0;j<M->rozmiar_x;j++){
            printf("| ");
            if((M->x == j) && (M->y == (M->rozmiar_y - 1 - i)))
            {
                if(M->plansza[M->rozmiar_y - 1 - i][j] == 'G')
                    printf(ANSI_COLOR_GREEN);
                else if(M->plansza[M->rozmiar_y - 1 - i][j] == 'S')
                    printf(ANSI_COLOR_YELLOW);
                if(strcmp(M->kierunek, "N")==0)
                    printf("^ ");
                else if(strcmp(M->kierunek, "E")==0)
                    printf("> ");
                else if(strcmp(M->kierunek, "S")==0)
                    printf("v ");
                else if(strcmp(M->kierunek, "W")==0)
                    printf("< ");
                printf(ANSI_COLOR_RESET);
            }
            else{
                if(M->plansza[M->rozmiar_y - 1 - i][j] == 'G')
                    printf(ANSI_COLOR_GREEN "G " ANSI_COLOR_RESET);
                else if(M->plansza[M->rozmiar_y - 1 - i][j] == 'W')
                    printf(ANSI_COLOR_RED "W " ANSI_COLOR_RESET);
                else if(M->plansza[M->rozmiar_y - 1 - i][j] == 'S')
                    printf(ANSI_COLOR_YELLOW "S " ANSI_COLOR_RESET);
                else if(M->plansza[M->rozmiar_y - 1 - i][j] == ' ')
                    printf("  ");

            }
                // printf("%c ", M->plansza[M->rozmiar_y - 1 - i][j]);
        }
        printf("|%d", (M->rozmiar_y - 1 - i));
        printf("\n");
        for(a=0;a<M->rozmiar_x;a++)
            printf("+ - ");
        printf("+");
        printf("\n");        
    }
    for(i=0;i<M->rozmiar_x; i++)
        printf("%3d ", i);
    printf("\n");
}

void *save(Map *M){
    FILE *fout = fopen("board.txt", "w");
    int i, j;

    fprintf(fout, "%d\n", M->rozmiar_x);
    fprintf(fout, "%d\n", M->rozmiar_y);
    fprintf(fout, "%d\n", M->delta_x);
    fprintf(fout, "%d\n", M->delta_y);
    for(i=0;i<M->rozmiar_y;i++){
        for(j=0;j<M->rozmiar_x;j++){
            fprintf(fout, "%3d", M->plansza[i][j]);
        }
        fprintf(fout, "\n");
    }
    fclose(fout);
}

Map *load(Map *M){

    Map *New;
    New = (Map*) malloc(sizeof(Map));
    FILE *fin = fopen("board.txt", "r");
    if(fin != NULL){
        int i, j;
        fscanf(fin, "%d", &New->rozmiar_x);
        fscanf(fin, "%d", &New->rozmiar_y);
        fscanf(fin, "%d", &New->delta_x);
        fscanf(fin, "%d", &New->delta_y);
        // printf("New->rozmiar_x: %d (load)\n", New->rozmiar_x);
        // printf("New->rozmiar_y: %d (load)\n", New->rozmiar_y);
        New->plansza = (int**) calloc(New->rozmiar_y, sizeof(int*));
        for(i=0;i<New->rozmiar_y;i++){
            New->plansza[i] = (int*) calloc(New->rozmiar_x, sizeof(int));
            // printf("i: %d\n", i);
            for(j=0;j<New->rozmiar_x;j++){
                fscanf(fin, "%3d", &New->plansza[i][j]);
                // printf("j: %d, ", j);
            }
            // printf("\n");
        }
        New->kierunek = (char*) malloc(sizeof(char) * strlen((M->kierunek) + 1));
        strcpy(New->kierunek, M->kierunek);
        New->x = M->x + New->delta_x;
        New->y = M->y + New->delta_y;
        free_map(M);
        fclose(fin);
        return New;
    }
    else
    {
        printf("Error: can't find the .txt file\n");
    }    
}

void free_map(Map *M)
{
    for(int i = 0; i < M->rozmiar_y; i++)
        free(M->plansza[i]);
    free(M->plansza);
    free(M->kierunek);
    free(M);
}

void free_area(Area *F)
{
    free(F->type);
    free(F->dir);
    free(F);
}