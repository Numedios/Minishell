/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 15:30:15 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/02/17 15:35:01 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	after_redirection(char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		if (line[i] == '>')
		{
			i++;
			if (line[i] == '>')
				i++;
			while (line[i] == ' ')
				i++;
			if (line[i] == '\0')
			{
				ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", 2);
				g_exit_code[0] = 2;
				return (g_exit_code[0]);
			}
		}
		i++;
	}
	return (0);
}

int	check_parenthesis(char *line)//(")"0 ;;; (")" 0) -> est ce qu'il traiter les "()" comment les guillemets
{
	int	i;
	int	count_1;
	int	count_2;

	i = 0;
	count_1 = 0;
	count_2 = 0;
	while (line && line[i])
	{
		i = skip_quote(line, i);
		if (i == -1 || !line || line[i] == '\0')
			return (0);
		if (line[i] == '(')
			count_1++;
		if (line[i] == ')')
			count_2++;
		if (count_2 > count_1)
			return (1);
		i++;
	}
	if (count_1 != count_2)
		return (1);
	return (0);
}

int	check_1(char *line)
{
	int	i;
	int	j;

	i = 0;
	while (line && line[i])
	{
		i = skip_quote(line, i);
		if (i == -1 || !line || line[i] == '\0')
			return (0);
		if (check_error_2_space(line, '(', ')', i) == 2)
		{
			ft_putstr_fd("bash: syntax error near unexpected token `)'\n", 2);
			return (1);
		}
		if (check_error_3_space(line, '<', ">>", i) == 2)
		{
			ft_putstr_fd("bash: syntax error near unexpected token `>>'\n", 2);
			return (1);
		}
		if (line[i] == '<' && line[i + 1] == '>')
		{
			ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", 2);
			return (1);
		}
		if (check_error_2_space(line, '<', '>', i) == 2)
		{
			ft_putstr_fd("bash: syntax error near unexpected token `>'\n", 2);
			return (1);
		}
		if (check_error_3_space(line, '>', "<<", i) == 2)
		{
			ft_putstr_fd("bash: syntax error near unexpected token `<<'\n", 2);
			return (1);
		}
		if (check_error_2_space(line, '>', '<', i) == 2)
		{
			ft_putstr_fd("bash: syntax error near unexpected token `<'\n", 2);
			return (1);
		}
		if (line[i] == '>' && line[i + 1] == '>' && line[i + 2] == '>')
		{
			ft_putstr_fd("bash: syntax error near unexpected token `>>'\n", 2);
			return (1);
		}
		if (line[i] == '<' && line[i + 1] == '<' && line[i + 2] == '<')
		{
			ft_putstr_fd("bash: syntax error near unexpected token `>>''\n", 2);
			return (1);
		}
		if (line[i] == '<' && line[i + 1] == '>' && line[i + 2] == '>')
		{
			ft_putstr_fd("bash: syntax error near unexpected token `>'\n", 2);
			return (1);
		}
		if (line[i] == '|' && line[i + 1] == '|' && line[i + 2] == '|')
		{
			ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 2);
			return (1);
		}
		if (check_error_space(line, '|', i) == 2)
		{
			ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 2);
			return (1);
		}
		if (line[i] == '&')
		{
			ft_putstr_fd("bash: syntax error near unexpected token `&'\n", 2);
			return (1);
		}
		if (line[i] == '\\')
		{
			ft_putstr_fd("bash: syntax error near unexpected token `\'\n", 2);
			return (1);
		}
		if (line[i] == ';')
		{
			ft_putstr_fd("bash: syntax error near unexpected token `;'\n", 2);
			return (1);
		}
		while (line[i] == '"' && line[i + 1] == '"' && line[i+ 2] == '"')
			i++;
		while (line[i] == '\'' && line[i + 1] == '\'' && line[i+ 2] == '\'')
			i++;
		i++;
	}
	return (0);
}