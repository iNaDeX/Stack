#include "liste_generique_simple_chainage.h"

/// Variables globales pour tracer le bilan des allocations/libérations des maillons

// Total des maillons alloués
int nb_maillons_alloues = 0;

// Total des maillons libérés
int nb_maillons_liberes = 0;

/// Implémentation des sous-programmes du module

// Constructeur
t_liste* liste_creer()
{
    t_liste* nouv;
    nouv = (t_liste*) malloc(1*sizeof(t_liste));

    nouv->longueur = 0;
    nouv->p_tete = NULL;
    nouv->p_queue = NULL;
    nouv->p_courant = NULL;

    return nouv;
}

// Destructeur
void liste_detruire(t_liste* lst, tpf_detruire detruire)
{
    // pour détruire la liste, on va commencer par la vider.
    // En effet, il faut détruire (free) chaque maillon un par un.
    // on garde en tête que pour chaque "malloc" il faut un "free"
    // -> on a fait un malloc par nouveau maillon --> un free par maillon sera nécessaire

    liste_vider(lst,detruire);

    // on a détruit tous les maillons
    // on peut donc détruire l'instance "liste" (la structure qui contient : la longueur de la liste et le pointeur sur la tête
    // -> on a fait un malloc pour créer la liste --> un free pour libérer la liste

    free(lst);
}

// Vider la liste sans la détruire
void liste_vider(t_liste* lst, tpf_detruire detruire)
{
    while(!liste_vide(lst))
    {
        liste_supprimer_tete(lst,detruire);
    }
}

// Constructeur par copie
t_liste* liste_copier(t_liste* lst, tpf_copier copier)
{
    t_liste* listecopie;
    void* elem;
    listecopie = liste_creer();

    for(liste_demarrer(lst); liste_encore(lst); liste_suivant(lst))
    {
        elem = copier(liste_elem_courant(lst));
        liste_ajout_queue(listecopie,elem);
    }

    return listecopie;
}

// Ajout d'élément en tête
void liste_ajout_tete(t_liste* lst, void* elem)
{
    t_maillon* nouv;
    nouv = (t_maillon*) malloc(1*sizeof(t_maillon));
    nouv->elem = elem; // on accroche la donnée reçue en paramètre
    nouv->p_suiv = NULL;

    nb_maillons_alloues++; // on augmente le compteur de bilan mémoire

    if(liste_vide(lst)) // si la liste était vide
    {
        nouv->p_suiv = lst->p_tete; // on fait pointer le nouveau maillon sur la tête actuelle
        lst->p_tete = nouv; // on met à jour la tete
        lst->p_queue = nouv; // on met à jour la queue aussi
    }
    else
    {
        nouv->p_suiv = lst->p_tete; // on fait pointer le nouveau maillon sur la tête actuelle
        lst->p_tete = nouv; // on met à jour la tete
    }
    lst->longueur = lst->longueur + 1;
}

// Ajout d'élément en queue
void liste_ajout_queue(t_liste* lst, void* elem)
{
    t_maillon* nouv;
    nouv = (t_maillon*) malloc(1*sizeof(t_maillon));
    nouv->elem = elem; // on accroche la donnée reçue en paramètre
    nouv->p_suiv = NULL;

    nb_maillons_alloues++; // on augmente le compteur de bilan mémoire

    if(liste_vide(lst)) // si la liste était vide
    {
        lst->p_queue = nouv; // on accroche le nouveau maillon sur la queue
        lst->p_tete = nouv; // on met à jour la tete aussi
    }
    else
    {
        lst->p_queue->p_suiv = nouv; // on accroche le nouveau maillon sur la queue actuelle
        lst->p_queue = nouv; // on met à jour la queue
    }
    lst->longueur = lst->longueur + 1;
}

// Nombre d'éléments référencés
int liste_taille(t_liste* lst)
{
    return lst->longueur;
}

// Retourne 1 (Vrai) si la liste est vide
int liste_vide(t_liste* lst)
{
    return (lst->longueur ==0) ? 1 : 0;
}

// Accès élément en tête
void* liste_elem_tete(t_liste* lst)
{
    if(!liste_vide(lst)) {
        return lst->p_tete->elem;
    }
    else {
        #if MODE_DEBUG==1
            printf("DEBUG (liste_generique): tentative d'acces a l'element de tete d'une liste vide\n");
        #endif // MODE_DEBUG
        return NULL;
    }
}

// Accès élément en queue
void* liste_elem_queue(t_liste* lst)
{
    if(!liste_vide(lst)) {
        return lst->p_queue->elem;
    }
    else {
        #if MODE_DEBUG==1
            printf("DEBUG (liste_generique): tentative d'acces a l'element de queue d'une liste vide\n");
        #endif // MODE_DEBUG
        return NULL;
    }
}

// Accès élément courant
void* liste_elem_courant(t_liste* lst)
{
     if(lst->p_courant != NULL) {
        return lst->p_courant->elem;
    }
    else {
        #if MODE_DEBUG==1
            printf("DEBUG (liste_generique): le maillon courant est NULL et on tente d'acceder a sa donnee\n");
        #endif // MODE_DEBUG
        return NULL;
    }
}

void liste_supprimer_tete(t_liste* lst, tpf_detruire detruire)
{
    detruire(liste_recup_tete(lst));
}

// Initialiser un parcours
void liste_demarrer(t_liste* lst)
{
    lst->p_courant = lst->p_tete;
}

// Retourne 1 (Vrai) s'il reste encore des éléments à parcourir
int liste_encore(t_liste* lst)
{
    // attention ne pas faire lst->p_courant->psuiv sinon on réagit un niveau trop tôt
    return (lst->p_courant != NULL) ? 1 : 0;
}

// Déplacement du courant au suivant
void liste_suivant(t_liste* lst)
{
    if(lst->p_courant != NULL)
    {
        lst->p_courant = lst->p_courant->p_suiv;
    }

}

// Affichage bilan allocations/libérations
void liste_bilan()
{
    printf("\n\n");
    printf("///////////////////////////////////////\n");
    printf("Nombre de maillons alloues: %d\n",nb_maillons_alloues);
    printf("Nombre de maillons liberes: %d\n",nb_maillons_liberes);
    printf("Nombre de maillons encore reserves: %d\n",nb_maillons_alloues-nb_maillons_liberes);
    printf("\n");
    printf("Attention cette fonction ne verifie pas si le CONTENU des maillons a ete libere proprement.\n");
    printf("Cette fonction sert juste a verifier qu'on a pas perdu des maillons.\n");
    printf("///////////////////////////////////////\n\n");
}

void liste_afficher(t_liste* lst, tpf_afficher afficher)
{
    for(liste_demarrer(lst); liste_encore(lst); liste_suivant(lst))
    {
        afficher(liste_elem_courant(lst));
    }
}

void liste_fusionner(t_liste* lst1, t_liste* lst2, tpf_copier copier)
{
    void* elem;
    // on parcourt la liste2, et une ajoute une COPIE de chacun de ses éléments à la liste1
    for(liste_demarrer(lst2); liste_encore(lst2); liste_suivant(lst2))
    {
        elem = copier(liste_elem_courant(lst2));
        liste_ajout_queue(lst1,elem);
    }
}

void liste_supprimer_queue(t_liste* lst, tpf_detruire detruire)
{
    detruire(liste_recup_queue(lst));
}

void liste_dereferencer_tete(t_liste* lst)
{
    liste_recup_tete(lst);
}

void liste_dereferencer_queue(t_liste* lst)
{
    liste_recup_queue(lst);
}

void liste_dereferencer(t_liste* lst)
{
    while(!liste_vide(lst))
    {
        liste_dereferencer_tete(lst);
    }
}

void liste_trier(t_liste* lst, tpf_trier trier)
{
    int i;
    int taille_liste;
    void** tab_elem = NULL;

    taille_liste = liste_taille(lst);

    // on ne trie que les listes de plus d'un élément ..
    if (taille_liste > 1)
    {
        tab_elem = (void**) malloc(taille_liste*sizeof(void*)); // on alloue un tableau de pointeurs sur elements

        // on parcourt la liste,on référence chaque élément dans le tableau temporaire
        i=0;
        for(liste_demarrer(lst); liste_encore(lst); liste_suivant(lst))
        {
            tab_elem[i] = liste_elem_courant(lst);
            i++;
        }

        // on ne détruit pas la liste, on va la réutiliser
        // on ne vide pas la liste, car les éléments listés sont aussi référencés dans le tableau
        // -> on ne veut pas détruire les éléments listés
        // --> on veut juste déréférencer tous les maillons de notre liste
        // ( = obtenir une liste vide, sans avoir détruit les éléments, ils sont encore en mémoire quelque part)
        liste_dereferencer(lst);

        qsort(tab_elem,taille_liste,sizeof(void*),trier); // on trie le tableau

        // on recopie le tableau trié dans la liste qui ne comporte actuellement plus aucun élément
        for(i=0; i<taille_liste; i++)
        {
            liste_ajout_queue(lst,tab_elem[i]);
        }

        // on free le tableau temporaire, mais pas ses éléments, car on les a ajoutés à la liste !
        free(tab_elem);
    }
    else
    {
        //tri inutile, on traite une liste de moins de 2 elements
    }
}

void liste_ajout_trie(t_liste* lst, void* elem, tpf_trier trier)
{
    // On va gérer 4 cas séparément:
    // _ l'ajout dans une liste vide
    // _ l'ajout en tete
    // _ l'ajout en queue
    // _ l'ajout au milieu

    t_maillon* pprec = NULL;

    void** ptr_elem = &elem;
    void* elem_tete = liste_elem_tete(lst);
    void** ptr_elem_tete = &elem_tete;
    void* elem_queue = liste_elem_queue(lst);
    void** ptr_elem_queue = &elem_queue;
    void* elem_courant = NULL;
    void** ptr_elem_courant = NULL;

    // cas de l'ajout dans une liste vide
    if(liste_taille(lst) == 0)
    {
        liste_ajout_tete(lst,elem);
    }

    // cas de l'ajout en tête ( = si l'élément à ajouter est censé être placé avant la tete )
    //else if(  (trier( &(elem),&(liste_elem_tete(lst))) )  <   0   )
    else if(  trier(ptr_elem,ptr_elem_tete)  <   0   )
    {
        liste_ajout_tete(lst,elem);
    }
    // cas de l'ajout en queue ( = si l'élément à ajouter est censé être placé après la queue )
    else if( trier(ptr_elem,ptr_elem_queue)  >  0 )
    {
        liste_ajout_queue(lst,elem);
    }
    // cas de l'ajout au milieu
    else
    {
        t_maillon* nouv;
        nouv = (t_maillon*) malloc(1*sizeof(t_maillon));
        nouv->elem = elem; // on accroche la donnée reçue en paramètre
        nouv->p_suiv = NULL;
        nb_maillons_alloues++; // on augmente le compteur de bilan mémoire
        lst->longueur = lst->longueur + 1;

        // on parcourt toute la liste, et on regarde si l'élément doit être placé avant l'élément actuel
        // le 1er tour de la boucle for traite le cas de l'ajout en tête, ce qui bugguerait vu les actions faites
        // mais le cas de l'ajout en tête est impossible ici, car il a déjà été traité avant
        pprec = lst->p_tete;
        for(liste_demarrer(lst); liste_encore(lst); liste_suivant(lst))
        {
            elem_courant = liste_elem_courant(lst);
            ptr_elem_courant = &elem_courant;
            if( trier(ptr_elem,ptr_elem_courant) < 0 )
            {
                nouv->p_suiv = lst->p_courant;
                pprec->p_suiv = nouv;
                break; // on arrete de parcourir la liste, c'est bon, on a placé notre élément
            }
            pprec = lst->p_courant;
        }
    }
}

// ATTENTION, lst_elem_a_supprimer est une liste de REFERENCES vers des éléments existant dans lst.
// les éléments de lst_elem_a_supprimer sont CEUX de lst.
// ce ne sont PAS des copies
void liste_supprimer_partie(t_liste* lst, t_liste* lst_elem_a_supprimer, tpf_detruire detruire)
{
    // on parcourt la liste référençant les éléments à supprimer
    for(liste_demarrer(lst_elem_a_supprimer); liste_encore(lst_elem_a_supprimer); liste_suivant(lst_elem_a_supprimer))
    {
        // on supprime dans lst l'élément actuel de lst_elem_a_supprimer
        liste_supprimer_precis(lst,liste_elem_courant(lst_elem_a_supprimer),detruire);
    }

    // on enlève tous les maillons de la liste, sans détruire les éléments pointés car on vient de le faire avant!
    liste_dereferencer(lst_elem_a_supprimer);
}

void liste_supprimer_precis(t_liste* lst, void* elem, tpf_detruire detruire)
{
    /*
    Le  cas de la liste à un élément (l'élément cherché est pointé par la tete ET la queue) est géré par le elseif
    -> on ne fera pas les deux cas ;)
    */

    int trouve = 0; // variable de debug
    t_maillon* tmp = NULL;
    t_maillon* tmp2 = NULL;

    if(liste_taille(lst) == 0)
    {
        #if MODE_DEBUG==1
            printf("DEBUG (liste_generique): suppression d'un element precis impossible car la liste est vide\n");
        #endif
    }
    else if(liste_elem_tete(lst) == elem) // on compare les adresses pour savoir si on est sur le bon maillon
    {
        trouve = 1;
        liste_supprimer_tete(lst,detruire);
    }
    else if(liste_elem_queue(lst) == elem) // // on compare les adresses pour savoir si on est sur le bon maillon
    {
        trouve = 1;
        liste_supprimer_queue(lst,detruire);
    }
    else // le maillon cherché n'est ni en tête ni en queue
    {
        tmp = lst->p_tete;
        // tant qu'on est pas sur le maillon précédant celui à supprimer
        // et tant qu'on n'est pas à la fin de la liste (impossible normalement car on doit trouver l'élément cherché)
        while(tmp->p_suiv->elem != elem && tmp->p_suiv != NULL )
        {
            tmp = tmp->p_suiv;
        }
        // on vérifie qu'on a bien trouvé le maillon qu'on veut supprimer
        if (tmp->p_suiv->elem == elem)
        {
            trouve = 1;

            //on s'assure que lst->p_courant pointe a tout moment vers un maillon valide, donc pas vers le maillon
            //que l'on va supprimer
            if(lst->p_courant == tmp->p_suiv){
                lst->p_courant = tmp;
            }

            tmp2 = tmp->p_suiv->p_suiv; // autorisé car on sait que tmp n'est pas la queue de la liste (cas traité avant)
            detruire(tmp->p_suiv->elem); // on détruit les données du maillon
            free(tmp->p_suiv); // on détruit le maillon
            tmp->p_suiv = tmp2; // on reforme les liens autour du maillon supprimé

            lst->longueur = lst->longueur -1; // on diminue la longueur de la liste
            nb_maillons_liberes++;  // on augmente le compteur de bilan mémoire
        }
    }

    if (trouve == 0) // DEBUG
    {
        #if MODE_DEBUG==1
            printf("DEBUG (liste_generique): bug: l'element qui devait etre supprime n'a pas ete trouve dans la liste\n");
        #endif
    }
}

void liste_dereferencer_precis(t_liste* lst, void* elem)
{
    /*
    Le  cas de la liste à un élément (l'élément cherché est pointé par la tete ET la queue) est géré par le elseif
    -> on ne fera pas les deux cas ;)
    */

    int trouve = 0; // variable de debug
    t_maillon* tmp = NULL;
    t_maillon* tmp2 = NULL;

    if(liste_taille(lst) == 0)
    {
        #if MODE_DEBUG==1
            printf("DEBUG (liste_generique): dereferencement d'un element precis impossible car la liste est vide\n");
        #endif
    }
    else if(liste_elem_tete(lst) == elem) // on compare les adresses pour savoir si on est sur le bon maillon
    {
        trouve = 1;
        liste_dereferencer_tete(lst);
    }
    else if(liste_elem_queue(lst) == elem) // // on compare les adresses pour savoir si on est sur le bon maillon
    {
        trouve = 1;
        liste_dereferencer_queue(lst);
    }
    else // le maillon cherché n'est ni en tête ni en queue
    {
        tmp = lst->p_tete;
        // tant qu'on est pas sur le maillon précédant celui à déréférencer
        // et tant qu'on n'est pas à la fin de la liste (impossible normalement car on doit trouver l'élément cherché)
        while(tmp->p_suiv->elem != elem && tmp->p_suiv != NULL )
        {
            tmp = tmp->p_suiv;
        }
        // on vérifie qu'on a bien trouvé le maillon qu'on veut déréférencer
        if (tmp->p_suiv->elem == elem)
        {
            trouve = 1;

            //on s'assure que lst->p_courant pointe a tout moment vers un maillon valide, donc pas vers le maillon
            //que l'on va supprimer
            if(lst->p_courant == tmp->p_suiv){
                lst->p_courant = tmp;
            }

            tmp2 = tmp->p_suiv->p_suiv; // autorisé car on sait que tmp n'est pas la queue de la liste (cas traité avant)
            free(tmp->p_suiv); // on détruit le maillon
            tmp->p_suiv = tmp2; // on reforme les liens autour du maillon supprimé

            lst->longueur = lst->longueur -1; // on diminue la longueur de la liste
            nb_maillons_liberes++;  // on augmente le compteur de bilan mémoire
        }
    }

    if (trouve == 0) // DEBUG
    {
        #if MODE_DEBUG==1
            printf("DEBUG (liste_generique): bug: l'element qui devait etre dereference n'a pas ete trouve dans la liste\n");
        #endif
    }
}

t_liste* liste_rechercher(t_liste* lst, tpf_recherche recherche)
{
    // On devrait recevoir en paramètre un paramètre facultatif
    // qui peut être parfois nécessaire dans la fonction de recherche
    // si l'on reçoit NULL, ça veut dire que l'utilisateur ne veut pas l'utiliser dans sa fonction de recherche

    t_liste* liste_trouvee = NULL;
    liste_trouvee = liste_creer();

    // on parcourt toute la liste
    for(liste_demarrer(lst); liste_encore(lst); liste_suivant(lst))
    {
        // si l'élément courant est interessant
        if(recherche(liste_elem_courant(lst)) == 1)
        {
            // on ajoute l'élément à la liste des éléments trouvés
            liste_ajout_queue(liste_trouvee,liste_elem_courant(lst));
        }
    }

    return liste_trouvee;
}

void liste_ajout_avant(t_liste* lst, void* elem_a_inserer, void* elem_ref)
{
    // On va gérer 4 cas séparément:
    // _ l'ajout dans une liste vide (impossible dans la logique de la fonction)
    // _ l'ajout en tete
    // _ l'ajout au milieu

    t_maillon* pprec = NULL;
    int trouve = 0; // DEBUG

    // cas de l'ajout dans une liste vide ou d'un élément de référence à NULL
    if((liste_taille(lst) == 0) || (elem_ref == NULL))
    {
        #if MODE_DEBUG==1
            printf("DEBUG (liste_generique): BUG: la liste est vide, impossible d'ajouter avant l'element demande car il ne sera pas dans la liste\n");
            printf("DEBUG (liste_generique): BUG: ou bien l'element de reference envoye vaut NULL\n");
        #endif
    }

    // cas de l'ajout en tête ( = si l'élément à ajouter est censé être placé avant la tete )
    else if(liste_elem_tete(lst) == elem_ref)
    {
        liste_ajout_tete(lst,elem_a_inserer);
    }
    // cas de l'ajout au milieu
    else
    {
        t_maillon* nouv;
        nouv = (t_maillon*) malloc(1*sizeof(t_maillon));
        nouv->elem = elem_a_inserer; // on accroche la donnée reçue en paramètre
        nouv->p_suiv = NULL;
        nb_maillons_alloues++; // on augmente le compteur de bilan mémoire
        lst->longueur = lst->longueur + 1;

        // on parcourt toute la liste, et on regarde si l'élément doit être placé avant l'élément actuel
        // le 1er tour de la boucle for traite le cas de l'ajout en tête, ce qui bugguerait vu les actions faites
        // mais le cas de l'ajout en tête est impossible ici, car il a déjà été traité avant
        pprec = lst->p_tete;
        for(liste_demarrer(lst); liste_encore(lst); liste_suivant(lst))
        {
            if(liste_elem_courant(lst) == elem_ref)
            {
                trouve=1;
                nouv->p_suiv = lst->p_courant;
                pprec->p_suiv = nouv;
                break; // on arrete de parcourir la liste, c'est bon, on a placé notre élément
            }
            pprec = lst->p_courant;
        }
        if(trouve==0)
        {
            #if MODE_DEBUG==1
                printf("DEBUG (liste_generique): BUG: impossible d'ajouter avant l'element demande car il n'est pas dans la liste\n");
            #endif
        }
    }
}

void* liste_recup_tete(t_liste* lst)
{
    t_maillon* tmp = NULL;
    void* elem_tete = NULL;

    if(!liste_vide(lst))
    {
        //on s'assure que lst->p_courant pointe a tout moment vers un maillon valide, donc pas vers le maillon
        //que l'on va supprimer
        if(lst->p_courant == lst->p_tete) {
            lst->p_courant = lst->p_tete->p_suiv;
        }
        tmp = lst->p_tete->p_suiv;
        elem_tete = lst->p_tete->elem;
        free(lst->p_tete); // on détruit le maillon, mais pas les données.
        lst->p_tete = tmp; // on fait pointer la tête sur le successeur du maillon détruit
        lst->longueur = lst->longueur -1; // on diminue la longueur de la liste
        if(lst->longueur == 0) // si on vient de supprimer le dernier element
        {
            lst->p_queue = NULL;
        }
        nb_maillons_liberes++;  // on augmente le compteur de bilan mémoire
    }
    else
    {
        #if MODE_DEBUG==1
            printf("DEBUG (liste_generique): BUG: impossible supprimer tete, la liste est vide\n");
        #endif
    }

    return elem_tete;
}

void* liste_recup_queue(t_liste* lst)
{
    t_maillon* tmp = NULL;
    void* elem_queue = NULL;

    if (liste_vide(lst)) // cas de la liste vide
    {
         #if MODE_DEBUG==1
            printf("DEBUG (liste_generique): BUG: liste vide impossible de recuperer l'elem de queue\n");
        #endif
    }

    else if (liste_taille(lst) == 1) // cas de la liste à un élément
    {
        //on s'assure que lst->p_courant pointe a tout moment vers un maillon valide, donc pas vers le maillon
        //que l'on va supprimer
        if(lst->p_courant == lst->p_tete) {
            lst->p_courant = NULL;
        }
        elem_queue = lst->p_tete->elem;
        free(lst->p_tete); // on détruit le maillon mais pas les données
        lst->p_tete = NULL;
        lst->p_queue = NULL;
        lst->longueur = lst->longueur -1; // on diminue la longueur de la liste
        nb_maillons_liberes++;  // on augmente le compteur de bilan mémoire
    }

    else // cas de la liste à plus d'un élément
    {
        tmp = lst->p_tete;
        while(tmp->p_suiv->p_suiv != NULL) // autorisé car on sait qu'il y a au moins 2 élements dans la liste
        {
            tmp = tmp->p_suiv;
        }
        //on s'assure que lst->p_courant pointe a tout moment vers un maillon valide, donc pas vers le maillon
        //que l'on va supprimer
        if(lst->p_courant == tmp->p_suiv){
            lst->p_courant = tmp;
        }
        elem_queue = tmp->p_suiv->elem;
        free(tmp->p_suiv); // on détruit le maillon de queue, mais pas les données
        tmp->p_suiv = NULL; // on indique que l'avant dernier maillon devient le dernier
        lst->p_queue = tmp; // on met à jour la queue
        lst->longueur = lst->longueur -1; // on diminue la longueur de la liste
        nb_maillons_liberes++;  // on augmente le compteur de bilan mémoire
    }

    return elem_queue;
}
