#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
#include "affichage.h"
#include "donnee.h"
#include "plateau.h"
#include "initialisation.h"

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    plein_ecran();

    srand(time(NULL));
    initialiser_nulls();
    extern casee case_null;
    extern pion pion_null;
    extern int socle[13][13];
    casee Plateau[13][13];
    extern tuile deck_tuile[40];

    return 0;
}
