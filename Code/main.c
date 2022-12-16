//mainc.c

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Structure d'une cellule sur un plateau de jeu :
//Attributs : - Position (x,y)
//            - Type ( Forme T, L, I) (Croisement, Tournant, Droit)
//            - Orientation (1,2,3,4)
//            - Compatibilité(1,2,3,4) (1: haut, 2: droite, 3: bas, 4: gauche)
//            - Mobilité (True, False) (True: la cellule peut bouger, False: la cellule ne peut pas bouger)
//            - Trésor (True, False) (True: la cellule contient un trésor, False: la cellule ne contient pas de trésor)
//            - Type_trésor (24 types de trésors) (1: trésor de type 1, 2: trésor de type 2, etc...)

//mobilité et trésor doivent être des booléens
//create 3 structures for each type of cell
//type T:
typedef struct cellule{
    int x;
    int y;
    int type;
    int orientation;
    int compatibilite[4];
    bool mobilité;
    bool tresor;
    int type_tresor;
}cellule;

//Définition des attibuts de la structure cellule
#define T 1
#define L 2
#define I 3
#define HAUT 1
#define DROITE 2
#define BAS 3
#define GAUCHE 4

//Création d'un plateau de 7*7 cases ( 49 cases au total) (liste de liste de cellules)
cellule plateau[7][7];

/*Comportement d'une cellule
    - Une cellule type T ou L(type = 1 ou 2) a 4 orientations possibles, tandis qu'une cellule type I(type = 3) a 2 orientations possibles
    - Les cellules ont 4 comptaibilités possibles, une pour chaque côté de la cellule, et si la cellule est sur le bord du plateau, elle n'a pas de compatibilité pour le côté correspondant
    - Les cellules sont initialisées avec une mobilité à true, sauf celles qui ont leurs deux coordonnées paires.
    - les 4 coins du plateau sont destinés à l'apparition des pions, et toutes les autres cases inamovibles (x et y paires) sont destinées à l'apparition des trésors
*/

//Fonction d'initialisation du plateau
void init_plateau(){
    //création d'un plateau aléatoire : 
    int i,j;
    for(i=0;i<7;i++){
        for(j=0;j<7;j++){
            plateau[i][j].x = i;
            plateau[i][j].y = j;
            plateau[i][j].type = rand()%3+1;

            //si la cellule est de type T ou L, alors elle a 4 orientations possibles, sinon elle a 2 orientations possibles (if avec ? : )
            plateau[i][j].orientation =  (plateau[i][j].type == I) ? rand()%2+1 : rand()%4+1;

            //si i et j sont paires, alors la cellule est inamovible (if avec ? : )
            plateau[i][j].mobilité = (i%2==0 && j%2==0) ? false : true;

            plateau[i][j].tresor = false;
            plateau[i][j].type_tresor = 0;
        }
    }
}

/*cellule T : 4 orientations possibles, 4 compatibilités possibles
orientation 1 : T -> droite, bas, gauche
orientation 2 : T -> haut, bas, gauche
orientation 3 : T -> haut, droite, gauche
orientation 4 : T -> haut, droite, bas

cellule L : 4 orientations possibles, 4 compatibilités possibles
orientation 1 : L -> haut, droite
orientation 2 : L -> droite, bas
orientation 3 : L -> bas, gauche
orientation 4 : L -> gauche, haut

cellule I : 2 orientations possibles, 2 compatibilités possibles
orientation 1 : I -> haut, bas
orientation 2 : I -> droite, gauche
*/


//Coucou je teste le git
//Fonction de mise à jour des compatibilités des cellules en fonction de leurs attributs avec des switch case
void update_compatibilite(){}
