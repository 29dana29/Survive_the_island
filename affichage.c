#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "donnee.h"
#include "affichage.h"

#define MAX_MESSAGES 10               // Nombre maximum de messages dans la file d'attente
#define MESSAGE_LENGTH 60             // Longueur maximale d'un message
#define MESSAGE_X 66                  // Coordonnée X pour la zone d'affichage des messages
#define MESSAGE_Y 20                  // Coordonnée Y pour la zone d'affichage des messages

int couleurs_equipe[4] = {4, 1, 2, 6};
extern casee Plateau[13][13];

// Définition d'une structure pour représenter un message
typedef struct
{
    char text[MESSAGE_LENGTH + 1];    // Texte du message (60 caractères max + caractère de fin '\0')
    int couleur_texte;                // Couleur du texte (avant-plan)
} Message;






void debug_afficher_pions(casee Plateau[13][13])
{
    for (int i = 0; i < 13; i++)
    {
        for (int j = 0; j < 13; j++)
        {
            for (int k = 0; k < 40; k++)
            {
                if (Plateau[i][j].pions[k].equipe != -1)
                {
                    printf("Pion trouve a [%d][%d] dans Plateau : equipe = %d\n", i, j, Plateau[i][j].pions[k].equipe);
                }
            }
            for (int k = 0; k < 3; k++)
            {
                if (Plateau[i][j].bateau.pions[k].equipe != -1)
                {
                    printf("Pion trouve a [%d][%d] dans Bateau : equipe = %d\n", i, j, Plateau[i][j].bateau.pions[k].equipe);
                }
            }
        }
    }
}


void plein_ecran()
{
    // Sauvegarde l'etat de visibilite du curseur
    CONSOLE_CURSOR_INFO cursorInfo;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Recupere le handle de la console
    GetConsoleCursorInfo(hConsole, &cursorInfo); // Lit les infos du curseur
    int cursorVisible = cursorInfo.bVisible; // Stocke la visibilite actuelle

    // Simule Alt + Entree pour basculer en plein ecran
    keybd_event(VK_MENU, 0x38, 0, 0); // Appui Alt
    keybd_event(VK_RETURN, 0x1c, 0, 0); // Appui Entree
    keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0); // Relâche Entree
    keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0); // Relâche Alt

    // Pause pour laisser le mode plein ecran s'activer
    Sleep(500); // Attente 500 ms

    // Restaure la visibilite du curseur
    GetConsoleCursorInfo(hConsole, &cursorInfo); // Relit les infos du curseur
    cursorInfo.bVisible = cursorVisible; // Retablit l'etat initial
    SetConsoleCursorInfo(hConsole, &cursorInfo); // Applique la modification
}



int get_input()
{
    /* 72 Fleche Haut
       80 Fleche Bas
       75 Fleche Gauche
       77 Fleche Droite
       13 Entree
       27 Échap */

    int key = getch(); // Recupere la premiere touche

    if (key == 224)     // Touche speciale (ex : fleche)
    {
        key = getch();
    } // Recupere le code reel

    if (key == 27)      // Échap
    {
        exit(0);
    }// Quitte immediatement

    return key;        // Renvoie le code de la touche
}



// Fonction pour deplacer le curseur a la position specifiee (x, y)
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
    0 Noir 1 BleuFonce 2 Vert 3 Cyan 4 Rouge 5 Magenta 6 JauneF 7 GrisC
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

Message messageQueue[MAX_MESSAGES];   // File d'attente pour stocker les messages
int messageCount = 0;                 // Nombre actuel de messages dans la file d'attente

// Fonction pour afficher tous les messages dans la file d'attente
void afficher_messages()
{
    // Effacer toute la zone d'affichage des messages
    rectangle(MESSAGE_X, MESSAGE_Y, MESSAGE_LENGTH, MAX_MESSAGES, NOIR);
    contour(MESSAGE_X-1, MESSAGE_Y-1, MESSAGE_LENGTH+2, MAX_MESSAGES+2);
    // Afficher chaque message dans la file d'attente
    for (int i = 0; i < messageCount; i++)
    {
        gotoxy(MESSAGE_X, MESSAGE_Y + i); // Positionner le curseur pour chaque ligne de message
        set_color(messageQueue[i].couleur_texte, NOIR); // Définir la couleur du texte avec un fond noir
        printf("%s", messageQueue[i].text); // Afficher le texte du message
    }

    // Réinitialiser la couleur par défaut (blanc sur fond noir)
    set_color(BLANC, NOIR);
}

// Fonction pour ajouter un nouveau message dans la file d'attente
void nouveau_message(const char *message, int couleur_texte)
{
    // Si la file d'attente est pleine, supprimer le message le plus ancien
    if (messageCount == MAX_MESSAGES)
    {
        for (int i = 1; i < MAX_MESSAGES; i++)
        {
            messageQueue[i - 1] = messageQueue[i];
        }
        messageCount--;
    }

    // Ajouter le nouveau message à la fin de la file d'attente
    strncpy(messageQueue[messageCount].text, message, MESSAGE_LENGTH);
    messageQueue[messageCount].text[MESSAGE_LENGTH] = '\0'; // Assurer la terminaison nulle
    messageQueue[messageCount].couleur_texte = couleur_texte;
    messageCount++;

    // Mettre à jour l'affichage
    afficher_messages();
}




void selection_menu(int x, int y, char *options[], int num_options, int *selected_index)
{
    int key = 0;
    *selected_index = 0;

    // Affichage initial du menu
    set_color(15, 0);
    for (int i = 0; i < num_options; i++)
    {
        gotoxy(0 + x, i +y+1); // Deplace le curseur sur chaque ligne du menu
        if (i == *selected_index)
            printf("-> %s", options[i]);  // Affiche l'option selectionnee avec la fleche
        else
            printf("   %s", options[i]);
    }

    while (1)
    {
        key = get_input();  // Recupere la touche pressee par l'utilisateur

        if (key == 72 && *selected_index > 0)    // Fleche haut
        {
            (*selected_index)--;  // Deplace la selection vers le haut
        }
        else if (key == 80 && *selected_index < num_options - 1)      // Fleche bas
        {
            (*selected_index)++;  // Deplace la selection vers le bas
        }
        else if (key == 13)      // Touche Entree
        {
            set_color(VERT, NOIR);
            gotoxy(0 + x, *selected_index+y+1);
            printf("   %s", options[*selected_index]);
            break;  // Quitte la boucle lorsque l'utilisateur appuie sur Entree
        }

        // Rafraîchit l'affichage en mettant a jour le menu sans effacer l'ecran
        for (int i = 0; i < num_options; i++)
        {
            gotoxy(0 + x, i+y+1);  // Deplace le curseur a la position de la ligne
            if (i == *selected_index)
                printf("-> %s", options[i]);  // Affiche l'option selectionnee avec la fleche
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
    0 Noir 1 BleuFonce 2 Vert 3 Cyan 4 Rouge 5 Magenta 6 JauneF 7 GrisC
    8 GrisClair 9 BleuClair 10 VertF 11 CyanC 12 RougeC 13 MagentaC 14 JauneClair 15 Blanc

    */
    int couleur_fond;
    if ((x==5*12||x==0)&&(y==12*3||y==0))   // Si on est dans un coin, couleur légèrement différente
    {
        couleur_fond = 14; //JAUne sable
    }
    else if (case1.terre_ferme==0)     // mer
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
    if (select==1)
    {
        gotoxy(x+4, y+2);
        set_color(0, 15);
        printf("X");
    }
    set_color(0, couleur_fond);

    gotoxy(x, y);
    if (compter_pions_couleur(case1.pions, 0, 40)+compter_pions_couleur(case1.pions, 1, 40)+compter_pions_couleur(case1.pions, 2, 40)+compter_pions_couleur(case1.pions, 3, 40) != 0)
    {
        printf("P");
    }
    // ROUGE:
    gotoxy(x+1, y);
    set_color(4, couleur_fond); //Rouge sur fond.
    if (compter_pions_couleur(case1.pions, 0, 40) == 10)
    {
        printf("X");
    }
    else if (compter_pions_couleur(case1.pions, 0, 40) != 0)
    {
        printf("%d", compter_pions_couleur(case1.pions, 0, 40));
    }
    // BLEU
    gotoxy(x+2, y);
    set_color(1, couleur_fond); // Bleu sur fond.
    if (compter_pions_couleur(case1.pions, 1, 40) == 10)
    {
        printf("X");
    }
    else if (compter_pions_couleur(case1.pions, 1, 40) != 0)
    {
        printf("%d", compter_pions_couleur(case1.pions, 1, 40));
    }
    // VERT
    gotoxy(x+3, y);
    set_color(2, couleur_fond); // Vert sur fond.
    if (compter_pions_couleur(case1.pions, 2, 40) == 10)
    {
        printf("X");
    }
    else if (compter_pions_couleur(case1.pions, 2, 40) != 0)
    {
        printf("%d", compter_pions_couleur(case1.pions, 2, 40));
    }
    // JAUNE
    gotoxy(x+4, y);
    set_color(6, couleur_fond); // JauneF
    if (compter_pions_couleur(case1.pions, 3, 40) == 10)
    {
        printf("X");
    }
    else if (compter_pions_couleur(case1.pions, 3, 40) != 0)
    {
        printf("%d", compter_pions_couleur(case1.pions, 3, 40));
    }

    // #################BATEAU ######################
    if (case1.bateau.equipe_leader!=-2) // CODE POUR BATEAU NON PRESENT, BATEAU_NULL
    {
        rectangle(x, y+2, 3, 1, 7);
        for (int i =0; i<=2; i++)
        {
            if (case1.bateau.pions[i].equipe!=-1)
            {
                gotoxy(x+i, y+2);
                set_color(couleurs_equipe[case1.bateau.pions[i].equipe], 7);
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


void selection_case(casee Plateau[13][13], int *x_s, int *y_s)
{
    //Proto:
    // void afficher_casee(int x, int y, casee case1, int select)  select: 0/1


    //P1234  1 pion rouge, 2 bleu,
    //SBR##
    //BBB#0  <-- indicateur de selection ici, type X en noir sur blanc

    /*
    72 pour fleche haut
    80 pour fleche bas
    75 pour fleche gauche
    77 pour fleche droite
    13 pour Entree
    */

    *x_s = 6; // 0->12
    *y_s = 6; // 0->12
    afficher_casee(*x_s*5, *y_s*3, Plateau[*x_s][*y_s], 1);
    while (1)
    {
        int key = get_input();
        if (key==72&&*y_s>0)   // Fleche haut + on est pas tout en haut
        {
            afficher_casee(*x_s*5, *y_s*3, Plateau[*x_s][*y_s], 0);
            *y_s-=1;
            afficher_casee(*x_s*5, *y_s*3, Plateau[*x_s][*y_s], 1);
        }
        else if (key== 80 && *y_s<12)     //Fleche bas + on est pas tout en bas
        {
            afficher_casee(*x_s*5, *y_s*3, Plateau[*x_s][*y_s], 0);
            *y_s+=1;
            afficher_casee(*x_s*5, *y_s*3, Plateau[*x_s][*y_s], 1);
        }
        else if (key==75 && *x_s>0)     // Fleche gauche + on est pas tout a droite
        {
            afficher_casee(*x_s*5, *y_s*3, Plateau[*x_s][*y_s], 0);
            *x_s-=1;
            afficher_casee(*x_s*5, *y_s*3, Plateau[*x_s][*y_s], 1);
        }
        else if (key==77 && *x_s<12)     // Fleche droite + on est pas tout a droite
        {
            afficher_casee(*x_s*5, *y_s*3, Plateau[*x_s][*y_s], 0);
            *x_s+=1;
            afficher_casee(*x_s*5, *y_s*3, Plateau[*x_s][*y_s], 1);
        }
        else if (key==13)     // Entree
        {
            afficher_casee(*x_s*5, *y_s*3, Plateau[*x_s][*y_s], 0); //Enleve le tick de selection de la case selectinnee
            break; //Quitte la boucle, on garde donc la derniere case selectionnee

        }
    }

}
