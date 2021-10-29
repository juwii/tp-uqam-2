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
    cesar c;
    afficher_manuel(argc, argv, &c);
    gestion_erreurs_systeme(argv, &c, argc);
    ouvrir_fichiers(argv, &c);
    gestion_erreurs(argc, argv, &c);
    // appel fonctions
    dechiffrer_message(&c);
    fermer_fichiers(&c);
    return 0;
}