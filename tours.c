#include "donnee.h"
#include "affichage.h"
#include "stdio.h"
#include "cartes.h"
#include "initialisation.h"

extern bateau bateau_null;
extern pion pion_null;
extern creature creature_null;
extern tuile tuile_null;
extern int montee_eaux;
extern int couleurs_equipe[4];
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

        if ((compter_pions_couleur(Plateau[x_s][y_s].pions, (*j).equipe, 40) + compter_pions_couleur(Plateau[x_s][y_s].bateau.pions, (*j).equipe, 40)) >= 1)
        {
            valide = 1;
        }
        else
        {
            rectangle(65, 1, 60, 39, 0);
            gotoxy(75, 15);
            printf("Nan y'a pas de pion a toi la.");
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
    -1 : Toute creature confondue
    Permet de selectionner une creature sur le plateau, avec option de restriction sur le type.
    Retourne un pointeur vers la creature selectionnee, ou NULL si aucune n’est disponible.
    */

    //rectangle(65, 1, 60, 39, 0);
    gotoxy(69, 5);
    printf("Selectionne la case contenant la creature a deplacer.");

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
            printf("Aucune creature valide ici. Choisis une autre case.");
        }
    }

    char *option_creatures[] = {"Serpent", "Requin", "Baleine"};
    int creatures_et_i[3]; // Max 3 creatures par case
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
    printf("Selectionne la creature que tu veux bouger");

    int i_select = 0;
    selection_menu(75, 4, options, n_creatures, &i_select);
    *x_i = x_s;
    *y_i = y_s;
    return &Plateau[x_s][y_s].creatures[creatures_et_i[i_select]];
}


void deplacer_pion(joueur *joueur, casee Plateau[13][13], int *p_mouvement, int nageur) // NAGEUR 1/0 si il doit etre un nageur et se deplacer dans l'eau
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
                ((nageur == 0) || (Plateau[x_d][y_d].terre_ferme == 0)))  // Soit pas nageur soit c en MER
        {
            valide = 1;

        }
        else
        {
            gotoxy(75, 20);
            set_color(12, 5);
            printf("Selectionne une case adjacente");
        }
    }
    if ((x_d==12||x_d==0)&&(y_d==12||y_d==0))   // Si c'est un coin
    {
        (*joueur).points+=copie_pion_source.numero; // augmentation du score
        gotoxy(75, 22);
        set_color(0, 15);
        printf("+1 pion sauve !");

    }
    else     // Si c'est pas un coin
    {
        *pion_arrivee = copie_pion_source;
    }
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
            printf("Case invalide (doit etre mer+adjacente+vide)");
        }
    }

    Plateau[x_d][y_d].bateau = source_copie;
    Plateau[x_d][y_d].bateau.equipe_leader = determiner_leader(Plateau[x_d][y_d].bateau);
    afficher_casee(x_d*5, y_d*3, Plateau[x_d][y_d], 0);
    afficher_casee(x_s*5, y_s*3, Plateau[x_s][y_s], 0);

    if (x_d != x_s || y_d != y_s)
        (*p_mouvement)--;
}


int action_serpent(casee Plateau[13][13], int x, int y) // Verifiee
{
    int proie = 0;

    // Supprimer tous les pions
    for (int i = 0; i < 6; i++)
    {
        if (Plateau[x][y].pions[i].equipe != -1)
        {
            Plateau[x][y].pions[i] = pion_null;
            proie = 1;
        }
    }

    // Supprimer bateau s'il n'est pas vide
    if (compter_pions_couleur(Plateau[x][y].bateau.pions, 4, 3) >0)
    {
        Plateau[x][y].bateau = bateau_null;
        proie = 1;
    }
    afficher_casee(x*5, y*3, Plateau[x][y], 0);

    return proie;
}


int action_requin(casee Plateau[13][13], int x, int y)
{
    /*Retourne 1 si jamais il y a une proie, 0 s'il n'y en a pas
    Il enleve:
        -tous les pions dans la case de mer hors de bateaux
    */
    int proie = 0;
    for (int i = 0; i<40; i++)
    {
        if (Plateau[x][y].pions[i].equipe!=-1)
        {
            proie = 1;
            Plateau[x][y].pions[i] = pion_null;
        }
    }
    afficher_casee(x*5, y*3, Plateau[x][y], 0);
    return proie;

}
int action_baleine(casee Plateau[13][13], int x, int y)
{
    /*Retourne 1 si jamais il y a une proie, 0 s'il n'y en a pas
    Elle enleve:
        -le bateau de la case, s'il n'est pas vide
        les anciens pion du navire deviennent des pions dans la case de mer

    */
    int proie = 0;
//copie des pions dans la case s'il y en a:
    for (int i =0; i<3; i++)
    {
        if (Plateau[x][y].bateau.pions[i].equipe != -1)
        {
            proie = 1;
            for (int j = 0; j < 40; j++)
            {
                if (Plateau[x][y].pions[j].equipe == -1)
                {
                    Plateau[x][y].pions[j] = Plateau[x][y].bateau.pions[i];
                    break;
                }
            }

        }
    }
    if (proie == 1)   // Sabordage du navire !
    {
        Plateau[x][y].bateau = bateau_null;
    }
    afficher_casee(x*5, y*3, Plateau[x][y], 0);

    return proie;
}

void de_creature(casee Plateau[13][13])
{
    char * creatures[3] = {"Serpent", "Requin", "Baleine"};
    int type = rand()%3;
    // Le nombre de mouvement de chaque creature c 1+ l'id de la creature
    int valide;
    rectangle(65, 1, 60, 39, 0);
    gotoxy(70, 1);
    set_color(4, 2);
    printf("De creature: %s   ", creatures[type]);

    if (compter_creatures_plateau(Plateau, type) <= 0)
    {
        gotoxy(19, 6);
        set_color(4, 3);

        //printf("%d Bah nan en fait, y'en a aucune sur le plato", compter_creatures_plateau(Plateau, type));
    }
    else
    {
        int proie = 0;
        int p_mouvement = 1+type;// Le nombre de mouvement de chaque creature c 1+ l'id de la creature
        int x_s, y_s;
        creature *creature_source = selectionner_creature(Plateau, type, &x_s, &y_s);


        while (p_mouvement>0 && proie==0)
        {
            //Selection de la destination
            valide = 0;
            int x_d, y_d;
            gotoxy(70, 6);
            set_color(4, 3);
            printf("Selectionne une case adjacente comme destination %d", p_mouvement);
            while (valide==0)
            {
                selection_case(Plateau, &x_d, &y_d);
                if (abs(x_s - x_d) <= 1 && abs(y_s - y_d) <= 1 && Plateau[x_d][y_d].terre_ferme==0 && compter_creatures(Plateau[x_d][y_d], 3)<3)
                {
                    valide =1;
                }
                else
                {
                    gotoxy(70, 7);
                    set_color(4, 3);
                    printf("Pas la place / pas mer / trop loin");
                }
            }
            int indice_copie=0;
            for (int i =0; i<3; i++)
            {
                if (Plateau[x_d][y_d].creatures[i].type==-1)
                {
                    indice_copie=i;
                    break;
                }
            }
            Plateau[x_d][y_d].creatures[indice_copie] = *creature_source;
            *creature_source = creature_null;

            switch (type)
            {
            case 0:
                proie=action_serpent(Plateau, x_d, y_d);
                break;
            case 1:
                proie=action_requin(Plateau, x_d, y_d);
                break;
            case 2:
                proie=action_baleine(Plateau, x_d, y_d);
                break;
            }
            afficher_casee(x_d*5, y_d*3, Plateau[x_d][y_d], 0);
            afficher_casee(x_s*5, y_s*3, Plateau[x_s][y_s], 0);

            // L'actuelle destination devient la source du prochain deplacement
            x_s = x_d;
            y_s = y_d;
            creature_source = &Plateau[x_d][y_d].creatures[indice_copie];

            p_mouvement--;
        }
    }
}

void enelever_tuile(joueur *joueur, casee Plateau[13][13])
{
    int valide = 0;


    rectangle(65, 2, 45, 20, 0);
    gotoxy(70, 2);
    printf("Choisi une tuile a enlever!");

    int x_s, y_s;

    while (valide==0)
    {
        selection_case(Plateau, &x_s, &y_s);
        if ((Plateau[x_s][y_s].terre_ferme==1)&&(Plateau[x_s][y_s].tuile.type==montee_eaux))
        {
            valide = 1;
        }
        else
        {
            gotoxy(70, 15);
            printf("Pas valide.");
        }
    }
    casee copie1 = Plateau[x_s][y_s];
    Plateau[x_s][y_s].tuile=tuile_null;
    Plateau[x_s][y_s].terre_ferme=0;
    obtenir_carte(Plateau, copie1, joueur, x_s, y_s);
    montee_eaux = deter_montee_eaux(Plateau);
    afficher_casee(x_s*5, y_s*3, Plateau[x_s][y_s], 0);
}

void tour(joueur *joueur, casee Plateau[13][13])
{
    rectangle(65, 1, 60, 39, 0);
    gotoxy(66, 0);
    set_color(couleurs_equipe[(*joueur).equipe], 15);
    printf("TOUR DU JOUEUR %d", (*joueur).equipe);

    // ##############"" CARTES

    if (compter_cartes(*joueur) >= 1)
    {
        int i_carte;
        choisir_carte(*joueur, &i_carte);
        jouer_carte(Plateau, joueur, i_carte);
    }

    // ############ MOUVEMENTS

    int p_mouvement = 3;
    char *options[] = {"Deplacer un pion", "Deplacer un bateau"};
    int select_indice;

    while (p_mouvement > 0 && total_pion_couleur(Plateau, (*joueur).equipe)>0)
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

    // ############# ENLEVER TUILE
    enelever_tuile(joueur, Plateau);

    // ####### De creature
    de_creature(Plateau);

}
