#include "../minishell.h"

static char	*comparaison(int a, size_t len, char *base, char *found)
{
	size_t	i;
	int		j;

	i = 0;
	j = 0;
	while (i < len && base[i])
	{
		while (base[i] == found[j] && base[i] && i < len)
		{
			if (j == 0)
				a = i;
			i++;
			j++;
			if (found[j] == '\0')
				return (&((char *)base)[a]);
		}
		if (j > 0)
		{
			j = 0;
			i = a;
		}
		i++;
	}
	return (NULL);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*base;
	char	*found;
	size_t	i;
	int		a;

	base = (char *) big;
	found = (char *) little;
	i = 0;
	a = 0;
	if (big == NULL || little == NULL)
		return (NULL);
	if (little[i] == '\0')
		return ((char *)big);
	return (comparaison(a, len, base, found));
}

static char	*sub(char *s_copy, char *s1, size_t len, int start)
{
	size_t	n;

	n = 0;
	while (s_copy[start] && (n < len))
	{
		s1[n] = s_copy[start];
		start++;
		n++;
	}
	s1[n] = '\0';
	return (s1);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	taille_s;
	char			*s1;
	char			*s_copy;

	s_copy = (char *) s;
	taille_s = ft_strlen_const(s);
	if ((start >= taille_s) || len == 0)
	{
		s1 = malloc (1 * sizeof(char));
		if (s1 == NULL)
			return (NULL);
		s1[0] = 0;
		return (s1);
	}
	if ((len + 1) < ((taille_s + 1) - start))
		s1 = malloc ((len + 1) * sizeof(char));
	else
		s1 = malloc (((taille_s + 1) - start) * sizeof(char));
	if (s1 == NULL)
		return (NULL);
	return (sub(s_copy, s1, len, start));
}

void	free_tab(char **tab, int i)
{
	if (tab != NULL)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
		tab = NULL;
	}
}

void	free_all(two_pipe *two_pipe)
{
	int	i;

	i = 0;
	if (two_pipe->the_path != NULL)
	{
		free(two_pipe->the_path);
		two_pipe->the_path = NULL;
	}
	if (two_pipe->path != NULL)
	{
		free(two_pipe->path);
		two_pipe->path = NULL;
	}
	free_tab(two_pipe->cmd1, 0);
	two_pipe->cmd1 = NULL;
	free_tab(two_pipe->cmd2, 0);
	two_pipe->cmd2 = NULL;
	free_tab(two_pipe->cmd_path, 0);
	two_pipe->cmd_path = NULL;
}