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
    // -2 : pas de bateau -1:Personne leader 0->3:le leader est...
} bateau;
typedef struct {
    int type; //0->2 0:Serpent, 1:Requin, 2:Baleine
} creature;
typedef struct{
    int type; // 0: plage; 1: foret; 2: Montagne
    int carte; // 0-> 9 / 1-> 10
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




int determiner_leader(bateau bateau);
int compter_pions_couleur(casee case1, int couleur);
#endif // DONNEE_H_INCLUDED
