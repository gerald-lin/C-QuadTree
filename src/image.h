#ifndef __IMAGE__
#define __IMAGE__

#include <MLV/MLV_all.h>
#include "quadtree.h"
#include "gestionClic.h"


void creer_fond_blanc(MLV_Image *image);
void redimension(MLV_Image *source, MLV_Image *cible);
void transforme_noir_blanc(MLV_Image *image, int taille_image);
void conversion_en_img(Arbre a, MLV_Image *cible, int x_debut, int y_debut, int taille);

void surligne_carre(Arbre a, Arbre b, int niveau, int niv_actuel, int x_debut, int y_debut, int taille, MLV_Image *img, int t_x, int t_y, int t_i);
void clignote_carre(Arbre a, Arbre b, MLV_Image *img, int fenetre_x, int fenetre_y, int taille, int niveau);

#endif