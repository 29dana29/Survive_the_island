#include "donnee.h"
#include "affichage.h"
#include "stdio.h"
#include "cartes.h"
#include "initialisation.h"

extern bateau bateau_null;
extern pion pion_null;

pion* selectionner_pion_sur_plateau(joueur *j, casee Plateau[13][13],int *x_i,int *y_i)
{
    int x_s, y_s;
    int valide = 0;

    while (!valide)
    {
        rectangle(65, 1, 60, 39, 0);
        gotoxy(75, 15);
        printf("Selectionne la case d'ou tu veux bouger.");

        selection_case(Plateau, &x_s, &y_s);

        if ((compter_pions_couleur(Plateau[x_s][y_s].pions, (*j).equipe) + compter_pions_couleur(Plateau[x_s][y_s].bateau.pions, (*j).equipe)) >= 1)
        {
            valide = 1;
        }
        else
        {
            rectangle(65, 1, 60, 39, 0);
            gotoxy(75, 15);
            printf("Nan y'a pas de pion a toi là.");
        }
    }
    *x_i = x_s;
    *y_i = y_s;

    char* options_pions[40];
    pion* adresse_associe[40];
    int nb = 0;

    for (int i = 0; i < 40; i++)
        options_pions[i] = malloc(20 * sizeof(char));

    for (int i = 0; i < 40; i++)
    {
        if (Plateau[x_s][y_s].pions[i].equipe == (*j).equipe && Plateau[x_s][y_s].pions[i].numero > 0)
        {
            strcpy(options_pions[nb], Plateau[x_s][y_s].pions[i].nom);
            adresse_associe[nb] = &Plateau[x_s][y_s].pions[i];
            nb++;
        }
    }
    for (int i = 0; i < 3; i++)   // Boucle dans les pions du bateau
    {
        if (Plateau[x_s][y_s].bateau.pions[i].equipe == (*j).equipe && Plateau[x_s][y_s].bateau.pions[i].numero > 0)
        {
            snprintf(options_pions[nb], 20, "%s (bateau)", Plateau[x_s][y_s].bateau.pions[i].nom);
            adresse_associe[nb] = &Plateau[x_s][y_s].bateau.pions[i];
            nb++;
        }
    }


    int select_indice;
    rectangle(65, 1, 60, 39, 0);
    gotoxy(75, 15);
    printf("Selectionne un pion --");
    selection_menu(75, 16, options_pions, nb, &select_indice);

    for (int i = 0; i < 40; i++)
    {
        free(options_pions[i]);
    }

    return adresse_associe[select_indice];
}

pion* selectionner_emplacement_vide_pion(joueur *j, casee Plateau[13][13], int *x_i, int *y_i) // si c dans un bato ou pas
{
    int x_d, y_d;
    rectangle(65, 1, 60, 39, 0);
    gotoxy(75, 15);
    printf("Selectionne la case de destination");
    selection_case(Plateau, &x_d, &y_d);
    *x_i=x_d;
    *y_i=y_d;

    int i_selec_b_p=1; // Si ca va dans un bateau ou une case
    // 1:CASE 0:BATEAU
    int indice_dispo=-1;
    int i_copie;
    for (int i = 0; i<40; i++)   // on va check tous les emplacements jusqu'a un vide
    {
        if (Plateau[x_d][y_d].pions[i].equipe==-1)   // VIDE
        {
            i_copie=i;
            break;
        }
    }

    if (Plateau[x_d][y_d].bateau.equipe_leader!=-2)   // DONC S'IL EXISTE
    {
        for (int i =0; i<3; i++)   // Recherche d'un emplacement vide dans le bateau
        {
            if(Plateau[x_d][y_d].bateau.pions[i].equipe==-1)
            {
                indice_dispo=i;
            }
        }

        if (indice_dispo!=-1)
        {
            // Faut maintenant choisir entre bateau et juste la mer
            char * choix_b_p[2] = {"Rejoindre le bateau", "Juste aller dans la case"};
            rectangle(65, 1, 60, 39, 0);
            gotoxy(70, 1);
            printf("Ou voulez vous mettre le pion");
            selection_menu(70, 4, choix_b_p, 2, &i_selec_b_p);

        }
    }

    if (i_selec_b_p==0)   //BATEAU
    {
        return &Plateau[x_d][y_d].bateau.pions[indice_dispo];
    }
    else     // Pas bateau
    {

        return &Plateau[x_d][y_d].pions[i_copie];
    }
}

creature* selectionner_creature(casee Plateau[13][13], int type_restriction,int *x_i, int *y_i)
{
    /*
    Permet de sélectionner une créature sur le plateau, avec option de restriction sur le type.
    Retourne un pointeur vers la créature sélectionnée, ou NULL si aucune n’est disponible.
    */

    rectangle(65, 1, 60, 39, 0);
    gotoxy(69, 1);
    printf("Sélectionne la case contenant la créature à déplacer.");

    int x_s, y_s;
    int valide = 0;

    while (!valide)
    {
        selection_case(Plateau, &x_s, &y_s);

        for (int i = 0; i < 3; i++)
        {
            if (Plateau[x_s][y_s].creatures[i].type != -1 &&
               (type_restriction == -1 || Plateau[x_s][y_s].creatures[i].type == type_restriction))
            {
                valide = 1;
                break;
            }
        }

        if (!valide)
        {
            gotoxy(69, 3);
            printf("Aucune créature valide ici. Choisis une autre case.");
        }
    }

    char *option_creatures[] = {"Serpent", "Requin", "Baleine"};
    int creatures_et_i[3]; // Max 3 créatures par case
    int n_creatures = 0;

    for (int i = 0; i < 3; i++)
    {
        int t = Plateau[x_s][y_s].creatures[i].type;
        if (t != -1 && (type_restriction == -1 || t == type_restriction))
        {
            creatures_et_i[n_creatures] = i;
            n_creatures++;
        }
    }

    if (n_creatures == 0)
    {
        return NULL;
    }

    char *options[n_creatures];
    for (int i = 0; i < n_creatures; i++)
    {
        options[i] = option_creatures[Plateau[x_s][y_s].creatures[creatures_et_i[i]].type];
    }

    rectangle(65, 1, 60, 39, 0);
    gotoxy(75, 2);
    set_color(5, 4);
    printf("Sélectionne la créature que tu veux bouger");

    int i_select = 0;
    selection_menu(75, 4, options, n_creatures, &i_select);
    *x_i = x_s;
    *y_i = y_s;
    return &Plateau[x_s][y_s].creatures[creatures_et_i[i_select]];
}


void deplacer_pion(joueur *joueur, casee Plateau[13][13], int *p_mouvement, int nageur) // NAGEUR 1/0 si il doit être un nageur et se deplacer dans l'eau
{
    int x_s, y_s;
    int x_d, y_d;
    int valide = 0;
    pion *pion_source;
    while (!valide)
    {
        pion_source = selectionner_pion_sur_plateau(joueur, Plateau, &x_s, &y_s);
        if (nageur == 0 || Plateau[x_s][y_s].terre_ferme == 0)
        {
            valide = 1;
        }
    }

    pion copie_pion_source = *pion_source;
    *pion_source = pion_null;
    afficher_casee(x_s*5, y_s*3, Plateau[x_s][y_s], 0);

    pion *pion_arrivee;
    valide=0;
    while (!valide)
    {
        pion_arrivee = selectionner_emplacement_vide_pion(joueur, Plateau, &x_d, &y_d);
        if ((abs(x_s - x_d) <= 1) && (abs(y_s - y_d) <= 1) &&
                ((nageur == 0) || (Plateau[x_d][y_d].terre_ferme == 0))){ // Soit pas nageur soit c en MER
            valide = 1;

                }
        else
        {
            gotoxy(75, 20);
            set_color(12, 5);
            printf("Selectionne une case adjacente");
        }
    }

    *pion_arrivee = copie_pion_source;
    Plateau[x_s][y_s].bateau.equipe_leader = determiner_leader(Plateau[x_s][y_s].bateau);
    Plateau[x_d][y_d].bateau.equipe_leader = determiner_leader(Plateau[x_d][y_d].bateau);
    afficher_casee(x_s*5, y_s*3, Plateau[x_s][y_s], 0);
    afficher_casee(x_d*5, y_d*3, Plateau[x_d][y_d], 0);

    if (pion_arrivee != pion_source)
        (*p_mouvement)--;
}

void deplacer_bateau(joueur *joueur, casee Plateau[13][13], int *p_mouvement)
{
    int x_s, y_s;
    int x_d, y_d;
    int valide = 0;

    rectangle(65, 2, 60, 39, 0);
    gotoxy(70, 2);
    set_color(15, 0);
    printf("Selectionne la case du bateau a bouger");

    while (!valide)
    {
        selection_case(Plateau, &x_s, &y_s);
        if (Plateau[x_s][y_s].bateau.equipe_leader == joueur->equipe || Plateau[x_s][y_s].bateau.equipe_leader == -1)
            valide = 1;
        else
        {
            gotoxy(70, 3);
            set_color(15, 0);
            printf("Dont tu es le capitaine ou vide");
        }
    }

    bateau source_copie = Plateau[x_s][y_s].bateau;
    Plateau[x_s][y_s].bateau = bateau_null;
    afficher_casee(x_s*5, y_s*3, Plateau[x_s][y_s], 0);

    rectangle(65, 1, 60, 39, 0);
    gotoxy(70, 2);
    set_color(15, 0);
    printf("Selectionne la case ou bouger le bateau");

    valide = 0;
    while (!valide)
    {
        selection_case(Plateau, &x_d, &y_d);
        if (abs(x_d - x_s) <= 1 && abs(y_d - y_s) <= 1 &&
                Plateau[x_d][y_d].terre_ferme == 0 &&
                Plateau[x_d][y_d].bateau.equipe_leader == -2)
            valide = 1;
        else
        {
            gotoxy(70, 6);
            set_color(12, 0);
            printf("Case invalide (doit être mer+adjacente+vide)");
        }
    }

    Plateau[x_d][y_d].bateau = source_copie;
    Plateau[x_d][y_d].bateau.equipe_leader = determiner_leader(Plateau[x_d][y_d].bateau);
    afficher_casee(x_d*5, y_d*3, Plateau[x_d][y_d], 0);
    afficher_casee(x_s*5, y_s*3, Plateau[x_s][y_s], 0);

    if (x_d != x_s || y_d != y_s)
        (*p_mouvement)--;
}



void tour(joueur *joueur, casee Plateau[13][13])
{
    rectangle(65, 1, 60, 39, 0);
    gotoxy(66, 0);
    set_color(0, 15);
    printf("TOUR DU JOUEUR %d", joueur->equipe);

    if (compter_cartes(*joueur) >= 1)
    {
        int i_carte;
        choisir_carte(*joueur, &i_carte);
        jouer_carte(Plateau, joueur, i_carte);
    }

    int p_mouvement = 3;
    char *options[] = {"Deplacer un pion", "Deplacer un bateau"};
    int select_indice;

    while (p_mouvement > 0)
    {
        rectangle(65, 1, 60, 39, 0);
        gotoxy(70, 2);
        printf("Il vous reste %d deplacement(s)", p_mouvement);
        selection_menu(70, 4, options, 2, &select_indice);

        if (select_indice == 0)
            deplacer_pion(joueur, Plateau, &p_mouvement, 0);
        else
            deplacer_bateau(joueur, Plateau, &p_mouvement);
    }

}
