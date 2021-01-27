#include "logic.h"
#define RANDOMNUMBER 160

int getStartX(char *token)
{
    char *response;
    response = info(token, 0);
    Area *field = DJson_info(response, 0);
    free(response);
    int start_x = field->x;
    free_area(field);

    return start_x;
}

int getStartY(char *token)
{
    char *response;
    response = info(token, 0);
    Area *field = DJson_info(response, 0);
    free(response);
    int start_y = field->y;
    free_area(field);

    return start_y;
}

Map * moveToHit(char *token, Map *M)
{
    char *response;
    response = info(token, 0);
    Area *field = DJson_info(response, 0);
    free(response);
    int bufor_x = RANDOMNUMBER;
    int bufor_y = RANDOMNUMBER; 
    int i = 0;
    for(field->x = getStartX(token), field->y = getStartY(token); field->x != bufor_x || field->y != bufor_y; NULL)
    {
        bufor_x = getStartX(token);
        bufor_y = getStartY(token);

        tank_exp_whole(token, M, 0);

        tank_move_whole(token, M, 0);

        if((check_border(M)) == 0) //dopisywanie mapy
        {
            M = render(M);
        }                        //koniec
        free_area(field);
        char *response1;
        response1 = info(token, 0);
        field = DJson_info(response1, 0);
        free(response1);
    }
    free_area(field);
    return M;
}


Map * rotL_Move(char *token, Map *M)
{
    tank_rot_whole(token, M, 0, 1); //rotacja w lewo

        tank_exp_whole(token, M, 0);

    tank_move_whole(token, M, 0);
    if((check_border(M)) == 0) //dopisywanie mapy
    {
        M = render(M);
    }                        //koniec

        tank_exp_whole(token, M, 0);

    return M;
}

Map * rotR_Move(char *token, Map *M)
{
    tank_rot_whole(token, M, 0, 2); //rotacja w prawo

        tank_exp_whole(token, M, 0);

    tank_move_whole(token, M, 0);
    if((check_border(M)) == 0) //dopisywanie mapy
    {
        M = render(M);
    }                        //koniec

    return M;
}

Map * roundsL(char *token, Map *M)
{
    printf("przed for\n");
    char *response1;
    char *response;
    response1 = info(token, 0);
    Area *field = DJson_info(response1, 0);
    free(response1);
    int i = 0;

    int bufor_x = RANDOMNUMBER;
    int bufor_y = RANDOMNUMBER;
    int start_x = getStartX(token);
    int start_y = getStartY(token);
    int fx;
    int fy;

    for(field->x, field->y; field->x != bufor_x || field->y != bufor_y; NULL)
    {
        bufor_x = getStartX(token);
        bufor_y = getStartY(token);

        M = rotL_Move(token, M);

        free_area(field);
        response = info(token, 0);
        field = DJson_info(response, 0);
        free(response);
        
        for(bufor_x, field->x, bufor_y, field->y; bufor_x == field->x && bufor_y == field->y; NULL)
        {
            free_area(field);
            M = rotR_Move(token, M);
            response = info(token, 0);
            field = DJson_info(response, 0);
            free(response);
        }
        fx = field->x;
        fy = field->y;
        if(2 == fx + M->delta_x && 3 == fy + M->delta_y)
        {
            break;
        }
    }
    free_area(field);
    return M;
}