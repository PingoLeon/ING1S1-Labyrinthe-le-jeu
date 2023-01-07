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
#define COULEUR_TEXTE 9
#define COULEUR_FOND 0


//Création d'un plateau de 7*7 cases ( 49 cases au total) (liste de liste de cellules)
cellule plateau[7][7];

//Création d'une cellule global_tile qui va être utilisée pour faire bouger le plateau
cellule global_tile; 

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
void derniere_tuile(int t_counter, int l_counter, int l_nontresor_counter){

    // Seed the random number generator with the current time
    srand(time(NULL)); 
    
    // check the values of the counters
    if(t_counter < 6){
        // create a T cell with a treasure
        global_tile.type = T;
        global_tile.tresor = true;
        global_tile.type_tresor = rand()%24+1;
        global_tile.orientation = rand()%4+1;
    }else if(l_counter < 6){
        // create an L cell with a treasure
        global_tile.type = L;
        global_tile.tresor = true;
        global_tile.type_tresor = rand()%24+1;
        global_tile.orientation = rand()%4+1;
    }else if(l_nontresor_counter < 10){
        // create an L cell without a treasure
        global_tile.type = L;
        global_tile.tresor = false;
        global_tile.type_tresor = 0;
        global_tile.orientation = rand()%4+1;
    }else{
        // create an I cell without a treasure
        global_tile.type = I;
        global_tile.orientation = rand()%2+1;
        global_tile.tresor = false;
        global_tile.type_tresor = 0;
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
    derniere_tuile(t_counter, l_counter, l_nontresor_counter);
}

//Fonction d'initialisation du plateau qui crée un plateau rempli de cellules définies uniquement par leur mobilité
void init_plateau(){
    //création d'un plateau aléatoire : 
    int i,j;
    for(i=0;i<7;i++){
        for(j=0;j<7;j++)
        {
            plateau[i][j].x = i; 
            plateau[i][j].y = j;
            plateau[i][j].mobilité = (i%2 == 0 && j%2 == 0) ? false : true; // Si la cellule est sur une ligne ou une colonne paire, elle est inamovible
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
    for (int i = 0; i < 7; i++) {
        for(int num_line = 0; num_line < 3; num_line++){
            for (int j = 0; j < 7; j++) {
                if (num_line == 0){
                    Color(COULEUR_TEXTE,COULEUR_FOND);
                    afficher_cellule_ligne1(plateau[i][j].type, plateau[i][j].orientation);
                    Color(15,0);
                } else if (num_line == 1){
                    Color(COULEUR_TEXTE,COULEUR_FOND);
                    afficher_cellule_ligne2(plateau[i][j].type, plateau[i][j].orientation);
                    Color(15,0);
                } else if (num_line == 2){
                    Color(COULEUR_TEXTE,COULEUR_FOND);
                    afficher_cellule_ligne3(plateau[i][j].type, plateau[i][j].orientation);
                    Color(15,0);
                }
            }
            printf("\n");
        }
    }
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
    if (plateau[x][y].tresor == true) { // Si la case est déjà occupée, on ne fait rien
        if (type == T) { // Si la tuile est un T
            if (x != 0 && x != 7 && y != 0 && y != 7) { // Si la tuile n'est pas sur les bords du plateau 
                plateau[x][y].type = T;
                plateau[x][y].orientation = orientation; 
                plateau[x][y].tresor = 1; // On place le trésor
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



//Fonction qui permet de charger une partie
void ChargerPartie()
{
    FILE* fichier = NULL;
    fichier = fopen("sauvegarde.txt", "r");
    if (fichier != NULL)
    {
        char caractereActuel = 0;
        while (caractereActuel != EOF)
        {
            caractereActuel = fgetc(fichier);
            printf("%c", caractereActuel);
        }
        fclose(fichier);
    }
    else
    {
        printf("Impossible d'ouvrir le fichier sauvegarde.txt");
    }
}

// Fonction qui permet de sauvegarder une partie
void SauvegarderPartie()
{
    FILE* fichier = NULL;
    fichier = fopen("sauvegarde.txt", "w");
    if (fichier != NULL)
    {
        fprintf(fichier, "Sauvegarde");
        fclose(fichier);
    }
    else
    {
        printf("Impossible d'ouvrir le fichier sauvegarde.txt");
    }
}

// Structure qui permet de créer un pion
struct Pion
{
    int numero;
    int x;
    int y;
    char symbole;
};

// On génère les 4 pions possibles
struct Pion pion1 = {1, 0, 0, '*'};
struct Pion pion2 = {2, 0, 6, '*'};
struct Pion pion3 = {3, 6, 0, '*'};
struct Pion pion4 = {4, 6, 6, '*'};

// Fonction qui initialise les joueurs et leur attribue un pion
int ChoixPions(){
    int nbJoueurs;
    int choixPions; 
    char *pions [] = {"Asterix", "Obelix", "Idefix", "Panoramix"};
    printf("Choisissez votre pion : \n");


    int i; 
    for(i = 0; i < 4; i++)
    {
        printf("%d: %s\n", i+1, pions[i]);
    }
    
scanf("%d", &choixPions); 

switch(choixPions){
        case 1:
        printf("\rVous avez choisi Asterix!\nVous avez le pion vert.\n"); 
        break;

        case 2:
        printf("Vous avez choisi Obelix!\nVous avez le pion bleu.\n");
        break;

        case 3:
        printf("Vous avez choisi Idefix!\nVous avez le pion blanc.\n");
        break;

        case 4:
        printf("Vous avez choisi Panoramix!\nVous avez le pion rouge.\n");
        break;

        default:
            printf("Veuillez choisir un personnage qui est dans la liste.\n");
            break;

    }

}

void init_pions()
{
    int nbJoueurs;
    printf("Combien de joueurs ? (2 à 4) : ");
    scanf("%d", &nbJoueurs);
    if (nbJoueurs < 2 || nbJoueurs > 4)
    {
        printf("Erreur : le nombre de joueurs doit être compris entre 2 et 4.\n");
    }
    else
    {
        printf("Il y a %d joueurs.\n", nbJoueurs);
    }

    // On génère les 4 pions
    if (nbJoueurs == 2)
    {
        ChoixPions();
        printf("Pion 1 : %c\n", pion1.symbole);
        printf("Pion 2 : %c\n", pion2.symbole);
    }
    else if (nbJoueurs == 3)
    {
        ChoixPions();
        printf("Pion 1 : %c\n", pion1.symbole);
        printf("Pion 2 : %c\n", pion2.symbole);
        printf("Pion 3 : %c\n", pion3.symbole);
    }
    else if (nbJoueurs == 4)
    {
        ChoixPions();
        printf("Pion 1 : %c\n", pion1.symbole);
        printf("Pion 2 : %c\n", pion2.symbole);
        printf("Pion 3 : %c\n", pion3.symbole);
        printf("Pion 4 : %c\n", pion4.symbole);
    }

} 

// CARTE TRESOR
// Création d'une carte de face 
void carteDeFace() {

  char map[10][10] = {
    {' ', '_', '_', '_', '_', '_', '_', '_', '_', ' '},
    {'|', ' ', 'T', 'r', 'e', 's', 'o', 'r', ' ', '|'},
    {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
    {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
    {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
    {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
    {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
    {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
    {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
    {'|', '_', '_', '_', '_', '_', '_', '_', '_', '|'} };


    char tresors[24] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L'};

    for (int i = 0; i < 10; i++) 
    {
        for (int j = 0; j < 10; j++) 
        {

        printf("\033[1;37m%c\033[0m ", map[i][j]);// pour afficher la carte en blanc
        //\033[1;37mTexte en blanc\033[0m     blanc

        if ( i==5 && j==4)
        {
        srand(time(0));
        int k = rand() % 24;

        printf("\033[33m%c\033[33m ", tresors[k]);// pour afficher le trésor en jaune
        //\033[33mTexte en jaune\033[33m       jaune
        }
       }
     printf("\n");
    }
}

// Création d'une carte trésor de dos
void carteDeDos (){
    char map[10][10] = {
        {' ', '_', '_', '_', '_', '_', '_', '_', '_', ' '},
        {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
        {'|', ' ', 'T', 'r', 'e', 's', 'o', 'r', ' ', '|'},
        {'|', ' ', ' ', 'r', ' ', ' ', ' ', ' ', ' ', '|'},
        {'|', ' ', ' ', ' ', 'e', ' ', ' ', ' ', ' ', '|'},
        {'|', ' ', ' ', ' ', ' ', 's', ' ', ' ', ' ', '|'},
        {'|', ' ', ' ', ' ', ' ', ' ', 'o', ' ', ' ', '|'},
        {'|', ' ', 'T', 'r', 'e', 's', 'o', 'r', ' ', '|'},
        {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
        {'|', '_', '_', '_', '_', '_', '_', '_', '_', '|'} };

        for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {

            printf("\033[0;37m%c\033[0m ", map[i][j]); // en gris

            }
            printf("\n"); 
            }
            //printf("\n"); 

}

// Création d'une fonction qui va appeler les deux fonctions précédentes pour créer une carte trésor de face et de dos
void carteTresor ()
{
    carteDeFace();
    carteDeDos();
}


// Fonction qui permet de mettre en place le déroulement de la partie
void initialisationPartie () 
{
    init_plateau();
    afficher_plateau();
    init_pions();
    carteTresor();
    placer_tresor();
}

// Fonction qui affiche les règles du jeu
void Regles()
{
    int choixRegles;
    int choixDeroulement;

    do
    {
    printf(" 1 - But du jeu\n");
    printf(" 2 - Préparation du jeu\n");
    printf(" 3 - Déroulement du jeu\n");
    printf(" 4 - Fin de la partie\n");
    printf(" Tapez 0 si vous voulez revenir au menu principal\n");
    printf("\n Votre choix : ");
    scanf("%d", &choixRegles);
    
    switch(choixRegles)
    {
        case 1:
            printf("\nBut du jeu\n");
            printf("\t Dans un labyrinthe enchanté, les joueurs partent à la chasse aux objets et aux créatures magiques.\n");
            printf("\t Chacun cherche à se frayer un chemin jusqu’à eux en faisant coulisser astucieusement les couloirs.\n");
            printf("\t Le premier joueur à découvrir tous ses secrets et à revenir à son point de départ remporte cette passionnante chasse aux trésors.\n\n");
            break;
        
        case 2:
            printf("\nPréparation du jeu\n");
            printf("\t 1 - Mélanger les plaques face cachée, puis les placer sur les emplacements libres du plateau pour créer un labyrinthe aléatoire. La plaque supplémentaire servira à faire coulisser les couloirs du labyrinthe.\n");
            printf("\t 2 - Mélanger à leur tour les 24 cartes Objectif face cachée.\n");
            printf("\t 3 - En distribuer le même nombre à chaque joueur. Chacun les empile devant lui sans les regarder.\n");
            printf("\t 4 - Chaque joueur choisit ensuite un pion qu’il place sur sa case Départ au coin du plateau de la couleur correspondante.\n\n");
            break;
        
        case 3:
           printf("\nDéroulement du jeu\n");
           printf("\t Chaque joueur regarde secrètement la carte supérieure de sa pile. Le plus jeune joueur commence.\n");
           printf("\t La partie se poursuit dans le sens des aiguilles d’une montre.\n");
           printf("\t A son tour de jeu, le joueur doit essayer d’atteindre la plaque représentant le même dessin que celui sur la carte supérieure de sa pile.\n");
           printf("\t Pour cela il commence toujours par faire coulisser une rangée ou une colonne du labyrinthe en insérant la plaque supplémentaire du bord vers l’intérieur du plateau, puis il déplace son pion.\n");
           printf("\t Ainsi, un tour se compose toujours de deux phases :\n\n");

           printf(" 1 - Modification des couloirs (Introduction de la carte couloir supplémentaire).\n");
           printf(" 2 - Déplacement du pion.\n");
           printf("\n Votre choix : ");
           scanf("%d", &choixDeroulement);
           
           if (choixDeroulement == 1)
           {
           printf("\n\n 1 - Modification des couloirs (Introduction de la carte couloir supplémentaire).\n");
           printf("\t Quand vient son tour, le joueur choisit l’une de ces rangées ou colonnes et pousse la plaque supplémentaire vers l’intérieur du plateau jusqu’à ce qu’une nouvelle plaque soit expulsée à l’opposé.\n");
           printf("\t La plaque expulsée reste au bord du plateau jusqu’à ce qu’elle soit réintroduite à un autre endroit par le joueur suivant.\n");
           printf("\t Un joueur est toujours obligé de modifier le labyrinthe avant de déplacer son pion, même s’il aurait pu atteindre le dessin recherché sans déplacer les couloirs.\n");
           printf("\t Si, en faisant coulisser les couloirs du labyrinthe, un joueur expulse son pion ou un pion adverse du plateau, il est alors replacé à l’opposé, sur la plaque qui vient d’être introduite.\n\n");
           }
           
           else if (choixDeroulement == 2)
           {
           printf("\n\n 2 - Déplacement du pion.\n");
           printf("\t Dès qu’il a modifié le labyrinthe, le joueur peut déplacer son pion. Il peut le déplacer aussi loin qu’il veut jusqu’à n’importe quelle plaque en suivant un couloir ininterrompu.\n");
           printf("\t Un joueur peut même s’arrêter sur une case déjà occupée.\n");
           printf("\t Si le joueur n’atteint pas le dessin recherché (= celui figurant sur la carte supérieure de sa pile), il peut déplacer son pion aussi loin qu’il veut de manière à être en bonne position pour le prochain tour.\n");
           printf("\t S’il atteint le dessin recherché, il retourne sa carte à côté de sa pile. Il peut immédiatement regarder secrètement la carte suivante de sa pile pour connaître son prochain objectif.\n\n");
           }

           else 
            {
            printf("Erreur");
            main();
            }
           break;
        
        case 4:
            printf("\nFin de partie\n");
            printf("\t La partie s’arrête dès qu’un joueur a atteint tous ses objectifs et qu’il est revenu à son point de départ.\n");
            printf("\t C’est lui qui a su se déplacer le mieux dans le labyrinthe et il remporte la partie !\n\n");
            break;
    
        default:
            printf("------------------------------------\n\n");
            main();
            break;
    }

    } while (choixRegles != 0);
    
    main();
}


// Fonction qui permet de quitter le jeu
void Quitter()
{
    printf("Merci d'avoir joué au Labyrinth !\n");
    exit(0);
}
  

// Menu principal du jeu
void menuPrincipal()
{
    int choix;
    printf(" 1 - Nouvelle Partie\n");
    printf(" 2 - Charger une partie\n");
    printf(" 3 - Afficher les règles / crédits\n");
    printf(" 4 - Quitter\n");
    printf("\n Votre choix : ");
    scanf("%d", &choix);

    switch(choix)
    {
        case 1:
            printf("\nNouvelle Partie\n");
            initialisationPartie();
            break;
        
        case 2:
            printf("\nCharger une partie\n");
            ChargerPartie();
          break;
        
        case 3:
            printf("\nAfficher les règles / crédits\n");
            Regles();
            break;
        
        case 4:
            printf("\nQuitter\n");
            Quitter();
            break;
        
        default:
            printf("Erreur");
            break;
        }
} 

int main () 
{
menuPrincipal();
return 0; 
}
