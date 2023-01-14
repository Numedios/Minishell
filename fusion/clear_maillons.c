#include "minishell.h"

/*
void free_maillon_middle(t_maillons **lst, t_maillons **first)
{
    t_maillons **tmp;

    tmp = malloc(sizeof(t_maillons *));
    *tmp = NULL;
    if ((*lst)->next)
        *tmp = (*lst) ->next;
    if ((*lst)->prev)
    {
        (*lst) -> prev -> next = (*lst)->next;
        if ((*lst) -> next)
            (*lst) -> next -> prev = (*lst) -> prev;
    }
    else 
    {
        if ((*lst) -> next)
            (*lst) -> next -> prev = NULL;
        if (*first)
            *first = (*lst) -> next;
    }
    if (lst && *lst)
    {
        free_maillon(*lst);
    }
    free(*lst);
    *lst = *tmp;
    free(tmp);
}*/
/*
void free_maillon_middle(t_maillons **lst, t_maillons **first)
{
    t_maillons **tmp; // tmp sert a stocker l'element suivant l'endroit ou l'on se trouve

    tmp = malloc(sizeof(t_maillons *));
    *tmp = (*lst) ->next; // on stock l'element suivant 
    if ((*lst)->prev) // si il existe un element precedent
    {
        (*lst) -> prev -> next = (*lst)->next; // l'ellement avant prend comme suivant le suivant de l'element 
        if ((*lst) -> next) // si il y a un suivant
            (*lst) -> next -> prev = (*lst) -> prev; // le suivant  prend comme prend comme prev le prev de l'element
    }
    else // si il n'existe pas de precedent
    {
        if ((*lst) -> next)   // si il existe un suivant
            (*lst) -> next -> prev = NULL; // le suivant prend comme precedent NULL
        *first = (*lst) -> next; // FIRST devien le suivant de l'element actuelle
    }
    if (lst && *lst)
    {
        free_maillon(*lst);
    }
    free(*lst);
    *lst = *tmp; // lst devien tmp
    free(tmp);
}*/


/*
* return (1) si lst contient sep dans un operator
* return (0) sinon
*
*
*
*
*/

void free_maillon_middle(t_maillons **lst, t_maillons **first) 
{
  // Sauvegarder les pointeurs sur les éléments précédent et suivant
  t_maillons *prev = (*lst)->prev;
  t_maillons *next = (*lst)->next;

  // Libérer l'élément courant
  free_maillon(*lst);
  *lst = NULL;

  // Mettre à jour le pointeur suivant de l'élément précédent
  if (prev != NULL) {
    prev->next = next;
  } else {
    *first = next;
  }

  // Mettre à jour le pointeur précédent de l'élément suivant
  if (next != NULL) {
    next->prev = prev;
  }
}


/*
*
* return 1 si il y a le separateur souhaiter
* 0 sinon 
*/

int find_if_have_output(t_input_output *lst, char *sep)
{
    int i;

    i = 0;
    while (lst)
    {
        if (ft_strcmp(lst-> operator, sep))
        {
            return (1);
        }
        lst = lst ->next;
    }
    return (0);
}

char    *find_name_sep(t_input_output *lst, char *sep)
{
    int i;

    i = 0;
    while (lst && lst)
    {
        if (ft_strcmp(lst-> operator, sep))
            return (lst->file_name);
        lst = lst ->next;
    }
    return (NULL);
}


void    find_maillon_without_cmd(t_maillons **maillons)
{
    t_maillons *first;
    t_maillons *tmp;
  

    tmp = NULL;
    first = *maillons;
    while (*maillons)
    {
        if ((*maillons) && !((*maillons) -> command))
        {
            tmp = ((*maillons) -> prev);
            free_maillon_middle(&(*maillons), &first);
            *maillons = tmp;
            while (*maillons && !find_if_have_output((*maillons) -> output,">"))
            {
                tmp = (*maillons)->prev;
                free_maillon_middle(&(*maillons), &first);
                *maillons = tmp;
            };
        *maillons = first;
        }
        if (!(*maillons))
        {
            break;
        }
        *maillons = (*maillons) -> next;
    }
    ft_print_maillon(*maillons);
    *maillons = first;
    
}

// > a | 1| 2 | 3 > a | b | >c | 4 | 5  >a | b | d |e | >4 | 6 >a| >a