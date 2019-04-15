#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "quadtreeMelange.h"


/*
Fonction générant un nombre aléatoire entre a et b.
*/
int rand_a_b(int a, int b) {
    return rand()%(b-a) + a;
}


/*
Fonction qui interchange aléatoirement les noeuds d'un niveau donné en paramètre.
*/
void melange_arbre(Arbre *a, Arbre racine, int niveau, int niv_actuel) {
    int nb;
    Arbre pere = NULL, tmp = NULL;

    assert(0 < niveau && niveau < 4);
    assert(niv_actuel >= 0);

    if (NULL != *a) {
        if (niv_actuel == niveau) {
            /* récupérer le noeud interne de hauteur : niveau - 1
               pour pouvoir échanger les noeuds dans cette fonction */
            pere = melange_arbre_aux(racine, niveau, 0);

            nb = rand_a_b(1, 5);
            /* un cas pour chaque fils */
            switch (nb) {
                case 1:
                    tmp = *a;
                    *a = pere->f1;
                    pere->f1 = tmp;
                    break;

                case 2:
                    tmp = *a;
                    *a = pere->f2;
                    pere->f2 = tmp;
                    break;

                case 3:
                    tmp = *a;
                    *a = pere->f3;
                    pere->f3 = tmp;
                    break;

                case 4:
                    tmp = *a;
                    *a = pere->f4;
                    pere->f4 = tmp;
                    break;
                }
            return;
        }

        melange_arbre( &((*a)->f1), racine, niveau, niv_actuel + 1 );
        melange_arbre( &((*a)->f2), racine, niveau, niv_actuel + 1 );
        melange_arbre( &((*a)->f3), racine, niveau, niv_actuel + 1 );
        melange_arbre( &((*a)->f4), racine, niveau, niv_actuel + 1 );
    }
}


/*
Fonction qui parcours aléatoirement l'arbre jusqu'au niveau donné en paramètre.
Elle renvoie l'adresse du noeud interne au bout du chemin.
*/
Arbre melange_arbre_aux(Arbre a, int niveau, int niv_actuel) {
    int nb;

    if (niv_actuel == niveau - 1)
        return a;

    nb = rand_a_b(1, 5);
    switch (nb) {
        case 1: 
            return melange_arbre_aux( a->f1, niveau, niv_actuel + 1 );
            break;
        case 2:
            return melange_arbre_aux( a->f2, niveau, niv_actuel + 1 );
            break;
        case 3:
            return melange_arbre_aux( a->f3, niveau, niv_actuel + 1 );
            break;
        case 4:
            return melange_arbre_aux( a->f4, niveau, niv_actuel + 1 );
            break;
    }
    return NULL;
}