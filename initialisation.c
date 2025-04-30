#include "initialisation.h"
#include "donnee.h"
void initialiser_nulls() {
    pion_null.equipe=-1;
    pion_null.nom="Z";
    pion_null.numero=-1;
    for (int i =0; i<3; i++) {
        bateau_null.pions[i] = pion_null;
    }
    bateau_null.equipe_leader = -1;
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
