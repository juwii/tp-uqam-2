# inf3135-automne2021-tp2

TP2 de INF3135 : décryption du chiffrement de César


# Description

Ce projet est effectué dans le cadre du cours à l'UQAM "INF3135" (construction et maintenance de logiciels) enseigné par M. Serge Dogny. Il s'agit du TP2.  
Ce projet a pour but de déchiffrer des messages chiffrés avec le chiffrement de César avec une clé précise.  
Le langage de programmation utilisé est le langage C.
Dans ce cas, il s'agit d'une clé de 3. La lettre `a` est donc chiffrée par `d`.  
Le programme respecte la casse et ne déchiffre pas les caractères spéciaux.  
Le nombre de caractères maximum par ligne est 80.  
Il prend en compte les erreurs systèmes et les erreurs de saisie de l'utilisateur.


# Fichiers

* `Fichiers .c` : code
* `Fichiers .h` : interface contenant les imports des librairies, les déclarations des types et la 
documentation des fonctions.
* `Makefile` : script permettant de lancer automatiquement la compilation, les tests et d'autres commandes.
* `check.bats` : fichier contenant les tests
* `README.md` : documentation du projet
* `Sujet.md` : sujet du TP
* `.gitignore` : fichier permettant d'ignorer certains types de fichiers
* `fichier css` : 
* `gitlab-CI` : permet l'intégration continue du projet sur gitlab
* `Exemples` : dossier contenant des fichiers exemples utilisés par les tests


# Auteur

Juliette Létondot (LETJ74550003)


# Fonctionnement  

Pour utiliser le programme, il faut tout d'abord le compiler avec un terminal en lançant la commande `make build`.  
* Pour afficher le manuel du programme, exécuter le programme sans argument : `./cesar`.  
Le manuel du programme sera alors affiché :  

```bash
$ ./cesar
Manuel d'utilisation de ./cesar :
./cesar FICHIER1 FICHIER2
Le programme déchiffre le message contenu dans FICHIER1 et écrit le clair dans FICHIER2.
FICHIER1 : fichier en entrée contenant le message chiffré.
FICHIER2 : fichier en sortie qui va contenir le message déchiffré.
Attention : le programme va écraser le contenu du FICHIER2.
```

* Pour exécuter le programme, il faut alors utiliser la commande `./cesar fichier1.txt fichier2.txt` avec fichier1 et fichier2 les chemins vers les fichiers souhaités.  
Rappel : le fichier1 est le fichier dont le contenu sera déchiffré, le fichier2 sera le fichier dans lequel sera écrit le message en clair. Le programme n'affichera rien en sortie si tout s'est bien passé.  

Exemple :  

```bash
$ ./cesar exemples/chiffre.txt exemples/clair.txt
$ echo $?
0
$ cat exemples/chiffre.txt
D ! Erqmrxu mh p'dsshooh Mxolhwwh.

/!
$ cat exemples/clair.txt
A ! Bonjour je m'appelle Juliette.

/!
```
Le chiffré de `exemples/clair.txt` a donc bien été déchiffré dans `exemples/clair.txt`.  

* En cas d'erreur, le programme affiche un message d'erreur associé et quitte le programme.  
Exemple :

* Les différents cas d'erreurs gérés sont : le fichier d'entrée n'est pas accessible en lecture ou n'existe pas,  
le fichier en sortie n'est pas accessible en écriture, le nombre de caractères par ligne est trop long,  
le nombre de paramètres saisis par l'utilisateur n'est pas bon.  
  

# Tests

Les tests peuvent être lancés automatiquement avec la commande `make start`.  
Voici la liste des tests du programme ainsi que leur statut : 

bats check.bats
 ✓ Avec aucun argument, affiche le manuel
 ✓ Avec 1 argument affiche une erreur
 ✓ Avec 3 arguments affiche une erreur
 ✓ Affiche une erreur quand le fichier en entrée n'existe pas
 - Affiche une erreur quand le fichier en sortie n'est pas modifiable (skipped)
 ✓ Affiche une erreur quand le fichier a des lignes trop longues
 ✓ Déchiffre un caractère
 ✓ Déchiffre un mot
 ✓ Toutes les lettres alphabétiques minuscules sont déchiffrées correctement
 ✓ Le déchiffrement respecte la casse
 ✓ Toutes les lettres alphabétiques majuscules sont déchiffrées correctement
 ✓ Les caractères spéciaux ne sont pas déchiffrés
 ✓ Déchiffre un message avec plusieurs lignes
 ✓ Déchiffre un message de plusieurs lignes avec des lettres et des caractères non alphabétiques

14 tests, 0 failures, 1 skipped


# Dépendances

gcc
bats


# Références


# Etat du projet

Exigences du code source :  
[X] L'indentation doit être de 3 espaces.  
[X] Code découpé en fonctions ne dépassant pas 10 lignes.  
[X] Fichier d'en-tête .h et fichier d'implémentation .c  
[X] Erreurs systèmes gérées  
[X] Identifiants de fonctions et variables en snake_case  
[X] Rédaction de "bons" tests unitaires  
[X] `bats` comme cadre de test  
[X] Intégration continue gitlab-CI  

Exigences techniques :  
[X] Projet en C qui compile sans avertissement et sans erreur sur le serveur java de l'UQAM  
[X] Votre dépôt doit se nommer exactement ....  
[X] URL exactement ...  
[X] Dépôt privé  
[X] Correcteurs ont accès  

