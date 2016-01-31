#include "pile.h"

// Alloue une pile
t_pile* pile_creer()
{
    return liste_creer();
}

// Détruit une pile
void pile_detruire(t_pile* pile, tpf_detruire detruire)
{
    liste_detruire(pile, detruire);
}

// Vide une pile
void pile_vider(t_pile* pile, tpf_detruire detruire)
{
    liste_vider(pile, detruire);
}

// Empile ( = ajoute ) un élément à la pile
void pile_empiler(t_pile* pile, void* elem)
{
    liste_ajout_tete(pile,elem);
}

// Dépile ( = retire ) un élément à la pile
void* pile_depiler(t_pile* pile)
{
    return liste_recup_tete(pile);
}

// Retourne l'élément du sommet de la pile, sans le retirer de la pile
void* pile_elem_sommet(t_pile* pile)
{
    return liste_elem_tete(pile);
}

// Retourne 1 si la pile est vide, 0 sinon
int pile_vide(t_pile* pile)
{
    return liste_vide(pile);
}

// Retourne une copie (profonde) de la pile reçue en paramètre
t_pile* pile_copier(t_pile* pile, tpf_copier copier)
{
    return liste_copier(pile,copier);
}

// Retourne le nombre d'éléments de la file
int pile_taille(t_pile* pile)
{
    return liste_taille(pile);
}

// Affichage bilan allocations/libérations
void pile_bilan(t_pile* pile)
{
    liste_bilan(pile);
}
