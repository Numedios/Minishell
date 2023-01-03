#include "minishell.h"

t_split_elem	*create_split_elem(char	*str)
{
	t_split_elem	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new -> arg = str; // maybe mettre un dump
	new -> next = NULL;
	return (new);
}

t_split_elem	*create_split_elem_dup(char	*str)
{
	t_split_elem	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new -> arg = ft_strdup(str); // maybe mettre un dump
	new -> next = NULL;
	return (new);
}

t_split_elem	*lstlast_split_elem(t_split_elem *lst)
{
	while (lst)
	{
		if (!(lst -> next))
			return (lst);
		lst = lst -> next;
	}
	return (lst);
}

void	add_end_split_elem(t_split_elem	**list, t_split_elem *add)
{
	t_split_elem	*search;

	//ft_print_split_elem(add);
	if (!*list)
	{
		*list = add;
		return ;
	}
	search = lstlast_split_elem(*list);
	search -> next = add;
}

/*void ft_strjoin_list(t_split_elem *list, t_split_elem **add, t_split_elem **first)
{
	t_split_elem *stock;
	//t_split_elem ***stock2;

	printf(" Voila la list \n");
	ft_print_split_elem(list);
	printf(" Voila add \n");
	ft_print_split_elem(*add);

	stock = (list) -> next;
	
	*first = *add;
	free_split_elem(list);
	list = *add;
	while(list)
	{
		if (!list -> next)
			break;
		list = list -> next;
	}
	list -> next = stock;
	*first = *add;
	
	printf(" Voila la list a la fin\n");
	ft_print_split_elem(list);
	printf(" Voila add a la fin\n");
	ft_print_split_elem(*add);
}*/

// 1>2>3 4 5 | 1 2>3>4 5