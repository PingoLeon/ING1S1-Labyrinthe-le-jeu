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
//DANS LA LISTE COMPATBILITE, LES INDICES DES ELEMENTS CORRESPONDENT AUX DIRECTIONS (0: haut, 1: droite, 2: bas, 3: gauche)

//Fonction de mise à jour des compatibilités des cellules en fonction de leurs attributs avec des switch case
//en fonction de la compatibilité de la cellule, on met dans la liste de compatibilité toutes les directions possibles
void update_compatibilite(){
    for(int i=0;i<7;i++){
        for(int j;j<7; j++){
            if (plateau[i][j].type == T){
                switch (plateau[i][j].orientation) {
                case 1:
                    //update the list of compatibilities
                    plateau[i][j].compatibilite[0] = 0;
                    plateau[i][j].compatibilite[1] = DROITE;
                    plateau[i][j].compatibilite[2] = BAS;
                    plateau[i][j].compatibilite[3] = GAUCHE;
                    break;
                    
                case 2:
                    //update the list of compatibilities
                    plateau[i][j].compatibilite[0] = HAUT;
                    plateau[i][j].compatibilite[1] = 0;
                    plateau[i][j].compatibilite[2] = BAS;
                    plateau[i][j].compatibilite[3] = GAUCHE;
                    break;
                case 3:
                    //update the list of compatibilities
                    plateau[i][j].compatibilite[0] = HAUT;
                    plateau[i][j].compatibilite[1] = DROITE;
                    plateau[i][j].compatibilite[2] = 0;
                    plateau[i][j].compatibilite[3] = GAUCHE;
                    break;

                case 4:
                    //update the list of compatibilities
                    plateau[i][j].compatibilite[0] = HAUT;
                    plateau[i][j].compatibilite[1] = DROITE;
                    plateau[i][j].compatibilite[2] = BAS;
                    plateau[i][j].compatibilite[3] = 0;
                    break;
                }
            }else if(plateau[i][j].type == L){
                switch (plateau[i][j].orientation) {
                case 1:
                    //update the list of compatibilities
                    plateau[i][j].compatibilite[0] = HAUT;
                    plateau[i][j].compatibilite[1] = DROITE;
                    plateau[i][j].compatibilite[2] = 0;
                    plateau[i][j].compatibilite[3] = 0;
                    break;
                    
                case 2:
                    //update the list of compatibilities
                    plateau[i][j].compatibilite[0] = 0;
                    plateau[i][j].compatibilite[1] = DROITE;
                    plateau[i][j].compatibilite[2] = BAS;
                    plateau[i][j].compatibilite[3] = 0;
                    break;
                case 3:
                    //update the list of compatibilities
                    plateau[i][j].compatibilite[0] = 0;
                    plateau[i][j].compatibilite[1] = 0;
                    plateau[i][j].compatibilite[2] = BAS;
                    plateau[i][j].compatibilite[3] = GAUCHE;
                    break;

                case 4:
                    //update the list of compatibilities
                    plateau[i][j].compatibilite[0] = HAUT;
                    plateau[i][j].compatibilite[1] = 0;
                    plateau[i][j].compatibilite[2] = 0;
                    plateau[i][j].compatibilite[3] = GAUCHE;
                    break;
                }
            }else if(plateau[i][j].type == I){
                switch (plateau[i][j].orientation) {
                case 1:
                    //update the list of compatibilities
                    plateau[i][j].compatibilite[0] = HAUT;
                    plateau[i][j].compatibilite[1] = BAS;
                    plateau[i][j].compatibilite[2] = 0;
                    plateau[i][j].compatibilite[3] = 0;
                    break;
                    
                case 2:
                    //update the list of compatibilities
                    plateau[i][j].compatibilite[0] = 0;
                    plateau[i][j].compatibilite[1] = 0;
                    plateau[i][j].compatibilite[2] = DROITE;
                    plateau[i][j].compatibilite[3] = GAUCHE;
                    break;
                }
            }
        }
    }
}








