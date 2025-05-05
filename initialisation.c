#include "initialisation.h"
#include "donnee.h"
#include <stdlib.h>
#include "affichage.h"
#include <stdio.h>


pion pion_null;
bateau bateau_null;
creature creature_null;
tuile tuile_null;
casee case_null;
joueur joueur_null;

int socle[13][13] = { // LISTE DE COLONNES
    //
    {0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,0,0,0,0},
    {0,0,0,1,1,1,1,1,1,0,0,0,0},
    {0,0,0,1,1,1,1,1,1,1,0,0,0},
    {0,0,0,1,1,1,0,1,1,1,0,0,0},
    {0,0,0,1,1,1,1,1,1,1,0,0,0},
    {0,0,0,0,1,1,1,1,1,0,0,0,0},
    {0,0,0,0,1,1,1,1,0,0,0,0,0},
    {0,0,0,0,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0}
    };

tuile deck_tuile[40] = {
    {0, 0},
    {0, 0},
    {0, 0},
    {1, 0},
    {1, 0},
    {1, 0},
    {0, 1},
    {0, 1},
    {0, 1},
    {1, 1},
    {1, 1},
    {0, 2},
    {1, 2},
    {1, 2},
    {1, 2},
    {1, 3},
    {1, 3},
    {2, 3},
    {2, 3},
    {2, 3},
    {2, 3},
    {2, 4},
    {2, 4},
    {2, 4},
    {2, 4},
    {0, 5},
    {0, 5},
    {0, 5},
    {1, 5},
    {0, 6},
    {0, 6},
    {1, 7},
    {1, 7},
    {0, 8},
    {0, 8},
    {1, 8},
    {1, 8},
    {0, 9},
    {0, 9},
    {1, 9}};

void initialiser_nulls() {
    pion_null.equipe=-1;
    pion_null.nom="Z";
    pion_null.numero=-1;
    for (int i =0; i<3; i++) {
        bateau_null.pions[i] = pion_null;
    }
    bateau_null.equipe_leader = -2;
    creature_null.type=-1;
    tuile_null.type=-1;
    tuile_null.carte=-1;
    case_null.bateau=bateau_null;
    for (int i = 0; i<3; i++) {
        case_null.creatures[i] = creature_null;
    }
    for (int i =0; i<40; i++) {
        case_null.pions[i] = pion_null;
    }
    case_null.terre_ferme=0;
    case_null.tuile=tuile_null;
    joueur_null.equipe=-1;
    joueur_null.points=-1;
    for (int i = 0; i<40; i++) {
        joueur_null.cartes[i] = -1;
    }
}

void initialiser_plateau(casee Plateau[13][13], casee casenulle) {
    for (int i =0; i<13; i++) {
        for (int j=0; j<13; j++) {
            Plateau[i][j] = casenulle;
        }
    }

}
void placer_serpents(casee Plateau[13][13]) {
Plateau[0][0].creatures[0].type = 0; // Hard code, placement des serpents
Plateau[0][12].creatures[0].type = 0;
Plateau[12][0].creatures[0].type = 0;
Plateau[12][12].creatures[0].type = 0;
Plateau[6][6].creatures[0].type = 0;

}

void melanger_tuiles(tuile tuiles[40]) {
    for (int i = 39; i > 0; i--) { // On boucle de la fin du tableau vers le début
        int j = rand() % (i + 1); // Choisit un indice aléatoire entre 0 et i inclus
        tuile tmp = tuiles[i];    // Stocke temporairement la tuile à l'indice i
        tuiles[i] = tuiles[j];    // Remplace la tuile à l'indice i par celle à l'indice j
        tuiles[j] = tmp;          // Place la tuile initialement à l'indice i à la position j
    }
}

void placer_tuiles(casee Plateau[13][13], tuile tuiles[40], int socle[13][13]) {
    int k = 0; // compteur de tuiles placées
    for (int i = 0; i < 13; i++) {  // Correction de la boucle
        for (int j = 0; j < 13; j++) {
            if (socle[i][j] == 1) {
                Plateau[i][j].tuile = tuiles[k];  // On place la tuile
                Plateau[i][j].terre_ferme = 1;
                k++;  // Incrémenter le compteur de tuiles
            }
        }
    }
}

void initialiser_joueurs(joueur joueurs[4], int *n_joueurs) {
    char *equipes[4] = {"Rouge", "Bleu", "Vert", "Jaune"};
    int selected;
    char *options[] = {"2 joueurs", "3 joueurs", "4 joueurs"};

    gotoxy(75, 3);
    printf("Combien de joueurs ?");
    selection_menu(75, 5, options, 3, &selected);

    rectangle(75, 3, 20, 6, 0);  // Nettoie la zone du menu (titre + choix)

    *n_joueurs = selected + 2;

    for (int i = 0; i < *n_joueurs; i++) {
        joueurs[i].equipe = i;
        joueurs[i].points = 0;
        gotoxy(75, 5 + i);
        printf("Joueur %d : %s", i + 1, equipes[i]);
    }
}
