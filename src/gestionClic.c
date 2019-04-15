#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <MLV/MLV_all.h>

#include "gestionClic.h"


int verif_clic(Clic *c, int fenetre_x, int fenetre_y, int taille_img) {
    assert(fenetre_x >= 0);
    assert(fenetre_y >= 0);
    assert(taille_img >= 0);

    MLV_wait_mouse( &(c->x), &(c->y) );
    
    if ( ((fenetre_x - taille_img) <= c->x) && (c->x < fenetre_x) ) {
        if ( ( ((fenetre_y - taille_img) / 2) <= c->y ) && (c->y < fenetre_y - ((fenetre_y - taille_img) / 2)) ) {

            c->x = c->x - (fenetre_x - taille_img);
            c->y = c->y - ((fenetre_y - taille_img) / 2);
            return 1;

        }
    }
    return 0;
}

