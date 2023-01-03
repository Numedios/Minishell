#include "minishell.h"

/*
*
* renvoie 1 si tout les quote sont fermer
* renvoie 0 sinon
*
*/

int quote_close(char *str)
{
	char	c;

	if (!str)
		return (0);
	while(str && *str)
	{
		if (*str && (*str == '\'' || *str == '\"'))
		{
			c = *str;
			str++;
			while (*str && *str != c)
				str++;
			if (*str != c)
				return (0);
		}
		str++;
	}
	return (1);
}


/*
* inter represente si on va interpreter ou non les caractere speciaux 
* si exemple (''$HOME'' = /cd/ls inter = 1 oui , '$HOME' =  $HOME si inter = -1 non 
*
*/

void	change_quote(char *str)
{
	int	i;
	int single;
	int	doubl;


	i = 0;
	single = 1;
	doubl = 1;
	while(str && str[i] && !check_sep(str[i], "\'\""))
	{
		if (str[i] && str[i] == '\'') // si single cote on change single
		{
			if (doubl == 1) // si on est pas dans un double cote 
				single = single * -1;
			else
				printf("%c",str[i]); // on interprete cette parenthese
		}
		if (str[i] && str[i] == '\"') // si double cote on change doubl
		{
			if (single == 1) // si on est pas un single cote 
				doubl  = doubl * -1;
			else
				printf("%c",str[i]); // on interprete cette parenthese
		}

		i++;
	}
	if (single == -1 && doubl == 1)
		printf("non interpreter\n");
	else
		printf("oui interpreter\n");
}