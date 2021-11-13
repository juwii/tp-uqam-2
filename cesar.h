/**
 * TP2 : décryption du chiffrement de César
 * 
 * Le projet a pour but de déchiffrer un texte d'un fichier en entree 
 * le texte en clair est enregistré dans un fichier en sortie 
 * 
 * @author  Juliette Létondot
 * 
 */

// imports
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// déclaration des constantes
#define MAX_CARACTERES 80
#define CLEF 3
#define MANUEL "Manuel d'utilisation de %s :\n\
%s FICHIER1 FICHIER2\n\
Le programme déchiffre le message contenu dans FICHIER1 et écrit le clair dans FICHIER2.\n\
FICHIER1 : fichier en entrée contenant le message chiffré.\n\
FICHIER2 : fichier en sortie qui va contenir le message déchiffré.\n\
Attention : le programme va écraser le contenu du FICHIER2.\n\
"
#define ERR_MANQUE_ARGUMENTS "Attention erreur argument manquant\n"
#define ERR_TROP_ARGUMENTS "Attention erreur trop d'arguments\n"
#define ERR_TEXTE_TROP_LONG "Attention erreur texte trop long\n"
#define ERR_LECTURE_ENTREE "Erreur système : le fichier en entrée n'existe pas ou n'est pas disponible en lecture\n"
#define ERR_PERMISSION_SORTIE "Erreur système : le chemin n'existe pas ou pas de permission d'écriture sur le fichier en sortie\n"
#define ERR_FERMETURE_FICHIER "Erreur lors de la fermeture des fichiers\n"

// déclaration des types
enum erreurs {
   MANQUE_ARGUMENTS = 44, 
   TROP_ARGUMENTS = 1,
   TEXTE_TROP_LONG = 2
};

enum erreurs_systeme {
   ERREUR_LECTURE_ENTREE = 3,
   ERREUR_PERMISSION_SORTIE = 4
};

typedef struct {
   char *chiffre; // contenu du texte chiffré
   char *clair; // contenu du texte en clair
   int taille; // taille du texte
   FILE* entree; // fichier en entree avec le contenu à déchiffrer
   FILE* sortie; // fichier en sortie qui contiendra le texte en clair
}cesar;

// declaration des fonctions

/**
* affiche une description de l'erreur rencontrée
* @param   enum erreurs erreur  numéro de l'erreur rencontrée
*/
void afficher_erreurs(enum erreurs erreur);

/**
 * affiche le manuel d'utilisation 
 * @param   int argc      nombre d'arguments en entrée
 *          char *argv    liste des arguments en entrée
 */
void afficher_manuel(int argc, char *argv[]);

/**
 * affiche une erreur s'il n'y a pas 3 arguments
 * @param   int argc       nombre d'arguments en entrée
 *          char *argv[]   liste des arguments en entrée
 */
void erreur_manque_arguments(int argc, char *argv[]);

/**
 * affiche une erreur s'il y a plus de 3 arguments
 * @param   int argc       nombre d'arguments en entrée
 *          char *argv[]   liste des arguments en entrée
 */
void erreur_trop_arguments(int argc, char *argv[]);

/**
 * teste si la taille de la longueur de la ligne respecte le maximum de caractères 
 * affiche un erreur si ce n'est pas le cas
 * @param   int taille      taille de la ligne
 *          cesar *c        pointeur vers la structure qui contient le fichier à examiner
 *          char caractere  caractere à vérifier exécute la vérification si c'est un fin de ligne
 */
void erreur_longueur_texte(int taille, cesar *c, char caractere);

/**
 * compte le nombre de caracteres sur chaque ligne pour vérifier que la condition
 * sur le maximum de caracteres par ligne est respectée
 * La fonction affiche une erreur si elle n'est pas respectée
 * @param   cesar *c   pointeur vers la structure qui contient le fichier à examiner
 */
void verifier_longueur_texte(cesar *c);

/**
 * appelle les fonctions de gestion des erreurs
 * @param   cesar *c       structure contenant les informations du message
 */
void gestion_erreurs(cesar *c);

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
 * Alloue de la mémoire dynamiquement et la libère à la fin de la fonction
 * @param   cesar *c   pointeur vers la structure c qui contient les informations
 *                     sur les message à déchiffrer
 */
void dechiffrer_message(cesar *c);

/**
 * ferme les fichiers c.entree et c.sortie
 * @param   cesar *c   pointeur vers la structure qui contient les fichiers à fermer
 */
void fermer_fichiers(cesar *c);

/**
 * ouvre les fichiers c.entree et c.sortie
 * @param   cesar *c       pointeur vers la structure qui contient les fichiers à ouvrir
 *          char *argv[]   liste des arguments en entrée   
 */
void ouvrir_fichiers(char *argv[], cesar *c);

/**
 * affiche les messages d'erreurs systèmes quand on tente d'ouvrir les fichiers
 * @param   enum erreurs_systeme erreur   numéro de l'erreur système
 */
void afficher_erreurs_systeme(enum erreurs_systeme erreur);

/**
 * affiche une erreur si le fichier en entrée ne s'ouvre pas
 * @param   char *argv[]   liste des arguments en entrée
 */
void erreur_fichier_inexistant(char *argv[]);

/**
 * affiche une erreur si le fichier en sortie ne s'ouvre pas en écriture
 * @param   char *argv[]   liste des arguments en entrée
 */
void erreur_permission_ecriture(char *argv[]);

/**
 * détecte les erreurs systèmes avant l'ouverture des fichiers
 * @param   char *argv[]   liste des arguments en entrée
 *          int argc       nombre d'arguments en entrée
 */
void gestion_erreurs_systeme(char *argv[], int argc);
