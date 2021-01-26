#include "serwer.h"
#include "APIdecoder.h"
#include "mapa.h"
#include "logic.h"

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
    char *bot="bot";
    token=argv[1];
    int i,j;

    if(argc<3)
    {
        response=info(token);
    }
    else
    {
        int i;
        response1 = info(token);
        Area *F = DJson_info(response1);
        free(response1);
        Map *M = new_map(F);
        free_area(F);
        M = load(M);
        for(i=2;i<argc;i++)
        {
            if(strcmp(argv[i],mov)==0)
            {
                printf("Wykonuję ruch.\n");
                response=move(token);
                Area *field = DJson_info(response);
                free(response);
                M = tank_move(M, field);
                write_info_Map(M, field);
                write(M);
                free_area(field);
            }
            else if(strcmp(argv[i],rotL)==0)
            {
                printf("Turning left\n");
                response=rotatel(token, "left");
                Area *field = DJson_info(response);
                free(response);
                M = tank_rot(M, field);
                write_info_Map(M, field);
                write(M);
                free_area(field);
            }
            else if(strcmp(argv[i],rotR)==0)
            {
                printf("Turning right\n");
                response=rotate(token, "right");
                Area *field = DJson_info(response);
                free(response);
                M = tank_rot(M, field);
                write_info_Map(M, field);
                write(M);
                free_area(field);
            }
            else if(strcmp(argv[i],exp)==0)
            {
                printf("Exlporing...\n\n");
                response=explore(token);
                Area3 *fielde = DJson_explore(response);
                free(response);
                response1 = info(token);
                Area *F = DJson_info(response1);
                free(response1);                
                printf("x: %d\n",M->x);
                printf("y: %d\n",M->y);
                M = tank_exp(M, fielde, F);
                write_inf_Map_exp(fielde, M);
                write(M);
                printf("x: %d\n",M->x);
                printf("y: %d\n",M->y);
                for(int i=0;i<3;i++)
                {
                    free(fielde->type[i]);
                }
                free(fielde);
                free_area(F);
            }
            else if(strcmp(argv[i],res)==0)
            {
                free_map(M);
                printf("Reseting world: %s\n\n",token);
                response=reset(token);
                Area *field = DJson_info(response);
                free(response);
                M = new_map(field);
                printf("field->type: %s\n", field->type);
                M = tank_move(M, field);
                write_info_Map(M, field);
                write(M);
                free_area(field);
            }
            else if(strcmp(argv[i],bot)==0)
            {
                moveToHit(token);
                rundkiL(token);
            }
            else
            {
                printf("\nBłąd: nieznana komenda!\n");
                exit(-1);
            }
            if((check_border(M)) == 0){
                M = render(M);
            }
        }
        save(M);
        free_map(M);
    }
    
    return 0;
}