#ifndef TOURS_H_INCLUDED
#define TOURS_H_INCLUDED
#include "donnee.h"
#include "affichage.h"
#include "cartes.h"
void tour(joueur *joueur, casee Plateau[13][13]);
pion* selectionner_pion_sur_plateau(joueur *j, casee Plateau[13][13],int *x_i,int *y_i);
pion* selectionner_emplacement_vide_pion(joueur *j, casee Plateau[13][13], int *x_i, int *y_i); // si c dans un bato ou pas


#endif // TOURS_H_INCLUDED
