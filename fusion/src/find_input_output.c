/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_input_output.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:11:17 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/02/17 17:49:38 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_input_output_loop(t_split_elem *lst)
{
	return ((!(ft_strcmp((lst)->arg, "<") || ft_strcmp((lst)->arg, "<<")
				|| ft_strcmp((lst)->arg, ">") || ft_strcmp((lst)->arg, ">>"))));
}

// si l' prev est un < ou << ou > ou >> (pour le premier if)
// si *lst differend de > >> < << (pour le deuxieme if)
t_input_output	*find_input_output(t_split_elem *lst)
{
	t_input_output	*first;
	t_input_output	*add;
	t_input_output	*input_prev;
	t_split_elem	*prev;

	prev = lst;
	first = NULL;
	input_prev = NULL;
	add = NULL;
	while (lst)
	{
		if (ft_strcmp(prev->arg, "<") || ft_strcmp(prev->arg, "<<")
			|| ft_strcmp(prev->arg, ">") || ft_strcmp(prev->arg, ">>"))
		{
			if (find_input_output_loop(lst))
			{
				add = create_input_output((lst)->arg, prev->arg, input_prev);
				add_end_input_output(&first, add);
			}
		}
		prev = lst;
		input_prev = add;
		lst = (lst)-> next;
	}
	return (first);
}
