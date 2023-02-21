/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars_interrogation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:13:39 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/02/20 13:43:53 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

extern int	g_exit_code[2];

void	new_in_old(for_dollar *var, t_index *index, char **new_env, int *skip)
{
	var->pos_new_env = str_len_env(new_env[index->j]);
	while (new_env[index->j][var->pos_new_env] == '='
	|| new_env[index->j][var->pos_new_env] == '+')
		var->pos_new_env++;
	while (var->i < (var->len_value - 1))
	{
		var->new_tab[var->pos] = new_env[index->j][var->pos_new_env];
		var->i++;
		var->pos++;
		var->pos_new_env++;
	}
	var->pos_tab = var->pos_tab + (*skip);
}

void	new_in_old_interrogation(for_dollar *var)
{
	var->pos_tab = var->pos_tab + 2;
	while (var->value[var->i])
	{
		var->new_tab[var->pos] = var->value[var->i];
		var->pos++;
		var->i++;
	}
}

char	*interrogation(char *tab, int skip, t_index index)
{
	for_dollar	var;

	var.pos = 0;
	var.pos_tab = 0;
	var.value = ft_itoa(g_exit_code[0]);
	var.len_tab = ft_strlen(tab);
	var.new_len = var.len_tab - skip;
	var.len_value = ft_strlen(var.value);
	var.new_tab = malloc (sizeof(char) * (var.new_len + var.len_value));
	while (var.pos < (index.a - 1))
	{
		var.new_tab[var.pos] = tab[var.pos];
		var.pos++;
		var.pos_tab++;
	}
	var.i = 0;
	new_in_old_interrogation(&var);
	while (tab && tab[var.pos_tab])
		var.new_tab[(var.pos)++] = tab[(var.pos_tab)++];
	var.new_tab[var.pos] = '\0';
	free(var.value);
	free(tab);
	tab = NULL;
	return (var.new_tab);
}

char	*do_replace(char *tab, char **new_env, int skip, t_index index)
{
	for_dollar	var;

	var.pos = 0;
	var.pos_tab = 0;
	var.len_tab = ft_strlen(tab);
	var.new_len = var.len_tab - skip;
	var.len_value = ft_strlen(&new_env[index.j][str_len_env(new_env[index.j])]);
	var.new_tab = malloc (sizeof(char) * (var.new_len + var.len_value));
	while (var.pos < (index.a - 1))
	{
		var.new_tab[var.pos] = tab[var.pos];
		var.pos++;
		var.pos_tab++;
	}
	var.i = 0;
	new_in_old(&var, &index, new_env, &skip);
	while (tab && tab[var.pos_tab])
	{
		var.new_tab[var.pos] = tab[var.pos_tab];
		var.pos++;
		var.pos_tab++;
	}
	var.new_tab[var.pos] = '\0';
	return (free(tab), var.new_tab);
}
