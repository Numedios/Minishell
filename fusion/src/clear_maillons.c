/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_maillons.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 19:36:23 by zakariyaham       #+#    #+#             */
/*   Updated: 2023/02/17 17:37:56 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* return (1) si lst contient sep dans un operator
* return (0) sinon
*
*
*
*
*/

void	free_maillon_middle(t_maillons **lst, t_maillons **first)
{
	t_maillons	*prev;
	t_maillons	*next;

	prev = (*lst)->prev;
	next = (*lst)->next;
	free_maillon(*lst);
	*lst = NULL;
	if (prev != NULL)
		prev->next = next;
	else
		*first = next;
	if (next != NULL)
		next->prev = prev;
}

/*
*
* return 1 si il y a le separateur souhaiter
* 0 sinon
*/

int	find_if_have_output(t_input_output *lst, char *sep)
{
	while (lst)
	{
		if (ft_strcmp(lst-> operator, sep))
		{
			return (1);
		}
		lst = lst ->next;
	}
	return (0);
}

char	*find_s(t_input_output *lst, char *sep)
{
	while (lst && lst)
	{
		if (ft_strcmp(lst-> operator, sep))
			return (lst->file_name);
		lst = lst ->next;
	}
	return (NULL);
}
// > a | 1| 2 | 3 > a | b | >c | 4 | 5  >a | b | d |e | >4 | 6 >a| >a