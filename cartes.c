#include "donnee.h"
#include "affichage.h"
#include "stdio.h"
#include "initialisation.h"
#include "tours.h"

extern pion pion_null;
extern casee case_null;
extern int jeu;

// Fonctions de jeu pour chaque carte
void carte_immediat_placer_requin(casee Plateau[13][13], int x, int y)
{
    nouveau_message("Placer requin", BLANC);
    Plateau[x][y].creatures[0].type = 1;
    action_requin(Plateau, x, y);
    afficher_casee(x * 5, y * 3, Plateau[x][y], 0);
}

void carte_immediat_placer_baleine(casee Plateau[13][13], int x, int y)
{
    //pas besoin de check pour les emplacement  vide comme c'etait un tuile terre ferme
    nouveau_message("Placer baleine", BLANC);
    Plateau[x][y].creatures[0].type = 2;
    action_baleine(Plateau, x, y);

    afficher_casee(x * 5, y * 3, Plateau[x][y], 0);
}

void carte_immediat_placer_bateau(casee Plateau[13][13], int x, int y)
{
    nouveau_message("Placer bateau", BLANC);
    Plateau[x][y].bateau.equipe_leader = -1;
    afficher_casee(x * 5, y * 3, Plateau[x][y], 0);
}

void carte_immediat_tourbillon(casee Plateau[13][13], int x, int y)
{
    nouveau_message("Oh non, un tourbillon !", BLEU);
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (x + i >= 0 && x + i < 13 && y + j >= 0 && y + j < 13)
            {
                if (Plateau[x+i][y+j].terre_ferme == 0)
                {
                    Plateau[x+i][y+j] = case_null;
                }
            }
        }
    }
}

void carte_immediat_eruption(casee Plateau[13][13], int x, int y)
{
    rectangle(65, 1, 60, 39, 0);

    gotoxy(80, 1);
    set_color(0, 15);
    nouveau_message("OH NON, LE VOLCAN ! C'EST BIENTOT FINI...", ROUGE_CLAIR);
    jeu = 0;
}

void carte_dauphin(casee Plateau[13][13], joueur *j)
{
    gotoxy(75, 22);
    nouveau_message("Un dauphin a la rescousse !", CYAN);
    int mouvements = 3;
    while (mouvements > 0)
    {
        deplacer_pion(j, Plateau, &mouvements, 1); // nageur = 1
    }
}

void carte_deplacer_bateau(casee Plateau[13][13], joueur *j)
{
    rectangle(65, 1, 60, 39, 0);
    gotoxy(75, 22);
    nouveau_message("Les vents favorables !", BLANC);
    int p_mouvements = 3;
    while (p_mouvements > 0)
    {
        char message[61];
        sprintf(message, "Bords restants: %d", p_mouvements);
        nouveau_message(message, BLEU);
        deplacer_bateau(j, Plateau, &p_mouvements);
    }

}

void carte_plongeon(casee Plateau[13][13], joueur *j)
{
    /*
    Deplacer n'importe quelle creature sur n'importe quelle case de mer.
    */
    gotoxy(75, 22);
    nouveau_message("Plongeon ?", BLANC);
    int x_s, y_s;
    creature *c = selectionner_creature(Plateau, -1, &x_s, &y_s);
    if (c == NULL) return;
//     if ((x_d==12||x_d==0)&&(y_d==12||y_d==0))   // Si c'est un coin

    // Selection de la case de destination
    int x_d, y_d;
    int valide = 0;

    nouveau_message("Selectionne la case de destination (case de mer).", BLANC);

    while (!valide)
    {
        selection_case(Plateau, &x_d, &y_d);
        if ((Plateau[x_d][y_d].terre_ferme==0) && (compter_creatures(Plateau[x_d][y_d], 3)<3)) // Si mer + pas pleine
        {
            valide = 1;
        }
        else
        {
            nouveau_message("Ce n'est pas une case de mer valide. Reessaie.", ROUGE);
        }
    }

    // Deplacement reel
    for (int i = 0; i < 3; i++)
    {
        if (Plateau[x_d][y_d].creatures[i].type == -1)
        {
            Plateau[x_d][y_d].creatures[i] = *c;
            switch(Plateau[x_d][y_d].creatures[i].type)   // Pour gerer l'action
            {
            case 0: // serpent
                action_serpent(Plateau, x_d, y_d);
                break;
            case 1: // requin
                action_requin(Plateau, x_d, y_d);
                break;
            case 2: // Balein
                action_baleine(Plateau, x_d, y_d);
                break;
            }
            (*c).type = -1; // Suppression de la creature de sa case d'origine
            afficher_casee(x_d*5, y_d*3, Plateau[x_d][y_d], 0);
            afficher_casee(x_s*5, y_s*3, Plateau[x_s][y_s], 0);
            break;
        }
    }
}

void carte_de_creature(casee Plateau[13][13], joueur *j)
{
    de_creature(Plateau);
}

void carte_repulsif(casee Plateau[13][13], joueur *j)
{
    nouveau_message("REPULSIF", BLANC);
}

void obtenir_carte(casee Plateau[13][13], casee case1, joueur *j, int x, int y)
{
    char *type_cartes[10] =
    {
        "Placer Requin",
        "Placer Baleine",
        "Placer Bateau",
        "Tourbillon",
        "Eruption",
        "Dauphin",
        "Bouger Bateau",
        "Plongeon",
        "De creature",
        "Repulsif"
    };
    int id = case1.tuile.carte;
    if (id < 0 || id > 9) return;
    if (id <= 4)
    {
        switch (id)
        {
        case 0:
            carte_immediat_placer_requin(Plateau, x, y);
            break;
        case 1:
            carte_immediat_placer_baleine(Plateau, x, y);
            break;
        case 2:
            carte_immediat_placer_bateau(Plateau, x, y);
            break;
        case 3:
            carte_immediat_tourbillon(Plateau, x, y);
            break;
        case 4:
            carte_immediat_eruption(Plateau, x, y);
            break;
        }
    }
    else
    {
        char message[61];
        sprintf(message, "Carte obtenue: %s", type_cartes[id]);
        nouveau_message(message, BLANC);
        int i = 0;
        while ((*j).cartes[i] != -1) i++;
        (*j).cartes[i] = id;
    }
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
                if (Plateau[x][y].terre_ferme == 0 && compter_pions_couleur(Plateau[x][y].pions, (*j).equipe, 40) >= 1)
                {
                    nageur_trouve = 1;
                }
            }
        }
        if (nageur_trouve)
        {
            carte_dauphin(Plateau, j);
        }
        else
        {
            nouveau_message("Aucun nageur pour utiliser la carte Dauphin !", ROUGE);
        }
        break;
    }
    case 6:
        carte_deplacer_bateau(Plateau, j);
        break;
    case 7:
        carte_plongeon(Plateau, j);
        break;
    case 8:
        carte_de_creature(Plateau, j);
        break;
    case 9:
        carte_repulsif(Plateau, j);
        break;
    }
    (*j).cartes[i_carte] = -1;
}

void choisir_carte(joueur j, int *i_carte)
{
    char *type_cartes[11] =
    {
        "Passer",
        "Placer Requin",
        "Placer Baleine",
        "Placer Bateau",
        "Tourbillon",
        "Eruption",
        "Dauphin",
        "Bouger Bateau",
        "Plongeon",
        "De creature",
        "Repulsif"
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

    char *options[n_cartes + 1];
    options[0] = type_cartes[0];
    for (int i = 0; i < n_cartes; i++)
    {
        options[i + 1] = type_cartes[carte_et_i[i][0] + 1];
    }

    int i_select = 0;

    nouveau_message("Selectionne la carte que tu veux jouer.\n", BLANC);

    selection_menu(75, 4, options, n_cartes + 1, &i_select);

    if (i_select == 0)

    {
        *i_carte = -1;
    }
    else
    {
        *i_carte = carte_et_i[i_select - 1][1];
    }
}
