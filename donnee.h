#ifndef DONNEE_H_INCLUDED
#define DONNEE_H_INCLUDED


typedef struct {
    int equipe; // 0 Rouge, 1 Bleu, 2 Vert, 3 Jaune
    int numero; //points de 1 -> 5
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
    creature creatures[3];
    bateau bateau;
    tuile tuile;
    pion pions[40];

} casee;


typedef struct {
    int equipe; // 0 Rouge, 1 Bleu, 2 Vert, 3 Jaune
    int points; // somme de pions sortis * leur numéro respectif
    int cartes [40]; // PEUT ETRE MODIFIE EN STRUCT MAIS PAS FORCEMENT NECESSAIRE
} joueur;

extern pion pion_null;
extern bateau bateau_null;
extern creature creature_null;
extern tuile tuile_null;
extern casee case_null;
extern joueur joueur_null;



void initialiser_nulls();
int determiner_leader(bateau bateau);
int compter_pions_couleur(casee case1, int couleur);
#endif // DONNEE_H_INCLUDED
