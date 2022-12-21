#include <stdio.h>
#include <stdlib.h>


void sauvgarde(int score,int coups,char *nom_fichier) {
    FILE *fichier;
    fichier=fopen(nom_fichier,"score.txt");
    if (fichier==NULL){
        printf("Impossible de charger la partie");
        return;
    }

    fprintf(fichier,"score=%d",score);
    fprintf(fichier,"coups=%d",coups);
    fclose(fichier);
    printf("Partie sauvgardée");
}

//sauvgarde de la partie dans un fichier texte tout en prenant en parametres les scores du jeu et le nombre de coups joués par le joueur et le nom du fichier dans lequel on veut sauvgarder la partie
