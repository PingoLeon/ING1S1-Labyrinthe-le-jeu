#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <locale.h>
#include <windows.h>

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

/*
    0 : Noir
    1 : Bleu foncé
    2 : Vert foncé
    3 : Turquoise
    4 : Rouge foncé
    5 : Violet
    6 : Vert caca d'oie
    7 : Gris clair
    8 : Gris foncé
    9 : Bleu fluo
    10 : Vert fluo
    11 : Turquoise
    12 : Rouge fluo
    13 : Violet 2
    14 : Jaune
    15 : Blanc
    */
#define COULEUR_TEXTE 15
#define COULEUR_TEXTE_ALTERNATIVE 12
#define COULEUR_FOND 0


//Création d'un plateau de 7*7 cases ( 49 cases au total) (liste de liste de cellules)
cellule plateau[7][7];

//Création d'une cellule global_tile qui va être utilisée pour faire bouger le plateau
cellule global_tile; 
cellule global_tile_temp;


//initialisation de la couleur du texte et du fond de la console
void Color(int couleurDuTexte,int couleurDeFond) // fonction d'affichage de couleurs
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}

/*Comportement d'une cellule
    - Une cellule type T ou L(type = 1 ou 2) a 4 orientations possibles, tandis qu'une cellule type I(type = 3) a 2 orientations possibles
    - Les cellules ont 4 comptaibilités possibles, une pour chaque côté de la cellule, et si la cellule est sur le bord du plateau, elle n'a pas de compatibilité pour le côté correspondant
    - Les cellules sont initialisées avec une mobilité à true, sauf celles qui ont leurs deux coordonnées paires.
    - les 4 coins du plateau sont destinés à l'apparition des pions, et toutes les autres cases inamovibles (x et y paires) sont destinées à l'apparition des trésors
*/

/*Nombre de cellules et répartition du plateau : 
Le jeu comporte 16 tuiles inamovibles (x et y paires), et 34 tuiles amovibles (x et y impaires)
Parmis les 16 tuiles inamovibles : 
    - 4 sont destinées à l'apparition des pions en L
    - 12 sont destinées à l'apparition des trésors en T

Parmis les 34 tuiles amovibles, on compte :
    - 6 Tuiles en T avec un trésor
    - 6 Tuiles en L avec un trésor
    - 10 tuiles en L sans trésor
    - 12 tuiles en I sans trésor

 Note : la tuile restante est mise à disposition des joueurs pour faire bouger le labyrinthe
*/

/*Compatibilité des cellules :

DANS LA LISTE COMPATBILITE, LES INDICES DES ELEMENTS CORRESPONDENT AUX DIRECTIONS (0: haut, 1: droite, 2: bas, 3: gauche)
En fonction de la compatibilité de la cellule, on met dans la liste de compatibilité toutes les directions possibles

cellule T : 4 orientations possibles, 4 compatibilités possibles
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

//Fonction de mise à jour des compatibilités des cellules en fonction de leurs types et orientations
void maj_compatibilite(){
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

            //Si la cellule est au bord du plateau, on met à jour les compatibilités
            if(i==0){
                plateau[i][j].compatibilite[0] = 0;
            }
            if(i==6){
                plateau[i][j].compatibilite[2] = 0;
            }
            if(j==0){
                plateau[i][j].compatibilite[3] = 0;
            }
            if(j==6){
                plateau[i][j].compatibilite[1] = 0;
            }
        }
    }
}

//Fonction qui génère la dernière tuile excroissante
void derniere_tuile(int t_counter, int l_counter, int l_nontresor_counter, int i_nontresor_counter){

    // Seed the random number generator with the current time
    srand(time(NULL));
    int choosen = 1;
    int random = rand()%4+1;
    while(choosen == 1){    
        if(random == 1 && t_counter < 6){
            global_tile.type = T;
            global_tile.orientation = rand()%4+1;
            global_tile.tresor = true;
            global_tile.type_tresor = rand()%24+1;
            t_counter++;
            choosen = 0;
        }else if(random == 2 && l_counter < 6){
            global_tile.type = L;
            global_tile.orientation = rand()%4+1;
            global_tile.tresor = true;
            global_tile.type_tresor = rand()%24+1;
            l_counter++;
            choosen = 0;
        }else if(random == 3 && l_nontresor_counter < 10){
            global_tile.type = L;
            global_tile.orientation = rand()%4+1;
            global_tile.tresor = false;
            global_tile.type_tresor = 0;
            l_nontresor_counter++;
            choosen = 0;
        }else if(random == 4 && i_nontresor_counter < 12){
            global_tile.type = I;
            global_tile.orientation = rand()%2+1;
            global_tile.tresor = false;
            global_tile.type_tresor = 0;
            i_nontresor_counter++;
            choosen = 0;
        }else{
            random = rand()%4+1;
        }
    }
}

//Fonction de remplissage du plateau
void remplissage_plateau(){

    // Seed the random number generator with the current time
    srand(time(NULL));

    //correction des cellules inamovibles
    int t_counter = 0;  // counter for T cells with a treasure
    int l_counter = 0;  // counter for L cells with a treasure
    int l_nontresor_counter = 0;  // counter for L cells without a treasure
    int i_nontresor_counter = 0;  // counter for I cells without a treasure
    for(int i=0;i<7;i++){
        for(int j=0;j<7;j++){
            //16 tuiles inamovibles : On dit qu'elles ont un trésor 
            if(plateau[i][j].mobilité == false ){
                if ((i!=0 || j!=0) && (i!=0 || j!=6) && (i!=6 || j!=0) && (i!=6 || j!=6)){ // Si la cellule n'est pas une des 4 coins, elle a alors une forme de T, et si c'est un coin, elle possède un trésor
                    plateau[i][j].type = T;
                    plateau[i][j].tresor = true;
                    plateau[i][j].type_tresor = rand()%24+1;
                    plateau[i][j].orientation = rand()%4+1;
                }else{
                    plateau[i][j].type = L;
                    plateau[i][j].tresor = false;

                    //corners should be L cells with different orientations
                    if(i==0 && j==0){
                        plateau[i][j].orientation = 2;
                    }else if(i==0 && j==6){
                        plateau[i][j].orientation = 3;
                    }else if(i==6 && j==0){
                        plateau[i][j].orientation = 1;
                    }else if(i==6 && j==6){
                        plateau[i][j].orientation = 4;
                    }
                }  
            }else{
                //generate a random number and assign it to a type of cell between the 4 stated above
                int choosen = 1;
                int random = rand()%4+1;
                while(choosen == 1){    
                    if(random == 1 && t_counter < 6){
                        plateau[i][j].type = T;
                        plateau[i][j].orientation = rand()%4+1;
                        plateau[i][j].tresor = true;
                        plateau[i][j].type_tresor = rand()%24+1;
                        t_counter++;
                        choosen = 0;
                    }else if(random == 2 && l_counter < 6){
                        plateau[i][j].type = L;
                        plateau[i][j].orientation = rand()%4+1;
                        plateau[i][j].tresor = true;
                        plateau[i][j].type_tresor = rand()%24+1;
                        l_counter++;
                        choosen = 0;
                    }else if(random == 3 && l_nontresor_counter < 10){
                        plateau[i][j].type = L;
                        plateau[i][j].orientation = rand()%4+1;
                        plateau[i][j].tresor = false;
                        plateau[i][j].type_tresor = 0;
                        l_nontresor_counter++;
                        choosen = 0;
                    }else if(random == 4 && i_nontresor_counter < 12){
                        plateau[i][j].type = I;
                        plateau[i][j].orientation = rand()%2+1;
                        plateau[i][j].tresor = false;
                        plateau[i][j].type_tresor = 0;
                        i_nontresor_counter++;
                        choosen = 0;
                    }else{
                        random = rand()%4+1;
                    }
                }   
            }
        }
    }

    // generate the last tile
    derniere_tuile(t_counter, l_counter, l_nontresor_counter, i_nontresor_counter);
}

//Fonction d'initialisation du plateau qui crée un plateau rempli de cellules définies uniquement par leur mobilité
void init_plateau(){
    //création d'un plateau aléatoire : 
    int i,j;
    for(i=0;i<7;i++){
        for(j=0;j<7;j++){
            plateau[i][j].x = i;
            plateau[i][j].y = j;
            plateau[i][j].mobilité = (i%2 == 0 && j%2 == 0) ? false : true;  
        }
    }
    //Appel de la fonction de correction du plateau qui va remplir les cellules inamovibles et les cellules amovibles, et créer la dernière cellule excroissante 
    remplissage_plateau();

    //Appel de la fonction de correction des compatibilités qui va remplir les compatibilités des cellules
    maj_compatibilite();
}

void fill(int nb){
    //each text has 3 characters possible, being filled with double space, or a full block (u2588)
    //We need all combinations of those 3 characters to fill the line
    switch (nb)
    {
    case 0:
        printf("      "); //000
        break;
    case 1:
        printf("    \u2588\u2588"); //001
        break;
    
    case 2:
        printf("  \u2588\u2588  "); //010
        break;
    
    case 3:
        printf("  \u2588\u2588\u2588\u2588"); //011
        break;
    
    case 4:
        printf("\u2588\u2588    "); //100
        break;
    
    case 5:
        printf("\u2588\u2588  \u2588\u2588"); //101
        break;
    
    case 6:
        printf("\u2588\u2588\u2588\u2588  "); //110
        break;

    case 7:
        printf("\u2588\u2588\u2588\u2588\u2588\u2588"); //111
        break;

    default:
        break;
    }
}

void afficher_cellule_ligne1(int type, int orientation) {
    if (type == T) {
        if (orientation == 1){
            fill(7);
        } else if (orientation == 2){
            fill(5);
        } else if (orientation == 3){
            fill(5);
        } else if (orientation == 4){
            fill(5);
        }
    } else if (type == L) {
        if (orientation == 1){
            fill(5);
        }else if (orientation == 2){
            fill(7);
        } else if(orientation == 3){
            fill(7);
        } else if (orientation == 4){
            fill(5);
        }
    } else if (type == I) {
        if (orientation == 1){
            fill(5);
        } else if (orientation == 2){
            fill(7);
        }
    }
}
void afficher_cellule_ligne2(int type, int orientation) {
    if (type == T) {
        if (orientation == 1){
            fill(0);
        } else if (orientation == 2){
            fill(1);
        } else if (orientation == 3){
            fill(0);
        } else if (orientation == 4){
            fill(4);
        }
    }else if (type == L) {
        if (orientation == 1){
            fill(4);
        }else if (orientation == 2){
            fill(4);
        } else if(orientation == 3){
            fill(1);
        } else if (orientation == 4){
            fill(1);
        }
    } else if (type == I) {
        if (orientation == 1){
            fill(5);
        } else if (orientation == 2){
            fill(0);
        }
    }
}

void afficher_cellule_ligne3(int type, int orientation){
    if (type == T) {
        if (orientation == 1){
            fill(5);
        } else if (orientation == 2){
            fill(5);
        } else if (orientation == 3){
            fill(7);
        } else if (orientation == 4){
            fill(5);
        }
    }else if (type == L){
        if (orientation == 1){
            fill(7);
        }else if (orientation == 2){
            fill(5);
        } else if(orientation == 3){
            fill(5);
        } else if (orientation == 4){
            fill(7);
        }
    } else if (type == I){
        if (orientation == 1){
            fill(5);
        } else if (orientation == 2){
            fill(7);
        }
    }
}




void afficher_plateau() {
    setlocale(LC_ALL, "en_US.utf8");
    //print all numbers of row separated by a tabulation
    printf("\t   \t2           4           6      \n\n");
    for (int i = 0; i < 7; i++) {
        for(int num_line = 0; num_line < 3; num_line++){
            if (num_line == 1){
                if (i%2 != 0){
                    printf("%d", i+1);
                }
            }   
            printf("\t");
            for (int j = 0; j < 7; j++) {
                if (num_line == 0){
                    if (plateau[i][j].mobilité == false){
                        Color(COULEUR_TEXTE_ALTERNATIVE,COULEUR_FOND);
                    } else {
                        Color(COULEUR_TEXTE,COULEUR_FOND);
                    }
                    afficher_cellule_ligne1(plateau[i][j].type, plateau[i][j].orientation);
                    Color(15,0);
                } else if (num_line == 1){
                    if (plateau[i][j].mobilité == false){
                        Color(COULEUR_TEXTE_ALTERNATIVE,COULEUR_FOND);
                    } else {
                        Color(COULEUR_TEXTE,COULEUR_FOND);
                    }
                    afficher_cellule_ligne2(plateau[i][j].type, plateau[i][j].orientation);
                    Color(15,0);
                } else if (num_line == 2){
                    if (plateau[i][j].mobilité == false){
                        Color(COULEUR_TEXTE_ALTERNATIVE,COULEUR_FOND);
                    } else {
                        Color(COULEUR_TEXTE,COULEUR_FOND);
                    }
                    afficher_cellule_ligne3(plateau[i][j].type, plateau[i][j].orientation);
                    Color(15,0);
                }
            }
            if (num_line == 1){
                if (i%2 != 0){
                    printf("\t%d", i+1);
                }
            }   
            printf("\n");
        }
    }
    printf("\n\t   \t2           4           6      ");
}

//Fonction permettant de placer les tresors en fonction de la tuile imposée
//Si la tuile est déjà occupée, on ne fait rien
//Les tuiles I et celles sur les bords ne peuvent pas contenir de trésor
//Les tuiles L et T peuvent contenir un trésor si elles sont libres et si elles ne sont pas sur les bords du plateau
//il faut 6L avec tresor
//il faut 4L avec position des pions
//il faut 6L sans tresor
//il faut 6T avec tresor
//il faut 12 I sans tresor

void placer_tresor(int type, int orientation, int x, int y) {
    if (plateau[x][y].tresor == true) {
        if (type == T) {
            if (x != 0 && x != 7 && y != 0 && y != 7) {
                plateau[x][y].type = T;
                plateau[x][y].orientation = orientation;
                plateau[x][y].tresor = 1;
            }
        } else if (type == L) {
            if (x != 0 && x != 7 && y != 0 && y != 7) {
                plateau[x][y].type = L;
                plateau[x][y].orientation = orientation;
                plateau[x][y].tresor = 1;
            }
        }
    }
}

void insertion_cellule(char ligcol, char num, char sens){
    //we have the board and the global tile. Push the tile on the board, move all the tiles, and set the global tile to the tile pushed at the end

    if(ligcol == 'L'){
        if(sens == 'G'){
            //insertion en ligne 2, par la gauche 
            //Extraire la cellule la plus à gauche de la ligne 2, et la mettre dans une tuile globale temporaire
            global_tile_temp = plateau[num-1][0];
            //on décale toutes les cellules de la ligne 2 vers la droite
            for(int i = 6; i > 0; i--){
                plateau[num-1][i] = plateau[num-1][i-1];
            }
            //on insère la tuile globale tout à droite
            plateau[num-1][6] = global_tile;
            
            //on met à jour la tuile globale
            global_tile = global_tile_temp;
        } else if(sens == 'D'){
            //insertion en ligne 2, par la droite
            //Extraire la cellule la plus à droite de la ligne 2, et la mettre dans une tuile globale temporaire
            global_tile_temp = plateau[num-1][6];
            //on décale toutes les cellules de la ligne 2 vers la gauche
            for(int i = 0; i < 6; i++){
                plateau[num-1][i] = plateau[num-1][i+1];
            }
            //on insère la tuile globale tout à gauche
            plateau[num-1][0] = global_tile;

            //on met à jour la tuile globale
            global_tile = global_tile_temp;
        }
    }else if(ligcol == 'C'){
        if(sens == 'H'){
            //insertion en colonne 2, par le haut
            //Extraire la cellule la plus en haut de la colonne 2, et la mettre dans une tuile globale temporaire
            global_tile_temp = plateau[0][num-1];
            //on décale toutes les cellules de la colonne 2 vers le bas
            for(int i = 6; i > 0; i--){
                plateau[i][num-1] = plateau[i-1][num-1];
            }
            //on insère la tuile globale tout en bas
            plateau[6][num-1] = global_tile;

            //on met à jour la tuile globale
            global_tile = global_tile_temp;
        } else if(sens == 'B'){
            //insertion en colonne 2, par le bas
            //Extraire la cellule la plus en bas de la colonne 2, et la mettre dans une tuile globale temporaire
            global_tile_temp = plateau[6][num-1];
            //on décale toutes les cellules de la colonne 2 vers le haut
            for(int i = 0; i < 6; i++){
                plateau[i][num-1] = plateau[i+1][num-1];
            }
            //on insère la tuile globale tout en haut
            plateau[0][num-1] = global_tile;

            //on met à jour la tuile globale
            global_tile = global_tile_temp;
        }
    }
}

void choix_insertion_cellule(){
    int state = 0;
    while(state == 0){
        char choix[3];

        //Affichage de la tuile globale
        printf("\n\n\nVoici la tuile en trop : \n");
        afficher_cellule_ligne1(global_tile.type, global_tile.orientation); 
        printf("\n");
        afficher_cellule_ligne2(global_tile.type, global_tile.orientation);
        printf("\n");
        afficher_cellule_ligne3(global_tile.type, global_tile.orientation);

        //Affichage du menu
        printf("\n\n\nSélection de l'insertion : \n");
        printf("1 : Choix de Ligne ou de colonne (L/C) \n");
        printf("2 : Choix de quelle ligne ou colonne (2/4/6) \n");
        printf("3 : Choix du sens : Droite/Gauche ou Haut/Bas (D/G ou H/B) \n");
        printf("Exemple : Insertion sur une ligne, numéro 2, et par la gauche : L2G \n Choix :");

        scanf("%s", choix);
        //check if the input is correct
        if (choix[0] == 'L' || choix[0] == 'C'){
            if (choix[1] == '2' || choix[1] == '4' || choix[1] == '6'){
                if (choix[2] == 'D' || choix[2] == 'G' || choix[2] == 'H' || choix[2] == 'B'){
                    state = 1;
                    insertion_cellule(choix[0], choix[1], choix[2]);
                }
            }
        }

        if(state == 0){
            printf("Attention : La saisie est incorrecte ! \n");
        }
    }
}

int main(){
    //erase the console
    init_plateau();
    
    afficher_plateau();

    choix_insertion_cellule();

    afficher_plateau();
    return 0;
}













