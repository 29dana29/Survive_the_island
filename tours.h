#ifndef TOURS_H_INCLUDED
#define TOURS_H_INCLUDED
#include "donnee.h"
#include "affichage.h"
#include "cartes.h"
void tour(joueur *joueur, casee Plateau[13][13]);
pion* selectionner_pion_sur_plateau(joueur *j, casee Plateau[13][13],int *x_i,int *y_i);
pion* selectionner_emplacement_vide_pion(joueur *j, casee Plateau[13][13], int *x_i, int *y_i); // si c dans un bato ou pas
void deplacer_pion(joueur *joueur, casee Plateau[13][13], int *p_mouvement, int nageur); // NAGEUR 1/0 si il doit être un nageur et se deplacer dans l'eau
void deplacer_bateau(joueur *joueur, casee Plateau[13][13], int *p_mouvement);
creature* selectionner_creature(casee Plateau[13][13], int type_restriction, int *x_i, int *y_i);
void de_creature(casee Plateau[13][13]);
int action_serpent(casee Plateau[13][13], int x, int y); // CHECK
int action_requin(casee Plateau[13][13], int x, int y); // CHECK
int action_baleine(casee Plateau[13][13], int x, int y);


#endif // TOURS_H_INCLUDED
