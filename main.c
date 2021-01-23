#include "serwer.h"
#include "APIdecoder.h"
#include "mapa.h"

int main(int argc, char **argv)
{    
    char *url;
    char *token;
    char *response;
    char *response1;
    char *mov="M";
    char *rotL="Rleft";
    char *rotR="Rright";
    char *exp="E";
    char *res="reset";    
    token=argv[1];
    int i,j;
    response1 = info(token);
    obszar *F = DJson_info(response1);
    free(response1);
    Mapa *M = nowa(F);
    free(F->type);
    free(F->dir);
    free(F);

    if(argc<3)
    {
        response=wypisz_info(token);
    }
    else
    {
        int i;
        for(i=2;i<argc;i++)
        {
            if(strcmp(argv[i],mov)==0)
            {
                wczytaj(M);
                response=move(token);
                obszar *field = DJson_info(response);
                free(response);
                M->x = field->x + M->delta_x;
                M->y = field->y + M->delta_y;
                M->kierunek = (char*) malloc(sizeof(char) * strlen((field->dir) + 1));
                strcpy(M->kierunek, field->dir);
                printf("M->rozmiar_x: %d\n", M->rozmiar_x);
                printf("M->rozmiar_y: %d\n", M->rozmiar_y);
                printf("kierunek: %s\n",M->kierunek);
                printf("x: %d\n",M->x);
                printf("y: %d\n",M->y);
                printf("Typ pola: %s\n",field->type);
                if(strcmp(field->type, "grass")==0)
                    M->plansza[M->y][M->x]='G';
                    printf("alamakota\n");
                if(strcmp(field->type, "sand")==0)
                    M->plansza[M->y][M->x]='S';
                if(strcmp(field->type, "wall")==0)
                    M->plansza[M->y][M->x]='W';
                zapisz(M);
                wypisz(M);
                free(field->type);
                free(field->dir);
                free(field);
            }
            else if(strcmp(argv[i],rotL)==0)
            {
                response=rotatel(token, "left");
                obszar *field = DJson_info(response);
                free(response);
                M->kierunek = (char*) malloc(sizeof(char) * strlen((field->dir) + 1));
                strcpy(M->kierunek, field->dir);
                free(field->type);
                free(field->dir);
                free(field);
            }
            else if(strcmp(argv[i],rotR)==0)
            {
                response=rotate(token, "right");
                obszar *field = DJson_info(response);
                free(response);
                M->kierunek = (char*) malloc(sizeof(char) * strlen((field->dir) + 1));
                strcpy(M->kierunek, field->dir);
                free(field->type);
                free(field->dir);
                free(field);
            }
            else if(strcmp(argv[i],exp)==0)
            {
                wczytaj(M);
                response=explore(token);
                obszar3 *fielde = DJson_explore(response);
                free(response);
                printf("x_0: %d\n",fielde->x[0]);
                printf("y_0: %d\n",fielde->y[0]);
                printf("Typ pola 0: %s\n",fielde->type[0]);
                printf("x_1: %d\n",fielde->x[1]);
                printf("y_1: %d\n",fielde->y[1]);
                printf("Typ pola 1: %s\n",fielde->type[1]);
                printf("x_2: %d\n",fielde->x[2]);
                printf("y_2: %d\n",fielde->y[2]);
                printf("Typ pola 2: %s\n",fielde->type[2]);
                for (int i = 0; i<3; i++){
                    if(strcmp(fielde->type[i], "grass")==0)
                    M->plansza[M->delta_y + fielde->y[i]][M->delta_x + fielde->x[i]]='G';
                    if(strcmp(fielde->type[i], "sand")==0)
                    M->plansza[M->delta_y + fielde->y[i]][M->delta_x + fielde->x[i]]='S';
                    if(strcmp(fielde->type[i], "wall")==0)
                    M->plansza[M->delta_y + fielde->y[i]][M->delta_x + fielde->x[i]]='W';
                }
                
                wypisz(M);
                zapisz(M);
                for(int i=0;i<3;i++)
                {
                free(fielde->type[i]);
                }
                free(fielde);                
            }
            else if(strcmp(argv[i],res)==0)
            {
                response=reset(token);
                obszar *field = DJson_info(response);
                free(response);
                M->x = field->x + M->delta_x;
                M->y = field->y + M->delta_y;
                M->kierunek = (char*) malloc(sizeof(char) * strlen((field->dir) + 1));
                strcpy(M->kierunek, field->dir);
                printf("kierunek: %s\n",M->kierunek);
                printf("x: %d\n",M->x);
                printf("y: %d\n",M->y);
                printf("Typ pola: %s\n",field->type);
                if(strcmp(field->type, "grass")==0)
                    M->plansza[M->y][M->x]='G';
                if(strcmp(field->type, "sand")==0)
                    M->plansza[M->y][M->x]='S';
                if(strcmp(field->type, "wall")==0)
                    M->plansza[M->y][M->x]='W';
                wypisz(M);
                zapisz(M);
                free(field->type);
                free(field->dir);
                free(field);
            }
            else
            {
                printf("\nBłąd: nieznana komenda!\n");
                exit(-1);
            }            
            if((check_border(M)) == 0){                 
                M = dopisz(M);        
                wypisz(M);                
                zapisz(M);               
            }
        }        
        zwolnij_mape(M);        
    }
    
    return 0;
}