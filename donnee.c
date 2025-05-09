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

int compter_pions_couleur(pion pions[], int equipe, int n)   // equipe=4: TOUTES LES EQUIPES
{
    int count = 0;
    for (int i =0; i<n; i++)
    {
        if (pions[i].equipe == equipe)
        {
            count+=1;
        }
        else if ((equipe==4)&&(pions[i].equipe!=-1))
        {
            count+=1;
        }
    }
    return count;
}

int total_pion_couleur(casee Plateau[13][13], int equipe) {
int somme = 0;
for (int i = 0; i<13; i++) {
    for (int j =0; j<13; j++) {
        somme += compter_pions_couleur(Plateau[i][j].pions, equipe, 40);
        somme += compter_pions_couleur(Plateau[i][j].bateau.pions, equipe, 3);
    }
}
return somme;
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

int compter_creatures(casee case1, int type) { // type=3: Toute creature
    // compte forcement dans une case donc forcement 3 emplacements
    int count = 0;
    for (int i =0; i<3; i++) {
        if (case1.creatures[i].type==type || (type==3 && case1.creatures[i].type!=-1)) {
            count ++;
        }
    }
    return count;
}
int compter_creatures_plateau(casee Plateau[13][13], int type) { // type ==3: Toute creature
    int count =0;
    for (int i = 0; i<13; i++) {
        for (int j = 0; j <13; j++) {
            count += compter_creatures(Plateau[i][j], type);
        }
    }
    return count;
}

int deter_montee_eaux(casee Plateau[13][13]) {
    int montee = 2; // set au max
    for (int i=0; i<13; i++) {
        for (int j = 0; j<13; j++) {
            if (montee==2&&Plateau[i][j].tuile.type==1) { // Foret
                montee = 1;
            } else if (Plateau[i][j].tuile.type==0) {
                montee = 0;
            }
        }
    }
    return montee;
}
