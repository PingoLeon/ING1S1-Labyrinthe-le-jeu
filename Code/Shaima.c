#include <stdio.h>
#include <stdlib.h> 


// Structure qui définit un pion
struct Pion
{
    int numero;
    int x;
    int y;
    char symbole;
};

// On génère les 4 pions possibles
struct Pion pion1 = {1, 0, 0, 'A'};
struct Pion pion2 = {2, 0, 6, 'B'};
struct Pion pion3 = {3, 6, 0, 'C'};
struct Pion pion4 = {4, 6, 6, 'D'};

// Fonction qui initialise les joueurs et leur attribue un pion
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
        printf("Il y a 2 joueurs.\n");
        printf("Pion 1 : %c\n", pion1.symbole);
        printf("Pion 2 : %c\n", pion2.symbole);
    }
    else if (nbJoueurs == 3)
    {
        printf("Il y a 3 joueurs.\n");
        printf("Pion 1 : %c\n", pion1.symbole);
        printf("Pion 2 : %c\n", pion2.symbole);
        printf("Pion 3 : %c\n", pion3.symbole);
    }
    else if (nbJoueurs == 4)
    {
        printf("Il y a 4 joueurs.\n");
        printf("Pion 1 : %c\n", pion1.symbole);
        printf("Pion 2 : %c\n", pion2.symbole);
        printf("Pion 3 : %c\n", pion3.symbole);
        printf("Pion 4 : %c\n", pion4.symbole);
    }

} 


// Fonction qui permet de créer une nouvelle partie et permet son déroulement
void nouvellepartie()
{
    init_pions();
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
            system("cls");
            main();
            }
           break;
        
        case 4:
            printf("\nFin de partie\n");
            printf("\t La partie s’arrête dès qu’un joueur a atteint tous ses objectifs et qu’il est revenu à son point de départ.\n");
            printf("\t C’est lui qui a su se déplacer le mieux dans le labyrinthe et il remporte la partie !\n\n");
            break;
    
        default:
            printf("Erreur");
            system("cls");
            main();
            break;
    }
    } while (choixRegles != 0);
    system("cls");
    main();
}

// Fonction qui permet de quitter le jeu
void Quitter()
{
    printf("Merci d'avoir joué au Labyrinthe !\n");
    exit(0);
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

// Menu principal du jeu
int main()
{
    
    int choix;
    printf(" 1 - Nouvelle Partie\n");
    printf(" 2 - Sauvegarde\n");
    printf(" 3 - Charger une partie\n");
    printf(" 4 - Afficher les règles / crédits\n");
    printf(" 5 - Quitter\n");
    printf("\n Votre choix : ");
    scanf("%d", &choix);

    switch(choix)
    {
        case 1:
            printf("\nNouvelle Partie\n");
            nouvellepartie();
            
            break;
        
        case 2:
            printf("\nSauvegarde\n");
            SauvegarderPartie();
            printf("Votre partie a été sauvegardée !\n");
            
            break;
        
        case 3:
            printf("\nCharger une partie\n");
            printf("Séléctionnez une partie à charger : \n");
            ChargerPartie();

            break;
        
        case 4:
            printf("\nAfficher les règles / crédits\n");
            Regles();
            
            break;
        
        case 5:
            printf("\nQuitter\n");
            Quitter();
            
            break;
        default:
            printf("Erreur");
            
            break;
        }
    
    return 0;
}
