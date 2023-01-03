#include "minishell.h"

/* renvoie 1 si il n'y a pas de separateur renvoie 0 sinon */

int check_sep(char c, char *sep)
{
	int i;

	i = 0;
	while (sep && sep[i])
	{
		if (sep[i] == c)
			return (0);
		i++;
	}
	return (1);
}

int count_words(char *str, char *sep)
{
	int i;
	int word;

	i = 0;
	word = 0;
	while (str && str[i])
	{
		while (str[i] && !check_sep(str[i], sep))
			i++;
		if (str[i] && check_sep(str[i], sep))
			word++;
		while (str[i] && check_sep(str[i], sep))
			i++;
	}
	return (word);
}

char	*create_word_quote(char *str, char *sep)
{
	char	*word;
	char	quote;
	int		i;

	i = 1;
	quote = *str;
	while (str && str[i] && str[i] != quote )
		i++;
	while (str && str[i] && check_sep(str[i], sep))
		i++;
	word = malloc(sizeof(char) * (i + 2));
	if (!word)
		return (NULL);
	i = 0;
	while (i == 0 || (str && str[i] && str[i] != quote))
	{
		word[i] = str[i];
		i++;
	}
	word[i] = quote;
	i++;
	while (str && str[i] && check_sep(str[i], sep))
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return(word);
}

char	*create_word_all(char *str, char *sep)
{
	char *word;

	if (*str == '\"' || *str == '\'')
		word = create_word_quote(str, sep);
	else
		word = create_word(str,sep);
	return (word);
}

char	*create_word(char *str, char *sep)
{
	char	*word;
	int		i;

	i = 0;
	while(str && str[i] && check_sep(str[i], sep))
		i++;
	word = malloc (sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (str && str[i] && check_sep(str[i], sep))
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return(word);
}

char **ft_split(char *str, char *sep)
{
	int i;
	int j;
	char **res;

	i = 0;
	j = 0;
	res = malloc(sizeof(char *) * (count_words(str, sep) + 1));
	if (!res)
		return (NULL);
	while (str && *str)
	{
		while (*str && !check_sep(*str, sep))
			str++;
		if (*str && check_sep(*str, sep))
		{
			res[i] = create_word(str, sep);
			i++;
		}
		while (*str && check_sep(*str, sep))
			str++;
	}
	res[i] = 0;
	return (res);
}