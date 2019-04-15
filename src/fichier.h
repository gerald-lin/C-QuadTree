#ifndef __FICHIER__
#define __FICHIER__

#include <stdio.h>
#include "quadtree.h"


int ouvrir_fichier(FILE **fichier);
void ecrire_arbre_dans_fichier(Arbre a, FILE *fichier);

int copie_arbre(Arbre *a, FILE *fichier);

int verif_img(char s[]);
int verif_fichier_quad(char s[]);

#endif