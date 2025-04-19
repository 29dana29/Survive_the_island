#include <windows.h>
#include <stdio.h>

void plein_ecran_total() {
    HWND hwnd = GetConsoleWindow();

    // Supprimer bordures, barre de titre, bouton X
    LONG style = GetWindowLong(hwnd, GWL_STYLE);
    style &= ~(WS_CAPTION | WS_THICKFRAME);
    SetWindowLong(hwnd, GWL_STYLE, style);

    // Supprimer la barre de menu
    LONG exStyle = GetWindowLong(hwnd, GWL_EXSTYLE);
    exStyle &= ~(WS_EX_DLGMODALFRAME | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE);
    SetWindowLong(hwnd, GWL_EXSTYLE, exStyle);

    // Redimensionner pour couvrir tout l'écran
    SetWindowPos(hwnd, HWND_TOP,
        0, 0,
        GetSystemMetrics(SM_CXSCREEN),
        GetSystemMetrics(SM_CYSCREEN),
        SWP_NOZORDER | SWP_FRAMECHANGED);
}


void gotoxy(int x, int y) {
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void set_color(WORD fg, WORD bg) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, (bg << 4) | fg);
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
