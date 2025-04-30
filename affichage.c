#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include "donnee.h"
void plein_ecran() {
    keybd_event(VK_MENU, 0x38, 0, 0); // Appuie sur Alt
    keybd_event(VK_RETURN, 0x1c, 0, 0); // Appuie sur Entrée
    keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0); // Lache Entrée
    keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0); // Lache Alt

}
int attendre_input()
{
    /*
    Flèche haut : 72
    Flèche bas : 80
    Flèche gauche : 75
    Flèche droite : 77
    */
    char ch = getch();  // Lire la touche
    return (unsigned char)ch;  // Retourne la valeur numérique du caractère
}

void gotoxy(int x, int y) {
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void set_color(WORD fg, WORD bg) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, (bg << 4) | fg);
}
void curseur_visible(int visible) {
    CONSOLE_CURSOR_INFO cursorInfo;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = visible; // 0 = cacher, 1 = afficher
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}
void rectangle(int x, int y, int w, int h, int c)
{
    set_color(15, c);
    for (int i = 0; i<w; i++){
        for (int j = 0; j<h; j++) {
            gotoxy(x+i, y+j);
            printf(" ");
        }
    }
}
void contour(int x, int y, int w, int h)
{
    set_color(15, 0);
    for (int i =0; i<=w-2; i++) {
        gotoxy(x+1+i, y);
        printf("─");
        gotoxy(x+1+i, y+h);
        printf("─");
    }
    for (int j = 0; j<=h-2; j++) {

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

void afficher_casee(int x, int y, casee case1)
{
    /* 5 x 3
    P1234  1 pion rouge, 2 bleu,
    #####
    #####
    0Noir 1BleuFoncé 2Vert 3Cyan 4Rouge 5Magenta 6JauneF
    7GrisC 10VertF 11CyanC 12RougeC 13MagentaC 14Jaune 15Blanc
    */
    int couleur_fond;
    if (case1.terre_ferme==0) { // mer
        couleur_fond = 1;
    } else if (case1.tuile.type==0) { // plage
        couleur_fond = 14;
    } else if (case1.tuile.type==1) { //foret
        couleur_fond = 2;
    } else if (case1.tuile.type==2) { //montagne
        couleur_fond = 8;
    }
    rectangle(x, y, 5, 3, couleur_fond);
    set_color(15, couleur_fond);
    gotoxy(x, y);
    printf("P");
    // ROUGE:
    gotoxy(x+1, y);
    set_color(4, couleur_fond); //Rouge sur fond.
    if (compter_pions_couleur(case1, 0) == 10) {
        printf("X");
    } else {
        printf("%d", compter_pions_couleur(case1, 0));
    }
    //BLEU
    gotoxy(x+2, y);
    set_color(1, couleur_fond);

}
