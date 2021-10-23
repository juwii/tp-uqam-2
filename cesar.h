/**
 * TP2 : décryption du chiffrement de César
 * 
 * Le projet consiste en le déchiffrage d'un texte d'un fichier en entree standard
 * le texte en clair est enregistré dans un fichier en sortie standard
 * @author  Juliette Létondot
 */


/* CONTRAINTES
indentation de 3 espaces
fonctions pas plus de 10 lignes
gerer erreurs systèmes
identifiants en snake case
*/

// import
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// constantes
#define MAX_CARACTERES 80
#define CLEF 3
#define MANUEL "Manuel d'utilisation de %s : \n"
#define ERR_MANQUE_ARGUMENTS "Attention erreur argument manquant \n"
#define ERR_TROP_ARGUMENTS "Attention erreur trop d'arguments \n"
#define ERR_TEXTE_TROP_LONG "Attention erreur texte trop long"
#define ASCII(X) ((int)(X))

// types
enum erreurs {
   MANQUE_ARGUMENTS = 404,
   TROP_ARGUMENTS = 1,
   TEXTE_TROP_LONG = 2
};

typedef struct {
   char *chiffre; // contenu du texte chiffré
   char *clair; // contenu du texte en clair
   int taille; // taille du texte
   FILE* entree; // fichier en entree avec le contenu à déchiffrer
   FILE* sortie; // fichier en sortie qui contiendra le texte en clair
}cesar;

// definition des fonctions

/**
* affiche une description de l'erreur rencontrée
* @param   enum erreurs erreur  numéro de l'erreur rencontrée
*/
void afficher_erreurs(enum erreurs erreur);

/**
* affiche le manuel d'utilisation 
* @param   int argc      nombre d'arguments en entrée
           char *argv    liste des arguments en entrée
*/
void afficher_manuel(int argc, char *argv[]);

/**
 * affiche une erreur s'il n'y a pas 3 arguments
 * @param   int argc   nombre d'arguments en entrée
 */
void erreur_manque_arguments(int argc);

/**
 * affiche une erreur s'il y a plus de 3 arguments
 * @param   int argc   nombre d'arguments en entrée
 */
void erreur_trop_arguments(int argc);

