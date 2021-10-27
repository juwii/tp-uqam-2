/**
 * TP2 : décryption du chiffrement de César
 * 
 * Le projet consiste en le déchiffrage d'un texte d'un fichier en entree standard
 * le texte en clair est enregistré dans un fichier en sortie standard
 * 
 * @author  Juliette Létondot
 * 
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
#include <ctype.h>

// constantes
#define MAX_CARACTERES 80
#define CLEF 3
#define MANUEL "Manuel d'utilisation de %s : \n"
#define ERR_MANQUE_ARGUMENTS "Attention erreur argument manquant \n"
#define ERR_TROP_ARGUMENTS "Attention erreur trop d'arguments \n"
#define ERR_TEXTE_TROP_LONG "Attention erreur texte trop long"

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

/**
 * appelle les fonctions de gestion des erreurs
 * @param   int argc       nombre d'arguments en entrée
 *          char *argv[]   liste des arguments
 */
void gestion_erreurs(int argc, char *argv[]);

/**
 * calcule le nombre de caracteres du texte chiffré
 * @param   cesar *c   pointeur vers la structure contenant 5 paramètres avec les fichiers utilisés, 
 *                     les tableaux contenant les textes chiffré et clair et la taille
 */
void recuperer_taille(cesar *c);

/**
 * remplit le tableau chiffre de la structure c avec le texte chiffré
 * @param   cesar *c   pointeur vers la structure qui contient le champ qui sera modifié
 */
void recuperer_texte_chiffre(cesar *c);

/**
 * calcule un nouveau caractère décalé de la clef par rapport à celui de référence
 * @param   cesar *c      pointeur vers la structure c qui contient le texte chiffré et déchiffré
 *          int indice    indice du caractère à décaler dans le tableau chiffre de c
 */
void decaler_caractere(cesar *c, int indice);

/**
 * remplit le tableau clair de la structure c avec le texte en clair
 * @param   cesar *c   pointeur vers la structure c qui contient le texte en clair
 */
void remplir_tableau_clair(cesar *c);

/**
 * écrit dans le fichier en sortie le message en clair
 * @param   cesar *c   pointeur vers la structure c qui contient le texte en clair
 */
void ecrire_clair(cesar *c);

/**
 * appelle les fonctions intermédiaires pour déchiffrer le message et l'écrire dans le 
 * fichier en sortie
 * @param   cesar *c   pointeur vers la structure c qui contient les informations
 *                     sur les message à déchiffrer
 */
void dechiffrer_message(cesar *c);