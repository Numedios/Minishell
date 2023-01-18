#include <stdio.h>
#include <stdlib.h>

static int		len_int(long n_copy);
static char		*recusrive_more(char *s, long n, long len);
static char		*recusrive_less(char *s, long n, long len);
char	*ft_itoa(int n)
{
	long	n_copy;
	long	len;
	char	*s;

	n_copy = n;
	len = len_int(n_copy);
	if (n >= 0)
	{
		len = (len + 2);
		s = malloc (len * sizeof(char));
		if (s == NULL)
			return (NULL);
		recusrive_more(s, n_copy, (len - 2));
	}
	if (n < 0)
	{
		len = (len + 3);
		s = malloc (len * sizeof(char));
		if (s == NULL)
			return (NULL);
		recusrive_less(s, n_copy, (len - 2));
	}
	s[len - 1] = '\0';
	return (s);
}

int ft_str_len(char *str)
{
    int i;

    if (!str)
        return(0);
    i = 0;
    while (str[i])
        i++;
    return (i);
}

int main (void)
{
    int i;
    int len;
    char    *tab;


    tab = ft_itoa(001);
    len = ft_str_len(tab);
    printf("%d\n", len);
    printf("%s\n", tab);
    printf("%s\n", tab);
    return (0);
}



static int	len_int(long n_copy)
{
	long	len;

	len = 0;
	if (n_copy < 0)
		n_copy = n_copy * -1;
	while (n_copy > 9)
	{
		n_copy = n_copy / 10;
		len++;
	}
	return (len);
}

static char	*recusrive_more( char *s, long n, long len)
{
	long	a;

	a = 0;
	while (len >= 0)
	{
		if (n > 9)
		{
			a = n % 10;
			n = n / 10;
		}
		if (len > 0)
			s[len] = a + 48;
		if (len == 0)
			s[len] = n + 48;
		len--;
	}
	return (s);
}

static char	*recusrive_less(char *s, long n, long len)
{
	long	a;

	a = 0;
	if (n < 0)
	{
		n = -1 * n;
		s[0] = '-';
	}
	while (len >= 1)
	{
		if (n > 9)
		{
			a = n % 10;
			n = n / 10;
		}
		if (len > 1)
			s[len] = a + 48;
		if (len == 1)
			s[len] = n + 48;
		len--;
	}
	return (s);
}
