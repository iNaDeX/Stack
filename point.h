#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

// Module point pour tester la liste chain�e

typedef struct point
{
    int x;
    int y;
}t_point;

// retourne 1 si le point correspond � ce qu'on cherche
// 0 sinon
int point_chercher(t_point* p);

// Crit�re de comparaison entre 2 points
int point_trier_simple(t_point* p1,t_point* p2);

// Crit�re de tri en passant par des t_point** (n�cessaire pour l'appel � qsort ici)
int point_trier(t_point** pp1,t_point** pp2);

// Alloue et initialise un point
t_point* point_creer(int x, int y);

// Constructeur par copie
t_point* point_copier(t_point* p);

// Affiche les coordonn�es d'un point
void point_afficher(t_point* p);

// Lib�re un point
void point_detruire(t_point* p);

#endif // POINT_H_INCLUDED
