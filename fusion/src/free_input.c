#include "minishell.h"

void	free_input_output_middle(t_input_output **lst, t_input_output **first)
{
	t_input_output	*prev;
	t_input_output	*next;

	prev = (*lst)->prev;
	next = (*lst)->next;
	free_input_output(lst);
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
	if (lst && *lst)
	{
		while (*lst)
		{
			tmp = (*lst)->next;
			free_input_output(lst);
			*lst = tmp;
		}
	}
}

void	free_input_output(t_input_output **lst)
{
	t_input_output	*current;

	if (*lst)
	{
		current = *lst;
		*lst = (*lst)->next;
		if (current->file_name)
		{
			free(current->file_name);
			current->file_name = NULL;
		}
		if (current->operator)
		{
			free(current->operator);
			current->operator = NULL;
		}
		free(current);
		current = NULL;
	}
}
