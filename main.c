#include <stdio.h>
#include <stdlib.h>

#include "pile.h"
#include "point.h"

int main()
{
    t_pile* mapile = NULL;
    t_point* p = NULL;

    mapile = pile_creer();

    if(pile_vide(mapile))
        printf("pile vide\n");
    else
        printf("pile non vide\n");

    printf("on ajoute un point\n");
    p = point_creer(1,1);
    pile_empiler(mapile,p);

    if(pile_vide(mapile))
        printf("pile vide\n");
    else
        printf("pile non vide\n");

    p = point_creer(2,2);
    pile_empiler(mapile,p);

    p = point_creer(3,3);
    pile_empiler(mapile,p);

    // on affiche le sommet actuel
    point_afficher(pile_elem_sommet(mapile));

    p = point_creer(4,4);
    pile_empiler(mapile,p);

    p = point_creer(5,5);
    pile_empiler(mapile,p);

    p = pile_depiler(mapile);
    // on affiche l'élément dépilé
    point_afficher(p);

    // on affiche le sommet actuel
    point_afficher(pile_elem_sommet(mapile));

    // on vide la pile
    pile_vider(mapile, (tpf_detruire)point_detruire);
    if(pile_vide(mapile))
        printf("pile vide\n");
    else
        printf("pile non vide\n");

    pile_detruire(mapile, (tpf_detruire)point_detruire);

    return 0;
}
