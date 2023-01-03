#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int ChoixPions(){
  //asterix https://www.pngwing.com/en/free-png-zwdeu       ::vert
  //obelix https://www.pngwing.com/en/free-png-iyddk        ::bleu
  //idefix https://www.pngwing.com/en/free-png-cgyal        ::blanc
  //panoramix https://www.pngwing.com/en/free-png-pmcwe     ::rouge
for (int i = 0; i < 10; i++) {
  char personnages[4]= {'Asterix: https://www.pngwing.com/en/free-png-zwdeu' , 'Obelix:https://www.pngwing.com/en/free-png-iyddk ', 'Panoramix: https://www.pngwing.com/en/free-png-pmcwe', 'Idefix: https://www.pngwing.com/en/free-png-cgyal'};
  printf("%c", personnages[i]); 
  
}

}



int main()
{
    //MenuPrincipal();
    ChoixPions(); 
    return 0;
}