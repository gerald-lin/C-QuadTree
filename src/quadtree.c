#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <MLV/MLV_all.h>

#include "quadtree.h"


/*
Fonction qui alloue un noeud.
*/
Arbre allouerNoeud(int valeur) {
    Arbre adr = NULL;
    adr = (Noeud *)malloc(sizeof(Noeud));

    if (adr == NULL)
        exit(EXIT_FAILURE);

    adr->valeur = valeur;
    adr->f1 = NULL;
    adr->f2 = NULL;
    adr->f3 = NULL;
    adr->f4 = NULL;

    return adr;
}


/*
Fonction qui créée l'arbre quaternaire qui correspond à l'image donnée en paramètre.
*/
void conversion_en_arbre(Arbre *a, MLV_Image *image, int x_debut, int y_debut, int taille) {
    RGB pixel;

    assert(NULL != image);
    assert(x_debut >= 0);
    assert(y_debut >= 0);
    assert(taille > 0);

    if ( !est_unie(image, x_debut, y_debut, taille) ) {
        *a = allouerNoeud(0);

        conversion_en_arbre( &((*a)->f1), image, x_debut, y_debut, taille/2 );
        conversion_en_arbre( &((*a)->f2), image, (x_debut + taille/2), y_debut, taille/2 );
        conversion_en_arbre( &((*a)->f3), image, x_debut, (y_debut + taille/2), taille/2 );
        conversion_en_arbre( &((*a)->f4), image, (x_debut + taille/2), (y_debut + taille/2), taille/2 );
    }

    else {
        MLV_get_pixel_on_image(image, x_debut, y_debut, &(pixel.r), NULL, NULL, NULL);
        *a = allouerNoeud(pixel.r);
    }
}


/*
Fonction qui compare si tous les pixels d'un carré, donné par ses coordonnées, sont de même couleur (même valeurs RGB).
Elle renvoie 1 si les pixels sont de même couleur, 0 sinon.
*/
int est_unie(MLV_Image *image, int x_debut, int y_debut, int taille) {
    RGB p1, p2;
    int i, j;

    assert(NULL != image);
    assert(x_debut >= 0);
    assert(y_debut >= 0);
    assert(taille > 0);

    /* le pixel qui sert de référence pour le comparer à tous les autres pixels */
    MLV_get_pixel_on_image( image, x_debut, y_debut, &(p1.r), &(p1.g), &(p1.b), NULL );

    for (i = 1; i < taille; i++) {
        for (j = 1; j < taille; j++) {
            MLV_get_pixel_on_image( image, (i + x_debut), (j + y_debut), &(p1.r), &(p1.g), &(p1.b), NULL );
            
            if ( !compare_pixel(p1, p2) )
                return 0;
        }
    }
    return 1;
}


/*
Fonction qui compare deux pixels en fonction de leur RGB donnés en paramètre.
Elle renvoie 1 si les valeurs sont identiques, 0 sinon.
*/
int compare_pixel(RGB p1, RGB p2) {
    if ( (p1.r == p2.r) && (p1.g == p2.g) && (p1.b == p2.b) )
        return 1;
    else
        return 0;
}


/*
Fonction qui compare deux arbres.
Elle renvoie 0 si les noeuds ne correspondent pas, 1 sinon.
*/
int compare_arbre(Arbre a, Arbre b) {
    if (NULL != a && NULL != b) {

        if (a->valeur != b->valeur)
            return 0;

        else {
            if ( !(compare_arbre(a->f1, b->f1)) )
                return 0;
            if ( !(compare_arbre(a->f2, b->f2)) )
                return 0;
            if ( !(compare_arbre(a->f3, b->f3)) )
                return 0;
            if ( !(compare_arbre(a->f4, b->f4)) )
                return 0;
        }
    }

    if ( (NULL != a && NULL == b) || (NULL == a && NULL != b) )
        return 0;

    return 1;
}


/* Fonction qui affiche le parcours en profondeur préfixe d'un arbre. */
void affiche_prefixe(Arbre a) {
    if (NULL != a) {
        printf("%d ", a->valeur);

        affiche_prefixe(a->f1);
        affiche_prefixe(a->f2);
        affiche_prefixe(a->f3);
        affiche_prefixe(a->f4);
    }
}

/* Fonction qui libère la mémoire occupée par un arbre. */
void detruire_arbre(Arbre *a) {
    if (NULL != *a) {
        detruire_arbre( &((*a)->f1) );
        detruire_arbre( &((*a)->f2) );
        detruire_arbre( &((*a)->f3) );
        detruire_arbre( &((*a)->f4) );

        free(*a);
        *a = NULL;
    }
}


void cherche_noeud_clic(Arbre a, Arbre *noeud, Clic c, int x_debut, int y_debut, int taille, int niveau, int niv_actuel) {
    if (NULL != a) {
        if (niv_actuel == niveau) {
            if ( (x_debut < c.x && c.x < x_debut + taille) && (y_debut < c.y && c.y < y_debut + taille) )
                *noeud = a;
        }

        else {
            cherche_noeud_clic( a->f1, noeud, c, x_debut, y_debut, taille/2, niveau, niv_actuel + 1 );
            cherche_noeud_clic( a->f2, noeud, c, (x_debut + taille/2), y_debut, taille/2, niveau, niv_actuel + 1 );
            cherche_noeud_clic( a->f3, noeud, c, x_debut, (y_debut + taille/2), taille/2, niveau, niv_actuel + 1 );
            cherche_noeud_clic( a->f4, noeud, c, (x_debut + taille/2), (y_debut + taille/2), taille/2, niveau, niv_actuel + 1 );
        }
    }
}

/* *noeud est le noeud du clic */
void cherche_noeud_pere(Arbre a, Arbre noeud, Arbre *pere, int niveau, int niv_actuel) {
    if (NULL != a) {
        if (niv_actuel == niveau - 1) {
            if (a->f1 == noeud || a->f2 == noeud || a->f3 == noeud || a->f4 == noeud)
                *pere = a;
        }

        else {
            cherche_noeud_pere(a->f1, noeud, pere, niveau, niv_actuel + 1);
            cherche_noeud_pere(a->f2, noeud, pere, niveau, niv_actuel + 1);
            cherche_noeud_pere(a->f3, noeud, pere, niveau, niv_actuel + 1);
            cherche_noeud_pere(a->f4, noeud, pere, niveau, niv_actuel + 1);
        }
    }
}


void echange_noeuds(Arbre *a, Clic c1, Clic c2, int taille, int niveau) {
    Arbre n1 = NULL, n2 = NULL;
    Arbre p1 = NULL, p2 = NULL;

    assert(0 < niveau && niveau < 4);
    assert(taille > 0);

    cherche_noeud_clic(*a, &n1, c1, 0, 0, taille, niveau, 0);
    cherche_noeud_clic(*a, &n2, c2, 0, 0, taille, niveau, 0);

    cherche_noeud_pere(*a, n1, &p1, niveau, 0);
    cherche_noeud_pere(*a, n2, &p2, niveau, 0);

    if (p1->f1 == n1) {
        if (p2->f1 == n2) {
            p1->f1 = n2; p2->f1 = n1;
        }
        else if (p2->f2 == n2) {
            p1->f1 = n2; p2->f2 = n1;
        }
        else if (p2->f3 == n2) {
            p1->f1 = n2; p2->f3 = n1;
        }
        else {
            p1->f1 = n2; p2->f4 = n1;
        }
    }

    else if (p1->f2 == n1) {
        if (p2->f1 == n2) {
            p1->f2 = n2; p2->f1 = n1;
        }
        else if (p2->f2 == n2) {
            p1->f2 = n2; p2->f2 = n1;
        }
        else if (p2->f3 == n2) {
            p1->f2 = n2; p2->f3 = n1;
        }
        else {
            p1->f2 = n2; p2->f4 = n1;
        }
    }

    else if (p1->f3 == n1) {
        if (p2->f1 == n2) {
            p1->f3 = n2; p2->f1 = n1;
        }
        else if (p2->f2 == n2) {
            p1->f3 = n2; p2->f2 = n1;
        }
        else if (p2->f3 == n2) {
            p1->f3 = n2; p2->f3 = n1;
        }
        else {
            p1->f3 = n2; p2->f4 = n1;
        }
    }

    else {
        if (p2->f1 == n2) {
            p1->f4 = n2; p2->f1 = n1;
        }
        else if (p2->f2 == n2) {
            p1->f4 = n2; p2->f2 = n1;
        }
        else if (p2->f3 == n2) {
            p1->f4 = n2; p2->f3 = n1;
        }
        else {
            p1->f4 = n2; p2->f4 = n1;
        }
    }
}