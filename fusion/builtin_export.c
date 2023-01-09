#include "minishell.h"

//possibilite de devoir faire un parsing pour ne pas accepter les option, et checker toutes les erreurs possible pour chaque builtin
//new_env = do_export("FOO=bar", new_env);
//gerer le cas "+="
//que faire si on utilise export sans rien derriere (imprimer env)

int str_len_env(char *str)
{
    int i;

    i = 0;
    while (str && str[i])
    {
        if(str[i] == '+' || str[i] == '=')
            return (i);
        i++;
    }
    return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	c_copy;

	if (s == NULL)
		return (NULL);
	c_copy = (unsigned char) c;
	i = 0;
	if (c_copy == 0)
		return ((char *)&s[ft_strlen((char *)s)]);
	while (s[i])
	{
		if (s[i] != c_copy)
			i++;
		else
			return ((char *)&s[i]);
	}
	return (NULL);
}

int check_if_tab_exist (char *tab, char **env)
{
    int len_tab;
    int len_env;
    int i;

    len_tab = ft_strlen(tab);
    i = 0;
    while (env[i])
    {
        len_env = ft_strlen(env[i]);
        if (len_tab != len_env || ft_strncmp(env[i], tab, len_tab) != 0)
            i++;
        else
            return(1);
    }
    return (0);

}

int	ft_isdigit(int c)
{
	if (47 < c && c < 58)
		return (2);
	else
		return (0);
}

int parse_value(char *tab, int i)//return 1 si tout se passe bien autre en cas de probleme
{
    int a;

    a = 0;
    if (tab[i] == '+')
    {
        a = 3;
        i = i + 2;
    }
    else 
        i++;
    if (tab && (tab[i] == '\0' || tab[i] == ' ' || tab[i] == '\t' || tab[i] == '\n' || tab[i] == '\v' || tab[i] == '\f' || tab[i] == '\r'))
    {
        if(a == 3)
            return (5);
        else
            return (4);
    }
    while (tab && tab[i])
    {
        i = skip_quote(tab, i);
        if (i == -1)
            return (1);
        i++;
    }
    // if (!tab)
    //     return (4);
    return (a);
}

int parse_export(char *tab)//ne pas commencer par un nombre pas de caractere speciale, pas de "=="
{
    int i;
    int a;
//return 2 si il y a rien et donc imprimer env,  1 pour erreur, 0 pour remplacer et 3 pour ajouter a c qu'il existe deja, return (4) si apres '=' il a un espace, 5 si il ya '+=' et apres un ' '
    i = 0;
    a = 1;
    while (tab && tab[i] == ' ')
        i++;
    if (!tab)
        return (2);
    if (ft_isdigit(tab[i]) == 2)
        return (1);
    while (tab && tab[i])
    {
        if (tab[i] == '+' && tab[i + 1] != '=')
            return (1);
        if (tab[i] == '+' && tab[i + 1] == '=' && i == 0)
            return (1);
        if ((tab[i] == '+' && tab[i + 1] == '=') ||tab[i] == '=')//ou appeler une fonction qui parse apres le '='
        {
            a = parse_value(tab, i);
            break;
        }
        if (tab[i] == ' ' || tab[i] == '\t' || tab[i] == '\n' || tab[i] == '\v' || tab[i] == '\f' || tab[i] == '\r')
            return (1);
        if (tab[i] == '-' || tab[i] == '!' || tab[i] == '@' || tab[i] == '#' || tab[i] == '$' || tab[i] == '%' || tab[i] == '^' || tab[i] == '&' || tab[i] == '*' || tab[i] == '(' || tab[i] == ')' || tab[i] == '{' || tab[i] == '}' || tab[i] == '[' || tab[i] == ']' || tab[i] == '|' || tab[i] == ';' || tab[i] == ':' || tab[i] == '<' || tab[i] == '>' || tab[i] == '?' || tab[i] == '/'|| tab[i] == '~' || tab[i] == '\\')
        {
            return (1);
        }
        i++;
    }
    return (a);
    
}



int what_to_do(char *tab, char **env)//il faut retourner la bonne ligne et faire un if tel que
{
    int len_tab;
    int len_env;
    int i;
    int j;

    j = 0;
    i = 0;
    len_tab = str_len_env(tab);
    while (env && env[j])
    {
        len_env = str_len_env(env[j]);
        while(tab[i] == env[j][i])
        {
            if (env[j][i] == '=' || env[j][i] == '+')
                break ;
            i++;
        }
        if (i == len_env && len_env == len_tab && (tab[i] == '=' || tab[i] == '+'))
            return (j);
        j++;
        i = 0;
    }
    return (-1);
}

char **replace_value(int j, int a, char *tab, char **env)
{
    int i;

    i = 0;
    if (a == 0)
    {
        free(env[j]);
        env[j] = ft_strdup(tab);
        return (env);
    }
    if (a == 3)
    {
        while (tab && tab[i] != '=')
            i++;
        i++;
        env[j] = ft_strjoin(env[j], &tab[i]);
        return (env);
    }
    if (a == 4)//a verifier
    {
        free(env[j]);
        env[j] = ft_strdup(tab);//ca depend comment je recois tab
        return (env);
    }
    else 
        return (env);
}

char **new_value (int i, int a, char *tab, char **env)
{
   int j;

    j = 0;
    if (a == 0)
    {
        free(env[i]);
        env[i] = ft_strdup(tab);
        return (env);
    }
    if (a == 3)
    {
        while (tab && tab[j] != '=')
            j++;
        j++;
        env[i] = ft_strjoin(env[i], &tab[j]);
        return (env);
    }
    if (a == 4)//a verifier
    {
        free(env[i]);
        env[i] = ft_strdup(tab);//ca depend comment je recois tab
        return (env);
    }
    else 
        return (env);
}

char **do_export(char *tab, char **env_copy)//checker si la variable existe deja dans env, si oui remplacer par la nouvelle valeur
{
    int i;
    int a;
    int j;
    char **new_env;
    
    i = 0;
    a = 0; 
    if (ft_strchr(tab, '=') == NULL)//pas d'espace avant le "="
    {
        printf("export: `%s': not a valid identifier\n", tab);
        return (env_copy);
    }
    a = parse_export(tab);
    if (a == 1)
    {
        printf("export: `%s': not a valid identifier\n", tab);
        return (env_copy);
    }
    if (a == 2)
    {
        do_env(env_copy);
        return (env_copy);
    }
    if (check_if_tab_exist(tab, env_copy) == 1)
    {
        printf("export: '%s' : already defined\n", tab);
        return (env_copy);
    }
    //if name exist replace value
    j = what_to_do(tab, env_copy);
    if (j != -1)//on a trouve la ligne dans env
    {
        env_copy = replace_value(j, a, tab, env_copy);
        return (env_copy);
    }
    else
    {
        while (env_copy[i])
            i++;
        new_env = malloc ((i + 2) * sizeof(char*));//il faut ajouter une ligne de plus pour la nouvelle variable
        i = 0;
        while (env_copy[i])
        {
            new_env[i] = ft_strdup_const(env_copy[i]);
            free(env_copy[i]);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
            i++;
        }
        free(env_copy);
        //pour la nouvelle ligne faire un cas pour chaque a
        new_env = new_value(i, a, tab, new_env);
        //new_env[i] = ft_strdup_const(tab);
        new_env[i + 1] = NULL;
        return (new_env);
    }
}
