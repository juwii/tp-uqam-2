#ifndef CESAR_H
#define CESAR_H
#endif

#include "cesar.h"

/* ******* CONTRAINTES ***********
indentation de 3 espaces
fonctions pas plus de 10 lignes
gerer erreurs systèmes
identifiants en snake case
*/


// main doit faire 10 lignes max
int main(int argc, char *argv[]){
    gestion_erreurs(argc, argv);
    cesar c;
    c.entree = fopen(argv[1],"r");
    c.sortie = fopen(argv[2],"w");
    // appel fonctions
    dechiffrer_message(&c);
    fclose(c.entree);
    fclose(c.sortie);
    return 0;
}