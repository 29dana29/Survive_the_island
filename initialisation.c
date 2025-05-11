#include "initialisation.h"
#include "donnee.h"
#include <stdlib.h>
#include "affichage.h"
#include <stdio.h>


pion pion_null;
bateau bateau_null;
creature creature_null;
tuile tuile_null;
casee case_null;
joueur joueur_null;
extern int couleurs_equipe[4];
int socle[13][13] =   // LISTE DE COLONNES
{
    //
    {0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,0,0,0,0},
    {0,0,0,1,1,1,1,1,1,0,0,0,0},
    {0,0,0,1,1,1,1,1,1,1,0,0,0},
    {0,0,0,1,1,1,0,1,1,1,0,0,0},
    {0,0,0,1,1,1,1,1,1,1,0,0,0},
    {0,0,0,0,1,1,1,1,1,0,0,0,0},
    {0,0,0,0,1,1,1,1,0,0,0,0,0},
    {0,0,0,0,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0}
};

int valeurs_pions[] = {1, 1, 2, 2, 3, 3, 4, 4, 5, 5};

tuile deck_tuile[40] =
{
    {0, 0},
    {0, 0},
    {0, 0},
    {1, 0},
    {1, 0},
    {1, 0},
    {0, 1},
    {0, 1},
    {0, 1},
    {1, 1},
    {1, 1},
    {0, 2},
    {1, 2},
    {1, 2},
    {1, 2},
    {1, 3},
    {1, 3},
    {2, 3},
    {2, 3},
    {2, 3},
    {2, 3},
    {2, 4},
    {2, 4},
    {2, 4},
    {2, 4},
    {0, 5},
    {0, 5},
    {0, 5},
    {1, 5},
    {0, 6},
    {0, 6},
    {1, 7},
    {1, 7},
    {0, 8},
    {0, 8},
    {1, 8},
    {1, 8},
    {0, 9},
    {0, 9},
    {1, 9}
};

void initialiser_nulls()
{
    pion_null.equipe=-1;
    strcpy(pion_null.nom, "Z");
    pion_null.numero=-1;
    for (int i =0; i<3; i++)
    {
        bateau_null.pions[i] = pion_null;
    }
    bateau_null.equipe_leader = -2;
    creature_null.type=-1;
    tuile_null.type=-1;
    tuile_null.carte=-1;
    case_null.bateau=bateau_null;
    for (int i = 0; i<3; i++)
    {
        case_null.creatures[i] = creature_null;
    }
    for (int i =0; i<40; i++)
    {
        case_null.pions[i] = pion_null;
    }
    case_null.terre_ferme=0;
    case_null.tuile=tuile_null;
    joueur_null.equipe=-1;
    joueur_null.points=-1;
    for (int i = 0; i<40; i++)
    {
        joueur_null.cartes[i] = -1;
    }
}

void initialiser_plateau(casee Plateau[13][13], casee casenulle)
{
    for (int i =0; i<13; i++)
    {
        for (int j=0; j<13; j++)
        {
            Plateau[i][j] = casenulle;
        }
    }

}
void placer_serpents(casee Plateau[13][13])
{
    Plateau[1][1].creatures[0].type = 0; // Hard code, placement des serpents
    Plateau[1][11].creatures[0].type = 0;
    Plateau[11][1].creatures[0].type = 0;
    Plateau[11][11].creatures[0].type = 0;
    Plateau[6][6].creatures[0].type = 0;

}

void melanger_tuiles(tuile tuiles[40])
{
    for (int i = 39; i > 0; i--)   // On boucle de la fin du tableau vers le debut
    {
        int j = rand() % (i + 1); // Choisit un indice aleatoire entre 0 et i inclus
        tuile tmp = tuiles[i];    // Stocke temporairement la tuile a l'indice i
        tuiles[i] = tuiles[j];    // Remplace la tuile a l'indice i par celle a l'indice j
        tuiles[j] = tmp;          // Place la tuile initialement a l'indice i a la position j
    }
}

void placer_tuiles(casee Plateau[13][13], tuile tuiles[40], int socle[13][13])
{
    int k = 0; // compteur de tuiles placees
    for (int i = 0; i < 13; i++)    // Correction de la boucle
    {
        for (int j = 0; j < 13; j++)
        {
            if (socle[i][j] == 1)
            {
                Plateau[i][j].tuile = tuiles[k];  // On place la tuile
                Plateau[i][j].terre_ferme = 1;
                k++;  // Incrementer le compteur de tuiles
            }
        }
    }
}

void initialiser_joueurs(joueur joueurs[4], int *n_joueurs)
{
    for (int i = 0; i<4; i++)   //
    {
        joueurs[i] = joueur_null;
    }
    char *equipes[4] = {"Rouge", "Bleu", "Vert", "Jaune"};
    int selected;
    char *options[] = {"2 joueurs", "3 joueurs", "4 joueurs"};

    gotoxy(75, 3);
    set_color(15, 0);
    printf("Combien de joueurs ?");
    selection_menu(75, 5, options, 3, &selected);

    rectangle(75, 3, 20, 6, 0);  // Nettoie la zone du menu (titre + choix)

    *n_joueurs = selected + 2;

    for (int i = 0; i < *n_joueurs; i++)
    {
        joueurs[i].equipe = i;
        joueurs[i].points = 0;
        gotoxy(75, 5 + i);
        printf("Joueur %d : %s", i + 1, equipes[i]);
    }
}

void placer_pions(casee Plateau[13][13], joueur joueurs[], int n_joueurs)
{

    char * noms_pions[10]= {"A","B","C","D","E","F","G","H","I","J"};
    for (int i = 0; i<2; i++)
    {
        int val_pion = (i+2)/2; //Valeur Formule pas piquee des hannetons grace a division euclid, qui permet de veski toute une liste de pions
        for (int j = 0; j<n_joueurs; j++)
        {

            pion pion_actuel;
            pion_actuel.equipe=j;

            strcpy(pion_actuel.nom, noms_pions[i]);

            pion_actuel.numero=val_pion;
            gotoxy(13*5, 2);
            set_color(couleurs_equipe[j], 0);
            printf("JOUEUR %d: Place le pion %s de valeur %d", j, noms_pions[i], val_pion);
            int x_pion, y_pion;

            do
            {
                selection_case(Plateau, &x_pion, &y_pion);
                if (Plateau[x_pion][y_pion].terre_ferme!=1 || Plateau[x_pion][y_pion].pions[0].equipe!=-1)
                {
                    nouveau_message("Case invalide", ROUGE);
                }
            }
            while (Plateau[x_pion][y_pion].terre_ferme!=1 || Plateau[x_pion][y_pion].pions[0].equipe!=-1);
            Plateau[x_pion][y_pion].pions[0] = pion_actuel;
            afficher_casee(x_pion*5, y_pion*3, Plateau[x_pion][y_pion], 0);

        }
    }
}

void placer_bateaux(casee Plateau[13][13], joueur joueurs[], int n_joueurs)
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < n_joueurs; j++)
        {
            bateau bateau_actuel = bateau_null;
            bateau_actuel.equipe_leader = -1; // -1 = aucun capitaine, -2 = vide

            int x_bateau, y_bateau;
            gotoxy(13 * 5, 2);
            set_color(15, 0);
            printf("                                            ");
            gotoxy(13 * 5, 2);

            set_color(couleurs_equipe[j], 7);

            printf("JOUEUR %d: Selectionne ou placer un bateau", j);
            selection_case(Plateau, &x_bateau, &y_bateau);
            while ((Plateau[x_bateau][y_bateau].bateau.equipe_leader!=-2)||   // Si il y a deja un bateau
                    (Plateau[x_bateau][y_bateau].terre_ferme==1) // check que on est sur la terre ferme
                    ||(Plateau[x_bateau][y_bateau].creatures[0].type!=-1) // check que il y a une creature la
                    ||!( // Check que aucune case asdjacente n'est de la terre ferme
                        (Plateau[x_bateau+1][y_bateau+1].terre_ferme==1)
                        ||(Plateau[x_bateau][y_bateau+1].terre_ferme==1)
                        ||(Plateau[x_bateau-1][y_bateau+1].terre_ferme==1)
                        ||(Plateau[x_bateau-1][y_bateau].terre_ferme==1)
                        ||(Plateau[x_bateau-1][y_bateau-1].terre_ferme==1)
                        ||(Plateau[x_bateau][y_bateau-1].terre_ferme==1)
                        ||(Plateau[x_bateau+1][y_bateau-1].terre_ferme==1)
                        ||(Plateau[x_bateau+1][y_bateau].terre_ferme==1)
                    )
                  )
            {
                nouveau_message("Case invalide!", ROUGE);
                selection_case(Plateau, &x_bateau, &y_bateau);

            }

            Plateau[x_bateau][y_bateau].bateau = bateau_actuel;
            afficher_casee(x_bateau*5, y_bateau*3, Plateau[x_bateau][y_bateau], 0);
        }
    }
}

