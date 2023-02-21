/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 17:50:49 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/02/17 17:53:02 by zhamdouc         ###   ########.fr       */
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
	lst = NULL;
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
		tab[i] = NULL;
		i++;
	}
	if (tab)
		free(tab);
	tab = NULL;
}

void	free_maillon(t_maillons *lst)
{
	if (lst)
	{
		if (lst -> args)
		{
			ft_free_tab(lst -> args);
			lst -> args = NULL;
		}	
		if (lst -> command)
		{
			free(lst -> command);
			lst ->command = NULL;
		}	
		if (lst -> output)
		{
			free_inputs_outputs(&lst->output);
			lst ->output = NULL;
		}
		if (lst)
			free(lst);
	}
	lst = NULL;
}

void	free_maillons(t_maillons *lst)
{
	t_maillons	*tmp;

	tmp = lst;
	if (lst)
	{
		while (lst)
		{
			if (lst != NULL)
				tmp = (lst)->next;
			else
				tmp = NULL;
			free_maillon(lst);
			lst = tmp;
		}
	}
}
