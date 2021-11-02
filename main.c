/********** Inclusion **********/

#ifndef CESAR_H
#define CESAR_H
#endif

#include "cesar.h"

/* ******* CONTRAINTES ***********
indentation de 3 espaces v
fonctions pas plus de 10 lignes v
gerer erreurs systèmes v
identifiants en snake case v
*/

int main(int argc, char *argv[]){
   cesar c;
   afficher_manuel(argc, argv, &c);
   gestion_erreurs_systeme(argv, &c, argc);
   ouvrir_fichiers(argv, &c);
   gestion_erreurs(argc, argv, &c);
   dechiffrer_message(&c);
   fermer_fichiers(&c);
   return 0;
}