#include "minishell.h"

void    cd(char **arg)
{
    if (!arg)
    {
        dprintf(2, "minishell: cd: path argument required\n"); // remplacer
        return;
    }
    if (arg[1])
    {
		dprintf(2, "minishell: cd: to many arguments\n");
		return ;
    }
    if (!chdir(arg[0]))
        return;
    dprintf(2, "minishell: cd: ");
    perror("chdir");
}