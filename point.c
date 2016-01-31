#include "point.h"

// Critère de comparaison entre 2 points
int point_trier_simple(t_point* p1,t_point* p2)
{
    if(p1->x < p2->x)
        return -1;
    else if(p1->x > p2->x)
        return 1;
    else
        return 0;
}

// retourne 1 si le point correspond à ce qu'on cherche
// 0 sinon
int point_chercher(t_point* p)
{
    if(p->x != p->y) // ici on dit qu'on s'intéresse aux points dont x != y
        return 1;
    else
        return 0;
}

// Critère de tri en passant par des t_point** (nécessaire pour l'appel à qsort ici)
int point_trier(t_point** pp1,t_point** pp2)
{
    t_point* p1 = *pp1; // on simplifie l'écriture
    t_point* p2 = *pp2; // on simplifie l'écriture

    if(p1->x < p2->x)
        return -1;
    else if(p1->x > p2->x)
        return 1;
    else
        return 0;
}

t_point* point_creer(int x, int y)
{
    t_point* nouv = (t_point*) malloc(1*sizeof(t_point));
    nouv->x = x;
    nouv->y = y;

    return nouv;
}

t_point* point_copier(t_point* p)
{
    t_point* copie = (t_point*) malloc(1*sizeof(t_point));
    copie->x = p->x;
    copie->y = p->y;

    return copie;
}

void point_afficher(t_point* p)
{
    printf("(%d, %d)\n",p->x,p->y);
}

void point_detruire(t_point* p)
{
    free(p);
}
