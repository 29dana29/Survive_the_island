#ifndef AFFICHAGE_H_INCLUDED
#define AFFICHAGE_H_INCLUDED
#include <windows.h>
#include "donnee.h"

void plein_ecran();
void contour(int x, int y, int w, int h);
void set_color(WORD fg, WORD bg);
void curseur_visible(int visible); //   0/1
void rectangle(int x, int y, int w, int h, int c);
void afficher_casee(int x, int y, casee case1);
int get_input();
void selection_menu(int x, int y, char *titre, char *options[], int num_options, int *selected_index);


#endif // AFFICHAGE_H_INCLUDED
