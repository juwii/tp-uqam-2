// Inclusions 

#ifndef CESAR_H
#define CESAR_H
#endif

#include "cesar.h"

int main(int argc, char *argv[]){
   cesar c;
   afficher_manuel(argc, argv);
   gestion_erreurs_systeme(argv, argc);
   ouvrir_fichiers(argv, &c);
   gestion_erreurs(&c);
   dechiffrer_message(&c);
   fermer_fichiers(&c);
   return 0;
}