#ifndef PILE_H_INCLUDED
#define PILE_H_INCLUDED

// Ceci est un module de pile générique.

// Pour l'utiliser correctement, il faut juste appeler les fonctions listées ci dessous.
// Il faudra bien entendu coder un module correspondant aux traitements à effectuer sur les éléments
// par exemple pour une pile de films, il faudra coder le module "film" (film_creer, film_afficher etc..)

/*// Attention, certaines fonctions nécessitent de recevoir une fonction en paramètre
// par exemple: t_pile* pile_copier(t_pile* pile,tpf_copier copier);
// Il est logique que pour copier chaque élément de la pile
// il faut avoir une fonction qui se charge de copier 1 élément.
// Cette fonction doit être transmise en paramètre.
// L'appel à pile_copier sera donc par exemple:
// pile_copier(mapile, (tpf_copier)point_copie);
// avec point_copier le nom de la fonction qui copie 1 point.
// dont le prototype serait par exemple:
// t_point* point_copier(t_point* p);
*/

//On inclut les librairies standard
#include <stdio.h>
#include <stdlib.h>

// On inclut la libraire liste_generique_simple_chainage
// En effet ce module de pile générique repose sur une implémentation en liste
#include "liste_generique_simple_chainage.h"

// On crée un alias du type t_liste, c'est à dire qu'on le renomme en t_pile pour une cohérence logique
// Ainsi l'utilisateur du module n'utilisera pas le type t_liste ni le mot "liste" dans son code.
typedef t_liste t_pile;

// Alloue une pile
t_pile* pile_creer();

// Détruit une pile
void pile_detruire(t_pile* pile, tpf_detruire detruire);

// Vide une pile
void pile_vider(t_pile* pile, tpf_detruire detruire);

// Empile ( = ajoute ) un élément à la pile
void pile_empiler(t_pile* pile, void* elem);

// Dépile ( = retire ) un élément à la pile
void* pile_depiler(t_pile* pile);

// Retourne l'élément du sommet de la pile, sans le retirer de la pile
void* pile_elem_sommet(t_pile* pile);

// Retourne 1 si la pile est vide, 0 sinon
int pile_vide(t_pile* pile);

// Retourne une copie (profonde) de la pile reçue en paramètre
t_pile* pile_copier(t_pile* pile,tpf_copier copier);

// Retourne le nombre d'éléments de la file
int pile_taille(t_pile* pile);

// Affichage bilan allocations/libérations
void pile_bilan(t_pile* pile);

#endif // PILE_H_INCLUDED
