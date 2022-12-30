#include "../includes/minishell.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>


char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	c_copy;

	if (s == NULL)
		return (NULL);
	c_copy = (unsigned char) c;
	i = 0;
	if (c_copy == 0)
		return ((char *)&s[ft_strlen((char *)s)]);
	while (s[i])
	{
		if (s[i] != c_copy)
			i++;
		else
			return ((char *)&s[i]);
	}
	return (NULL);
}

int check_if_tab_exist (char *tab, char **env)
{
    int len;
    int i;

    len = 0;
    len = ft_strlen(tab);
    i = 0;
    while (env[i])
    {
        if (ft_strncmp(env[i], tab, len) != 0)
            i++;
        else
            return(1);
    }
    return (0);

}

char **do_export(char *tab, char **env_copy)//checker si la variable existe deja dans env
{
    int i;
    char **new_env;
    
    i = 0;
    if (ft_strchr(tab, '=') == NULL)
    {
        printf("export: `%s': not a valid identifier\n", tab);
        return (env_copy);
    }
    if (check_if_tab_exist(tab, env_copy) == 1)
    {
        printf("export: '%s' : already defined\n", tab);
        return (env_copy);
    }
    while (env_copy[i])
        i++;
    new_env = malloc ((i + 1) * sizeof(char*));//il faut ajouter une ligne de plus pour la nouvelle variable
    i = 0;
    while (env_copy[i])
    {
        new_env[i] = ft_strdup(env_copy[i]);
        free(env_copy[i]);
        i++;
    }
    free(env_copy);
    new_env[i] = ft_strdup(tab);
    new_env[i + 1] = NULL;
    return (new_env);
}
