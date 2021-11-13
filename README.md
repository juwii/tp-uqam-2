# inf3135-automne2021-tp2

TP2 de INF3135 : décryption du chiffrement de César


## Description

Ce projet est effectué dans le cadre du cours à l'UQAM "INF3135" (construction et maintenance de logiciels) enseigné par M. Serge Dogny. Il s'agit du TP2.  
Ce projet a pour but de déchiffrer des messages chiffrés avec le chiffrement de César avec une clé précise.  
Le langage de programmation utilisé est le langage C.
Pour ce TP, il s'agit d'une clé fixe de 3. La lettre `a` est donc chiffrée par `d`.  
Le programme respecte la casse et ne déchiffre pas les caractères spéciaux.  
Le nombre de caractères maximum par ligne est 80.  
Il prend en compte les erreurs systèmes et les erreurs de saisie de l'utilisateur.


## Fichiers

* `Fichiers .c` : implémentation des fonctions
* `Fichiers .h` : interface contenant les imports des librairies, les déclarations des types et la 
documentation des fonctions.
* `Makefile` : script permettant de lancer automatiquement la compilation, les tests et d'autres commandes. Il supporte les cibles : all, start, build, link, clean.
* `check.bats` : fichier contenant les tests
* `README.md` : documentation du projet
* `TP2.pdf` : sujet du TP
* `.gitignore` : fichier permettant d'ignorer certains types de fichiers
* `gitlab-CI` : permet l'intégration continue du projet sur gitlab
* `Exemples` : dossier contenant des fichiers exemples utilisés par les tests


## Auteur

Juliette Létondot (LETJ74550003)


## Fonctionnement  

* Pour utiliser le programme, il faut tout d'abord le compiler avec un terminal en lançant la commande `make build` ou `make`. 
       
* Pour afficher le manuel du programme, exécuter le programme sans argument : `./cesar`.  
Le manuel du programme sera alors affiché :  

```
$ ./cesar
Manuel d'utilisation de ./cesar :
./cesar FICHIER1 FICHIER2
Le programme déchiffre le message contenu dans FICHIER1 et écrit le clair dans FICHIER2.
FICHIER1 : fichier en entrée contenant le message chiffré.
FICHIER2 : fichier en sortie qui va contenir le message déchiffré.
Attention : le programme va écraser le contenu du FICHIER2.
```

* Pour exécuter le programme, il faut utiliser la commande `./cesar fichier1.txt fichier2.txt` avec fichier1 et fichier2 les chemins vers les fichiers souhaités.  
Rappel : le fichier1 est le fichier dont le contenu sera déchiffré, le fichier2 sera le fichier dans lequel sera écrit le message en clair. Le programme n'affichera rien en sortie si tout s'est bien passé.  

Exemple :  

```
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
Exemple avec quelques cas d'erreurs :

```
$ ./cesar entree.txt
Attention erreur argument manquant
Manuel d'utilisation de ./cesar :
./cesar FICHIER1 FICHIER2
Le programme déchiffre le message contenu dans FICHIER1 et écrit le clair dans FICHIER2.
FICHIER1 : fichier en entrée contenant le message chiffré.
FICHIER2 : fichier en sortie qui va contenir le message déchiffré.
Attention : le programme va écraser le contenu du FICHIER2.
$ ./cesar entree.txt entree.txt sortie.txt
Attention erreur trop d'arguments
Manuel d'utilisation de ./cesar :
./cesar FICHIER1 FICHIER2
Le programme déchiffre le message contenu dans FICHIER1 et écrit le clair dans FICHIER2.
FICHIER1 : fichier en entrée contenant le message chiffré.
FICHIER2 : fichier en sortie qui va contenir le message déchiffré.
Attention : le programme va écraser le contenu du FICHIER2.
$ ./cesar fichier_inconnu.txt sortie.txt
Erreur système : le fichier en entrée n'existe pas ou n'est pas disponible en lecture
```

* Les différents cas d'erreurs gérés sont : le fichier d'entrée n'est pas accessible en lecture ou n'existe pas, le fichier en sortie n'est pas accessible en écriture ou le chemin n'existe pas, les erreurs de fermeture du fichier, le nombre de caractères par ligne est trop long, le nombre de paramètres saisis par l'utilisateur n'est pas bon.  
  
* Makefile : La cible **build** permet de compiler le programme. La cible **link** permet d'obtenir un fichier exécutable. La cible **clean** permet de supprimer les fichiers .o et le fichier exécutable. La cible **start** permet de lancer les tests. La cible **all** appelle les cibles **link** et **start** donc elle compile le programme et lance les tests.


## Tests

Les tests peuvent être lancés automatiquement avec la commande `make start`.  
Voici la liste des tests du programme ainsi que leur statut : 

```
bats check.bats    
 ✓ Avec aucun argument, affiche le manuel  
 ✓ Avec 1 argument affiche une erreur  
 ✓ Avec 3 arguments affiche une erreur  
 ✓ Affiche une erreur quand le fichier en entrée n'existe pas  
 ✓ Affiche une erreur quand le chemin vers le fichier en sortie n'existe pas  
 ✓ Affiche une erreur quand le fichier a des lignes trop longues  
 ✓ Déchiffre un caractère  
 ✓ Déchiffre un mot  
 ✓ Toutes les lettres alphabétiques minuscules sont déchiffrées correctement  
 ✓ Le déchiffrement respecte la casse  
 ✓ Toutes les lettres alphabétiques majuscules sont déchiffrées correctement  
 ✓ Les caractères spéciaux ne sont pas déchiffrés  
 ✓ Déchiffre un message avec plusieurs lignes  
 ✓ Déchiffre un message de plusieurs lignes avec des lettres et des caractères non alphabétiques  
 ✓ Déchiffre le message du fichier test de Serge Dogny  

15 tests, 0 failures
```

## Dépendances

* [bats](https://github.com/bats-core/bats-core)  
* [gcc](https://gcc.gnu.org/)  


## Références

* Chiffrement de César avec Python : [https://www.bibmath.net/forums/viewtopic.php?id=2382](https://www.bibmath.net/forums/viewtopic.php?id=2382)
* Gestion de fermeture de fichiers : [https://openclassrooms.com/forum/sujet/fermeture-de-fichier-54059](https://openclassrooms.com/forum/sujet/fermeture-de-fichier-54059)


## Etat du projet

Exigences du code source :

* [X] L'indentation doit être de 3 espaces. Aucune tabulation n'est permise dans l'indentation.
* [X] Votre code doit être découpé en fonctions d’une longueur ne dépassant pas 10 lignes par fonction.
* [X] Vous devez adapter une approche de programmation modulaire. Utilisez de fichier d’en-tête (.h) pour représenter vos interfaces et cacher vos implémentations dans les fichiers (.c). Vos modules devraient suivre le standard vu en classe.
* [X] Les erreurs systèmes doivent être gérées correctement (ouverture-fermeture de fichier).
* [X] Les identifiants de fonctions et variables doivent être en snake_case.
* [X] Vous devez rédiger suffisamment de « bons » tests unitaires afin d'acquérir une couverture de tests satisfaisante sur tout votre projet.
* [X] Vous devrez utiliser bats comme cadre de test de votre logiciel.
* [X] Une attention particulière doit être apportée à la lisibilité du code source.
* [X] Vous devez ajouter une intégration continue (GitLab-CI) de votre projet.

Exigences techniques :

* [X] Votre travail doit être rédigé en langage C et doit compiler sans erreur et sans avertissement (compilation avec l'option -Wall) sur le serveur Java de l’UQAM (java.labunix.uqam.ca). Pour vous y connecter, vous devez connaître votre CodeMS (de la forme ab123456) ainsi que votre mot de passe (de la forme ABC12345) (Pénalité **20%**).
* [X] Votre dépôt doit se nommer exactement inf3135-automne2021-tp2 (Pénalité **20%**).
* [X] L'URL de votre dépôt doit être exactement https://gitlab.info.uqam.ca/letondot.juliette/inf3135-automne2021-tp2 (Pénalité **20%**).
* [X] Votre dépôt doit être privé (Pénalité **20%**).
* [X] Les usagers @correcteurs et dogny_g doivent avoir accès à votre projet comme Developer (Pénalité **20%**).
