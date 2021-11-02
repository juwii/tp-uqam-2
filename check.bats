# Tests

# def des constantes

examples_folder=examples
prog=cesar
aide_premiere_ligne="Manuel d'utilisation de ./cesar :"
erreur_manque_argument="Attention erreur argument manquant"
erreur_trop_argument="Attention erreur trop d'arguments"
erreur_lecture_entree="Erreur système : le fichier en entrée n'existe pas ou n'est pas disponible en lecture"
erreur_permission_sortie="Erreur système : pas de permission d'écriture sur le fichier en sortie"
erreur_longueur_texte="Attention erreur texte trop long"

# Normal usage

@test "Avec aucun argument, affiche le manuel" {
   run ./$prog
   [ "$status" -eq 0 ]
   [ "${lines[0]}" = "$aide_premiere_ligne" ]
}

@test "Avec 1 argument affiche une erreur" {
   run ./$prog test.txt
   [ "$status" -eq 44 ]
   [ "${lines[0]}" = "$erreur_manque_argument" ]
}

@test "Avec 3 arguments affiche une erreur" {
   run ./$prog test.txt test.txt test.txt
   [ "$status" -eq 1 ]
   [ "${lines[0]}" = "$erreur_trop_argument" ]
}

@test "Affiche une erreur quand le fichier en entrée n'existe pas" {
   run ./$prog fichier_non_existant test.txt
   [ "$status" -eq 3 ]
   [ "${lines[0]}" = "$erreur_lecture_entree" ]
}

@test "Affiche une erreur quand le fichier en sortie n'est pas modifiable" {
   skip
   run ./$prog exemples/chiffre.txt exemples/clair2.txt
   [ "$status" -eq 4 ]
   [ "${lines[0]}" = "$erreur_permission_sortie" ]
}

@test "Affiche une erreur quand le fichier a des lignes trop longues" {
   run ./$prog exemples/trop_long.txt exemples/clair.txt
   [ "$status" -eq 2 ]
   [ "${lines[0]}" = "$erreur_longueur_texte" ]
} 

@test "Déchiffre un caractère" {
   run ./$prog exemples/caractere_d.txt exemples/clair.txt
   [ "$status" -eq 0 ]
   run cat exemples/clair.txt
   [ "$status" -eq 0 ]
   [ "${lines[0]}" = "y" ]
}

@test "Déchiffre un mot" {
   run ./$prog exemples/mot.txt exemples/clair.txt
   [ "$status" -eq 0 ]
   run cat exemples/clair.txt
   [ "$status" -eq 0 ]
   [ "${lines[0]}" = "Bonjour" ]
}

@test "Toutes les lettres alphabétiques minuscules sont déchiffrées correctement" {
   run ./$prog exemples/alphabet_minuscule.txt exemples/clair.txt
   [ "$status" -eq 0 ]
   run cat exemples/clair.txt
   [ "$status" -eq 0 ]
   [ "${lines[0]}" = "abcdefghijklmnopqrstuvwxyz" ]
} 

# comment on fait pour accents ?

@test "Le déchiffrement respecte la casse" {
   run ./$prog exemples/minuscule_maj.txt exemples/clair.txt
   [ "$status" -eq 0 ]
   run cat exemples/clair.txt
   [ "$status" -eq 0 ]
   [ "${lines[0]}" = "aB" ]
}

@test "Toutes les lettres alphabétiques majuscules sont déchiffrées correctement" {
   run ./$prog exemples/alphabet_majuscule.txt exemples/clair.txt
   [ "$status" -eq 0 ]
   run cat exemples/clair.txt
   [ "$status" -eq 0 ]
   [ "${lines[0]}" = "ABCDEFGHIJKLMNOPQRSTUVWXYZ" ]
}

@test "Les caractères spéciaux ne sont pas déchiffrés" {
   run ./$prog exemples/caracteres_speciaux.txt exemples/clair.txt
   [ "$status" -eq 0 ]
   run cat exemples/clair.txt
   [ "$status" -eq 0 ]
   [ "${lines[0]}" = '&~#3|-\`\"\(\\^,_+./*;!$¤?:%<> ' ]
}

@test "Déchiffre un message avec plusieurs lignes" {
   run ./$prog exemples/lignes.txt exemples/clair.txt
   [ "$status" -eq 0 ]
   run cat exemples/clair.txt
   [ "$status" -eq 0 ]
   [ "${lines[0]}" = "bonjourjesuisjuliette  " ]
   [ "${lines[1]}" = "jedoisecriresanscaracteresspeciaux" ]
}

@test "Déchiffre un message de plusieurs lignes avec des lettres et des caractères non alphabétiques" {
   run ./$prog exemples/texte.txt exemples/clair.txt
   [ "$status" -eq 0 ]
   run cat exemples/clair.txt
   [ "$status" -eq 0 ]
   [ "${lines[0]}" = "Bonjour, je suis Juliette.  " ]
   [ "${lines[1]}" = "Je dois ecrire sans caracteres speciaux.  " ]
   [ "${lines[2]}" = "Enfin plus maintenant haha ! 8)  " ]
}

