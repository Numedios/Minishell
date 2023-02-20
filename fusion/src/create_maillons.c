/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_maillons.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 19:36:31 by zakariyaham       #+#    #+#             */
/*   Updated: 2023/02/13 11:29:04 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_maillons	*create_maillons(t_split_elem **s, t_maillons *p, t_garbage *g)
{
	t_maillons	*new;

	new = malloc(sizeof(*new));
	if (!new)
		free_garbage_env_exit(g, 1);
	new -> command = find_command(*s);
	new -> args = find_argument(*s);
	new -> output = find_input_output(*s, g);
	new -> heredoc = -1;
	new -> next = NULL;
	new -> prev = p;
	return (new);
}

t_maillons	*lstlast_maillons(t_maillons *lst)
{
	while (lst)
	{
		if (!lst -> next)
			return (lst);
		lst = lst -> next;
	}
	return (lst);
}

void	add_end_maillons(t_maillons **lst, t_maillons *add)
{
	t_maillons	*search;

	if (!(*lst))
	{
		*lst = add;
		return ;
	}
	search = lstlast_maillons(*lst);
	search -> next = add;
}
