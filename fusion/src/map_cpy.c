#include "minishell.h"

char *ft_strdup_map(char *str)
{
    char *res;
    int i;

    i = 0;
    res = malloc(sizeof(char) * (ft_strlen(str) + 1));
    while (str[i])
    {
        res[i] = str[i];
        i++;
    }
    res[i] = '\0';
    return (res);
}

int ft_len_char_tab(char **map)
{
    int i;

    i = 0;
    while(map[i] != NULL)
    {
        i++;
    }
    return (i);
}


char **map_copy(char **map)
{
    char **cpy;
    int i;

    i = 0;
    cpy = malloc(sizeof(char *) * (ft_len_char_tab(map) + 1));
    
    while (map[i] != NULL)
    {
        cpy[i] = ft_strdup_map(map[i]);
        i++;
    }
    cpy[i] = 0;
    return (cpy);
}