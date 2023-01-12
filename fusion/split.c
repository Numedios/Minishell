#include "minishell.h"

/* 
* renvoie 1 si c n'est pas un separateur renvoie 0 sinon 
* renvoie 0 sinon
* 
*/

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

/*
*
* compte str classique dans un mot (split classique)
*
*/

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

/*
*
* crer et renvoie les mots qui ont en premiere occurence une quote
* exemple "abcde ererre "
* exemple " bonjours "aurevoir
*/

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

/*
* crer les mot sans quote (splut classique)
*
*
*/

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

/*
* renvoie la taille de str par rapport a des mot contenant des cote 
* exemple 12"34" renvera 6
* exemple 12"34"78 renvera 8
*
*/

int	count_word_and_quote(char *str, char *sep)
{
	int		i;
	char	quote;

	i = 0;
	while (str && str[i])
	{
		while (str && str[i] && (str[i] != '\"' && str[i] != '\''))
			i++;
		quote = str[i];
		i++;
		while (str && str[i] && (str[i] != quote))
			i++;
		if (str && str[i] &&  (str[i] == '\"' && str[i] == '\''))
			i++;
		if (str && str[i] && !(check_sep(str[i], sep)))
			break ;
	}
	return (i);
}


/*
* creer les mot qui contient pas en premiere occurence et  le renvoie
*  exemple abc"123 456"zde sera traiter ici
*  exemple abc"123 456" sera traiter ici
*/

char	*create_word_and_quote(char *str, char *sep)
{
	char	*word;
	char	quote;
	int		i;
	int len;

	len = count_word_and_quote(str, sep);
	word = malloc(sizeof(char) * (len + 1));
	i = 0;
	while (str && str[i])
	{
		while (str && str[i] && (str[i] != '\"' && str[i] != '\''))
		{
			word[i] = str[i];
			i++;
		}
		quote = str[i];
		word[i] = str[i];
		i++;
		while (str && str[i] && (str[i] != quote))
		{
			word[i] = str[i];
			i++;
		}
		if (str && str[i] &&  (str[i] == '\"' && str[i] == '\''))
		{
			word[i] = str[i];
			i++;
		}
		if (str && str[i] && !(check_sep(str[i], sep)))
			break ;
	}
	word[i] = '\0';
	return (word);
}

int	count_word_and_quote2(char *str, char *sep)
{
	int		i;
	char	quote;

	i = 0;
	while (str && str[i])
	{
		while (str && str[i] && (str[i] != '\"' && str[i] != '\''))
		{
			if (str && str[i] && !(check_sep(str[i], sep)))
				break ;
			//printf("1 str[%d] = %c\n", i, str[i]);
			i++;
		}
		if (str && str[i] && !(check_sep(str[i], sep)))
		{
			//printf("stop str[%d] = %c\n", i, str[i]);
			break ;
		}
		quote = str[i];
		i++;
		while (str && str[i] && (str[i] != quote))
		{
			//printf("2 str[%d] = %c\n", i, str[i]);
			i++;
		}
		if (str && str[i] &&  (str[i] == '\"' || str[i] == '\''))
		{
			//printf("3 str[%d] = %c\n", i, str[i]);
			i++;
		}
		if (str && str[i] && !(check_sep(str[i], sep)))
		{
			//printf("stop str[%d] = %c\n", i, str[i]);
			break ;
		}
	}
	return (i);
}
 // 1">"4>5
char	*create_word_and_quote2(char *str, char *sep)
{
	char	*word;
	char	quote;
	int		i;
	int len;

	len = count_word_and_quote2(str, sep);
	//printf("len = %d\n", len);
	word = malloc(sizeof(char) * (len + 1));
	i = 0;
	while (str && str[i])
	{
		while (str && str[i] && (str[i] != '\"' && str[i] != '\''))
		{
			if (str && str[i] && !(check_sep(str[i], sep)))
				break ;
			word[i] = str[i];
			i++;
		}
		if (str && str[i] && !(check_sep(str[i], sep)))
			break ;
		quote = str[i];
		word[i] = str[i];
		i++;
		while (str && str[i] && (str[i] != quote))
		{
			word[i] = str[i];
			i++;
		}
		if (str && str[i] &&  (str[i] == '\"' || str[i] == '\''))
		{
			word[i] = str[i];
			i++;
		}
		if (str && str[i] && !(check_sep(str[i], sep)))
			break ;
	}
	word[i] = '\0';
	return (word);
}

/*
* 	while (str && str[i] && (str[i] != '\"' && str[i] != '\''))
	{
		word[i] = str[i];
		i++;
	}
	word[i] = str[i];
	i++;
	while (str && str[i] && (str[i] != quote))
	{
		word[i] = str[i];
		i++;
	}
	word[i] = str[i];
	i++;
	while (str && str[i] && check_sep(str[i], sep))
	{
		word[i] = str[i];
		i++;
	}
*
*/



/*
*  renvoie 0 si le mot contient des quote    bon"jour" return 0
* renvoie 1 sinon   asbas return 1
*
*/

int	check_word_quote(char *str, char *sep)
{
	while (str && *str && check_sep(*str, sep))
	{
		if (*str == '\"' || *str == '\'')
			return(0);
		str++;
	}
	return (1);
}


/*
* appele la fonction adequate pour decouper en fonction de la presence de quote ou non
* 
*
*/

char	*create_word_all2(char *str, char *sep)
{
	char *word;

	if (!check_word_quote(str, sep))
	{
		//printf("2 create word and quote \n");
		word = create_word_and_quote2(str, sep);
	}
	else if (*str == '\"' || *str == '\'')
	{
		//printf("1 create_word_quote\n");
		word = create_word_quote(str, sep);
	}
	else
	{
		//printf("1 create word\n");
		word = create_word(str,sep);
	}
	//printf("word = %s\n", word);
	return (word);
}

char	*create_word_all(char *str, char *sep)
{
	char *word;

	if (*str == '\"' || *str == '\'')
		word = create_word_quote(str, sep);
	else if (!check_word_quote(str, sep))
		word = create_word_and_quote(str, sep);
	else
		word = create_word(str,sep);
	return (word);
}

char **ft_split(char *str, char *sep)
{
	int i;
	int j;
	char **res;
	char quote;

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
			res[i] = create_word_all2(str, sep);
			i++;
		}
		while (*str && check_sep(*str, sep))
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
	res[i] = 0;
	return (res);
}