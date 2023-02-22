/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 19:36:02 by zakariyaham       #+#    #+#             */
/*   Updated: 2023/02/20 22:33:27 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* renvoie 1 et change space ( si space == 1) si str est valable comme  option -n
* 0 sinon
*/
// rajouter echo $? qui imprime le code erreur

extern int	g_exit_code[2];

int	check_option_n(char *str, int *space)
{
	int	i;

	if (!str)
		return (0);
	i = 2;
	if (str[1] == '\0')
		return (0);
	if ((str[0] && str[1]) && (str[0] != '-' || str[1] != 'n'))
		return (0);
	while (str && str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	if (*space == 1)
		*space = *space * -1;
	return (1);
}

/*
*  space = 1 signifie qu'il n'y a pas de -n
*  space = -1 signifie au'il y a un -n
*
* reproduit le comportement de echo avec loption -n
* enlever les printf
*
* gestion cas d'erreur a faire --> tout free et message d'erreur
*/

void	do_echo(char **arg)
{
	int	space;
	int	i;

	i = 0;
	space = 1;
	if (arg)
	{
		while (check_option_n(arg[i], &space))
			i++;
	}
	while (arg && arg[i])
	{
		s_fd(arg[i], 1);
		if (arg && arg[i] && arg[i + 1])
			s_fd(" ", 1);
		i++;
	}
	if (space == 1)
		printf("\n");
	g_exit_code[0] = 0;
}
