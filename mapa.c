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
    M->plansza = (char**) malloc(sizeof(char*) *N);
    for(i=0; i<N; i++)
    {
        M->plansza[i] = (char*) malloc(sizeof(char) * N);
        for(j=0;j<N;j++)
        {
            M->plansza[i][j]='*';
        }
    }
    return M;
}

void wypisz(Mapa *M){
    int i, j;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            
            printf("%2c", M->plansza[i][j]);
            
        }
        printf("\n");
    }

}



/*
Mapa *zapisz(Mapa *plansza, Mapa *rozmiar_x, Mapa *rozmiar_y){
    FILE *fout = fopen("plansza.txt", "w");
    int i, j;

    for(i=0;i<MAX_SIZE;i++){
        for(j=0;j<MAX_SIZE;j++){
            fprintf(fout, "%c", plansza[i][j]);
        }
        fprintf(fout, "\n");
    }
    fclose(fout);
}

void wczytaj(char plansza[MAX_SIZE][MAX_SIZE]){
    FILE *fin = fopen("plansza.txt", "r");
    if(fin != NULL){
        int i, j;
        char bufor[MAX_SIZE+2];
        for(i=0;i<MAX_SIZE;i++){
            fgets(bufor, MAX_SIZE+2, fin);
            for(j=0;j<MAX_SIZE;j++){
                plansza[i][j]=bufor[j];
            }
        }
    }
    fclose(fin);
}
*/
void *offset (Mapa M)
{
    //funkcja przerabia koordynaty z serwera na koordynaty lokalnej mapy programu C
}
// stworzyc funkcje ktora w przypadku wykroczenia odkurzacza poza lokalna mape, dorobi nowe pola i zaktualizuje funkcje offset

// Na swojej mapie zaczynamy zawsze na środku mapy (20:00)
