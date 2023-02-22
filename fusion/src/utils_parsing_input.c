/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing_input.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:44:19 by sbelabba          #+#    #+#             */
/*   Updated: 2023/02/22 17:34:13 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code[2];

static int	condition(t_input_output *output, \
	t_input_output **input_output, t_input_output *first)
{
	if (check_output(output) == -1)
	{
		*input_output = first;
		return (0);
	}
	return (1);
}

static int	condition_2(t_input_output *input, \
	t_input_output **input_output, t_input_output *first)
{
	if (check_input(input) == -1)
	{
		*input_output = first;
		return (0);
	}
	return (1);
}

int	check_input_output2(t_input_output **input_output, \
	t_input_output *input, t_input_output *output, t_input_output *first)
{
	while (*input_output)
	{
		if (ft_strcmp((*input_output)->operator, ">")
			|| ft_strcmp((*input_output)->operator, ">>"))
		{
			if (output)
				free_input_output_middle(&output, &first);
			output = (*input_output);
			if (condition(output, input_output, first) == 0)
				return (-1);
		}
		else if (ft_strcmp((*input_output)->operator, "<")
			|| ft_strcmp((*input_output)->operator, "<<"))
		{
			if (input)
				free_input_output_middle(&input, &first);
			input = (*input_output);
			if (condition_2(input, input_output, first) == 0)
				return (-1);
		}
		*input_output = (*input_output)->next;
	}
	*input_output = first;
	return (1);
}

/*NE SERT PLUS A RIEN*/
/*

int	return_output_check(t_input_output *input_output)
{
	return ((ft_strcmp((input_output)->operator, ">")
			|| ft_strcmp((input_output)->operator, ">>")));
}

int	return_input_check(t_input_output *input_output)
{
	return (ft_strcmp((input_output)->operator, "<")
		|| ft_strcmp((input_output)->operator, "<<"));
}

int	check_input_output_output(t_input_output *input_output)
{
	t_input_output	*output;
	t_input_output	*first;

	first = input_output;
	output = NULL;
	while (input_output)
	{
		if (return_output_check(input_output))
		{
			if (output)
				free_input_output_middle(&output, &first);
			output = (input_output);
			if (check_output(output) == -1)
			{
				input_output = first;
				return (-1);
			}
		}
		input_output = (input_output)->next;
	}
	input_output = first;
	return (1);
}

int	check_input_output_input(t_input_output *input_output)
{
	t_input_output	*first;
	t_input_output	*input;

	first = input_output;
	input = NULL;
	while (input_output)
	{
		if (return_input_check(input_output))
		{
			if (input)
				free_input_output_middle(&input, &first);
			input = (input_output);
			if (check_input(input) == -1)
			{
				input_output = first;
				return (-1);
			}
		}
		input_output = (input_output)->next;
	}
	input_output = first;
	return (1);
}

int	check_input_output(t_input_output *input_output)
{
	dprintf(2,"check_input_output\n");
	if (check_input_output_input(input_output) == -1)
	{
		dprintf(2, "je suis check input\n");
		ft_print_input_output(input_output);
		return (-1);
	}
	if (check_input_output_output(input_output) == -1)
	{
		dprintf(2, "je suis check output\n");
		ft_print_input_output(input_output);
		return (-1);
	}
	dprintf(2, "je suis check\n");
	//ft_print_input_output(input_output);
	return (1);
}


*/