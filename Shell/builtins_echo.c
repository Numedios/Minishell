#include "minishell.h"

/*
* renvoie 1 et change space ( si space == 1) si str est valable comme  option -n 
* 0 sinon 
*/

int check_option_n(char *str, int *space)
{
    int i;

    if (!str)
        return (0);
    i = 2;
    if ((str[0] && str[1]) && (str[0] != '-' || str[1] != 'n'))
        return (0);
    while (str[i])
    {
        if (str[i] != 'n')
            return (0);
        i++;
    }
    if (*space == 1)
        *space = *space * -1;
    return(1);

}


/*
*  space = 1 signifie qu'il n'y a pas de -n
*  space = -1 signifie au'il y a un -n
*
* reproduit le comportement de echo avec loption -n
* enlever les printf
*  
* gestion cas d'erreur a faire --> tout free et message d'erreur
*/

void echo(char **arg)
{
    int space;
    int i;
    int j;

    i = 0;
    space = 1;
    if (arg)
    {
        while (check_option_n(arg[i], &space))
           i++;
    }
    while (arg && arg[i])
    {
        printf("%s ", arg[i]);
        i++;
    }
    if (space == 1)
        printf("\n");
}