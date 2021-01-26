//przetwarzanie merytoryczne structa a API decoder
//układ sterowania i podejmowania decyzji

//eksploracja 44:00
//odpowiednia ilosc skretow oznacza wewnetrzna lub zewnetrznaotoczke

#include "APIdecoder.h"
#include "logic.h"
#include "mapa.h"
#define RANDOMNUMBER 160

int getStartX(char *token)
{
    Area *field = DJson_info(info(token, 0));
    int start_x = field->x;

    return start_x;
}

int getStartY(char *token)
{
    Area *field = DJson_info(info(token, 0));
    int start_y = field->y;

    return start_y;
}

void moveToHit(char *token)
{
 
    Area *field = DJson_info(info(token, 0));
    int bufor_x = RANDOMNUMBER;
    int bufor_y = RANDOMNUMBER; 
    int i = 0;
    for(field->x = getStartX(token), field->y = getStartY(token); field->x != bufor_x || field->y != bufor_y; field = DJson_info(info(token, 0)))
    {
        bufor_x = getStartX(token);
        bufor_y = getStartY(token);
 
        explore(token);
        move(token);
    }
}


void rotL_Move(char *token)
{
    rotatel(token, "left");
        explore(token);
    move(token);
        explore(token);
        //Area *field = DJson_info(info(token));
}

void rotR_Move(char *token)
{
    rotate(token, "right");
        explore(token);
        //printf("testrotrmove\n");     
    move(token);
    //printf("testrotrmove\n");
        //explore(token);
        //Area *field = DJson_info(info(token));
}

// void rundkiL(char *token)
// {
//     Area *field = DJson_info(info(token));
//     int bufor_x = RANDOMNUMBER;
//     int bufor_y = RANDOMNUMBER;

//     while(bufor_x != field->x || bufor_y != field->y)
//     {
//         bufor_x = field->x;
//         bufor_y = field->x;
//         printf("bufor_x = field->x = %d\n", bufor_x);
//         printf("bufor_y = field->y = %d\n", bufor_y);

//         rotL_Move(token);
//         Area *field = DJson_info(info(token));
//         printf("field->x po rotL_move = %d\n", field->x);
//         printf("field->y po rotL_move = %d\n", field->y);
//         while(bufor_x == field->x || bufor_y == field->y)
//         {
//             rotR_Move(token);
//             Area *field = DJson_info(info(token));
//             printf("field->x po rotR_move = %d\n", field->x);
//             printf("field->x po rotR_move = %d\n", field->x);
//         }
//     }
// }

void rundkiL(char *token)
{
    Area *field = DJson_info(info(token, 0));

    int bufor_x;
    int bufor_y;
    int start_x;
    int start_y;
    start_x=getStartX(token);
    start_y=getStartY(token);
    printf("start_x =%d\n", start_x);
    printf("start_y =%d\n", start_y);

    rundki:    
    bufor_x = field->x;
    bufor_y = field->y;
    printf("bufor_x = %d\n", bufor_x);
    printf("bufor_y = %d\n", bufor_y);
    free(field);

    rotL_Move(token);
    field = DJson_info(info(token, 0));
    printf("field->x po rotL_Move = %d\n", field->x);
    printf("field->y po rotL_Move = %d\n", field->y);
    if(bufor_x == field->x && bufor_y == field->y)
    {
        rotR:
        rotR_Move(token);
        //printf("jestem po rotrmove\n");        
    }
    field = DJson_info(info(token, 0));
    printf("field->x po rotR_Move = %d\n", field->x);
    printf("field->y po rotR_Move = %d\n", field->y);
    
    if(bufor_x != field->x || bufor_y != field->y)
    {
        goto rundki;
    }
    else
    {
        goto rotR;
    }
    

}

void rundkiR(char *token)
{
    Area *field = DJson_info(info(token, 0));
    int bufor_x = RANDOMNUMBER;
    int bufor_y = RANDOMNUMBER;
    int start_x = field->x;
    int start_y = field->y;

    while(bufor_x != field->x || bufor_y != field->y)
    {
        bufor_x = field->x;
        bufor_y = field->x;

        rotR_Move(token);
        while(bufor_x = field->x)
        {
            while(bufor_y = field->y)
            {
                rotL_Move(token);
            }

        }
    }
}