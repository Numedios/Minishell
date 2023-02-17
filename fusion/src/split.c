#include "minishell.h"

/*
* renvoie 1 si c n'est pas un separateur renvoie 0 sinon
* renvoie 0 sinon
*
*/

int	check_sep(char c, char *sep)
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