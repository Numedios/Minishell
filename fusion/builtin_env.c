#include "minishell.h"

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

char **	my_env(char **env)
{
	int i;
	char **env_copy;

	i = 0;
	if (env[i] == NULL)
		return (NULL);
	while(env[i])
		i++;
	env_copy = malloc ((i + 1) * sizeof(char*));
	if (env_copy == NULL)
		return (NULL);
	i = 0;
	while (env[i])
	{
		env_copy[i] = ft_strdup_const(env[i]);
		if (env_copy[i] == NULL)
			return (NULL);
		i++;
	}
	return (env_copy);
}