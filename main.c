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
{SetConsoleOutputCP(CP_UTF8);
    plein_ecran();
    initialiser_nulls();
    extern casee case_null;
    extern pion pion_null;
    extern int socle[13][13];
    int n=0;
    for (int i=0; i<13; i++) {
        for (int j = 0; j<13; j++) {
            if (socle[i][j]==1) {
                n++;
                printf("%d %d\n", i+1, j+1);
            }
        }
    }
    printf("%d", n);
printf("\n\n\n\n");

    return 0;
}
