#include "mapa.h"
//wypisywać kierunek czołgu i położenie w interfejsie
Mapa * nowa(obszar *F){
    int i, j;
    Mapa *M;
    M = (Mapa*) malloc(sizeof(Mapa));
    M->rozmiar_x = N;
    M->rozmiar_y = N;
    M->delta_x = 1;
    M->delta_y = 1;
    M->x = F->x + M->delta_x;
    M->y = F->y + M->delta_y;
    M->kierunek = (char*) malloc(sizeof(char) * strlen((F->dir)));
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
    free(F->type);
    free(F->dir);
    free(F);
    return M;
}

Mapa * nowa_reset(obszar *F){
    int i, j;
    Mapa *M;
    M = (Mapa*) malloc(sizeof(Mapa));
    M->rozmiar_x = N;
    M->rozmiar_y = N;
    M->delta_x = 1;
    M->delta_y = 1;
    M->x = F->x + M->delta_x;
    M->y = F->y + M->delta_y;
    M->kierunek = (char*) malloc(sizeof(char) * strlen((F->dir)));
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

Mapa * tank_rot(Mapa *M, obszar *F)
{
    Mapa *New = M;
    // New->kierunek = (char*) malloc(sizeof(char) * strlen((F->dir)));
    // strcpy(New->kierunek, F->dir);
    New->kierunek = F->dir;
    // free(M->kierunek);
    return New;
}

Mapa * tank_move(Mapa *M, obszar *F)
{   
    Mapa *New = M;
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

Mapa * tank_reset(Mapa *M, obszar *F)
{   
    Mapa *New = M;
    if(strcmp(F->type, "grass")==0)
        New->plansza[New->y][New->x]='G';
    if(strcmp(F->type, "sand")==0)
        New->plansza[New->y][New->x]='S';
    if(strcmp(F->type, "wall")==0)
        New->plansza[New->y][New->x]='W';
    return New;
}

Mapa * tank_exp(Mapa *M, obszar3 *Fe)
{    
    for (int i = 0; i<3; i++){
        if(strcmp(Fe->type[i], "grass")==0)
        M->plansza[M->delta_y + Fe->y[i]][M->delta_x + Fe->x[i]]='G';
        if(strcmp(Fe->type[i], "sand")==0)
        M->plansza[M->delta_y + Fe->y[i]][M->delta_x + Fe->x[i]]='S';
        if(strcmp(Fe->type[i], "wall")==0)
        M->plansza[M->delta_y + Fe->y[i]][M->delta_x + Fe->x[i]]='W';
    }
    return M;
}

void wyp_inf_Map_exp(obszar3 *Fe)
{
    printf("x 1: %d\n",Fe->x[0]);
    printf("y 1: %d\n",Fe->y[0]);
    printf("Type of field 1: %s\n",Fe->type[0]);
    printf("x 2: %d\n",Fe->x[1]);
    printf("y 2: %d\n",Fe->y[1]);
    printf("Type of field 2: %s\n",Fe->type[1]);
    printf("x 3: %d\n",Fe->x[2]);
    printf("y 3: %d\n",Fe->y[2]);
    printf("Type of field 3: %s\n",Fe->type[2]);
}

void wypisz_info_Mapa(Mapa *M, obszar *F)
{
    // printf("M->rozmiar_x: %d\n", M->rozmiar_x);
    // printf("M->rozmiar_y: %d\n", M->rozmiar_y);
    printf("Direction: %s\n",M->kierunek);
    printf("x: %d\n",M->x);
    printf("y: %d\n",M->y);
    printf("Field type: %s\n",F->type);
}

int check_border(Mapa *M)
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

Mapa * dopisz(Mapa *M)
{    
    Mapa *Nowa;  
    if(strcmp(M->kierunek, "N")==0)      {Nowa=dopisz_N(M);}
    else if(strcmp(M->kierunek, "E")==0) {Nowa=dopisz_E(M);}
    else if(strcmp(M->kierunek, "S")==0) {Nowa=dopisz_S(M);}
    else if(strcmp(M->kierunek, "W")==0) {Nowa=dopisz_W(M);}
    else
    {
        printf("błąd funkcji dopisz.\n");
    }
    return Nowa;    
}

Mapa * dopisz_N(Mapa *M)
{    
    int i, j;
    Mapa *New;    
    New = (Mapa*) malloc(sizeof(Mapa));    
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
    New->kierunek = (char*) malloc(sizeof(char) * strlen((M->kierunek)));
    strcpy(New->kierunek, M->kierunek);
    zwolnij_mape(M);
    return New;
}

Mapa * dopisz_E(Mapa *M)
{   
    int i, j;
    Mapa *New;    
    New = (Mapa*) malloc(sizeof(Mapa));    
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
    New->kierunek = (char*) malloc(sizeof(char) * strlen((M->kierunek)));
    strcpy(New->kierunek, M->kierunek);
    zwolnij_mape(M);
    return New;
}
Mapa * dopisz_S(Mapa *M)
{
    int i, j;
    Mapa *New;    
    New = (Mapa*) malloc(sizeof(Mapa));    
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
                New->plansza[i][j] = M->plansza[i][j];
            }            
        }        
    }
    New->delta_x = M->delta_x;
    New->delta_y = M->delta_y + M->rozmiar_y;
    New->x = M->x;
    New->y = M->y + New->delta_y;
    New->kierunek = (char*) malloc(sizeof(char) * strlen((M->kierunek)));
    strcpy(New->kierunek, M->kierunek);
    zwolnij_mape(M);
    return New;
}

Mapa * dopisz_W(Mapa *M)
{    
    int i, j;
    Mapa *New;    
    New = (Mapa*) malloc(sizeof(Mapa));    
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
                New->plansza[i][j] = M->plansza[i][j];
            }
        }
    }
    New->delta_x = M->delta_x + M->rozmiar_x;
    New->delta_y = M->delta_y;
    New->x = M->x + New->delta_x;
    New->y = M->y;
    New->kierunek = (char*) malloc(sizeof(char) * strlen((M->kierunek)));
    strcpy(New->kierunek, M->kierunek);
    zwolnij_mape(M);
    return New;
}

void wypisz(Mapa *M){
    int i, j, a;
    // if(M->rozmiar_y <11)
    //     printf(" ");
    // else
    //     printf("  ");
    
    for(i=0;i<M->rozmiar_x;i++)
        printf("+ - ");
    printf("+\n");

    for(i=0;i<M->rozmiar_y;i++){
    //     if(M->rozmiar_y<11)
    //         printf("%d", (M->rozmiar_y - 1 - i));
    //     else
    //         printf("%d ", (M->rozmiar_y - 1 - i));

        for(j=0;j<M->rozmiar_x;j++){
            printf("| ");
            printf("%c ", M->plansza[M->rozmiar_y - 1 - i][j]);
        }
        printf("|%d", (M->rozmiar_y - 1 - i));
        printf("\n");

        // if(M->rozmiar_y <11)
        //     printf(" ");
        // else
        //     printf("  ");
        for(a=0;a<M->rozmiar_x;a++)
            printf("+ - ");
        printf("+");
        printf("\n");        
    }
    for(i=0;i<M->rozmiar_x; i++)
        printf("%3d ", i);
    printf("\n");
}

void *zapisz(Mapa *M){
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

Mapa *wczytaj(Mapa *M){

    Mapa *New;
    New = (Mapa*) malloc(sizeof(Mapa));
    FILE *fin = fopen("board.txt", "r");
    if(fin != NULL){
        int i, j;
        fscanf(fin, "%d", &New->rozmiar_x);
        fscanf(fin, "%d", &New->rozmiar_y);
        fscanf(fin, "%d", &New->delta_x);
        fscanf(fin, "%d", &New->delta_y);
        // printf("New->rozmiar_x: %d (wczytaj)\n", New->rozmiar_x);
        // printf("New->rozmiar_y: %d (wczytaj)\n", New->rozmiar_y);
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
        New->kierunek = (char*) malloc(sizeof(char) * strlen((M->kierunek)));
        strcpy(New->kierunek, M->kierunek);
        New->x = M->x;
        New->y = M->y;
        zwolnij_mape(M);
        fclose(fin);
        return New;
    }
    else
    {
        printf("Błąd: nie można odnaleźć pliku .txt\n");
    }    
}

void zwolnij_mape(Mapa *M)
{       
    for(int i = 0; i < M->rozmiar_y; i++)
        free(M->plansza[i]);
    free(M->plansza);
    free(M->kierunek);
    free(M);
}