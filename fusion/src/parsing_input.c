/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 17:54:57 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/02/17 17:57:59 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*
* creer le fichier si il existe et renvoie 1
* si le open a echouer renvoie -1
*
*/

int	check_output(t_input_output *output)
{
	int	fd;

	if (ft_strcmp(output->operator, ">"))
	{
		fd = open(output->file_name,
				O_WRONLY | O_CREAT | O_TRUNC, 0644, !O_DIRECTORY);
	}
	else if (ft_strcmp(output->operator, ">>"))
	{
		fd = open(output->file_name,
				O_WRONLY | O_CREAT | O_APPEND, 0644, !O_DIRECTORY);
	}
	if (fd == -1)
		return (close(fd), -1);
	return (close(fd), 1);
}

int	check_input(t_input_output *output)
{
	int	fd;

	if (ft_strcmp(output->operator, "<"))
		fd = open(output->file_name, O_RDWR, O_DSYNC, !O_DIRECTORY);
	else if (ft_strcmp(output->operator, "<<"))
	{
		return (1);
	 //    fd = open("here_doc", O_CREAT | O_WRONLY | O_EXCL, 0647); // a changer
	}
	if (fd == -1)
		return (close(fd), -1);
	return (close(fd), 1);
}

int	check_input_output(t_input_output **input_output)
{
	t_input_output	*input;
	t_input_output	*output;
	t_input_output	*first;

	first = *input_output;
	input = NULL;
	output = NULL;
	while (*input_output)
	{
		if (ft_strcmp((*input_output)->operator, ">")
			|| ft_strcmp((*input_output)->operator, ">>"))
		{
			if (output)
				free_input_output_middle(&output, &first);
			output = (*input_output);
			if (check_output(output) == -1)
			{
				printf("%s ne s'est pas crer \n", (*input_output)-> file_name);
				// tout free et exit ou renvoyer -1 et gerer sa apres
				//exit(0);
				*input_output = first;
				return (0);
			}
		}
		else if (ft_strcmp((*input_output)->operator, "<")
			|| ft_strcmp((*input_output)->operator, "<<"))
		{
			if (input)
				free_input_output_middle(&input, &first);
			input = (*input_output);
			if (check_input(input) == -1)
			{
				// tout free et exit ou renvoyer -1 et gerer sa apres
				printf("%s n'existe pas \n", (*input_output)-> file_name);
				free_inputs_outputs(&input -> next);
				input->next = NULL;
				*input_output = first;
				return (0);
			}
		}
		*input_output = (*input_output)->next;
	}
	*input_output = first;
	return (1);
}

int	check_inputs_outputs(t_maillons *maillons)
{
	while (maillons)
	{
		check_input_output(&(maillons)->output);
		maillons = (maillons)->next;
	}
	return (1);
}
