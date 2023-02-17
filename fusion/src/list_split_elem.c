/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_split_elem.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:37:01 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/02/13 11:37:02 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_split_elem	*create_split_elem(char	*str)
{
	t_split_elem	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new -> arg = str; // maybe mettre un dump
	new -> next = NULL;
	return (new);
}

t_split_elem	*create_split_elem_dup(char	*str)
{
	t_split_elem	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new -> arg = ft_strdup(str); // maybe mettre un dump
	new -> next = NULL;
	return (new);
}

t_split_elem	*lstlast_split_elem(t_split_elem *lst)
{
	while (lst)
	{
		if (!(lst -> next))
			return (lst);
		lst = lst -> next;
	}
	return (lst);
}

void	add_end_split_elem(t_split_elem	**list, t_split_elem *add)
{
	t_split_elem	*search;

	//ft_print_split_elem(add);
	if (!*list)
	{
		*list = add;
		return ;
	}
	search = lstlast_split_elem(*list);
	search -> next = add;
}
