#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <MLV/MLV_all.h>

#include "image.h"


/*
Fonction qui dessine un rectangle blanc remplissant l'image donnée en paramètre.
*/
void creer_fond_blanc(MLV_Image *image) {
    int taille;

    assert(NULL != image);

    taille = MLV_get_image_width(image);
    MLV_draw_filled_rectangle_on_image(0, 0, taille, taille, MLV_rgba(255, 255, 255, 255), image);
}


/*
Fonction qui redimensionne une image qui n'est pas en 512x512 en 512x512.
*/
void redimension(MLV_Image *source, MLV_Image *cible) {
    int largeur, hauteur;
    int centre;

    assert(NULL != source);
    assert(NULL != cible);
    
    MLV_resize_image_with_proportions(source, 512, 512);
    MLV_get_image_size(source, &largeur, &hauteur);

    if (largeur > hauteur) {
        centre = (largeur - hauteur) / 2;
        MLV_draw_image_on_image(source, cible, 0, centre);
    }
    else {
        centre = (hauteur - largeur) / 2;
        MLV_draw_image_on_image(source, cible, centre, 0);
    }
}


/*
Fonction qui change les pixels de couleur en niveau de gris, de l'image donnée en paramètre.
*/
void transforme_noir_blanc(MLV_Image *image, int taille_image) {
    int i, j;
    int gris;
    RGB p;

    assert(NULL != image);
    assert(taille_image > 0);

    for (i = 0; i < taille_image; i++) {
        for (j = 0; j < taille_image ; j++) {

            MLV_get_pixel_on_image(image, i, j, &(p.r), &(p.g), &(p.b), NULL);
            gris = (0.299 * (p.r)) + (0.587 * (p.g)) + (0.114 * (p.b));
            MLV_set_pixel_on_image(i, j, MLV_rgba(gris, gris, gris, 255), image);
            
        }
    }
}


/*
Fonction qui créée et dessine l'image correspondant à l'arbre donnée en paramètre.
*/
void conversion_en_img(Arbre a, MLV_Image *image, int x_debut, int y_debut, int taille) {
    assert(x_debut >= 0);
    assert(y_debut >= 0);
    assert(taille > 0);
    assert(NULL != image);

    if (NULL != a) {
        if ( (NULL == a->f1) && (NULL == a->f2) && (NULL == a->f3) && (NULL == a->f4) )
            MLV_draw_filled_rectangle_on_image( x_debut, y_debut, taille, taille, MLV_rgba(a->valeur, a->valeur, a->valeur, 255), image );

        else {
            conversion_en_img( a->f1, image, x_debut, y_debut, taille/2 );
            conversion_en_img( a->f2, image, (x_debut + taille/2), y_debut, taille/2 );
            conversion_en_img( a->f3, image, x_debut, (y_debut + taille/2), taille/2 );
            conversion_en_img( a->f4, image, (x_debut + taille/2), (y_debut + taille/2), taille/2 );
        }
    }
}


void surligne_carre(Arbre a, Arbre b, int niveau, int niv_actuel, int x_debut, int y_debut, int taille, MLV_Image *img, int t_x, int t_y, int t_i) {
    if (NULL != a && NULL != b) {
        if (niv_actuel == niveau) {
            if ( !compare_arbre(a, b) )
                MLV_draw_filled_rectangle_on_image(x_debut, y_debut, taille, taille, MLV_rgba(25, 200, 225, 80), img);
        }

        else {
            surligne_carre( a->f1, b->f1, niveau, niv_actuel + 1, x_debut, y_debut, taille/2, img, t_x, t_y, t_i );
            surligne_carre( a->f2, b->f2, niveau, niv_actuel + 1, (x_debut + taille/2), y_debut, taille/2, img, t_x, t_y, t_i );
            surligne_carre( a->f3, b->f3, niveau, niv_actuel + 1, x_debut, (y_debut + taille/2), taille/2, img, t_x, t_y, t_i );
            surligne_carre( a->f4, b->f4, niveau, niv_actuel + 1, (x_debut + taille/2), (y_debut + taille/2), taille/2, img, t_x, t_y, t_i );
        }
    }
}

void clignote_carre(Arbre a, Arbre b, MLV_Image *img, int fenetre_x, int fenetre_y, int taille, int niveau) {
    MLV_Image *copie = NULL;
    int i;

    for (i = 0; i < 2; i++) {
        copie = MLV_copy_image(img);
        surligne_carre(a, b, niveau, 0, 0, 0, taille, copie, fenetre_x, fenetre_y, taille);
        MLV_draw_image(copie, fenetre_x - taille, (fenetre_y - taille) / 2);
        MLV_actualise_window();
        MLV_wait_milliseconds(250);

        MLV_draw_image(img, fenetre_x - taille, (fenetre_y - taille) / 2);
        MLV_actualise_window();
        MLV_wait_milliseconds(150);
    }
}