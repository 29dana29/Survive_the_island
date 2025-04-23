#ifndef DONNEE_H_INCLUDED
#define DONNEE_H_INCLUDED
typedef struct {
    int equipe; // 0, 1, 2, 3
    int numero; //points de 1 -> 6
    char nom; // "A", "B"  pour reconnaitre sur le plateau
} pion;

typedef struct {
    pion pions[3];
    int equipe_leader; // 0  FONCTION determiner_leader
} bateau;
typedef struct {
    int type; //0->2
} creature;
typedef struct{
    int type; // 0: plage; 1: foret; 2: Montagne
    int carte; // 0-> 11 / 1-> 12
} tuile;
typedef struct {
    int terre_ferme; //0 : mer     1 : terre ferme
    creature creatures[20];
    bateau bateau;
    tuile tuile;
    pion pions[40];

} casee;


typedef struct {
    int equipe; // 0, 1, 2, 3
    int points; // somme de pions sortis * leur numéro respectif
    int cartes [40]; // PEUT ETRE MODIFIE EN STRUCT MAIS PAS FORCEMENT NECESSAIRE
} joueur;


int determiner_leader(bateau bateau);

#endif // DONNEE_H_INCLUDED
