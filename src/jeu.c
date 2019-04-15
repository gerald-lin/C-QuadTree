#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <string.h>

#include "jeu.h"

#define TAILLE_X 1280
#define TAILLE_Y 720
#define TAILLE_IMG 512


void jeu() {
    MLV_Image *image = NULL, *img_redim = NULL, *img_jeu = NULL;
    FILE *fichier = NULL;
    Arbre arb_origine = NULL, arb_puzzle = NULL;
    char *nom_fichier, chemin_img[500] = "images/";

    int niveau, menu, menu2;
    int nb_coups = 0;
    Clic c1, c2;

    /* permet la gestion du mélange aléatoire plus bas */
    srand(time(NULL));

    MLV_create_window("Quadtree", "Quadtree", TAILLE_X, TAILLE_Y);
    
    menu = affiche_menu(TAILLE_X, TAILLE_Y);
    if (menu == 0) {

        menu2 = affiche_menu_piece(TAILLE_X, TAILLE_Y);

        if (menu2 == 0)
            niveau = 2;
        if (menu2 == 1)
            niveau = 3;

        boite_saisie(TAILLE_X, TAILLE_Y, menu, &nom_fichier);
        strcat(chemin_img, nom_fichier);

        /* chargement et création des images nécessaires */
        image = MLV_load_image(chemin_img);
        img_redim = MLV_create_image(TAILLE_IMG, TAILLE_IMG);
        img_jeu = MLV_create_image(TAILLE_IMG, TAILLE_IMG);
        creer_fond_blanc(img_redim);

        /* préparation de l'image */
        redimension(image, img_redim);
        transforme_noir_blanc(img_redim, TAILLE_IMG);
        MLV_draw_image(img_redim, 0, (TAILLE_Y - TAILLE_IMG) / 2);

        /* conversion de l'image en arbre */
        conversion_en_arbre(&arb_origine, img_redim, 0, 0, TAILLE_IMG);

        /* création et écriture du fichier .quad */
        ouvrir_fichier(&fichier);
        ecrire_arbre_dans_fichier(arb_origine, fichier);

        /* création d'un arbre à partir du fichier .quad */
        rewind(fichier);
        copie_arbre(&arb_puzzle, fichier);
        fclose(fichier);

        /* création du puzzle */
        melange_arbre(&arb_puzzle, arb_puzzle, niveau, 0);

        do {
            /* création d'une image à partir d'un arbre */
            conversion_en_img(arb_puzzle, img_jeu, 0, 0, TAILLE_IMG);
            MLV_draw_image(img_jeu, TAILLE_X - TAILLE_IMG, (TAILLE_Y - TAILLE_IMG) / 2);
            MLV_draw_image(img_redim, 0, (TAILLE_Y - TAILLE_IMG) / 2);
            MLV_actualise_window();

            if (compare_arbre(arb_origine, arb_puzzle))
                break;

            /* affichage de l'aide à la résolution */
            clignote_carre(arb_origine, arb_puzzle, img_jeu, TAILLE_X, TAILLE_Y, TAILLE_IMG, niveau);

            if ( verif_clic(&c1, TAILLE_X, TAILLE_Y, TAILLE_IMG) ) {
                if ( verif_clic(&c2, TAILLE_X, TAILLE_Y, TAILLE_IMG) ) {
                    echange_noeuds(&arb_puzzle, c1, c2, TAILLE_IMG, niveau);
                    nb_coups += 1;
                }
            }

        } while (1);
    }

    MLV_wait_mouse(NULL, NULL);

    /* Libérer la mémoire */
    MLV_free_image(image);
    MLV_free_image(img_redim);
    MLV_free_image(img_jeu);

    detruire_arbre(&arb_origine);
    detruire_arbre(&arb_puzzle);
    
    MLV_free_window();

    printf("Nombre de coups : %d\n", nb_coups);
}