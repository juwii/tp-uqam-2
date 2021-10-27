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

// appelle fonctions erreurs
void gestion_erreurs(int argc, char *argv[]){
   afficher_manuel(argc,argv);
   erreur_manque_arguments(argc);
   erreur_trop_arguments(argc);
}

// a voir si besoin de gérer hors bash si pas fichier en argument => OUI

/* Ouverture du fichier */

// recuperer taille 
void recuperer_taille(cesar *c){
   fseek(c->entree,0,SEEK_SET);
   c->taille = 0;
   char caractere;
   while(1){
      caractere = (char)fgetc(c->entree);
      if (feof(c->entree)) break;
      c->taille = c->taille + 1;
   }
}

// ini pointeurs
void initialiser_pointeurs(cesar *c){
   c->chiffre = malloc(sizeof(char)*c->taille);
   c->clair = malloc(sizeof(char)*c->taille);
}

// libérer pointeurs
void liberer_pointeurs(cesar *c){
   free(c->chiffre);
   free(c->clair);
}

// recuperer texte chiffré
void recuperer_texte_chiffre(cesar *c){
   int i = 0;
   fseek(c->entree,0,SEEK_SET);
   while(1){
      c->chiffre[i] = fgetc(c->entree);
      if (feof(c->entree)) break;
      i = i + 1;
   } 
}

// decaler un caractere
void decaler_caractere(cesar *c, int indice){
   if(c->chiffre[indice] - CLEF < 'a' && islower(c->chiffre[indice])!=0){
      c->clair[indice] = 'z' - CLEF + c->chiffre[indice] - 'a';
   } 
   else if(c->chiffre[indice] - CLEF < 'A' && isupper(c->chiffre[indice])!=0){
      c->clair[indice] = (char)('Z' - CLEF + c->chiffre[indice]);
   } else {
      c->clair[indice] = c->chiffre[indice] - CLEF;
   }
}

// remplir le tableau clair
void remplir_tableau_clair(cesar *c){
   int i = 0;
   for(i = 0; i<c->taille; i++){
      if((c->chiffre[i]>='a' && c->chiffre[i]<='z') || (c->chiffre[i]>='A' && c->chiffre[i]<='Z')){
         decaler_caractere(c, i);
      } else {
         c->clair[i] = c->chiffre[i];
      }  
   }
}

// ecrire dans le fichier en sortie
void ecrire_clair(cesar *c){
   int i;
   for(i = 0; i<c->taille; i++){
      fputc(c->clair[i],c->sortie);
   }
}

// dechiffrer
void dechiffrer_message(cesar *c){
   recuperer_taille(c);
   initialiser_pointeurs(c);
   recuperer_texte_chiffre(c);
   remplir_tableau_clair(c);
   ecrire_clair(c);
}









