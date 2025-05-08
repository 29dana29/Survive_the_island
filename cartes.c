#include "donnee.h"
#include "affichage.h"
#include "stdio.h"
#include "initialisation.h"
#include "tours.h"

extern pion pion_null;
extern casee case_null;

// Fonctions de jeu pour chaque carte
void jouer_carte_immediat_placer_requin(casee Plateau[13][13], int x, int y)
{
    int i;
    for (int j = 0; j < 40; j++)
    {
        Plateau[x][y].pions[j] = pion_null;
    }
    i = 0;
    while (Plateau[x][y].creatures[i].type != -1) i++;
    Plateau[x][y].creatures[i].type = 1;
    afficher_casee(x * 5, y * 3, Plateau[x][y], 0);
}

void jouer_carte_immediat_placer_baleine(casee Plateau[13][13], int x, int y)
{
    int i = 0;
    while (Plateau[x][y].creatures[i].type != -1) i++;
    Plateau[x][y].creatures[i].type = 2;
    afficher_casee(x * 5, y * 3, Plateau[x][y], 0);
}

void jouer_carte_immediat_placer_bateau(casee Plateau[13][13], int x, int y)
{
    Plateau[x][y].bateau.equipe_leader = -2;
    afficher_casee(x * 5, y * 3, Plateau[x][y], 0);
}

<<<<<<< Updated upstream
void jouer_carte_immediat_tourbillon(casee Plateau[13][13], int x, int y) {
    for(int i = -1; i < 1; i++)
    {
        for(int j = -1; j < 1; j++)
        {
            if (Plateau[x+i][y+j].terre_ferme == 0)
            {
                Plateau[x+i][y+j] = case_null;
            }
        }
    }
=======
void jouer_carte_immediat_tourbillon(casee Plateau[13][13], int x, int y)
{
    // À implémenter
>>>>>>> Stashed changes
}

void jouer_carte_immediat_eruption(casee Plateau[13][13], int x, int y)
{
    // À implémenter
}

void jouer_carte_dauphin(casee Plateau[13][13], joueur *j)
{
    int mouvements = 3;
    while (mouvements > 0)
    {
        deplacer_pion(j, Plateau, &mouvements, 1); // nageur = 1
    }
}



void jouer_carte_deplacer_bateau(casee Plateau[13][13], joueur *j)
{
    /*
    Deokacez un de vos bateaux jusqu'a 3 cases.
    */
    rectangle(65, 1, 60, 39, 0);
    gotoxy(70, 1);
    printf("Carte deplacer bateau");
    int p_mouvements = 3;
    while (p_mouvements>0)
    {
        gotoxy(80, 1);
        printf("Mouvements: %d", p_mouvements);
        deplacer_bateau(j, Plateau, &p_mouvements);
    }
}

void jouer_carte_plongeon(casee Plateau[13][13], joueur *j)
{
    // À implémenter
}

void jouer_carte_deplacement_creature(casee Plateau[13][13], joueur *j)
{
    // À implémenter
}

void jouer_carte_repulsif(casee Plateau[13][13], joueur *j)
{
    // À implémenter
}

void obtenir_carte(casee Plateau[13][13], joueur *j, int x, int y)
{
    int id = Plateau[x][y].tuile.carte;
    if (id < 0 || id > 9) return;
    if (id <= 4)
    {
        // Carte immédiate
        switch (id)
        {
        case 0:
            jouer_carte_immediat_placer_requin(Plateau, x, y);
            break;
        case 1:
            jouer_carte_immediat_placer_baleine(Plateau, x, y);
            break;
        case 2:
            jouer_carte_immediat_placer_bateau(Plateau, x, y);
            break;
        case 3:
            jouer_carte_immediat_tourbillon(Plateau, x, y);
            break;
        case 4:
            jouer_carte_immediat_eruption(Plateau, x, y);
            break;
        }
    }
    else
    {
        // Carte à stocker
        int i = 0;
        while ((*j).cartes[i] != -1)
        {
            i++;
        }
        (*j).cartes[i] = id;
    }
    Plateau[x][y].tuile.carte = -1;
}

void jouer_carte(casee Plateau[13][13], joueur *j, int i_carte)
{

    int id = (*j).cartes[i_carte];
    if (id < 5 || id > 9) return;
    switch (id)
    {
    case 5:
    {
        int nageur_trouve = 0;
        for (int x = 0; x < 13 && !nageur_trouve; x++)
        {
            for (int y = 0; y < 13 && !nageur_trouve; y++)
            {
                if (Plateau[x][y].terre_ferme == 0 && compter_pions_couleur(Plateau[x][y].pions, (*j).equipe) >= 1)
                {
                    nageur_trouve = 1;
                }
            }
        }
        if (nageur_trouve)
        {
            jouer_carte_dauphin(Plateau, j);
        }
        else
        {
            gotoxy(75, 20);
            set_color(12, 5);
            printf("Aucun nageur pour utiliser la carte Dauphin !");
        }
        break;
    }

    case 6:
        jouer_carte_deplacer_bateau(Plateau, j);
        break;
    case 7:
        jouer_carte_plongeon(Plateau, j);
        break;
    case 8:
        jouer_carte_deplacement_creature(Plateau, j);
        break;
    case 9:
        jouer_carte_repulsif(Plateau, j);
        break;
    }
    (*j).cartes[i_carte] = -1;
}

void choisir_carte(joueur j, int *i_carte)
{
    char *type_cartes[11] =  // On augmente la taille pour inclure "Passer"
    {
        "Passer",               // Option pour passer
        "Placer Requin",
        "Placer Baleine",
        "Placer Bateau",
        "Tourbillon",
        "Eruption",
        "Dauphin",
        "Bouger Bateau",
        "Plongeon",
        "Dé créature",
        "Répulsif"
    };

    int carte_et_i[40][2];
    int n_cartes = 0;

    for (int i = 0; i < 40; i++)
    {
        if (j.cartes[i] != -1)
        {
            carte_et_i[n_cartes][0] = j.cartes[i];
            carte_et_i[n_cartes][1] = i;
            n_cartes++;
        }
    }

    if (n_cartes == 0)
    {
        *i_carte = -1;
        return;
    }

    // L'option "Passer" doit être en premier
    char *options[n_cartes + 1];  // +1 pour l'option "Passer"

    options[0] = type_cartes[0];  // "Passer"

    for (int i = 0; i < n_cartes; i++)
    {
        options[i + 1] = type_cartes[carte_et_i[i][0] + 1];  // On décalle d'1 car "Passer" est déjà à l'index 0
    }

    int i_select = 0;

    gotoxy(75, 2);
    set_color(8, 4);
    printf("Selectionne la carte que tu veux jouer (ou Passer).");

    selection_menu(75, 4, options, n_cartes + 1, &i_select);

    if (i_select == 0)  // Si le joueur choisit "Passer"
    {
        *i_carte = -1;
    }
    else
    {
        *i_carte = carte_et_i[i_select - 1][1];  // -1 pour accéder à la carte correcte
    }
}
