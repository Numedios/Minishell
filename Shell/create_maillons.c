#include "minishell.h"

t_maillons  *create_maillons(t_split_elem **split, t_maillons *maillons)
{
    t_maillons  *new;

    ft_print_split_elem(*split);
    new = malloc(sizeof(new));
    new -> command = find_command(*split);
    new -> args = find_argument(*split);
    new -> output = find_input_output(*split); 
    printf("\n\n");
    new -> next = NULL;
    ft_print_split_elem(*split);
    /*printf("la commande est %s\n", new->command);
    printf("les arg sont :  ");
    ft_print_split_elem(new ->args);
    printf("les output sont :  \n");
    ft_print_input_output(new->output);*/
    return (new);
}