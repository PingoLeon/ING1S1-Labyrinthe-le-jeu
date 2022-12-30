#include <stdio.h>
#include <stdlib.h>


void sauvgardeetcharger(int score,int nbtresors,char labyrinthe,char *nom_fichier) {
    FILE *fichier;
    fichier=fopen(nom_fichier,"score.txt");
    if (fichier==NULL){
        printf("Impossible de charger la partie");
        return;
    }

    fprintf(fichier,"score=%d",score);
    fprintf(fichier,"trésors trouvés=%d",coups);
    fprint(fichier, "chargement du labyrinthe en cours...",labyrinthe);
    fclose(fichier);
    printf("Partie sauvgardée");
}

void main() {
    sauvegardeetcharger(1000,10,"score.txt");
    }
