#include "minishell.h"

t_maillons  *create_maillons(t_split_elem **split, t_maillons *prev)
{
    t_maillons  *new;

    new = malloc(sizeof(*new));
    new -> command = find_command(*split);
    new -> args = find_argument(*split);
    new -> output = find_input_output(*split); 
    new -> next = NULL;
    new -> prev = prev;
    
    /*printf("la commande est %s\n", new->command);
    printf("les arg sont :  ");
    ft_print_split_elem(new ->args);
    printf("les output sont :  \n");
    ft_print_input_output(new->output);*/
    return (new);
}

t_maillons  *lstlast_maillons(t_maillons *lst)
{
    while (lst)
    {
        if (!lst -> next)
            return (lst);
        lst = lst -> next;
    }
    return (lst);
}

void    add_end_maillons(t_maillons **lst, t_maillons *add)
{
    t_maillons    *search;

    if (!(*lst))
    {
        *lst = add;
        return ;
    }
    search = lstlast_maillons(*lst);
    search -> next = add;
}


/*
    pour create maillons

    /*printf("la commande est %s\n", new->command);
    printf("les arg sont :  ");
    ft_print_split_elem(new ->args);
    printf("les output sont :  \n");
    ft_print_input_output(new->output);
*/