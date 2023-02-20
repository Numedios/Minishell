/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelabba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:14:50 by sbelabba          #+#    #+#             */
/*   Updated: 2023/02/20 16:14:52 by sbelabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* --suppressions=readline_leaks.txt */

int	only_white_space(char *line_read)
{
	int	i;

	i = 0;
	while (line_read[i])
	{
		if (line_read[i] != ' ' )
			return (0);
		i++;
	}
	return (1);
}

/* Read a string, and return a pointer to it.  Returns NULL on EOF. */

char	*rl_gets(void)
{
	static char	*line_read;

	line_read = (char *) NULL;
	line_read = readline("Minishell > ");
	if (line_read && *line_read)
	{
		if (only_white_space(line_read) == 0)
			add_history(line_read);
	}
	return (line_read);
}

int	g_exit_code[2];

t_maillons	*loop_create_maillons(char *line, t_garbage *garbage, int i)
{
	t_maillons		*maillons;
	t_maillons		*maillon;
	t_maillons		*prev;

	prev = NULL;
	garbage->split_pipe = ft_split2(line, "|");
	garbage ->maillons = NULL;
	if (!(garbage->split_pipe))
		return (0);
	while (garbage && garbage->split_pipe[i])
	{
		garbage->split_lst = ft_split_list(garbage->split_pipe[i], WHITE_SPACE);
		if (!(garbage->split_lst))
			break ;
		create_split_arg(&garbage->split_lst);
		maillon = create_maillons(&garbage->split_lst, prev);
		add_end_maillons(&garbage->maillons, maillon);
		prev = maillon;
		ft_free_split_arg(&garbage->split_lst);
		i++;
	}
	ft_free_tab(garbage->split_pipe);
	garbage->split_lst = NULL;
	garbage->split_pipe = NULL;
	return (garbage->maillons);
}

void	end_quote_add(t_garbage *g, int *i)
{
	while (g && g->maillons && (g->maillons->args)[(*i)])
	{
		(g->maillons->args)[*i] = del_q(((g->maillons->args)[(*i)]), 0, 0);
		(*i)++;
	}
	if (g && g->maillons && g->maillons->command)
		g->maillons->command = del_q(g->maillons->command, 0, 0);
	while (g && g-> maillons && g->maillons->output)
	{
		g->maillons->output->file_name = del_q(g->maillons->output->file_name,
				0, 0);
		g->maillons->output = g->maillons->output->next;
	}
}

void	end_quote(t_garbage *garbage)
{
	t_maillons		*tmp;
	t_input_output	*tmp2;
	int				i;

	i = 0;
	tmp = NULL;
	tmp2 = NULL;
	if (garbage && garbage-> maillons)
		tmp = garbage->maillons;
	while (garbage && garbage->maillons)
	{
		i = 0;
		if (garbage && garbage-> maillons && garbage->maillons->output)
			tmp2 = garbage->maillons->output;
		else
			tmp2 = NULL;
		end_quote_add(garbage, &i);
		if (tmp2)
			garbage->maillons->output = tmp2;
		garbage->maillons = garbage->maillons->next;
	}
	if (tmp)
		garbage->maillons = tmp;
}

int	main(int argc, char **argv, char **env)
{
	char		*line;
	t_garbage	garbage;
	char		**new_env;

	initialize_garbage(&garbage);
	garbage.new_env = my_env(env);
	while (1)
	{
		g_exit_code[1] = 0;
		setup_signal_handlers();
		line = rl_gets();
		if (line && line[0] == '\0')
			g_exit_code[0] = 0;
		if (line == NULL && g_exit_code[1] != 8)
		{
			s_fd("\nexit11\n", 2);
			free_garbage_env_exit(&garbage, 0);
		}
		if (parse(line) == 0)
		{
			garbage.line = delete_dollar(line, garbage.new_env, 0, 0);
			garbage.line = replace_dollar(line, garbage.new_env, 0, 0);
			loop_create_maillons(garbage.line, &garbage, 0);
			cmd_to_path(garbage.maillons, garbage.new_env);
			find_all_heredoc(garbage.maillons);
			end_quote(&garbage);
			if (g_exit_code[1] != 7)
				pipex(garbage.maillons, &garbage.new_env, &garbage);
			free_garbage(&garbage);
		}
	}
	free_garbage_and_env(&garbage);
	return (1);
}
