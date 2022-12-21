/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:27:54 by zhamdouc          #+#    #+#             */
/*   Updated: 2022/06/15 19:06:24 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int		which_argument(const char *s, int i, int *len, va_list arg);
static void		ft_putchar_printf(char c, int fd, int *len);
static void		ft_putstr_printf(char *s, int fd, int *len);

int	ft_printf(const char *s, ...)
{
	va_list	arg;
	int		i;
	int		incrementation;
	int		*len;

	len = &incrementation;
	va_start (arg, s);
	i = 0;
	incrementation = ft_strlen(s);
	while (s[i])
	{
		while (s[i] != '%' && s[i])
		{
			write (1, &s[i], 1);
			i++;
		}
		if (s[i] == '%')
		{
			which_argument(s, i, len, arg);
			i = i + 2;
		}
	}
	va_end(arg);
	return (incrementation);
}

static int	which_argument(const char *s, int i, int *len, va_list arg)
{
	*len = *len - 2;
	if (s[i] == '%' && s[i + 1] == '%')
	{
		write(1, "%%", 1);
		*len = *len + 1;
	}
	else if (s[i + 1] == 'c')
		ft_putchar_printf((unsigned char) va_arg(arg, int), 1, len);
	else if (s[i + 1] == 's')
		ft_putstr_printf(va_arg(arg, char *), 1, len);
	else if (s[i + 1] == 'p')
		f_pba((unsigned long long)va_arg(arg, void *), "0123456789abcdef", len);
	else if (s[i + 1] == 'd' || s[i + 1] == 'i')
		ft_putnbr_printf(va_arg(arg, int), len);
	else if (s[i + 1] == 'u')
		ft_putnbr_base(va_arg(arg, unsigned int), "0123456789", len);
	else if (s[i + 1] == 'x')
		ft_putnbr_base(va_arg(arg, unsigned int), "0123456789abcdef", len);
	else if (s[i + 1] == 'X')
		ft_putnbr_base(va_arg(arg, unsigned int), "0123456789ABCDEF", len);
	return (0);
}

static void	ft_putchar_printf(char c, int fd, int *len)
{
	const void	*buf;

	buf = &c;
	write(fd, buf, 1);
	*len += 1;
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
