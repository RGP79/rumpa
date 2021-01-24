#include "serwer.h"
#include "APIdecoder.h"
#include "mapa.h"

int main(int argc, char **argv)
{    
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
                M = wczytaj(M);
                response=move(token);
                obszar *field = DJson_info(response);
                free(response);
                M = tank_move(M, field);
                wypisz_info_Mapa(M, field);
                zapisz(M);
                wypisz(M);
                free(field->type);
                free(field->dir);
                free(field);
            }
            else if(strcmp(argv[i],rotL)==0)
            {
                printf("Turning left\n");
                response=rotatel(token, "left");
                obszar *field = DJson_info(response);
                free(response);
                M = tank_rot(M, field);
                wypisz_info_Mapa(M, field);
                free(field->type);
                free(field->dir);
                free(field);
            }
            else if(strcmp(argv[i],rotR)==0)
            {
                printf("Turning right\n");
                response=rotate(token, "right");
                obszar *field = DJson_info(response);
                free(response);
                M = tank_rot(M, field);
                wypisz_info_Mapa(M, field);
                free(field->type);
                free(field->dir);
                free(field);
            }
            else if(strcmp(argv[i],exp)==0)
            {
                printf("Exlporing...\n\n");
                M = wczytaj(M);
                response=explore(token);
                obszar3 *fielde = DJson_explore(response);
                free(response);
                M = tank_exp(M, fielde);
                wyp_inf_Map_exp(fielde);
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
                printf("Reseting world: %s\n\n",token);
                response=reset(token);
                obszar *field = DJson_info(response);
                free(response);
                M = tank_move(M, field);
                wypisz_info_Mapa(M, field);
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
                //wypisz(M);                
                zapisz(M);               
            }
        }        
        zwolnij_mape(M);        
    }
    
    return 0;
}