#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include "affichage.h"
#include "donnee.h"
#include "plateau.h"
#include "initialisation.h"

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    plein_ecran();
    curseur_visible(0);
    srand(time(NULL));
    initialiser_nulls();
    extern casee case_null;
    extern joueur joueur_null;
    extern int socle[13][13];
    casee Plateau[13][13];
    initialiser_plateau(Plateau, case_null);
    extern tuile deck_tuile[40];
    tuile tuiles[40];
    memcpy(tuiles, deck_tuile, sizeof(tuiles)); // Copie des 40 éléments de deck_tuile dans tuiles
    melanger_tuiles(tuiles);
    placer_tuiles(Plateau, tuiles, socle);
    placer_serpents(Plateau);
    for (int i = 0; i<13; i++) {
        for (int j = 0; j<13; j++) {
            afficher_casee(5*i, 3*j, Plateau[i][j]);
        }
    }
    int n_joueurs=0;
    joueur joueurs[4]; // Tout ca peut etre mis dans initilialisation comme ca change jamais
    for (int i = 0; i<4; i++) { //
        joueurs[i] = joueur_null; //
    } //
    initialiser_joueurs(joueurs, &n_joueurs);

    return 0;
}
