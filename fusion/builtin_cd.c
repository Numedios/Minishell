#include "minishell.h"

int do_cd(char *path)
{
    if (chdir(path) != 0)
    {
        perror("chdir");
        return (1);
    }
    return (0);
}
