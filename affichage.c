#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include "donnee.h"

int couleurs_equipe[4] = {4, 1, 2, 6};


void plein_ecran()
{
    keybd_event(VK_MENU, 0x38, 0, 0); // Appuie sur Alt
    keybd_event(VK_RETURN, 0x1c, 0, 0); // Appuie sur Entrée
    keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0); // Lache Entrée
    keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0); // Lache Alt

}

int get_input() {
    int key = getch();  // Récupère la première touche

    if (key == 224) {  // Si c'est un code spécial (comme une flèche)
        key = getch();  // Récupère la touche spéciale (flèche, etc.)
    }

    return key;  // Retourne le code de la touche
}


// Fonction pour déplacer le curseur à la position spécifiée (x, y)
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void set_color(WORD fg, WORD bg)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, (bg << 4) | fg);
}
void curseur_visible(int visible)
{
    CONSOLE_CURSOR_INFO cursorInfo;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = visible; // 0 = cacher, 1 = afficher
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}
void rectangle(int x, int y, int w, int h, int c)
{
    set_color(15, c);
    for (int i = 0; i<w; i++)
    {
        for (int j = 0; j<h; j++)
        {
            gotoxy(x+i, y+j);
            printf(" ");
        }
    }
}
void contour(int x, int y, int w, int h)
{
    set_color(15, 0);
    for (int i =0; i<=w-2; i++)
    {
        gotoxy(x+1+i, y);
        printf("─");
        gotoxy(x+1+i, y+h);
        printf("─");
    }
    for (int j = 0; j<=h-2; j++)
    {

        gotoxy(x, y+1+j);
        printf("│");
        gotoxy(x+w, y+1+j);
        printf("│");

    }
    gotoxy(x, y);
    printf("┌");
    gotoxy(x+w, y);
    printf("┐");
    gotoxy(x, y+h);
    printf("└");
    gotoxy(x+w, y+h);
    printf("┘");
}


void selection_menu(int x, int y, char *titre, char *options[], int num_options, int *selected_index) {
    int key = 0;
    *selected_index = 0;

    // Affichage initial du menu
    gotoxy(x, y);
    set_color(12, 2);
    printf("%s", titre);
    for (int i = 0; i < num_options; i++) {
        gotoxy(0 + x, i +y+1); // Déplace le curseur sur chaque ligne du menu
        if (i == *selected_index)
            printf("-> %s", options[i]);  // Affiche l'option sélectionnée avec la flèche
        else
            printf("   %s", options[i]);
    }

    while (1) {
        key = get_input();  // Récupère la touche pressée par l'utilisateur

        if (key == 72 && *selected_index > 0) {  // Flèche haut
            (*selected_index)--;  // Déplace la sélection vers le haut
        } else if (key == 80 && *selected_index < num_options - 1) {  // Flèche bas
            (*selected_index)++;  // Déplace la sélection vers le bas
        } else if (key == 13) {  // Touche Entrée
            break;  // Quitte la boucle lorsque l'utilisateur appuie sur Entrée
        }

        // Rafraîchit l'affichage en mettant à jour le menu sans effacer l'écran
        for (int i = 0; i < num_options; i++) {
            gotoxy(0 + x, i+y+1);  // Déplace le curseur à la position de la ligne
            if (i == *selected_index)
                printf("-> %s", options[i]);  // Affiche l'option sélectionnée avec la flèche
            else
                printf("   %s", options[i]);
        }
    }
}


void afficher_casee(int x, int y, casee case1)
{
    /* 5 x 3
    P1234  1 pion rouge, 2 bleu,
    SBR##
    #####
    0Noir 1BleuFoncé 2Vert 3Cyan 4Rouge 5Magenta 6JauneF
    7GrisC 10VertF 11CyanC 12RougeC 13MagentaC 14Jaune 15Blanc
    */
    int couleur_fond;
    if (case1.terre_ferme==0)   // mer
    {
        couleur_fond = 11;
    }
    else if (case1.tuile.type==0)     // plage
    {
        couleur_fond = 14; //Jaune
    }
    else if (case1.tuile.type==1)     //foret
    {
        couleur_fond = 10; // VertF
    }
    else if (case1.tuile.type==2)     //montagne
    {
        couleur_fond = 8; //Gris
    }
    rectangle(x, y, 5, 3, couleur_fond);
    set_color(0, couleur_fond);
    gotoxy(x, y);
    printf("P");
    // ROUGE:
    gotoxy(x+1, y);
    set_color(4, couleur_fond); //Rouge sur fond.
    if (compter_pions_couleur(case1, 0) == 10)
    {
        printf("X");
    }
    else if (compter_pions_couleur(case1, 0) != 0)
    {
        printf("%d", compter_pions_couleur(case1, 0));
    }
    // BLEU
    gotoxy(x+2, y);
    set_color(1, couleur_fond); // Bleu sur fond.
    if (compter_pions_couleur(case1, 1) == 10)
    {
        printf("X");
    }
    else if (compter_pions_couleur(case1, 1) != 0)
    {
        printf("%d", compter_pions_couleur(case1, 1));
    }
    // VERT
    gotoxy(x+3, y);
    set_color(2, couleur_fond); // Vert sur fond.
    if (compter_pions_couleur(case1, 2) == 10)
    {
        printf("X");
    }
    else if (compter_pions_couleur(case1, 2) != 0)
    {
        printf("%d", compter_pions_couleur(case1, 2));
    }
    // JAUNE
    gotoxy(x+4, y);
    set_color(6, couleur_fond); // JauneF
    if (compter_pions_couleur(case1, 3) == 10)
    {
        printf("X");
    }
    else if (compter_pions_couleur(case1, 3) != 0)
    {
        printf("%d", compter_pions_couleur(case1, 3));
    }

    // #################BATEAU ######################
    if (case1.bateau.equipe_leader!=-2) // CODE POUR BATEAU NON PRESENT, BATEAU_NULL
    {
        rectangle(x, y+2, 3, 1, 13);
        for (int i =0; i<=2; i++)
        {
            if (case1.bateau.pions[i].equipe!=-1)
            {
                gotoxy(x+i, y+2);
                set_color(couleurs_equipe[i], 13);
                printf("P");
            }
        }
    }
    // ################## CREATURES ################

    for (int i =0; i<3; i++)
    {
        gotoxy(x+i, y+1);
        // Serpent: rouge sur noir, Requin:Bleu sur noir, Baleine:Violet sur noir
        set_color(0, couleur_fond); // Noir sur fond

        switch (case1.creatures[i].type)
        {
        case 0:
            printf("S");
            break;
        case 1:
            printf("R");
            break;
        case 2:
            printf("B");
            break;
        case -1:
            break;
        default:
            break;
        }

    }

}


