#include "minishell.h"


char	*get_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strcmp_pipex(envp[i], "PATH="))
			break ;
		i++;
	}
	if (envp[i])
		return (&*envp[i] + 5);
	return (NULL);
}


/* 
*
* retun 1 si contien un /
* return 0 sinon
* 
*/

int	check_is_path(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

/*
* str contient la suposer commande ls
* tab contient les chemin possible ex ( /usr/bin , /usr, /bin/usr/lol )
*
*/
void change_cmd(char **str, char **tab)
{
    char *res;
    int i;

    i = 0;
    res = NULL;
    if (check_is_path(*str))
        return ;
    while (tab && tab[i])
    {
        res = ft_strjoin_pipex(tab[i], *str);
        if (access(res, X_OK | F_OK) == 0)
			{
				free(*str);
                *str = res;
				return ;
			}
        free(res);
        i++;
    }

}

int cmd_to_path(t_maillons *maillons, char **env)
{
    char    **pat;

    pat = split_pipex(get_path(env), ':');
    while (maillons)
    {
        change_cmd(&(maillons->command) , pat);
        maillons = maillons->next;
    }
    ft_free_tab(pat);
    return (1);
}