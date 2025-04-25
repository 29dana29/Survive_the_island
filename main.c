#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
#include "affichage.h"
#include "donnee.h"
#include "plateau.h"


int main()
{
    SetConsoleOutputCP(CP_UTF8);
    plein_ecran();
    system("cls");

    int c, i;
    i=0;
    while ((c = attendre_input()) != 13) { // input différent de Entrée
        switch (c) {
    case 72:
        i++;
        break;
    case 80:
        i--;
        break;
        }
        printf("%d\n", i);
    }




    return 0;
}
