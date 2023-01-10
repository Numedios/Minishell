/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelabba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 14:55:25 by sbelabba          #+#    #+#             */
/*   Updated: 2022/12/01 14:57:45 by sbelabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* ajoute /cmd a la fin de chaque ligne du tableau et renvoie le res*/

void	add_cmd(char **cpy, char *cmd)
{
	int	i;

	i = 0;
	while (cpy[i])
	{
		cpy[i] = ft_strjoin_pipex(cpy[i], cmd);
		i++;
	}
	cpy[i++] = ft_strdup(cmd);
	cpy[i] = 0;
}

/* creer une copie d'un tableau de char*/

char	**create_cpy_tab(char **path)
{
	char	**cpy;
	int		i;

	cpy = NULL;
	i = 0;
	cpy = malloc(sizeof(char *) * (ft_strlen_tab(path) + 2));
	if (!cpy)
		return (NULL);
	while (path[i])
	{
		cpy[i] = ft_strdup(path[i]);
		if (!cpy[i])
		{
			free_tab(cpy);
			return (NULL);
		}
		i++;
	}
	cpy[i++] = 0;
	cpy[i] = 0;
	return (cpy);
}

/* Appele les fonction pour creer une copie du  tableau et le return 
 renvoie NULL si echoue
 */

char	**cpy_cmd_tab(char **path, char *cmd)
{
	char	**cpy;

	cpy = create_cpy_tab(path);
	if (!cpy)
		return (NULL);
	add_cmd(cpy, cmd);
	if (!cpy)
		return (NULL);
	return (cpy);
}
