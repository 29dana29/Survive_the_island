#ifndef CARTES_H_INCLUDED
#define CARTES_H_INCLUDED

void choisir_carte(joueur joueur, int *i_carte);
void jouer_carte(casee Plateau[13][13], joueur *joueur,int i_carte);
void jouer_carte_immediate(casee Plateau[13][13], joueur *joueur, int i_carte, int x_carte, int y_carte);
#endif // CARTES_H_INCLUDED
