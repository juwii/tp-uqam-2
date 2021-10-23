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


// main
int main(int argc, char *argv[]){
    afficher_manuel(argc,argv);
    erreur_manque_arguments(argc);
    erreur_trop_arguments(argc);
    return 0;
}