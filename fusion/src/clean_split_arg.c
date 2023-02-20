/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_split_arg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 19:36:21 by zakariyaham       #+#    #+#             */
/*   Updated: 2023/02/17 17:36:44 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// " a <b> c">d

void	add_el_loop(t_split_elem	**d, t_split_elem ***s, t_split_elem ***a)
{
	*d = **s;
	**s = **a;
}

/*
*	ajoute add dans lst
*/

void	add_el(t_split_elem *lst, t_split_elem **start, t_split_elem *prev)
{
	t_split_elem	*tmp;
	t_split_elem	*del;
	t_split_elem	**add;

	add = split_redirection((lst)->arg, "<>");
	if (!add)
		return ;
	del = NULL;
	if (lst && *start && *add && lst == *start)
		add_el_loop(&del, &start, &add);
	else
	{
		del = prev->next;
		prev->next = *add;
	}
	tmp = *add;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp && lst && lst->next)
		tmp->next = lst->next;
	lst = tmp;
	if (del)
		free_split_elem(del);
	if (*add)
		free(add);
}

/*
* separe les redirection colle
* transforme les >>out2 en >> out2
*
*
*/
// rename avec create
void	create_split_arg(t_split_elem **lst)
{
	t_split_elem	**add;
	t_split_elem	*stock;
	t_split_elem	*prev;

	stock = *lst;
	prev = *lst;
	while (*lst)
	{
		if (chek_sep_str((*lst)->arg, "<>") && !ft_strcmp((*lst)->arg, ">")
			&& !ft_strcmp((*lst)->arg, ">>") && !ft_strcmp((*lst)->arg, "<")
			&& !ft_strcmp((*lst)->arg, "<<"))
		{
			add_el(*lst, &stock, prev);
			*lst = stock;
		}
		prev = *lst;
		*lst = (*lst)->next;
	}
	*lst = stock;
}

// 12>30\"ab<cd\"abbb>e>f
// 1>2>3 4 5 | 1 2>3 4 5