/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 18:18:43 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/02/17 18:19:57 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		dprintf(2, "%s\n", tab[i]);
		i++;
	}
}

void	ft_print_split_elem(t_split_elem *list)
{
	while (list != NULL)
	{
		printf(" %s |", list-> arg);
		list = list -> next;
	}
	printf("\n");
}

void	ft_print_input_output(t_input_output *list)
{
	while (list != NULL)
	{
		// printf("file = %s operator = %s ||", list->file_name, list->operator);
		printf("    lst->name = %s\tlst->operator = %s   \n", list->file_name, list->operator);
		list = list -> next;
	}
	printf("\n");
}

void	ft_print_maillon(t_maillons	*maillons)
{
	if (maillons)
	{
		printf("maillons\n{\n");
		if (maillons -> command)
			printf("  maillons -> commande = %s\n", maillons -> command);
		printf("  maillons ->args\n  {\n    ");
		if (maillons -> args)
			ft_print_tab(maillons -> args);
		printf("  }\n");
		printf("  maillons -> outputs\n  {\n");
		if (maillons -> output)
			ft_print_input_output(maillons ->output);
		printf("  }\n}\n\n");
	}
	else
		printf("(null)\n");
}

void	ft_print_maillons(t_maillons	*maillons)
{
	dprintf(2,"***********************************\n");
	if (maillons)
	{
		while (maillons)
		{
			printf("maillons\n{\n");
			if (maillons -> command)
				printf("  maillons -> commande = *%s*\n", maillons -> command);
			printf("  maillons ->args\n  {\n    ");
			if (maillons -> args)
				ft_print_tab(maillons -> args);
			printf("  }\n");
			printf("  maillons -> outputs\n  {\n");
			if (maillons -> output)
				ft_print_input_output(maillons ->output);
			printf("heredoc = %d\n", maillons-> heredoc);
			printf("  }\n}\n\n");
			maillons = maillons -> next;
		}
	}
	else
		printf("(null)\n");
	dprintf(2,"***********************************\n");
}

void	ft_print_garbage(t_garbage	*garbage)
{
	dprintf(2, "char** split_pipe\n");
	if (garbage->split_pipe && garbage->split_pipe[0])
		ft_print_tab(garbage -> split_pipe);
	dprintf(2, "\n");
	dprintf(2, "split_elem\n");
	if (garbage->split_lst)
		ft_print_split_elem(garbage -> split_lst);
	dprintf(2, "\n");
	dprintf(2, "maillons dans garbage\n");
	if (garbage->maillons)
		ft_print_maillons(garbage -> maillons);
	dprintf(2, "\n");
	dprintf(2, "pipes \n");
	if (garbage->pipes && garbage->pipes->pipe[0] && garbage->pipes->pipe[1])
		dprintf(2, "pipe[0] = %d // pipes[1] =%d \n", garbage->pipes->pipe[0], garbage->pipes->pipe[1]);
	dprintf(2, "\n");
}
