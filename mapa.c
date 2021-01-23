#include "mapa.h"


//3:30
//obsługa przechowywania mapy
//struktura (?)
//alokacja pamieci dla mapy (dwuwymiarowa tablica)
//zwalnianie pamieci po mapie
//wypisywanie mapy do pliku
//wypisywanie mapy z pliku do interfejsu



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
    M->plansza = (int**) calloc(M->rozmiar_y, sizeof(int*));
    for(i=0; i<M->rozmiar_y; i++)
    {
        M->plansza[i] = (int*) calloc(M->rozmiar_x, sizeof(int));
        for(j=0;j<M->rozmiar_x;j++)
        {
            M->plansza[i][j]='*';
        }
    }
    return M;
}

int check_border(Mapa *M)
{
    // printf("warunek N: %d = %d\n", (M->rozmiar_y - M->delta_y - M->y), 0);
    // printf("warunek E: %d = %d\n", (M->delta_x + M->x), (M->rozmiar_x));
    // printf("warunek S: %d = %d\n", (M->rozmiar_y - M->delta_y - M->y), (M->rozmiar_y-1));
    // printf("warunek W: %d = %d\n", (M->delta_x + M->x), 0);
    if((M->rozmiar_y - M->delta_y - M->y) == 0 || (M->delta_x + M->x) == (M->rozmiar_x) || (M->rozmiar_y - M->delta_y - M->y) == (M->rozmiar_y-1) || (M->delta_x + M->x) == (0)){
        printf("zwracam 0\n");
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
                New->plansza[i][j]='*';
            }            
        }        
    }
    New->delta_x = M->delta_x;
    New->delta_y = M->delta_y;
    New->x = M->x;
    New->y = M->y;
    New->kierunek = (char*) malloc(sizeof(char) * strlen((M->kierunek) + 1));
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
                New->plansza[i][j]='*';
            }            
        }        
    }
    New->delta_x = M->delta_x;
    New->delta_y = M->delta_y;
    New->x = M->x;
    New->y = M->y;
    New->kierunek = (char*) malloc(sizeof(char) * strlen((M->kierunek) + 1));
    strcpy(New->kierunek, M->kierunek);
    zwolnij_mape(M);
    return New;
}
Mapa * dopisz_S(Mapa *M)
{

}

Mapa * dopisz_W(Mapa *M)
{    

}

Mapa * offset(Mapa *M)
{
    
}

void wypisz(Mapa *M){
    int i, j;
    for(i=0;i<M->rozmiar_y;i++){
        for(j=0;j<M->rozmiar_x;j++){
            
            printf("%2c", M->plansza[M->rozmiar_y - 1 - i][j]);
            
        }
        printf("\n");
    }
    printf("\n");
}

void *zapisz(Mapa *M){
    FILE *fout = fopen("board.txt", "w");
    int i, j;

    fprintf(fout, "%d\n", M->rozmiar_x);
    fprintf(fout, "%d\n", M->rozmiar_y);
    for(i=0;i<M->rozmiar_y;i++){
        for(j=0;j<M->rozmiar_x;j++){
            fprintf(fout, "%c", M->plansza[i][j]);
        }
        fprintf(fout, "\n");
    }
    fclose(fout);
}

void *wczytaj(Mapa *M){
    
    FILE *fin = fopen("board.txt", "r");
    if(fin != NULL){
        int i, j;
        fscanf(fin, "%d", &M->rozmiar_x);
        fscanf(fin, "%d", &M->rozmiar_y);
        for(i=0;i<M->rozmiar_y;i++){
            printf("i: %d\n", i);
            for(j=0;j<M->rozmiar_x;j++){
                fscanf(fin, "%d", &M->plansza[i][j]);
                printf("j: %d, ", j);
            }
            printf("\n");
        }
        wypisz(M);
    }
    else
    {
        printf("Błąd: nie można odnaleźć pliku .txt\n");
    }
    
    fclose(fin);
}

// stworzyc funkcje ktora w przypadku wykroczenia odkurzacza poza lokalna mape, dorobi nowe pola i zaktualizuje funkcje offset

void zwolnij_mape(Mapa *M)
{       
    for(int i = 0; i < M->rozmiar_y; i++)
        free(M->plansza[i]);
    free(M->plansza);
    free(M->kierunek);
    free(M);
}