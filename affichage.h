#ifndef AFFICHAGE_H_INCLUDED
#define AFFICHAGE_H_INCLUDED
#include <windows.h>
#include "donnee.h"

#define NOIR 0
#define BLEU 1
#define VERT 2
#define CYAN 3
#define ROUGE 4
#define MAGENTA 5
#define JAUNE 6
#define GRIS_CLAIR 7
#define GRIS_FONCE 8
#define BLEU_CLAIR 9
#define VERT_CLAIR 10
#define CYAN_CLAIR 11
#define ROUGE_CLAIR 12
#define MAGENTA_CLAIR 13
#define JAUNE_CLAIR 14
#define BLANC 15

void plein_ecran();
void contour(int x, int y, int w, int h);
void set_color(WORD fg, WORD bg);
void curseur_visible(int visible); //   0/1
void rectangle(int x, int y, int w, int h, int c);
void afficher_casee(int x, int y, casee case1, int select);
int get_input();
void gotoxy(int x, int y);
void selection_menu(int x, int y, char *options[], int num_options, int *selected_index);
void selection_case(casee Plateau[13][13], int *x_s, int *y_s);
void nouveau_message(const char * message, int couleur_texte);

#endif // AFFICHAGE_H_INCLUDED
