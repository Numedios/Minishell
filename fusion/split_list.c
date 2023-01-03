#include "minishell.h"

t_split_elem	*ft_split_list(char *str, char *sep)
{
	int             j;
	t_split_elem    *lst;
	t_split_elem	*elem;
	char	*res;
	char	quote;

	j = 0;
	lst = NULL;
	while (str && *str)
	{
		while (*str && !check_sep(*str, sep))
			str++;
		if (*str && check_sep(*str, sep))
		{
			res = create_word_all2(str, sep);
			elem = create_split_elem(res);
			add_end_split_elem(&lst, elem);
		}
		while (str && *str && check_sep(*str, sep))
		{
			if (*str == '\"' || *str == '\'')
			{
				quote = *str;
				str++;
				while (*str != quote)
					str++;
			}
			str++;
		}
	}
	return (lst);
}