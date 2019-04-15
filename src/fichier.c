#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "fichier.h"


/*
Fonction qui ouvre un fichier en mode écriture.
*/
int ouvrir_fichier(FILE **fichier) {
    *fichier = fopen("arbres/arbre.quad", "w+");
    
    if (NULL == *fichier)
        return 0;

    return 1;
}

/*
Fonction qui vérifie que le fichier image de la chaîne de caractères existe.
Elle renvoie 1 si elle existe, 0 sinon.
*/
int verif_img(char s[]) {
    char chemin[500] = "images/";
    FILE *fichier = NULL;

    strcat(chemin, s);
    fichier = fopen(chemin, "r");
    
    if (NULL == fichier)
        return 0;

    return 1;
}

/*
Fonction qui vérifie que le fichier Quadtree de la chaîne de caractères existe.
Elle renvoie 1 si elle existe, 0 sinon.
*/
int verif_fichier_quad(char s[]) {
    char chemin[500] = "arbres/";
    FILE *fichier = NULL;

    strcat(chemin, s);
    fichier = fopen(chemin, "r");
    
    if (NULL == fichier)
        return 0;

    return 1;
}


/*
Fonction qui code les noeuds de l'arbre dans un fichier.
0 pour un noeud interne, et 1 suivi du niveau de gris pour une feuille.
*/
void ecrire_arbre_dans_fichier(Arbre a, FILE *fichier) {
    assert(NULL != fichier);
    
    if (NULL != a) {
        if ( (NULL == a->f1) && (NULL == a->f2) && (NULL == a->f3) && (NULL == a->f4) )
            fprintf(fichier, "1 %d ", a->valeur);

        else
            fprintf(fichier, "0 ");

        ecrire_arbre_dans_fichier(a->f1, fichier);
        ecrire_arbre_dans_fichier(a->f2, fichier);
        ecrire_arbre_dans_fichier(a->f3, fichier);
        ecrire_arbre_dans_fichier(a->f4, fichier);
    }
}


/*
Fonction qui créée l'arbre écrit dans un fichier.
*/
int copie_arbre(Arbre *a, FILE *fichier) {
    int res, val;
    
    res = fscanf(fichier, "%d ", &val);
    if (res < 1)
        return 0;

    if (val == 0) {
        *a = allouerNoeud(val);

        if ( !copie_arbre(&((*a)->f1), fichier) )
            return 0;
        if ( !copie_arbre(&((*a)->f2), fichier) )
            return 0;
        if ( !copie_arbre(&((*a)->f3), fichier) )
            return 0;
        if ( !copie_arbre(&((*a)->f4), fichier) )
            return 0;
    }

    else {
        res = fscanf(fichier, "%d ", &val);
        if (res < 1)
            return 0;

        *a = allouerNoeud(val);
    }

    return 1;
}