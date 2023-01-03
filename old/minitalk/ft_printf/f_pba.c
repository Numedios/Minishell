/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_pba.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 22:27:04 by zhamdouc          #+#    #+#             */
/*   Updated: 2022/06/15 19:06:41 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int		check_base(long nbr, char *base, int i, int *len);
static void		ft_putstr_printf(char *s, int fd, int *len);

void	f_pba(unsigned long long nbr, char *base, int *len)
{
	unsigned long long	i;
	unsigned long long	nb;

	i = 0;
	nb = nbr;
	while (base[i])
		i++;
	if (check_base(nbr, base, i, len) == 1)
		return ;
	if (nb < i)
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

static int	check_base(long nbr, char *base, int i, int *len)
{
	int	a;
	int	b;

	if (nbr == 0 || nbr == -1)
	{
		if (nbr == 0)
			ft_putstr_printf("(nil)", 1, len);
		if (nbr == -1)
			ft_putstr_printf("0xffffffffffffffff", 1, len);
		return (1);
	}
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
	ft_putstr_printf("0x", 1, len);
	return (0);
}

static void	ft_putstr_printf(char *s, int fd, int *len)
{
	int			i;
	const void	*buf;

	if (s == NULL)
	{
		write(1, "(null)", 6);
		*len = *len + 6;
		return ;
	}
	i = ft_strlen(s);
	*len = *len + i;
	buf = s;
	write(fd, buf, i);
}
/*
int     main()
{
        ft_putnbr_base(-2147483648, "01");

}*/
