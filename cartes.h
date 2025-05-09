#ifndef CARTES_H_INCLUDED
#define CARTES_H_INCLUDED

#include "donnee.h"

void choisir_carte(joueur joueur, int *i_carte);
void jouer_carte(casee Plateau[13][13], joueur *joueur, int i_carte);
void jouer_carte_immediate(casee Plateau[13][13], joueur *joueur, int i_carte, int x_carte, int y_carte);
void obtenir_carte(casee Plateau[13][13], casee case1, joueur *j, int x, int y);

// Fonctions des cartes immediates
void carte_placer_requin(casee Plateau[13][13], int x, int y);
void carte_placer_baleine(casee Plateau[13][13], int x, int y);
void carte_placer_bateau(casee Plateau[13][13], int x, int y);
void carte_tourbillon(casee Plateau[13][13], int x, int y);
void carte_eruption(casee Plateau[13][13], int x, int y);

// Fonctions des cartes jouables pendant le tour
void carte_dauphin(casee Plateau[13][13], joueur *joueur);
void carte_deplacer_bateau(casee Plateau[13][13], joueur *joueur);
void carte_plongeon(casee Plateau[13][13], joueur *joueur);
void carte_de_creature(casee Plateau[13][13], joueur *joueur);
void carte_repulsif(casee Plateau[13][13], joueur *joueur);

#endif // CARTES_H_INCLUDED
