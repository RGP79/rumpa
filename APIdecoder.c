//4:30
//przetwarzanie zwróconej przez serwer odpowiedzi API
//input to string (responce)
//przetwarzanie pliku tekstowego za pomocą biblioteki cJSON
//output danych w postaci stucta (koordynaty i typ, kierunek, położenie)


struct resp_move * interpret_move(char * responses)
{
    //interpretacja z JSONem
    resp_move *r = malloc(sizeof(resp_move));
    r->x=cJSON.get/*wartosci*/
}