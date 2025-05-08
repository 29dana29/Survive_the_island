#include <stdio.h>
#include <windows.h>
#include "donnee.h"
#include "calcul.h"
int determiner_leader(bateau bateau)
{
    if (bateau.equipe_leader != -2)
    {
        int scores[4] = {0, 0, 0, 0};
        for (int i = 0; i < 3; i++)
        {
            if (bateau.pions[i].equipe != -1)
            {
                scores[bateau.pions[i].equipe]++;
            }
        }

        int max = 0, count = 0, leader = -1;
        for (int i = 0; i < 4; i++)
        {
            if (scores[i] > max)
            {
                max = scores[i];
                leader = i;
                count = 1;
            }
            else if (scores[i] == max && max > 0)
            {
                count++;
            }
        }

        if (count == 1)
            return leader;
        else
            return -1; // tie
    }
    else
    {
        return -2;
    }
}

int compter_pions_couleur(pion pions[], int equipe)   // equipe=4: TOUTES LES EQUIPES
{
    int n = 0;
    for (int i =0; i<40; i++)
    {
        if (pions[i].equipe == equipe)
        {
            n+=1;
        }
        else if ((equipe==4)&&(pions[i].equipe!=-1))
        {
            n+=1;
        }
    }
    return n;
}

int compter_cartes(joueur j)
{
    int count = 0;
    for (int i = 0; i < 40; i++)
    {
        if (j.cartes[i] != -1)
        {
            count++;
        }
    }
    return count;
}
