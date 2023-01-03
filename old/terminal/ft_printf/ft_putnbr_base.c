/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 22:27:04 by zhamdouc          #+#    #+#             */
/*   Updated: 2022/06/03 14:21:34 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	check_base(char *base, int i);

void	ft_putnbr_base(long nbr, char *base, int *len)
{
	int			i;
	long long	nb;

	i = 0;
	nb = nbr;
	while (base[i])
		i++;
	if (check_base(base, i) == 1)
		return ;
	if (nb < 0)
	{
		write (1, "-", 1);
		nb = nb * -1;
		*len = *len + 1;
	}
	if ((0 <= nb) && (nb < i))
	{
		write(1, &base[nb], 1);
		*len = *len + 1;
	}
	if (nb >= i)
	{
		ft_putnbr_base(nb / i, base, len);
		ft_putnbr_base(nb % i, base, len);
	}
}

static int	check_base(char *base, int i)
{
	int	a;
	int	b;

	a = 0;
	b = 1;
	if (i == 0 || i == 1)
		return (1);
	while (base[a] != 0)
	{
		while (base[a] != base[b] && base[b] != '\0')
			b++;
		if (base[a] == base[b] || base[a] == '-' || base[a] == '+')
			return (1);
		a++;
	}
	return (0);
}
/*
int     main()
{
        ft_putnbr_base(-2147483648, "01");

}*/
