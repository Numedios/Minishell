/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_input_output.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:27:07 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/02/17 17:54:09 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* o pour operateur*/

t_input_output	*create_input_output(char *name, char *o, t_input_output *prev, t_garbage *g)
{
	t_input_output	*new;

	new = malloc(sizeof(*new));
	if (!new)
		free_garbage_env_exit(g, 1);
	new -> file_name = ft_strdup(name);
	if (!new->file_name)
		free_garbage_env_exit(g, 1);
	new -> operator = ft_strdup(o);
	if (!new->operator)
		free_garbage_env_exit(g, 1);
	new -> prev = prev;
	new -> next = NULL;
	return (new);
}

t_input_output	*lstlast_input_output(t_input_output *lst)
{
	while (lst)
	{
		if (!(lst -> next))
			return (lst);
		lst = lst -> next;
	}
	return (lst);
}

void	add_end_input_output(t_input_output **list, t_input_output *add)
{
	t_input_output	*search;

	if (!(*list))
	{
		*list = add;
		return ;
	}
	search = lstlast_input_output(*list);
	search -> next = add;
}
