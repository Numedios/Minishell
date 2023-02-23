#include "../includes/minishell.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>

//possibilite de creer sa propre env
void    do_env(char **env)
{
    int i;

    i = 0;
    if (env == NULL)
    {
        printf("vide\n");
        return ;
    }
    while (env[i])
    {
        printf("%s\n", env[i]);
        i++;
    }
}

