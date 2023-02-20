/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 17:50:49 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/02/20 14:26:14 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split_elem(t_split_elem *lst)
{
	if (lst)
		if (lst -> arg)
			free(lst->arg);
	lst->next = NULL;
	free(lst);
}

void	ft_free_split_arg(t_split_elem **lst)
{
	t_split_elem	*tmp;

	tmp = *lst;
	if (lst)
	{
		while (*lst)
		{
			tmp = (*lst)->next;
			free_split_elem(*lst);
			*lst = tmp;
		}
	}
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		i++;
	}
	if (tab)
		free(tab);
}

void	free_input_output(t_input_output *lst)
{
	if (lst)
	{
		if (lst -> file_name)
			free(lst -> file_name);
		if (lst -> operator)
			free(lst -> operator);
	}
	free(lst);
}

void	free_input_output_middle(t_input_output **lst, t_input_output **first)
{
	t_input_output	*prev;
	t_input_output	*next;

	prev = (*lst)->prev;
	next = (*lst)->next;
	free_input_output(*lst);
	*lst = NULL;
	if (prev != NULL)
		prev->next = next;
	else
		*first = next;
	if (next != NULL)
		next->prev = prev;
}

void	free_inputs_outputs(t_input_output **lst)
{
	t_input_output	*tmp;

	tmp = *lst;
	if (lst)
	{
		while (*lst)
		{
			tmp = (*lst)->next;
			free_input_output(*lst);
			*lst = tmp;
		}
	}
}

void	free_maillon(t_maillons *lst)
{
	if (lst)
	{
		if (lst -> args)
			ft_free_tab(lst -> args);
		if (lst -> command)
			free(lst -> command);
		if (lst -> output)
			free_inputs_outputs(&lst->output);
		free(lst);
	}
}

void	free_maillons(t_maillons **lst)
{
	t_maillons	*tmp;

	tmp = *lst;
	if (lst)
	{
		while (*lst)
		{
			tmp = (*lst)->next;
			free_maillon(*lst);
			*lst = tmp;
		}
	}
}
