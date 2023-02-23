/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelabba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 14:30:43 by sbelabba          #+#    #+#             */
/*   Updated: 2022/12/01 14:39:22 by sbelabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

char	*create_word(char *path, char sep)
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
			res[i] = create_word(path, sep);
			if (!res[i++])
			{
				free_tab(res);
				return (NULL);
			}
		}
		while (*path && *path != sep)
			path++;
	}
	res[i] = 0;
	return (res);
}
