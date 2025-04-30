#include <stdio.h>
#include <windows.h>
#include "donnee.h"
#include "calcul.h"
int determiner_leader(bateau bateau)
{
    int scores[4] = {0, 0, 0, 0};
    for (int i = 0; i<4; i++) {
        scores[bateau.pions[i].equipe] += 1;
    }
    if (scores[0] == scores[1] &&
    scores[1] == scores[2] &&
    scores[2] == scores[3])
    {
        return -1;
    } else
    {
       return indice_max(scores, 4);
    }
}
int compter_pions_couleur(casee case1, int equipe) {
    int n = 0;
    for (int i =0; i<40; i++) {
        if (case1.pions[i].equipe == equipe+1) {
            n+=1;
        }
    }
    return n;
}
