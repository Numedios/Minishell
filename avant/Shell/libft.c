#include "minishell.h"

int ft_strlen(char *str)
{
    int i;

    if (!str)
        return(0);
    i = 0;
    while (str[i])
        i++;
    return (i);
}

/* compare renvoie  1 si str == str2 renvoie 0 sinon*/

int ft_strcmp(char *str, char *str2)
{
    if (!str || !str2)
    {
        if (!str && !str2)
            return (1);
        return (0);
    }
    while (*str || *str2)
    {
        if (*str != *str2)
            return (0);
        str++;
        str2++;
    }
    return (1);
}

char    *ft_strdup(char *str)
{
    char    *res;
    int     i;

    i = 0;
    res = malloc(sizeof(char) * (ft_strlen(str) + 1));
    if (!res)
        return (NULL);
    while (str && str[i])
    {
        res[i] = str[i];
        i++;
    }
    res[i] = '\0';
    return (res);
}