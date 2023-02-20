/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 19:36:10 by zakariyaham       #+#    #+#             */
/*   Updated: 2023/02/20 13:35:05 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long	ft_atoll_capped(const char *nptr, int *flag, int j, int nb)
{
	long long	print;

	if (nptr == NULL)
		return (0);
	while (*nptr == 32 || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			j = -j;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		print = LLONG_MAX;
		if (j > 0 && (LLONG_MAX - *nptr + '0') / 10 < nb)
			return (++*flag, 0);
		print = ((LLONG_MAX + *nptr - '0') / 10);
		if (j < 0 && (LLONG_MAX + *nptr - '0') / 10 > -nb)
			return (++*flag, 0);
		nb = nb * 10 + *nptr - '0';
		nptr++;
	}
	return (nb * j);
}

void	exit_free(t_garbage *garbage, long long exit_code)
{
	s_fd("exit\n", 2);
	free_garbage_and_env(garbage);
	exit(exit_code);
}

void	do_exit(char *statut, t_garbage *garbage)
{
	long long	exit_code;
	int			flag;

	exit_code = 2;
	flag = 0;
	while (statut && statut[flag])
	{
		while (statut[flag] == 32 || (statut[flag] >= 9 && statut[flag] <= 13))
			flag++;
		if (statut[flag] == '-' || statut[flag] == '+')
			flag++;
		if (statut[flag] >= '0' && statut[flag] <= '9')
			flag++;
		else
		{
			dprintf(2, "Minishell: exit: %s: numeric argument required\n", statut);
			exit_free(garbage, 2);
		}
	}
	flag = 0;
	exit_code = ft_atoll_capped(statut, &flag, 1, 0);
	if (flag == 0)
		exit_free(garbage, exit_code);
	else
		exit_free(garbage, 2);
}
