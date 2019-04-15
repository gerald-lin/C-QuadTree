#ifndef __GESTIONCLIC__
#define __GESTIONCLIC__

#include <MLV/MLV_all.h>


typedef struct {
    int x;
    int y;
} Clic;


int verif_clic(Clic *c, int fenetre_x, int fenetre_y, int taille_img);


#endif