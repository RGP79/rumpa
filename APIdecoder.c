//4:30
//przetwarzanie zwróconej przez serwer odpowiedzi API
//input to string (responce)
//przetwarzanie pliku tekstowego za pomocą biblioteki cJSON
//output danych w postaci stucta (koordynaty i typ, kierunek, położenie)

#include "APIdecoder.h"
#include "serwer.h"

char *info(char *token)
{
    char *url; 
    char *url1="http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/info/";
    char *response;
    url = (char*) malloc((sizeof(char) * strlen(url1)) + (sizeof(char) *strlen((token) + 1)));
    strcpy(url,url1);
    strncat(url,token,9);
    printf("%s\n",url);
    printf("Informacje świata %s:\n\n",token);
    response=make_request(url);
    free(url);
    return response;
}

char *move(char *token)
{
    char *url; 
    char *url1="http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/move/";
    char *response;
    url = (char*) malloc((sizeof(char) * strlen(url1) + 10) + (sizeof(char) *strlen((token) + 1)));
    strcpy(url,url1);
    strncat(url,token,9);
    printf("%s\n",url);
    printf("Wykonuję ruch.\n\n");
    response=make_request(url);
    free(url);
    return response;
}

char *rotate(char *token, char *direction)
{
    char *url; 
    char *url1="http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/rotate/";
    char *response;
    url = (char*) malloc((sizeof(char) * strlen(url1) + 20) + (sizeof(char) * strlen((token) + 1)) + (sizeof(char) * strlen((direction) + 1)));
    strcpy(url,url1);
    strncat(url,token,9);
    strncat(url, "/", 1);
    strncat(url,direction,5);
    printf("%s\n",url);
    // if(strcmp(direction, "left")==0)
    //     printf("Obracam w lewo.\n\n");
    if(strcmp(direction, "right")==0)
        printf("Obracam się w prawo.\n\n");
    response=make_request(url);
    free(url);
    return response;
}

char *rotatel(char *token, char *direction)
{
    char *url; 
    char *url1="http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/rotate/";
    char *response;
    url = (char*) malloc((sizeof(char) * strlen(url1) + 10) + (sizeof(char) * strlen((token) + 1)) + (sizeof(char) * strlen((direction) + 10)));
    strcpy(url,url1);
    strncat(url,token,9);
    strncat(url, "/", 1);
    strncat(url,direction,4);
    printf("%s\n",url);
    if(strcmp(direction, "left")==0)
        printf("Obracam się w lewo.\n\n");
    // if(strcmp(direction, "right")==0)
    //     printf("Obracam w prawo.\n\n");
    response=make_request(url);
    free(url);
    return response;
}

char *explore(char *token){
    char *url; 
    char *url1="http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/explore/";
    char *response;
    url = (char*) malloc((sizeof(char) * strlen(url1)+10) + (sizeof(char) *strlen((token) + 1)));
    strcpy(url,url1);
    strncat(url,token,9);
    printf("%s\n",url);
    printf("Odkrywam.\n\n");
    response=make_request(url);
    free(url);
    return response;
}

char *reset(char *token){
    char *url; 
    char *url1="http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/reset/";
    char *response;
    url = (char*) malloc((sizeof(char) * strlen(url1)) + (sizeof(char) *strlen((token) + 1)));
    strcpy(url,url1);
    strncat(url,token,9);
    printf("%s\n",url);
    printf("Resetuję świat: %s\n\n",token);
    response=make_request(url);
    free(url);
    return response;
}

obszar *DJson_mov(char *response)
{
    obszar *a;
    const cJSON *status = NULL;
    const cJSON *payload = NULL;
    cJSON *response_json = cJSON_Parse(response);
    if (response_json == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        goto end;
    }
    payload = cJSON_GetObjectItemCaseSensitive(response_json, "payload");
    //cJSON_ArrayForEach(field, payload)
    {
        cJSON *current_x = cJSON_GetObjectItemCaseSensitive(payload, "current_x");
        cJSON *current_y = cJSON_GetObjectItemCaseSensitive(payload, "current_y");
        cJSON *field_type = cJSON_GetObjectItemCaseSensitive(payload, "field_type");
        cJSON *direction = cJSON_GetObjectItemCaseSensitive(payload, "direction");

        /*if (!cJSON_IsNumber(current_x) || !cJSON_IsNumber(current_y))
        {
            goto end;
        }*/

        a = malloc(sizeof(obszar));
        a->x=current_x->valueint;        
        a->y=current_y->valueint;
        a->type = (char*) malloc(sizeof(char) * strlen((field_type->valuestring) + 1));
        strcpy(a->type, field_type->valuestring);
        a->dir = (char*) malloc(sizeof(char) * strlen((direction->valuestring) + 1));
        strcpy(a->dir, direction->valuestring);
    }

end:
    cJSON_Delete(response_json);
    return a;
}

obszar3 *DJson_explore(char *response)
{
    obszar3 *a = NULL;
    int i=0;
    const cJSON *status = NULL;
    const cJSON *payload = NULL;
    const cJSON *list = NULL;
    const cJSON *field = NULL;
    cJSON *response_json = cJSON_Parse(response);
    if (response_json == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        goto end;
    }

    status = cJSON_GetObjectItemCaseSensitive(response_json, "status");
    payload = cJSON_GetObjectItemCaseSensitive(response_json, "payload");
    list = cJSON_GetObjectItemCaseSensitive(payload, "list");
    a = malloc(sizeof(obszar3));
    cJSON_ArrayForEach(field, list)
    {
        cJSON *x = cJSON_GetObjectItemCaseSensitive(field, "x");
        cJSON *y = cJSON_GetObjectItemCaseSensitive(field, "y");
        cJSON *type = cJSON_GetObjectItemCaseSensitive(field, "type");

        if (!cJSON_IsNumber(x) || !cJSON_IsNumber(y))
        {
            goto end;
        }

        a->x[i]=x->valueint;
        a->y[i]=y->valueint;
        a->type[i] = (char*) malloc(sizeof(char) * strlen((type->valuestring) + 1));
        strcpy(a->type[i], type->valuestring);
        i++;
    }

end:
    cJSON_Delete(response_json);
    return a;
}
/*
struct resp_move * interpret_move(char * responses)
{
    //interpretacja z JSONem
    resp_move *r = malloc(sizeof(resp_move));
    r->x=cJSON.get/*wartosci*
}
*/