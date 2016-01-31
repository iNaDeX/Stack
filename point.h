#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

// Module point pour tester la liste chainée

typedef struct point
{
    int x;
    int y;
}t_point;

// retourne 1 si le point correspond à ce qu'on cherche
// 0 sinon
int point_chercher(t_point* p);

// Critère de comparaison entre 2 points
int point_trier_simple(t_point* p1,t_point* p2);

// Critère de tri en passant par des t_point** (nécessaire pour l'appel à qsort ici)
int point_trier(t_point** pp1,t_point** pp2);

// Alloue et initialise un point
t_point* point_creer(int x, int y);

// Constructeur par copie
t_point* point_copier(t_point* p);

// Affiche les coordonnées d'un point
void point_afficher(t_point* p);

// Libère un point
void point_detruire(t_point* p);

#endif // POINT_H_INCLUDED
