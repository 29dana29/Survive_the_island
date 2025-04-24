#include <windows.h>
#include <stdio.h>
#include "donnee.h"
void plein_ecran() {
    keybd_event(VK_MENU, 0x38, 0, 0); // Appuie sur Alt
    keybd_event(VK_RETURN, 0x1c, 0, 0); // Appuie sur Entrée
    keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0); // Lache Entrée
    keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0); // Lache Alt

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
    printf("%d", case1.tuile.type);
}
