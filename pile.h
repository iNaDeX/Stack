#ifndef PILE_H_INCLUDED
#define PILE_H_INCLUDED

// Ceci est un module de pile g�n�rique.

// Pour l'utiliser correctement, il faut juste appeler les fonctions list�es ci dessous.
// Il faudra bien entendu coder un module correspondant aux traitements � effectuer sur les �l�ments
// par exemple pour une pile de films, il faudra coder le module "film" (film_creer, film_afficher etc..)

/*// Attention, certaines fonctions n�cessitent de recevoir une fonction en param�tre
// par exemple: t_pile* pile_copier(t_pile* pile,tpf_copier copier);
// Il est logique que pour copier chaque �l�ment de la pile
// il faut avoir une fonction qui se charge de copier 1 �l�ment.
// Cette fonction doit �tre transmise en param�tre.
// L'appel � pile_copier sera donc par exemple:
// pile_copier(mapile, (tpf_copier)point_copie);
// avec point_copier le nom de la fonction qui copie 1 point.
// dont le prototype serait par exemple:
// t_point* point_copier(t_point* p);
*/

//On inclut les librairies standard
#include <stdio.h>
#include <stdlib.h>

// On inclut la libraire liste_generique_simple_chainage
// En effet ce module de pile g�n�rique repose sur une impl�mentation en liste
#include "liste_generique_simple_chainage.h"

// On cr�e un alias du type t_liste, c'est � dire qu'on le renomme en t_pile pour une coh�rence logique
// Ainsi l'utilisateur du module n'utilisera pas le type t_liste ni le mot "liste" dans son code.
typedef t_liste t_pile;

// Alloue une pile
t_pile* pile_creer();

// D�truit une pile
void pile_detruire(t_pile* pile, tpf_detruire detruire);

// Vide une pile
void pile_vider(t_pile* pile, tpf_detruire detruire);

// Empile ( = ajoute ) un �l�ment � la pile
void pile_empiler(t_pile* pile, void* elem);

// D�pile ( = retire ) un �l�ment � la pile
void* pile_depiler(t_pile* pile);

// Retourne l'�l�ment du sommet de la pile, sans le retirer de la pile
void* pile_elem_sommet(t_pile* pile);

// Retourne 1 si la pile est vide, 0 sinon
int pile_vide(t_pile* pile);

// Retourne une copie (profonde) de la pile re�ue en param�tre
t_pile* pile_copier(t_pile* pile,tpf_copier copier);

// Retourne le nombre d'�l�ments de la file
int pile_taille(t_pile* pile);

// Affichage bilan allocations/lib�rations
void pile_bilan(t_pile* pile);

#endif // PILE_H_INCLUDED
