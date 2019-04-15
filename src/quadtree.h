#ifndef __QUADTREE__
#define __QUADTREE__

#include <MLV/MLV_all.h>
#include "gestionClic.h"


typedef struct noeud {
    int valeur;
    struct noeud *f1;
    struct noeud *f2;
    struct noeud *f3;
    struct noeud *f4;
} Noeud, *Arbre;

typedef struct {
    int r;
    int g;
    int b;
} RGB;


Arbre allouerNoeud(int valeur);

void conversion_en_arbre(Arbre *a, MLV_Image *image, int x_debut, int y_debut, int taille);
int est_unie(MLV_Image *image, int x_debut, int y_debut, int taille);
int compare_pixel(RGB p1, RGB p2);


void cherche_noeud_clic(Arbre a, Arbre *noeud, Clic c, int x_debut, int y_debut, int taille, int niveau, int niv_actuel);
void cherche_noeud_pere(Arbre a, Arbre noeud, Arbre *pere, int niveau, int niv_actuel);
void echange_noeuds(Arbre *a, Clic c1, Clic c2, int taille, int niveau);


int compare_arbre(Arbre a, Arbre b);
void detruire_arbre(Arbre *a);

#endif