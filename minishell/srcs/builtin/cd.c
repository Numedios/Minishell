#include "../../includes/minishell.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>

int cd(char *path)
{
    if (chdir(path) != 0)
    {
        perror("chdir");
        return (1);
    }
    return (0);
}




