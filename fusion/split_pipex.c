#include "minishell.h"


int	ft_strcmp_pipex(char *str, char *search)
{
	int	i;

	i = 0;
	while (search[i])
	{
		if (str[i] != search[i])
			return (0);
		i++;
	}
	return (1);
}

int	count_world(char *path, char sep)
{
	int	i;
	int	word;

	word = 0;
	i = 0;
	while (path && path[i])
	{
		while (path[i] && path[i] == sep)
			i++;
		if (path[i] && path[i] != sep)
			word++;
		while (path[i] && path[i] != sep)
			i++;
	}
	return (word);
}

char	*create_word_pipex(char *path, char sep)
{
	int		i;
	char	*res;

	i = 0;
	while (path && path[i] && path[i] != sep)
		i++;
	res = malloc(sizeof(char) * (i + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (path && path[i] && path[i] != sep)
	{
		res[i] = path[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	**split_pipex(char *path, char sep)
{
	char	**res;
	int		i;

	i = 0;
	res = malloc(sizeof(char *) * (count_world(path, sep) + 2));
	if (!res)
		return (NULL);
	while (path && *path)
	{
		while (*path && *path == sep)
			path++;
		if (path && *path != sep)
		{
			res[i] = create_word_pipex(path, sep);
			if (!res[i++])
			{
				ft_free_tab(res);
				return (NULL);
			}
		}
		while (*path && *path != sep)
			path++;
	}
	res[i] = 0;
	return (res);
}
