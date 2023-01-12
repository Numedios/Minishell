#include "minishell.h"

int ft_strlen_maillons(t_maillons *lst)
{
    int    i;
    
    i = 0;
    while (lst)
    {
        i++;
        lst = lst -> next;
    }
    return (i);
}