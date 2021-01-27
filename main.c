#include "map.h"
#include "logic.h"
#include "picture.h"

int main(int argc, char **argv)
{
    char *token;
    char *response;
    char *mov="M";
    char *rotL="Rleft";
    char *rotR="Rright";
    char *exp="E";
    char *res="reset";
    char *bot="bot";
    int i,j;
    token=argv[1];

    if(argc<3)
    {
        response=info(token, 1);
        free(response);
    }
    else
    {
        int i;
        response = info(token, 0);
        Area *F = DJson_info(response, 0);
        free(response);
        Map *M = new_map(F);
        free_area(F);
        M = load(M);
        if(strcmp(argv[2],bot)!=0)
        {
            for(i=2;i<argc;i++)
            {
                if(strcmp(argv[i],mov)==0)
                {
                    printf("Moving forward.\n");
                    tank_move_whole(token, M, 1);
                }
                else if(strcmp(argv[i],rotL)==0)
                {
                    printf("Turning left\n");
                    tank_rot_whole(token, M, 1, 1);
                }
                else if(strcmp(argv[i],rotR)==0)
                {
                    printf("Turning right\n");
                    tank_rot_whole(token, M, 1, 2);
                }
                else if(strcmp(argv[i],exp)==0)
                {
                    printf("Exlporing...\n\n");
                    tank_exp_whole(token, M, 1);
                }
                else if(strcmp(argv[i],res)==0)
                {
                    printf("Reseting world: %s\n\n",token);
                    M = tank_res_whole(token, M, 1);
                }
                else
                {
                    printf("\nError: unknown command!\n");
                    exit(-1);
                }
                if((check_border(M)) == 0)
                {
                    M = render(M);
                }
            }
        }
        else if(strcmp(argv[2],bot)==0)
        {
            M = moveToHit(token, M);
            M = roundsL(token, M);

        }
        save(M);
        png_map(M);
        free_map(M);
    }
    
    return 0;
}