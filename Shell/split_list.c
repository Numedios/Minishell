#include "minishell.h"


t_split_elem	**ft_split_list(char *str, char *sep)
{
	int             j;
	t_split_elem    **lst;
	t_split_elem	*elem;
	char	*res;

	j = 0;
	lst = malloc(sizeof(*lst));
	if (!lst)
		return (NULL);
	*lst = NULL;
	while (str && *str)
	{
		while (*str && !check_sep(*str, sep))
			str++;
		if (*str && check_sep(*str, sep))
		{
			res = create_word(str, sep);
			elem =  create_split_elem(res);
			add_end_split_elem(lst, elem);
		}
		while (*str && check_sep(*str, sep))
			str++;
	}
	return (lst);
}