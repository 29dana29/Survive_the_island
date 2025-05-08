#include "donnee.h"
#include "affichage.h"
#include "stdio.h"
#include "initialisation.h"
extern pion pion_null;

void jouer_carte(casee Plateau[13][13], joueur *joueur, int i_carte)
{
    gotoxy(75, 10);
    set_color(4, 9);
    switch ((*joueur).cartes[i_carte])
    {
    case 5:
        printf("Dauphin");
        break;
    case 6:
        printf("Deplacer bateau");
        break;
    case 7:
        printf("Plongeon");
        break;
    case 8:
        printf("De creature");
        break;
    case 9:
        printf("Repulsif");
        break;

    default:
        printf("Muvaise carte");
        break;

    }
    (*joueur).cartes[i_carte] = -1; // Suprime la carte
}

void jouer_carte_immediate(casee Plateau[13][13], joueur *joueur, int i_carte, int x_carte, int y_carte)
{
    int i;
    switch(i_carte)
    {
    case 0: // placer requin
        // ELimination des pions
        for (int i = 0; i<40; i++)
        {
            Plateau[x_carte][y_carte].pions[i] = pion_null;
        }
        // Placement du requin
        i = 0;
        while(Plateau[x_carte][y_carte].creatures[i].type!=-1)
        {
            i++;
        }
        Plateau[x_carte][y_carte].creatures[i].type = 1;
        afficher_casee(x_carte*5, y_carte*3, Plateau[x_carte][y_carte], 0);
        break;
    case 1: // Placer_baleine
        i = 0;
        while(Plateau[x_carte][y_carte].creatures[i].type!=-1)
        {
            i++;
        }
        Plateau[x_carte][y_carte].creatures[i].type = 2;
        afficher_casee(x_carte*5, y_carte*3, Plateau[x_carte][y_carte], 0);
        break;

    }
}

void choisir_carte(joueur joueur, int *i_carte)
{
    /* retourne l'indice dans joueur.cartes[] de la carte choisie

    */

    char * type_cartes[10] = {"Placer Requin", "Placer baleine", "Placer bateau", "Tourbillon", "Eruption", "Dauphin", "Bouger Bateau", "Plongeon", "Dé créature", "Répulsif"};

    int n_cartes=0;
    int carte_et_i[40][2];
    for (int i = 0; i<40; i++)
    {
        if (joueur.cartes[i]!=-1)
        {
            carte_et_i[n_cartes][0]= joueur.cartes[i];
            carte_et_i[n_cartes][1]=i;
            n_cartes++;
        }
    }
    if (n_cartes==0)
    {
        *i_carte=-1; // Sorte d'alerte
    }
    else
    {
        char * options [n_cartes];
        for (int i = 0; i<n_cartes; i++)
        {
            options[i] = type_cartes[carte_et_i[i][0]];
        }
        int i_select=0;
        gotoxy(75, 2);
        set_color(8, 4);
        printf("Selectionne la carte que tu veux jouer.");
        selection_menu(75, 4, options, n_cartes, &i_select);
        *i_carte = carte_et_i[i_select][1];
    }

}

void obtenir_carte(joueur *joueur, casee Plateau[13][13], int x_carte, int y_carte)
{
    if (Plateau[x_carte][y_carte].tuile.carte>=5)   // Tuile non instantanée
    {
        int i = 0;
        while ((*joueur).cartes[i]!=-1)   // tant que on est pas a un emplacement vide de carte
        {
            i++;
        }
        (*joueur).cartes[i] = Plateau[x_carte][y_carte].tuile.carte;
    }
}
