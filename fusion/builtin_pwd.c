#include "minishell.h"

int do_pwd(void)
{
    char    cwd[4096];

    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("Minishell : pwd");
        return (1);
    }
    else
    {
        ft_putstr_fd(cwd, 1);
        write(1, "\n", 1);
    }
    return (0);
}