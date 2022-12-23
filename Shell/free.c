#include "minishell.h"


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
    free(lst);
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