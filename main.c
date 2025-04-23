#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "affichage.h"
#include "donnee.h"
#include "plateau.h"
int main()
{

    SetConsoleOutputCP(CP_UTF8);
    system("cls");
    plein_ecran();
    for (int i =0; i<=3; i++) {
        printf("%d\n", i);
    }
    bateau bateau;
    bateau.equipe_leader= -1;
    bateau.pions[0].equipe=0;
    bateau.pions[1].equipe=0;
    bateau.pions[2].equipe=0;
    int leader = determiner_leader(bateau);
    printf("\n\n%d",leader);
    //contour(10, 10, 10, 10);
    getchar();
    return 0;
}
