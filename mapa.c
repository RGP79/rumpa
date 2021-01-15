//nie powinien zawierać includów!!!
//3:30
//obsługa przechowywania mapy
//struktura (?)
//alokacja pamieci dla mapy (dwuwymiarowa tablica)
//zwalnianie pamieci po mapie
//wypisywanie mapy do pliku
//wypisywanie mapy z pliku do interfejsu

typedef struct _Mapa
{
    int x;
    int y;
    int deltax;
    int deltay;
    char kierunek;
    char ** mapa;
} Mapa;


int offset (Mapa) 
{
    //funkcja przerabia koordynaty z serwera na koordynaty lokalnej mapy programu C
}
// stworzyc funkcje ktora w przypadku wykroczenia odkurzacza poza lokalna mape, dorobi nowe pola i zaktualizuje funkcje offset

// Na swojej mapie zaczynamy zawsze na środku mapy (20:00)