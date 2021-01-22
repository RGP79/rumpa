#include "mapa.h"


//3:30
//obsługa przechowywania mapy
//struktura (?)
//alokacja pamieci dla mapy (dwuwymiarowa tablica)
//zwalnianie pamieci po mapie
//wypisywanie mapy do pliku
//wypisywanie mapy z pliku do interfejsu



Mapa * nowa(Mapa *M){
    int i, j;
    M = (Mapa*) malloc(sizeof(Mapa));
    M->rozmiar_x = N;
    M->rozmiar_y = N;
    M->delta_x =1;
    M->delta_y =2;
    M->plansza = (char**) malloc(sizeof(char*) *M->rozmiar_y);
    for(i=0; i<M->rozmiar_y; i++)
    {
        M->plansza[i] = (char*) malloc(sizeof(char) * M->rozmiar_x);
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
    // printf("warunek E: %d = %d\n", (M->delta_x + M->x), (M->rozmiar_x - 1));
    // printf("warunek S: %d = %d\n", (M->rozmiar_y - M->delta_y - M->y), (M->rozmiar_y-1));
    // printf("warunek W: %d = %d\n", (M->delta_x + M->x), 0);
    if((M->rozmiar_y - M->delta_y - M->y) == 0 || (M->delta_x + M->x) == (M->rozmiar_x - 1) || (M->rozmiar_y - M->delta_y - M->y) == (M->rozmiar_y-1) || (M->delta_x + M->x) == (0)){
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
    Mapa *New = M;    
    New = (Mapa*) malloc(sizeof(Mapa));    
    New->rozmiar_x = M->rozmiar_x;
    New->rozmiar_y = M->rozmiar_y*2;  
    New->plansza = (char**) malloc(sizeof(char*) *New->rozmiar_y);
    printf("maniek\n");
    printf("M->rozmiar_y=%d\n", M->rozmiar_y);
    for(i=0; i<New->rozmiar_y; i++)
    {
        printf("i=%d\n", i);
        New->plansza[i] = (char*) malloc(sizeof(char) * New->rozmiar_x);
        
        for(j=0;j<New->rozmiar_x;j++)
        {
            printf("j=%d ", j);
            if(i < M->rozmiar_y){
                New->plansza[i][j]='*';
            }
            if(i >= M->rozmiar_y){
                New->plansza[i][j]=M->plansza[i][j];
            }
        }
        printf("\n");         
    }
    printf("żaden\n");
    New->delta_x = M->delta_x;
    New->delta_y = M->delta_y;
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
    New->plansza = (char**) malloc(sizeof(char*) *New->rozmiar_y);
    for(i=0; i<New->rozmiar_y; i++)
    {
        New->plansza[i] = (char*) malloc(sizeof(char) * New->rozmiar_x);
        for(j=0;j<New->rozmiar_x;j++)
        {                
            New->plansza[i][j]='*';
        }
        
    }
    New->delta_x = M->delta_x;
    New->delta_y = M->delta_y;
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
    New->plansza = (char**) malloc(sizeof(char*) *New->rozmiar_y);
    for(i=0; i<New->rozmiar_y; i++)
    {
        New->plansza[i] = (char*) malloc(sizeof(char) * New->rozmiar_x);
        for(j=0;j<New->rozmiar_x;j++)
        {
            New->plansza[i][j]='*';
        }
        
    }
    New->delta_x = M->delta_x;
    New->delta_y = M->delta_y + New->rozmiar_y - M->rozmiar_y;
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
    New->plansza = (char**) malloc(sizeof(char*) *New->rozmiar_y);
    for(i=0; i<New->rozmiar_y; i++)
    {
        New->plansza[i] = (char*) malloc(sizeof(char) * New->rozmiar_x);
        for(j=0;j<New->rozmiar_x;j++)
        {                
            New->plansza[i][j]='*';
        }
        
    }
    New->delta_x = M->delta_x + New->rozmiar_x - M->rozmiar_x;
    New->delta_y = M->delta_y;
    zwolnij_mape(M);
    return New;
}

Mapa * offset(Mapa *M)
{
    
}

void wypisz(Mapa *M){
    int i, j;
    for(i=0;i<M->rozmiar_y;i++){
        for(j=0;j<M->rozmiar_x;j++){
            
            printf("%2c", M->plansza[i][j]);
            
        }
        printf("\n");
    }
    printf("\n");

}

void *zapisz(Mapa *M){
    FILE *fout = fopen("plansza.txt", "w");
    int i, j;

    for(i=0;i<M->rozmiar_y;i++){
        for(j=0;j<M->rozmiar_x;j++){
            fprintf(fout, "%c", M->plansza[i][j]);
        }
        fprintf(fout, "\n");
    }
    fclose(fout);
}

void *wczytaj(Mapa *M){
    
    FILE *fin = fopen("plansza.txt", "r");
    if(fin != NULL){
        int i, j;
        char bufor[M->rozmiar_y+2];
        for(i=0;i<M->rozmiar_y;i++){
            fgets(bufor, M->rozmiar_y+2, fin);
            for(j=0;j<M->rozmiar_x;j++){
                M->plansza[i][j]=bufor[j];
            }
        }
    }
    fclose(fin);
}

// stworzyc funkcje ktora w przypadku wykroczenia odkurzacza poza lokalna mape, dorobi nowe pola i zaktualizuje funkcje offset

// Na swojej mapie zaczynamy zawsze na środku mapy (20:00)

void zwolnij_mape(Mapa *M)
{       
    for(int i = 0; i < M->rozmiar_y; i++)
        free(M->plansza[i]);
    free(M->plansza);    
    //free(M->kierunek); //zwalnianie tego wywala segmentasją    
    free(M);
}