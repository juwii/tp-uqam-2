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

// affichage des erreurs systèmes
void afficher_erreurs_systeme(enum erreurs_systeme erreur){
   switch(erreur){
      case 3 : printf(ERR_LECTURE_ENTREE); 
         break;
      case 4: printf(ERR_PERMISSION_SORTIE); 
         break;
   }
}

/* gestion des erreurs */

// a appeler au debut apres affichage du manuel
// manque des arguments
void erreur_manque_arguments(int argc, cesar *c){
   if(argc < 3) {
      fermer_fichiers(c);
      afficher_erreurs(404);
      exit(44);
   }
}

// trop d'arguments
void erreur_trop_arguments(int argc, cesar *c){
    if(argc > 3) {
       fermer_fichiers(c);
       afficher_erreurs(1);
       exit(1);
    }
}

// a appeler apres l'ouverture du fichier a voir si besoin de documenter
// texte trop long
void erreur_longueur_texte(int taille, cesar *c, char caractere){
    if(caractere=='\n'){
       if(taille > MAX_CARACTERES) {
          fermer_fichiers(c);
          afficher_erreurs(2);
          exit(2);
       }
       c->taille = 0;
    }
}

// on lit le fichier pour vérifier nombre de caracteres par ligne
void verifier_longueur_texte(cesar *c){
   fseek(c->entree,0,SEEK_SET);
   while(1){
      if(feof(c->entree)) break;
      c->taille = c->taille + 1; // c->taille initialisé à 0
      erreur_longueur_texte(c->taille-1, c, fgetc(c->entree));  
   }
}

/* affichage du manuel */
void afficher_manuel(int argc, char *argv[], cesar *c){
   if(argc == 1) {
      printf(MANUEL, argv[0]);
      exit(0);
   }
}

/* gestion des erreurs systèmes */

// si le fichier en entree n'existe pas ou pas les droits
void erreur_fichier_inexistant(char *argv[]){
   if(!(fopen(argv[1], "r"))){
      afficher_erreurs_systeme(3);
      exit(3);
   }
}

// si le fichier en sortie n'est pas accessible en écriture
void erreur_permission_ecriture(char *argv[]){
   if(!(fopen(argv[2], "w"))){
      afficher_erreurs_systeme(4);
      exit(4);
   }
}

void gestion_erreurs_systeme(char *argv[]){
   erreur_fichier_inexistant(argv);
   erreur_permission_ecriture(argv);
}

// appelle fonctions erreurs
void gestion_erreurs(int argc, char *argv[], cesar *c){
   erreur_manque_arguments(argc, c);
   erreur_trop_arguments(argc, c);
   erreur_fichier_inexistant(argv);
   c->taille = 0; // initialisation de la taille 
   verifier_longueur_texte(c);
}

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
      if((c->chiffre[i]>='a' && c->chiffre[i]<='z') || (c->chiffre[i]>='A' && c->chiffre[i]<='Z')){ // remplacer par isalpha
         decaler_caractere(c, i);
      } else {
         c->clair[i] = c->chiffre[i];
      }  
   }
}

// ecrire dans le fichier en sortie
void ecrire_clair(cesar *c){
   fseek(c->sortie,0,SEEK_SET);
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
   liberer_pointeurs(c);
}

// fonction qui va ouvrir les fichiers
void ouvrir_fichiers(char *argv[], cesar *c){
   c->entree = fopen(argv[1],"r");
   c->sortie = fopen(argv[2],"w");
}

// fonction qui va fermer les fichiers
void fermer_fichiers(cesar *c){
   fclose(c->entree);
   fclose(c->sortie);
}









