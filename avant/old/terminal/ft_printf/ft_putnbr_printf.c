/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_printf.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 08:30:57 by zhamdouc          #+#    #+#             */
/*   Updated: 2022/06/03 14:21:07 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	put_char(char a, int *len);
void		ft_putnbr_printf(int nb, int *len);

void	ft_putnbr_printf(int nb, int *len)
{
	if (nb == -2147483648)
	{
		write(1, "-2147483648", 11);
		*len = *len + 11;
		return ;
	}
	if (0 <= nb && nb < 10)
		put_char(nb + 48, len);
	if (nb < 0 && nb)
	{
		put_char('-', len);
		ft_putnbr_printf(nb * (-1), len);
	}
	if (nb >= 10)
	{
		ft_putnbr_printf(nb / 10, len);
		ft_putnbr_printf(nb % 10, len);
	}
}

static void	put_char(char a, int *len)
{
	write(1, &a, 1);
	*len = *len + 1;
}

/*if (nb == -2147483648) 
il y a plus de nombre negatif que positif 
car 0 est considere comme positif cela cree un decalage*/

/*ft_putnbr(nb / 10)
recursivite la fonction se repete tant qu'on obtient un nombre 
et le modulo conserve le resultat des restes de la division*/

/*ft_putnbr(nb % 10) 
les calculs vont permettre d'obtenir une suie de chiffre 
qui pourra traduire en char avec la table ASCII*/
