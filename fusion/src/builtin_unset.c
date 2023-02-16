/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 19:36:17 by zakariyaham       #+#    #+#             */
/*   Updated: 2023/02/15 21:57:58 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//on peut unset autant qu'on veut

/*
Probleme je fais dispa
*/
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
void	do_unset(char *tab, char **env_copy, int i, int found_line)
{
	int	n;

	n = 0;
	if (tab == NULL)
		return ;
	if (env_copy[i] == NULL)
		return ;
	while (tab && tab[n])
		n++;
	while (env_copy[i])
	{
		if (ft_strncmp(tab, env_copy[i], n) == 0)
		{
			free(env_copy[i]);
			env_copy[i] = env_copy[i + 1];
			found_line++;
		}
		if (found_line == 1)
			env_copy[i] = env_copy[i + 1];
		i++;
	}
	// if (found_line == 1)
	// 	free(env_copy[i - 1]);
}
