#include <stdio.h>
#include <stdlib.h>
#include "affichage.h"
#include <windows.h>

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    system("cls");
    plein_ecran();
    for (int i =0; i<=3; i++) {
        printf("%d\n", i);
    }
    //contour(10, 10, 10, 10);
    getchar();
    return 0;
}
