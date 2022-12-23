#include "minishell.h"

/*
*	renvoie 1 si str comporte un separateur chercher
*	renvoie 0 si vide ou si elle n'en comporte pas
*/

int	chek_sep_str(char *str, char *sep)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while(str[i])
	{
		if (!check_sep(str[i], sep))
			return (1);
		i++;
	}
	return (0);
}

void	create_word_sep(t_split_elem **lst, char *str, int len)
{
	char *res;
	int	i;

	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return	;
	i = 0;
	while (i < len)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	add_end_split_elem(lst , create_split_elem(res));
}

/*
* 
*
*
*/

t_split_elem	**split_redirection(char *str, char *sep)
{
	t_split_elem **add;
	int	i;

	add = malloc(sizeof(*add));
	if (!add)
		return (NULL);
	*add = NULL;
	i = 0;
	while(str && *str)
	{
		if (*str == '<' || *str == '>')
		{
			if (*str == str[1])
				{
					create_word_sep(add, str, 2);
					str++;
				}
			else	
				create_word_sep(add, str, 1);
			str++;
		}
		if (*str && check_sep(*str, "<>"))
			add_end_split_elem(add, create_split_elem(create_word(str, sep)));
		while (*str && check_sep(*str, "<>"))
			str++;
	}
	return (add);
}

/*
*	ajoute add dans lst
*	
*
*
*/

void	add_el(t_split_elem *lst, t_split_elem **start, t_split_elem *prev)
{
	t_split_elem	*tmp;
	t_split_elem     *del;
	t_split_elem	**add;
	
	add = split_redirection((lst) -> arg, "<>");
	del = NULL;
	if (lst == *start)
	{
		del = *start;
		*start = *add;
	}
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

void	create_split_arg(t_split_elem **lst) // rename avec create
{
	t_split_elem	**add;
	t_split_elem	*stock;
	t_split_elem	*prev;

	stock = *lst;
	prev = *lst;
	while (*lst)
	{
		if (chek_sep_str((*lst)->arg, "<>") && !ft_strcmp((*lst)->arg, ">") && !ft_strcmp((*lst)->arg, ">>") &&  !ft_strcmp((*lst)->arg, "<") && !ft_strcmp((*lst)->arg, "<<"))
		{
			add_el(*lst, &stock, prev);
			*lst = stock;
		}
		prev = *lst;
		*lst = (*lst) -> next;
	}
	*lst = stock;
}

// 1>2>3 4 5 | 1 2>3 4 5

/*
			printf("*lst au debut \n");
			ft_print_split_elem(*lst);
			printf("*stock au debut \n");
			ft_print_split_elem(stock);
			printf("prev au debut \n");
			ft_print_split_elem(prev);
			add_el(*lst, &stock, prev);
			printf("*lst a la fin \n");
			ft_print_split_elem(*lst);
			printf("*stock a la fin \n");
			ft_print_split_elem(stock);
			printf("prev a la fin \n");
			ft_print_split_elem(prev);
		*/