#include "calcul.h"

int indice_max(int liste[], int taille)
{
    int max_index = 0;
    for (int i = 1; i < taille; i++) {
        if (liste[i] > liste[max_index]) {
            max_index = i;
        }
    }
    return max_index;
}


