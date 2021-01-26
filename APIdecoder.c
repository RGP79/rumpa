#include "APIdecoder.h"
#include "serwer.h"

char *info(char *token, int a)
{
    char url[255]; 
    char *url1="http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/info/";
    char *response;
    strcpy(url,url1);
    strncat(url,token,500);
    response=make_request(url, a);
    return response;
}

char *move(char *token)
{
    char url[255]; 
    char *url1="http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/move/";
    char *response;
    strcpy(url,url1);
    strncat(url,token,500);
    //printf("%s\n",url);
    response=make_request(url, 0);
    return response;
}

char *rotate(char *token, char *direction)
{
    char url[255]; 
    char *url1="http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/rotate/";
    char *response;
    strcpy(url,url1);
    strncat(url,token,9);
    strncat(url, "/", 10);
    strncat(url,direction,500);
    //printf("%s\n",url);
    response=make_request(url, 0);
    return response;
}

char *rotatel(char *token, char *direction)
{
    char url[255]; 
    char *url1="http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/rotate/";
    char *response;
    strcpy(url,url1);
    strncat(url,token,9);
    strncat(url, "/", 10);
    strncat(url,direction,500);
    //printf("%s\n",url);
    response=make_request(url, 0);
    return response;
}

char *explore(char *token){
    char url[255]; 
    char *url1="http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/explore/";
    char *response;
    strcpy(url,url1);
    strncat(url,token,500);
    //printf("%s\n",url);
    response=make_request(url, 0);
    return response;
}

char *reset(char *token){
    char url[255]; 
    char *url1="http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/reset/";
    char *response;
    strcpy(url, url1);
    strncat(url,token,500);
    //printf("%s\n",url);    
    response=make_request(url, 0);
    return response;
}

Area *DJson_info(char *response)
{
    Area *a;
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
    }
    else
    {
        payload = cJSON_GetObjectItemCaseSensitive(response_json, "payload");
        //cJSON_ArrayForEach(field, payload)
        {
            cJSON *current_x = cJSON_GetObjectItemCaseSensitive(payload, "current_x");
            cJSON *current_y = cJSON_GetObjectItemCaseSensitive(payload, "current_y");
            cJSON *field_type = cJSON_GetObjectItemCaseSensitive(payload, "field_type");
            cJSON *direction = cJSON_GetObjectItemCaseSensitive(payload, "direction");

            a = malloc(sizeof(Area) +1);
            a->x=current_x->valueint;        
            a->y=current_y->valueint;
            a->type = (char*) malloc(sizeof(char) * strlen((field_type->valuestring) + 1));
            strcpy(a->type, field_type->valuestring);
            a->dir = (char*) malloc(sizeof(char) * strlen((direction->valuestring) + 1));
            strcpy(a->dir, direction->valuestring);
        }
    }

    cJSON_Delete(response_json);
    return a;
}

Area3 *DJson_explore(char *response)
{
    Area3 *a = NULL;
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
    }
    else
    {
        status = cJSON_GetObjectItemCaseSensitive(response_json, "status");
        payload = cJSON_GetObjectItemCaseSensitive(response_json, "payload");
        list = cJSON_GetObjectItemCaseSensitive(payload, "list");
        a = malloc(sizeof(Area3));
        cJSON_ArrayForEach(field, list)
        {
            cJSON *x = cJSON_GetObjectItemCaseSensitive(field, "x");
            cJSON *y = cJSON_GetObjectItemCaseSensitive(field, "y");
            cJSON *type = cJSON_GetObjectItemCaseSensitive(field, "type");

            if (!cJSON_IsNumber(x) || !cJSON_IsNumber(y))
            {
                cJSON_Delete(response_json);
                return a;
            }
            else
            {
                a->x[i]=x->valueint;
                a->y[i]=y->valueint;
                a->type[i] = (char*) malloc(sizeof(char) * strlen((type->valuestring) + 1));
                strcpy(a->type[i], type->valuestring);
                i++;
            }
        }
    }
    cJSON_Delete(response_json);
    return a;
}