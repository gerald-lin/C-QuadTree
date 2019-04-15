#ifndef __QUADTREEMELANGE__
#define __QUADTREEMELANGE__

#include <stdio.h>
#include "quadtree.h"


int rand_a_b(int a, int b);
void melange_arbre(Arbre *a, Arbre racine, int niveau, int niv_actuel);
Arbre melange_arbre_aux(Arbre a, int niveau, int niv_actuel);

#endif