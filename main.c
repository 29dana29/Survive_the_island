#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "affichage.h"
#include "donnee.h"
#include "plateau.h"
int main()
{
    SetConsoleOutputCP(CP_UTF8);
    plein_ecran();
    system("cls");

    /*contour(0, 0, 130, 40);
    gotoxy(1, 1);

    gotoxy(1, 1);
    for (int i =0; i<=12; i++) {
        rectangle(1, 1+(i*3), 6, 3, i%3+2);
    }*/

    casee case1;
    case1.tuile.type = 0;
    case1.terre_ferme = 1;
    //afficher_casee(4, 4, case1);
    printf("%d", case1.pions[2].equipe);

    getchar();
    return 0;
}
