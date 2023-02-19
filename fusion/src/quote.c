/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 18:06:12 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/02/17 18:10:32 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*
* renvoie 1 si tout les quote sont fermer
* renvoie 0 sinon
*
*/

int	quote_close(char *str)
{
	char	c;

	if (!str)
		return (0);
	while (str && *str)
	{
		if (*str && (*str == '\'' || *str == '\"'))
		{
			c = *str;
			str++;
			while (*str && *str != c)
				str++;
			if (*str != c)
				return (0);
		}
		str++;
	}
	return (1);
}