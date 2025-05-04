#include "initialisation.h"
#include "donnee.h"
#include <stdlib.h>

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
    case_null.terre_ferme=-1;
    case_null.tuile=tuile_null;
}

void initialiser_plateau(casee Plateau[13][13], casee casenulle) {
    for (int i =0; i<13; i++) {
        for (int j=0; j<13; j++) {
            Plateau[i][j] = casenulle;
        }
    }

}
void placer_serpents(casee Plateau[13][13]) {
Plateau[0][0].creatures[0].type = 0;
Plateau[0][12].creatures[0].type = 0;
Plateau[12][0].creatures[0].type = 0;
Plateau[12][12].creatures[0].type = 0;
Plateau[6][6].creatures[0].type = 0;

}
void

