/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing_input.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelabba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:44:19 by sbelabba          #+#    #+#             */
/*   Updated: 2023/02/20 17:44:21 by sbelabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (check_input_output_input(input_output) == -1)
		return (-1);
	if (check_input_output_output(input_output) == -1)	
		return (-1);
	return (1);
}
