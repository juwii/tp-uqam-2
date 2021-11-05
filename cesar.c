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

// Attention free la mémoire avant de exit

/********** Définition des fonctions **********/

void afficher_erreurs(enum erreurs erreur){
   switch(erreur){
      case 44 : printf(ERR_MANQUE_ARGUMENTS); 
         break;
      case 1: printf(ERR_TROP_ARGUMENTS); 
         break;
      case 2: printf(ERR_TEXTE_TROP_LONG); 
         break;
   }
}

void afficher_erreurs_systeme(enum erreurs_systeme erreur){
   switch(erreur){
      case 3 : printf(ERR_LECTURE_ENTREE); 
         break;
      case 4: printf(ERR_PERMISSION_SORTIE); 
         break;
   }
}

void erreur_manque_arguments(int argc, char *argv[], cesar *c){
   if(argc < 3) {
      afficher_erreurs(44);
      printf(MANUEL, argv[0], argv[0]);
      exit(44);
   }
}

void erreur_trop_arguments(int argc, char *argv[], cesar *c){
   if(argc > 3) {
      afficher_erreurs(1);
      printf(MANUEL, argv[0], argv[0]);
      exit(1);
   }
}

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

void verifier_longueur_texte(cesar *c){
   fseek(c->entree,0,SEEK_SET);
   while(1){
      if(feof(c->entree)) break;
      c->taille = c->taille + 1; 
      erreur_longueur_texte(c->taille-1, c, fgetc(c->entree));  
   }
}

void afficher_manuel(int argc, char *argv[], cesar *c){
   if(argc == 1) {
      printf(MANUEL, argv[0], argv[0]);
      exit(0);
   }
}

void erreur_fichier_inexistant(char *argv[]){
   if(!(fopen(argv[1], "r"))){
      afficher_erreurs_systeme(3);
      exit(3);
   }
}

void erreur_permission_ecriture(char *argv[]){
   if(!(fopen(argv[2], "w"))){
      // fermer fichier en entrée
      afficher_erreurs_systeme(4);
      exit(4);
   }
}

void gestion_erreurs_systeme(char *argv[], cesar *c, int argc){
   erreur_manque_arguments(argc, argv, c);
   erreur_trop_arguments(argc, argv, c);
   erreur_fichier_inexistant(argv);
   erreur_permission_ecriture(argv);
}

void gestion_erreurs(int argc, char *argv[], cesar *c){
   c->taille = 0; 
   verifier_longueur_texte(c);
}

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

void initialiser_pointeurs(cesar *c){
   c->chiffre = malloc(sizeof(char)*c->taille); // allocation mémoire à libérer
   c->clair = malloc(sizeof(char)*c->taille); // allocation mémoire à libérer
   if(!(c->chiffre) || !(c->chiffre)) {
      fprintf(stderr, "Erreur allocation de mémoire");
      exit(5);
   }
}

void liberer_pointeurs(cesar *c){
   free(c->chiffre); // libération de la mémoire allouée
   free(c->clair); // libération de la mémoire allouée
}

void recuperer_texte_chiffre(cesar *c){
   int i = 0;
   fseek(c->entree,0,SEEK_SET);
   while(1){
      c->chiffre[i] = fgetc(c->entree);
      if (feof(c->entree)) break;
      i = i + 1;
   } 
}

void decaler_caractere(cesar *c, int indice){
   if(c->chiffre[indice] - CLEF < 'a' && islower(c->chiffre[indice])!=0){
      c->clair[indice] = 'z' - CLEF + c->chiffre[indice] - 'a' + 1;
   } 
   else if(c->chiffre[indice] - CLEF < 'A' && isupper(c->chiffre[indice])!=0){
      c->clair[indice] = 'Z' - CLEF + c->chiffre[indice] - 'A' + 1;
   } else {
      c->clair[indice] = c->chiffre[indice] - CLEF;
   }
}

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

void ecrire_clair(cesar *c){
   fseek(c->sortie,0,SEEK_SET);
   int i;
   for(i = 0; i<c->taille; i++){
      fputc(c->clair[i],c->sortie);
   }
}

void dechiffrer_message(cesar *c){
   recuperer_taille(c);
   initialiser_pointeurs(c); // allocation mémoire
   recuperer_texte_chiffre(c);
   remplir_tableau_clair(c);
   ecrire_clair(c);
   liberer_pointeurs(c); // libération mémoire
}

void ouvrir_fichiers(char *argv[], cesar *c){
   c->entree = fopen(argv[1],"r");
   c->sortie = fopen(argv[2],"w");
}

void fermer_fichiers(cesar *c){
   if(fclose(c->entree)==EOF || fclose(c->sortie)==EOF){
      fprintf(stderr,ERR_FERMETURE_FICHIER);
      exit(6);
   }
}

