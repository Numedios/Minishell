/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:32:18 by zhamdouc          #+#    #+#             */
/*   Updated: 2022/06/15 17:57:08 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stdlib.h>
# include <stdarg.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stddef.h>

int		ft_printf(const char *s, ...);
size_t	ft_strlen(const char *str);
void	ft_putnbr_printf(int nb, int *len);
void	ft_putnbr_base(long nbr, char *base, int *len);
void	f_pba(unsigned long long nbr, char *base, int *len);

#endif