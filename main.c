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

    casee plateau[13][13];
    tuile tuile1;
    tuile1.type = 1;
    tuile1.carte = 3;
    pion pion1;
    pion1.equipe = 0;
    pion1.nom = 'A';
    pion1.numero=3;
    casee case1;
    case1.pions[0] = pion1;
    case1.tuile = tuile1;
    case1.terre_ferme = 1;
    plateau[0][0] = case1;
    afficher_casee(0, 0, case1);




    return 0;
}
