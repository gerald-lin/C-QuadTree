#ifndef __MENU__
#define __MENU__

#include <MLV/MLV_all.h>
#include "gestionClic.h"
#include "fichier.h"

typedef struct {
    int x1;
    int y1;
    int x2;
    int y2;
} Bouton;


int affiche_menu(int fenetre_x, int fenetre_y);
int affiche_menu_piece(int fenetre_x, int fenetre_y);
int verif_clic_bouton(Bouton *tab, int taille);
void boite_saisie(int fenetre_x, int fenetre_y, int menu_choix, char **nom);

#endif