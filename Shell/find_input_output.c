#include "minishell.h"

t_input_output  *find_input_output(t_split_elem *lst)
{
    t_input_output  *first;
    t_split_elem    *prev;

    prev = lst;
    first = NULL;
    while (lst)
    {
         if (ft_strcmp(prev->arg, "<") || ft_strcmp(prev->arg, "<<") || ft_strcmp(prev->arg, ">") || ft_strcmp(prev->arg, ">>")) // si l' prev est un < ou << ou > ou >>
            if (!(ft_strcmp((lst)->arg, "<") || ft_strcmp((lst)->arg, "<<") || ft_strcmp((lst)->arg, ">") || ft_strcmp((lst)->arg, ">>"))) // si *lst differend de > >> < << 
                    add_end_input_output(&first, create_input_output((lst)->arg, prev->arg));
        prev = lst;
        lst = (lst)-> next;
    }
    return (first);
}