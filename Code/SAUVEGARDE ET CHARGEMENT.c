#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//fonction qui permet de charger une partie sauvegardée
void chargerPartie()
{
    FILE* fichier = NULL;
    char chaine[100] = "";
    int i = 0;

    fichier = fopen("partieSauvegardee.txt", "r");

    if (fichier != NULL)
    {
        while (fgets(chaine, 100, fichier) != NULL) // On lit le fichier tant qu'on ne reçoit pas d'erreur (NULL)
        {
            printf("%s", chaine); // On affiche la chaîne qu'on vient de lire
        }
        fclose(fichier);
    }
}

//fonction qui permet de sauvegarder une partie
void sauvegarderPartie()
{
    FILE* fichier = NULL;
    char chaine[100] = "";
    int i = 0;

    fichier = fopen("partieSauvegardee.txt", "w");

    if (fichier != NULL)
    {
        while (fgets(chaine, 100, fichier) != NULL) // On lit le fichier tant qu'on ne reçoit pas d'erreur (NULL)
        {
            printf("%s", chaine); // On affiche la chaîne qu'on vient de lire
        }
        fclose(fichier);
    }
}

// J'aime mes frites 

