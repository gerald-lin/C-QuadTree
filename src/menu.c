#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <MLV/MLV_all.h>

#include "menu.h"


int affiche_menu(int fenetre_x, int fenetre_y) {
    int i, res, x, y;
    int largeur_box = 200, hauteur_box = 50;
    Bouton tab[2];
    char *chaine[] = {"Charger une image", "Quitter"};

    y = (fenetre_y / 20);
    for (i = 0; i < 2; i++) {

        x = fenetre_x / 2 - (largeur_box / 2);

        tab[i].x1 = x;
        tab[i].y1 = y;
        tab[i].x2 = x + largeur_box;
        tab[i].y2 = y + hauteur_box;

        MLV_draw_text_box(
            x, y, largeur_box, hauteur_box,
            chaine[i], 0,
            MLV_COLOR_RED, MLV_COLOR_BLACK, MLV_COLOR_WHITE,
            MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER
        );

        MLV_actualise_window();
        y += hauteur_box * 1.5;
    }
    
    while ( (res = verif_clic_bouton(tab, 2)) == -1 );
    return res;
}

int affiche_menu_piece(int fenetre_x, int fenetre_y) {
    int i, res, x, y;
    int largeur_box = 200, hauteur_box = 50;
    Bouton tab[2];
    char *chaine[] = {"Puzzle 16 pièces", "Puzzle 64 pièces"};

    y = (fenetre_y / 20);
    for (i = 0; i < 2; i++) {

        x = fenetre_x / 2 - (largeur_box / 2);

        tab[i].x1 = x;
        tab[i].y1 = y;
        tab[i].x2 = x + largeur_box;
        tab[i].y2 = y + hauteur_box;

        MLV_draw_text_box(
            x, y, largeur_box, hauteur_box,
            chaine[i], 0,
            MLV_COLOR_RED, MLV_COLOR_BLACK, MLV_COLOR_WHITE,
            MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER
        );

        MLV_actualise_window();
        y += hauteur_box * 1.5;
    }
    
    while ( (res = verif_clic_bouton(tab, 2)) == -1 );
    return res;
}


int verif_clic_bouton(Bouton *tab, int taille) {
    Clic c;
    int i;

    MLV_wait_mouse(&(c.x), &(c.y));

    for (i = 0; i < taille; i++) {
        if ( tab[i].x1 < c.x && c.x < tab[i].x2 ) {
            if ( tab[i].y1 < c.y && c.y < tab[i].y2 )
                return i;
        }
    }
    return -1;    
}

void boite_saisie(int fenetre_x, int fenetre_y, int menu_choix, char **nom) {
    int x, y;
    int largeur_box = fenetre_x / 4, hauteur_box = fenetre_y / 10;

    x = fenetre_x / 2 - (largeur_box / 2);
    y = fenetre_y / 2 - (hauteur_box / 2);

    if (menu_choix == 0) {
        do {
            MLV_wait_input_box(
                x, y,
                largeur_box, hauteur_box,
                MLV_COLOR_RED, MLV_COLOR_BLACK, MLV_COLOR_WHITE,
                "FORMAT \"fichier.jpg\" : ", &(*nom)
            );
            MLV_clear_window(MLV_COLOR_BLACK);
            MLV_actualise_window();

        } while ( !verif_img(*nom) );
    }
    
    if (menu_choix == 1) {
        do {
            MLV_wait_input_box(
                x, y,
                largeur_box, hauteur_box,
                MLV_COLOR_RED, MLV_COLOR_BLACK, MLV_COLOR_WHITE,
                "FORMAT \"fichier.quad\" : ", &(*nom)
            );
            MLV_actualise_window();

        } while ( !verif_fichier_quad(*nom) );
    }  
}