#include "minishell.h"
//on peut unset autant qu'on veut 
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
//mettre env en variable globale, malloc env dans une nouvelle variable pour pouvoir le manipuler comme on le souhaite
void    do_unset(char *tab, char **env_copy)
{
    int i;
    int n;
    int found_line;

    i = 0;
    found_line = 0;
    n = 0;
    if (tab ==  NULL)
        return ;
	if (env_copy[i] ==  NULL)
        return ;
    while (tab && tab[n])
        n++;
    while (env_copy[i])
    {
        if (ft_strncmp(tab, env_copy[i], n) == 0)
        {
            env_copy[i] = env_copy[i + 1];
            found_line++;
        }
        if (found_line == 1)
            env_copy[i] = env_copy[i + 1];
        i++;
    }
    if (found_line == 1)
        free(env_copy[i - 1]);
}