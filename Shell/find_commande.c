#include "minishell.h"

/*
*
* print la commande et ces argument si il y en a 
*   
*   a changer et a envoyer sa dans la structure maillon dans commande et arg sous forme de tab
*
*/



char    *find_command(t_split_elem *lst)
{
    t_split_elem	*prev;

	prev = lst;
    while (lst)
    {
        if (!(ft_strcmp(prev->arg, "<") || ft_strcmp(prev->arg, "<<") || ft_strcmp(prev->arg, ">") || ft_strcmp(prev->arg, ">>"))) // si l' prev est pas un < ou << ou > ou >>
            if (!(ft_strcmp((lst)->arg, "<") || ft_strcmp((lst)->arg, "<<") || ft_strcmp((lst)->arg, ">") || ft_strcmp((lst)->arg, ">>"))) // si *lst differend de > >> < << 
                    return ((lst)->arg);
        prev = lst;
        lst = (lst)->next;
    }
}


t_split_elem    *find_argument(t_split_elem *lst)
{
    t_split_elem	*prev;
    t_split_elem    *res;
    int i;

    i = 0;
	prev = lst;
    res = NULL;
    while (lst)
    {
        if (!(ft_strcmp(prev->arg, "<") || ft_strcmp(prev->arg, "<<") || ft_strcmp(prev->arg, ">") || ft_strcmp(prev->arg, ">>"))) // si l' prev est pas un < ou << ou > ou >>
            if (!(ft_strcmp((lst)->arg, "<") || ft_strcmp((lst)->arg, "<<") || ft_strcmp((lst)->arg, ">") || ft_strcmp((lst)->arg, ">>"))) // si *lst differend de > >> < << 
            {   
                if (i != 0)
                    add_end_split_elem(&res, create_split_elem(lst->arg));
                i++;
            }
        prev = lst;
        lst = (lst)->next;
    }
    return (res);
}


// > in >> in2 cat -e < out <out2 << out3 -l


/*
char    *find_command(t_split_elem *lst)
{
    t_split_elem	*prev;

    ft_print_split_elem(lst);
	prev = lst;
    while (lst)
    {
        if (!(ft_strcmp(prev->arg, "<") || ft_strcmp(prev->arg, "<<") || ft_strcmp(prev->arg, ">") || ft_strcmp(prev->arg, ">>"))) // si l' prev est pas un < ou << ou > ou >>
            if (!(ft_strcmp((lst)->arg, "<") || ft_strcmp((lst)->arg, "<<") || ft_strcmp((lst)->arg, ">") || ft_strcmp((lst)->arg, ">>"))) // si *lst differend de > >> < << 
            {
                    printf("commande = %s \n", lst->arg);
                    lst = lst->next;
                    //return ((prev)->arg);
                    break;
            }
        prev = lst;
        lst = (lst)->next;
    }
    while (lst)
    {
        if (!(ft_strcmp(prev->arg, "<") || ft_strcmp(prev->arg, "<<") || ft_strcmp(prev->arg, ">") || ft_strcmp(prev->arg, ">>"))) // si l' prev est pas un < ou << ou > ou >>
            if (!(ft_strcmp((lst)->arg, "<") || ft_strcmp((lst)->arg, "<<") || ft_strcmp((lst)->arg, ">") || ft_strcmp((lst)->arg, ">>"))) // si *lst differend de > >> < << 
                    printf("argument = %s \n", (lst)->arg);
        prev = lst;
        lst = (lst)->next;
    }
}*/

/*
char    *find_command(t_split_elem **lst)
{
    t_split_elem	*prev;
    t_split_elem    *first;

    first = *lst;
	prev = *lst;
    while (*lst)
    {
        if (!(ft_strcmp(prev->arg, "<") || ft_strcmp(prev->arg, "<<") || ft_strcmp(prev->arg, ">") || ft_strcmp(prev->arg, ">>"))) // si l' prev est pas un < ou << ou > ou >>
            if (!(ft_strcmp((*lst)->arg, "<") || ft_strcmp((*lst)->arg, "<<") || ft_strcmp((*lst)->arg, ">") || ft_strcmp((*lst)->arg, ">>"))) // si *lst differend de > >> < << 
            {
                    printf("commande = %s \n", (*lst)->arg);
                    prev = *lst;
                    *lst = (*lst)->next;
                    return ((prev)->arg);
                    break;
            }
        prev = *lst;
        *lst = (*lst)->next;
    }
    while (*lst)
    {
        if (!(ft_strcmp(prev->arg, "<") || ft_strcmp(prev->arg, "<<") || ft_strcmp(prev->arg, ">") || ft_strcmp(prev->arg, ">>"))) // si l' prev est pas un < ou << ou > ou >>
            if (!(ft_strcmp((*lst)->arg, "<") || ft_strcmp((*lst)->arg, "<<") || ft_strcmp((*lst)->arg, ">") || ft_strcmp((*lst)->arg, ">>"))) // si *lst differend de > >> < << 
                    printf("argument = %s \n", (*lst)->arg);
        prev = *lst;
        *lst = (*lst)->next;
    }
    *lst =first;
}*/


