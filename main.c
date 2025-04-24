#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "affichage.h"
#include "donnee.h"
#include "plateau.h"
int main()
{
    casee case1;
    SetConsoleOutputCP(CP_UTF8);
    plein_ecran();
    system("cls");
    contour(0, 0, 130, 40);
    gotoxy(1, 1);

    gotoxy(1, 1);
    for (int i =0; i<=12; i++) {
        rectangle(1, 1+(i*3), 6, 3, i%3+2);
    }

    casee Plateau[13][13];


    getchar();
    return 0;
}
