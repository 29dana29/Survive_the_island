#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include "donnee.h"

int couleurs_equipe[4] = {4, 1, 2, 6};


void plein_ecran() {
    // Sauvegarde l'état de visibilité du curseur
    CONSOLE_CURSOR_INFO cursorInfo;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Récupère le handle de la console
    GetConsoleCursorInfo(hConsole, &cursorInfo); // Lit les infos du curseur
    int cursorVisible = cursorInfo.bVisible; // Stocke la visibilité actuelle

    // Simule Alt + Entrée pour basculer en plein écran
    keybd_event(VK_MENU, 0x38, 0, 0); // Appui Alt
    keybd_event(VK_RETURN, 0x1c, 0, 0); // Appui Entrée
    keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0); // Relâche Entrée
    keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0); // Relâche Alt

    // Pause pour laisser le mode plein écran s'activer
    Sleep(500); // Attente 500 ms

    // Restaure la visibilité du curseur
    GetConsoleCursorInfo(hConsole, &cursorInfo); // Relit les infos du curseur
    cursorInfo.bVisible = cursorVisible; // Rétablit l'état initial
    SetConsoleCursorInfo(hConsole, &cursorInfo); // Applique la modification
}



int get_input() {
    /* 72 Fleche Haut
       80 Fleche Bas
       75 Fleche Gauche
       77 Fleche Droite
       13 Entrée
       27 Échap */

    int key = getch(); // Récupère la première touche

    if (key == 224)    // Touche spéciale (ex : flèche)
        key = getch(); // Récupère le code réel

    if (key == 27)     // Échap
        ExitProcess(0); // Quitte immédiatement

    return key;        // Renvoie le code de la touche
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
    /*
    0 Noir 1 BleuFoncé 2 Vert 3 Cyan 4 Rouge 5 Magenta 6 JauneF 7 GrisC
    8 GrisClair 9 BleuClair 10 VertF 11 CyanC 12 RougeC 13 MagentaC 14 JauneClair 15 Blanc
    */

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


void selection_menu(int x, int y, char *options[], int num_options, int *selected_index) {
    int key = 0;
    *selected_index = 0;

    // Affichage initial du menu
    set_color(15, 0);
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


void afficher_casee(int x, int y, casee case1, int select) // select 0/1
{
    /* 5 x 3
    P1234  1 pion rouge, 2 bleu,
    SBR##
    PPP#X <- select (X)
    0 Noir 1 BleuFoncé 2 Vert 3 Cyan 4 Rouge 5 Magenta 6 JauneF 7 GrisC
    8 GrisClair 9 BleuClair 10 VertF 11 CyanC 12 RougeC 13 MagentaC 14 JauneClair 15 Blanc

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
    if (select==1) {
        gotoxy(x+4, y+2);
        set_color(0, 15);
        printf("X");
    }
    gotoxy(x+4, y+1);
    set_color(0, couleur_fond);
    if (case1.tuile.carte>=0) {
            printf("%d", case1.tuile.carte);

    }
    gotoxy(x, y);
    if (compter_pions_couleur(case1.pions, 0)+compter_pions_couleur(case1.pions, 1)+compter_pions_couleur(case1.pions, 2)+compter_pions_couleur(case1.pions, 3) != 0) {
       printf("P");
    }
    // ROUGE:
    gotoxy(x+1, y);
    set_color(4, couleur_fond); //Rouge sur fond.
    if (compter_pions_couleur(case1.pions, 0) == 10)
    {
        printf("X");
    }
    else if (compter_pions_couleur(case1.pions, 0) != 0)
    {
        printf("%d", compter_pions_couleur(case1.pions, 0));
    }
    // BLEU
    gotoxy(x+2, y);
    set_color(1, couleur_fond); // Bleu sur fond.
    if (compter_pions_couleur(case1.pions, 1) == 10)
    {
        printf("X");
    }
    else if (compter_pions_couleur(case1.pions, 1) != 0)
    {
        printf("%d", compter_pions_couleur(case1.pions, 1));
    }
    // VERT
    gotoxy(x+3, y);
    set_color(2, couleur_fond); // Vert sur fond.
    if (compter_pions_couleur(case1.pions, 2) == 10)
    {
        printf("X");
    }
    else if (compter_pions_couleur(case1.pions, 2) != 0)
    {
        printf("%d", compter_pions_couleur(case1.pions, 2));
    }
    // JAUNE
    gotoxy(x+4, y);
    set_color(6, couleur_fond); // JauneF
    if (compter_pions_couleur(case1.pions, 3) == 10)
    {
        printf("X");
    }
    else if (compter_pions_couleur(case1.pions, 3) != 0)
    {
        printf("%d", compter_pions_couleur(case1.pions, 3));
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
                set_color(couleurs_equipe[case1.bateau.pions[i].equipe], 13);
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


void selection_case(casee Plateau[13][13], int *x_s, int *y_s) {
    //Proto:
    // void afficher_casee(int x, int y, casee case1, int select)  select: 0/1


    //P1234  1 pion rouge, 2 bleu,
    //SBR##
    //BBB#0  <-- indicateur de selection ici, type X en noir sur blanc

    /*
    72 pour flèche haut
    80 pour flèche bas
    75 pour flèche gauche
    77 pour flèche droite
    13 pour Entrée
    */

    *x_s = 6; // 0->12
    *y_s = 6; // 0->12
    afficher_casee(*x_s*5, *y_s*3, Plateau[*x_s][*y_s], 1);
    while (1) {
        int key = get_input();
        if (key==72&&*y_s>0) { // Fleche haut + on est pas tout en haut
            afficher_casee(*x_s*5, *y_s*3, Plateau[*x_s][*y_s], 0);
            *y_s-=1;
            afficher_casee(*x_s*5, *y_s*3, Plateau[*x_s][*y_s], 1);
        } else if (key== 80 && *y_s<12) { //Fleche bas + on est pas tout en bas
            afficher_casee(*x_s*5, *y_s*3, Plateau[*x_s][*y_s], 0);
            *y_s+=1;
            afficher_casee(*x_s*5, *y_s*3, Plateau[*x_s][*y_s], 1);
        } else if (key==75 && *x_s>0) { // Fleche gauche + on est pas tout a droite
            afficher_casee(*x_s*5, *y_s*3, Plateau[*x_s][*y_s], 0);
            *x_s-=1;
            afficher_casee(*x_s*5, *y_s*3, Plateau[*x_s][*y_s], 1);
        } else if (key==77 && *x_s<12) { // Fleche droite + on est pas tout a droite
            afficher_casee(*x_s*5, *y_s*3, Plateau[*x_s][*y_s], 0);
            *x_s+=1;
            afficher_casee(*x_s*5, *y_s*3, Plateau[*x_s][*y_s], 1);
        } else if (key==13) { // Entrée
            afficher_casee(*x_s*5, *y_s*3, Plateau[*x_s][*y_s], 0); //Enleve le tick de sélection de la case sélectinnée
            break; //Quitte la boucle, on garde donc la dernière case sélectionnée

        }
    }

}
