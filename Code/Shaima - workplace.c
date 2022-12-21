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
