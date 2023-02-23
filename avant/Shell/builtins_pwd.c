#include "minishell.h"

void    pwd()
{
    char *str;

    str = getcwd(NULL, 0);
    printf("%s\n", str);
    free(str);
}