#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "affichage.h"
#include "donnee.h"
#include "plateau.h"
int main()
{

    SetConsoleOutputCP(CP_UTF8);
    plein_ecran();
    system("cls");
    for (int i =0; i<=30; i++) {
        printf("%d\n", i);
    }

    /*contour(10, 10, 10, 10);
    int age;
    gotoxy(11, 11);
    printf("AGE:");
    gotoxy(11, 12);
    scanf("%d", age);*/

    getchar();
    return 0;
}
