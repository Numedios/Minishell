#include "minishell.h"

int	check_sep2(char c, char *sep)
{
	int	i;

	i = 0;
	while (sep && sep[i])
	{
		if (sep[i] == c)
			return (0);
		i++;
	}
	return (1);
}

int	count_words2(char *str, char *sep)
{
	int	i;
	int	j;

	if (!str)
		return (0);
	i = 0;
	j = 1;
	while (str[i] && !is_inquotes(str, i) && !check_sep2(str[i], sep))
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!is_inquotes(str, i) && !check_sep2(str[i], sep)
			&& check_sep2(str[i + 1], sep))
			j++;
		i++;
	}
	return (j);
}

int	ft_stablen(char *str, int tor, char *sep)
{
	static int	i;
	int			j;

	if (!str)
		return (0);
	if (tor == 0)
		i = 0;
	j = 0;
	while (str[i] && !is_inquotes(str, i) && !check_sep2(str[i], sep))
		i++;
	while (str[i] && (check_sep2(str[i], sep) || is_inquotes(str, i)))
	{
		if (!is_inquotes(str, i) && !check_sep2(str[i], sep))
			j--;
		i++;
		j++;
	}
	return (j);
}