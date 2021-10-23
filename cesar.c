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


// définition des fonctions

// affichage des erreurs a voir si les break marchent
void afficher_erreurs(enum erreurs erreur){
   switch(erreur){
      case 404 : printf(ERR_MANQUE_ARGUMENTS); 
         break;
      case 1: printf(ERR_TROP_ARGUMENTS); 
         break;
      case 2: printf(ERR_TEXTE_TROP_LONG); 
         break;
   }
}

/* gestion des erreurs */

// a appeler au debut apres affichage du manuel
// manque des arguments
void erreur_manque_arguments(int argc){
   if(argc < 3) {
      afficher_erreurs(404);
      exit(404);
   }
}

// trop d'arguments
void erreur_trop_arguments(int argc){
    if(argc > 3) {
       afficher_erreurs(1);
       exit(1);
    }
}

// a appeler apres l'ouverture du fichier a voir si besoin de documenter
// texte trop long
void erreur_longueur_texte(cesar c){
    if(c.taille > MAX_CARACTERES) {
       afficher_erreurs(2);
       exit(2);
    }
}


/* affichage du manuel */
void afficher_manuel(int argc, char *argv[]){
   if(argc == 1) {
      printf(MANUEL, argv[0]);
      exit(0);
   }
}

// a voir si besoin de gérer hors bash si pas fichier en argument

/* Ouverture du fichier */

