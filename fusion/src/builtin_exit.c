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

/*
* s pour status
*/

void	do_exit(char *s, t_garbage *garbage)
{
	long long	exit_code;
	int			flag;

	exit_code = 2;
	flag = 0;
	while (s && s[flag])
	{
		while (s[flag] == 32 || (s[flag] >= 9 && s[flag] <= 13))
			flag++;
		if (s[flag] == '-' || s[flag] == '+')
			flag++;
		if (s[flag] >= '0' && s[flag] <= '9')
			flag++;
		else
		{
			dprintf(2, "Minishell: exit: %s: numeric argument required\n", s);
			exit_free(garbage, 2);
		}
	}
	flag = 0;
	exit_code = ft_atoll_capped(s, &flag, 1, 0);
	if (flag == 0)
		exit_free(garbage, exit_code);
	else
		exit_free(garbage, 2);
}
