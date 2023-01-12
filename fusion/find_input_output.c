#include "minishell.h"

t_input_output  *find_input_output(t_split_elem *lst)
{
    t_input_output  *first;
    t_input_output  *add;
    t_input_output  *input_prev; 
    t_split_elem    *prev;

    prev = lst;
    first = NULL;
    input_prev = NULL;
    add = NULL;
    while (lst)
    {
         if (ft_strcmp(prev->arg, "<") || ft_strcmp(prev->arg, "<<") || ft_strcmp(prev->arg, ">") || ft_strcmp(prev->arg, ">>")) // si l' prev est un < ou << ou > ou >>
            if (!(ft_strcmp((lst)->arg, "<") || ft_strcmp((lst)->arg, "<<") || ft_strcmp((lst)->arg, ">") || ft_strcmp((lst)->arg, ">>"))) // si *lst differend de > >> < << 
            {
                add = create_input_output((lst)->arg, prev->arg, input_prev);
                add_end_input_output(&first, add);
            }
        prev = lst;
        input_prev = add;
        lst = (lst)-> next;
    }
    return (first);
}