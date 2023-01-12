#include "minishell.h"

t_input_output  *create_input_output(char *name, char *operator, t_input_output *prev)
{
    t_input_output  *new;


   
    new = malloc(sizeof(*new));
    if (!new)
        return (NULL);
    new -> file_name = ft_strdup(name);
    new -> operator = ft_strdup(operator);
    new -> prev = prev;
    new -> next = NULL;
    return (new);
}

t_input_output  *lstlast_input_output(t_input_output *lst)
{
    while (lst)
    {
        if (!(lst -> next))
            return (lst);
        lst = lst -> next;
    }
    return (lst);
}



void    add_end_input_output(t_input_output **list, t_input_output *add)
{
    t_input_output   *search;

    if (!(*list))
    {
        *list = add;
        return ;
    }
    search =  lstlast_input_output(*list);
    search -> next = add;
}