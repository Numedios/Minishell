#include"minishell.h"
//si il y a juste un dollar ecrire dolalr
//test a faire : echo $'hola'       echo $"hola"    echo $      echo $hol (hol n'existe pas)        echo $$SYSTEMD_EXEC_PID
//$"HOME" doit devenir HOME
char *do_replace(char *tab, char **new_env, int skip, t_index index)
{
    int len_tab;
    int len_value;
    int new_len;
    char *new_tab;
    int i;
    int pos;
    int pos_new_env;
    int pos_tab;

    pos = 0;
    pos_tab = 0;
    len_tab = ft_strlen(tab);
    new_len = len_tab - skip;
    len_value = ft_strlen(&new_env[index.j][str_len_env(new_env[index.j])]);
    new_tab = malloc (sizeof(char) * (new_len + len_value));
    while (pos < (index.a - 1))
    {
        new_tab[pos] = tab[pos];
        pos++;
        pos_tab++;
    }
    i = 0;
    pos_new_env = str_len_env(new_env[index.j]);
    while(new_env[index.j][pos_new_env] == '=' || new_env[index.j][pos_new_env] == '+')
        pos_new_env++;
    while (i < (len_value - 1))
    {
        new_tab[pos] = new_env[index.j][pos_new_env];
        i++;
        pos++;
        pos_new_env++;
    }
    pos_tab = pos_tab + skip;
    while (tab && tab[pos_tab])
    {
        new_tab[pos] = tab[pos_tab];
        pos++;
        pos_tab++;
    }
    new_tab[pos] = '\0';
    // free(tab);
    return (new_tab);
}

int research (int skip, int a, char *tab, char **new_env)// -1 veut dire qu'on a trouve
{
    int len_env;
    int i;

    i = 0;
    while (new_env[i])
    {
        len_env = str_len_env(new_env[i]);
        if ((skip - 1) != len_env || ft_strncmp(new_env[i], &tab[a], (skip - 1)) != 0)
            i++;
        else
            return(i);
    }
    return (-1);
}

char *found_it(char *tab, char **new_env, t_index *index, int *skip)
{
    // t_index index;
    int i;


    // index.a = i;
    i = index->a;
    while (tab[i])
    {
        if (tab[i] == '"' || tab[i] == ' ' || tab[i] == '-' || tab[i] == '!' || tab[i] == '@' || tab[i] == '#' || tab[i] == '$' || tab[i] == '%' || tab[i] == '^' || tab[i] == '&' || tab[i] == '*' || tab[i] == '(' || tab[i] == ')' || tab[i] == '{' || tab[i] == '}' || tab[i] == '[' || tab[i] == ']' || tab[i] == '|' || tab[i] == ';' || tab[i] == ':' || tab[i] == '<' || tab[i] == '>' || tab[i] == '?' || tab[i] == '/'|| tab[i] == '~' || tab[i] == '\\')
        {
            index->j = research(*skip, index->a, tab, new_env);
            if (index->j != -1)
            {
                tab = do_replace(tab, new_env, *skip, (*index));
            }
            return (tab);//verifier le cas ou le dollars n'est pas retrouve il faut faire avanceer i et continuer de chercher si il y a un autre dollar dans les guillemet par exemple
        }
        (*skip)++;
        i++;
    }
    index->j = research(*skip, index->a, tab, new_env);
    if (index->j != -1)
    {
        tab = do_replace(tab, new_env, *skip, (*index));
    }
    return (tab);
}
int replace_dollar(char *tab, char **new_env)//peu etre possible de pas renvoyer un char mais il faut dans ce cas envoyer l'adresse de tab
{
    int i;
    int skip;
    // int exist;
    t_index index;

    i = 0;
    // exist = 0;
    skip = 0;
    while (tab && tab[i])
    {
        if (tab[i] == '"')
        {
            i++;
            while (tab[i] && tab[i] != '"' && tab[i] != '\'')
            {
                while (tab[i] == '$' && tab[i + 1] == '$')
                    i++;
                while (tab[i] == '$')
                {
                    skip++;
                    index.a = i + 1;
                    tab = found_it(tab, new_env, &index, &skip);
                    // i = skip + i;
                    skip = 0;
                }
                i++;
            }
        }
        if (tab[i] && tab[i] == '\'')
        {
            i++;
            while (tab[i] && tab[i] != '\'')
                i++;
        }
        while (tab[i] && tab[i] == '$' && tab[i + 1] == '$')
                    i++;
        while (tab[i] && tab[i] == '$')
        {
            skip++;
            index.a = i + 1;
            tab = found_it(tab, new_env, &index, &skip);
            if (index.j == -1)
                break;
            //i = skip + i;
            skip = 0;
        }
        i++;
    }
    printf("%s\n\n", tab);
    return (0);
}


/*
void	interprete_quote(char *str)
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
*/