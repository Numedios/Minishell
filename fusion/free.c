#include "minishell.h"

void free_split_elem(t_split_elem *lst)
{
	if (lst)
    {
		if (lst -> arg)
		{
			//printf("free = %s\n", lst->arg);
			free(lst -> arg);
		}
    }
	lst-> next = NULL;
	free(lst);
}

void    ft_free_split_arg(t_split_elem  **lst)
{
    t_split_elem    *tmp;

    tmp = *lst;
    if (lst)
    {
        while (*lst)
        {
            tmp = (*lst)->next;
            free_split_elem(*lst);
            *lst = tmp;
        }
    }
    //free(lst);
}

void    ft_free_tab(char **tab)
{
    int i;

    i = 0;
    while (tab && tab[i])
    {
        free(tab[i]);
		i++;
    }
    if (tab)
        free(tab);
}

void    free_input_output(t_input_output *lst)
{
    if (lst)
    {
        if (lst -> file_name)
            free(lst -> file_name);
        if (lst -> operator)
            free(lst -> operator);
    }
    free(lst);
}

/*void    free_input_output_middle(t_input_output **lst, t_input_output **first)
{
    t_input_output **tmp;

    tmp = malloc(sizeof(t_input_output *));
    *tmp = (*lst) -> next;
    if ((*lst)->prev)
    {
        (*lst) -> prev -> next = (*lst)->next;
        (*lst) -> next -> prev = (*lst) -> prev;
    }
    else 
    {
        (*lst) -> next -> prev = NULL;
        if (*first)
            *first = (*lst) -> next;
    }
    if (lst && *lst)
    {
        if ((*lst) -> file_name)
            free((*lst) -> file_name);
        if ((*lst) -> operator)
            free((*lst) -> operator);
    }
   
    free(*lst);
    *lst = *tmp;
    free(tmp);
}*/

void    free_input_output_middle(t_input_output **lst, t_input_output **first)
{
    // Sauvegarder les pointeurs sur les éléments précédent et suivant
  t_input_output *prev = (*lst)->prev;
  t_input_output *next = (*lst)->next;

  // Libérer l'élément courant
  free_input_output(*lst);
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


void free_inputs_outputs(t_input_output **lst)
{
    t_input_output  *tmp;

    //ft_print_input_output(*lst);
    tmp = *lst;
    if (lst)
    {
        while (*lst)
        {
            tmp = (*lst)->next;
            free_input_output(*lst);
            *lst = tmp;
        }
    }
}



void    free_maillon(t_maillons *lst)
{
    if (lst)
    {
        /*printf("free maillons split_elem\n");
        ft_print_split_elem(lst -> args);
        printf("free output\n");
        ft_print_input_output(lst->output);
        printf("free cmd = %s\n", lst ->command);*/
        if (lst -> args)
            ft_free_split_arg(&lst -> args);
        if (lst -> command)
            free(lst -> command);
        if (lst -> output)
            free_inputs_outputs(&lst->output);
        free(lst);
    }
    
}

void    free_maillons(t_maillons **lst)
{
    t_maillons *tmp;

    tmp = *lst;
    if (lst)
    {
        while (*lst)
        {
            tmp = (*lst)->next;
            free_maillon(*lst);
            *lst = tmp;
        }
    }
}