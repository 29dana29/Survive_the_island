#include "donnee.h"
#include "affichage.h"
#include "stdio.h"

void choisir_carte(joueur joueur, int *i_carte) {
    char * type_cartes[10] = {"Placer Requin", "Placer baleine", "Placer bateau", "Tourbillon", "Eruption", "Dauphin", "Bouger Bateau", "Plongeon", "Dé créature", "Répulsif"};


    int n_cartes=0;
    int carte_et_i[40][2];
    for (int i = 0; i<40; i++) {
        if (joueur.cartes[i]!=-1) {
            carte_et_i[n_cartes][0]= joueur.cartes[i];
            carte_et_i[n_cartes][1]=i;
            n_cartes++;
        }
    }
    char * options [n_cartes];
    for (int i = 0; i<n_cartes; i++) {
        options[i] = type_cartes[carte_et_i[i][0]];
    }
    int i_select=0;
    gotoxy(75, 2);
    set_color(8, 4);
    printf("Selectionne la carte que tu veux jouer.");
    selection_menu(75, 4, options, n_cartes, &i_select);
    *i_carte = carte_et_i[i_select][1];

}

