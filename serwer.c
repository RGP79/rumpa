#include "serwer.h"

static size_t write_callback(void *data, size_t size, size_t nmemb, void *userp)
{
    /* to jest rzeczywista liczba bajtów przekazanych przez curl */
    size_t realsize = size * nmemb;

    /* jawnie konwertujemy (void*) na naszą strukturę, bo wiemy, że będziemy ją tutaj otrzymywać */
    Memory *mem = (Memory *) userp;

    char *ptr = NULL;

    /* Sprawdzamy czy pierwszy raz wywołujemy funkcję i trzeba zaalokować pamięć po raz pierwszy,
    czy trzeba zrobić reallokację (która kopiuje automatycznie starą zawartość w nowe miejsce) */
    if (mem->response != NULL)
        ptr = realloc(mem->response, mem->size + realsize);
    else
        ptr = malloc(mem->size + realsize);

    if (ptr == NULL)
        return 0; /* brak pamięci! */

    /* teraz zapamiętujemy nowy wskaźnik i doklejamy na końcu dane przekazane przez curl w 
       obszarze pamięci wskazywanym przez data */
    mem->response = ptr;
    memcpy(&(mem->response[mem->size]), data, realsize);
    mem->size += realsize;
    mem->response[mem->size] = 0; // to na końcu dodajemy bo to w końcu string, i zawsze powinien się skończyć!

    return realsize;
}

char *make_request(char *url, int a){
    CURL *curl;
    CURLcode res;
    Memory chunk;
    chunk.size = 0;
    chunk.response = NULL;
    //printf("debug1\n");

    curl = curl_easy_init();
    //printf("debug2\n");
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        //curl_easy_setopt(curl, CURLOPT_HEADER, 1L);

        /* to jest funkcja 'callback', która będzie wywołana przez curl gdy odczyta on kawałek danych
       ta funkcja musi mieć wywołanie zgodne z wymaganiami, które możesz sprawdzić tutaj:
       https://curl.se/libcurl/c/CURLOPT_WRITEFUNCTION.html */
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

        /* to jest adress struktury, który będzie przekazywany do naszej funkcji 'callback',
       do tej struktury nasz funkcja 'callback' będzie dopisywać wynik */
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk); //printf("debug6\n");

        /* Wykonaj zapytanie 'synchronicznie', to znaczy następna linijka kodu nie wykona się
       dopóki nie nadejdzie odpowiedź z serwera. */
        res = curl_easy_perform(curl); //printf("debug7\n");

        /* Sprawdzamy czy wystapił jakis błąd? */
        if (res != CURLE_OK){
            fprintf(stderr, "Error! curl_easy_perform() failure: %s\n", curl_easy_strerror(res));
        }
        else if(a==1)
        {
            printf("chunk response: %s", chunk.response);
        }

        /* zawsze po sobie sprzątaj */
        curl_easy_cleanup(curl);
 
    }
    return chunk.response;
}

// char * make_request(char *url)
// {
//     CURL *curl;
//     CURLcode res;
//     Memory chunk;
//     chunk.size = 0;
//     chunk.response = NULL;

//     curl = curl_easy_init();
//     if (curl)
//     {
//         curl_easy_setopt(curl, CURLOPT_URL, url);
//         curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
//         curl_easy_setopt(curl, CURLOPT_HEADER, 1L);

//         /* to jest funkcja 'callback', która będzie wywołana przez curl gdy odczyta on kawałek danych
//        ta funkcja musi mieć wywołanie zgodne z wymaganiami, które możesz sprawdzić tutaj:
//        https://curl.se/libcurl/c/CURLOPT_WRITEFUNCTION.html */
//         curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

//         /* to jest adress struktury, który będzie przekazywany do naszej funkcji 'callback',
//        do tej struktury nasz funkcja 'callback' będzie dopisywać wynik */
//         curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

//         /* Wykonaj zapytanie 'synchronicznie', to znaczy następna linijka kodu nie wykona się
//        dopóki nie nadejdzie odpowiedź z serwera. */
//         res = curl_easy_perform(curl);

//         /* Sprawdzamy czy wystapił jakis błąd? */
//         if (res != CURLE_OK)
//             fprintf(stderr, "Błąd! curl_easy_perform() niepowodzenie: %s\n", curl_easy_strerror(res));
//         else
//         {
//             printf("%s", chunk.response);
//         }

//         /* zawsze po sobie sprzątaj */
//         free(chunk.response);
//         curl_easy_cleanup(curl);
//     }
// }