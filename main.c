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
#include "cartes.h"
#include "tours.h"

int jeu = 1;
casee Plateau[13][13];

int montee_eaux = 0; // 0:On eneleve que la plage, 1:On enleve les forets, 2:On eneleve les montagnes
int main()
{
    SetConsoleOutputCP(CP_UTF8);
    curseur_visible(0);
    plein_ecran();
    extern int couleurs_equipe[4];
    srand(time(NULL));
    initialiser_nulls();
    extern casee case_null;
    extern int socle[13][13];
    initialiser_plateau(Plateau, case_null);
    extern tuile deck_tuile[40];
    tuile tuiles[40];
    memcpy(tuiles, deck_tuile, sizeof(tuiles)); // Copie des 40 elements de deck_tuile dans tuiles
    melanger_tuiles(tuiles);
    placer_tuiles(Plateau, tuiles, socle);
    placer_serpents(Plateau);

    /*Plateau[4][4].pions[0].equipe=0;
    Plateau[4][4].pions[0].numero=1;
    strcpy(Plateau[4][4].pions[0].nom, "A");
    Plateau[3][4].bateau.equipe_leader=-1;*/

    for (int i = 0; i<13; i++)
    {
        for (int j = 0; j<13; j++)
        {
            afficher_casee(5*i, 3*j, Plateau[i][j], 0);

        }
    }

    int n_joueurs=0;
    joueur joueurs[4];
    initialiser_joueurs(joueurs, &n_joueurs);
        char message[61];

    /*for (int i =0; i<15; i++) {
        sprintf(message, "Goat %d", i);
    nouveau_message(message, ROUGE); // Texte rouge sur fond noir
    }*/

    placer_pions(Plateau, joueurs, n_joueurs);
    placer_bateaux(Plateau, joueurs, n_joueurs);
    while (jeu==1)
    {
        for(int i = 0; i<n_joueurs; i++)
        {
            if (total_pion_couleur(Plateau, i)>0)
            {
                tour(&joueurs[i], Plateau);
            }
            else
            {
                jeu=0;
            }

        }
    }

    rectangle(0, 0, 135, 39, 3);
    for (int i = 0; i<n_joueurs; i++)
    {
        gotoxy(50, 20+i);
        set_color(couleurs_equipe[i], 3);
        printf("JOUEUR %d:  %d pts", i, joueurs[i].points);
    }
    get_input();

    return 0;
}
