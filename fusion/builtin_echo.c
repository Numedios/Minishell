#include "minishell.h"

int do_echo(char *string, int i)//envoyer i = 1 pour l'option "-n"
{
    if (i == 0)
    {
        printf("%s", string);
        return (0);
    }
    if (i == 1)
    {
        printf("%s\n", string);
        return (0);
    }
    return (1);
}
