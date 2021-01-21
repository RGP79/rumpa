//unit tests
#include "mapa.h"

int main(int argc, char **argv)
{
    char *mov="M";
    char *rotL="Rleft";
    char *rotR="Rright";
    char *exp="E";
    char *res="reset";
    char *n = "north";
    Mapa *M;
    Mapa *M2;
    M=nowa(M);
    M2=dopisz_pole(M, M2, n);
    wypisz(M);
    wypisz(M2);
    

        //testowanie funkcji z pliku mapa.c
        //testowanie przypadków związanych z potrzebą realokowania
        //taki trochę debbuger obsługi mapy

        //przykładowy test:
        //utworzenie mapy (np. [5][5])
        //zapamietanie wartosci
        //testowanie funkcji offset

        //valgrind
}