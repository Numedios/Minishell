/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelabba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 13:28:23 by sbelabba          #+#    #+#             */
/*   Updated: 2022/12/07 13:40:54 by sbelabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_arg(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (ft_strlen(argv[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	count_space(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[i])
		return (0);
	while (str[i])
	{
		if (str[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

/*
    permet le parsing de depart nb arg < 4 et si l'argument existe
*/

int	parsing(int argc, char **argv)
{
	if (!ft_strncmp("here_doc", argv[0]) && argc < 5)
		return (0);
	if (argc < 4)
		return (0);
	if (access(argv[0], F_OK | R_OK) == -1 && ft_strncmp("here_doc", argv[0]))
	{
		perror("access");
		return (0);
	}
	return (1);
}
