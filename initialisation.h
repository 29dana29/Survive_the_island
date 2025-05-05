#ifndef INITIALISATION_H_INCLUDED
#define INITIALISATION_H_INCLUDED
#include "donnee.h"
void initialiser_nulls();
void initialiser_plateau(casee Plateau[13][13], casee casenulle);
void placer_serpents(casee Plateau[13][13]);
void melanger_tuiles(tuile tuiles[40]);
void placer_tuiles(casee Plateau[13][13], tuile tuiles[40], int socle[13][13]);
void initialiser_joueurs(joueur joueurs[4], int *n_joueurs);
#endif // INITIALISATION_H_INCLUDED
