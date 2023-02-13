/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:09:08 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/02/13 21:10:55 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"
//si il y a juste un dollar ecrire dolalr
//test a faire : echo $'hola'       echo $"hola"    echo $      echo $hol (hol n'existe pas)        echo $$SYSTEMD_EXEC_PID
//$"HOME" doit devenir HOME

extern int	g_exit_code[2];

void	new_in_old(for_dollar *var, t_index *index, char **new_env, int *skip)
{
	var->pos_new_env = str_len_env(new_env[index->j]);
	while (new_env[index->j][var->pos_new_env] == '='
	|| new_env[index->j][var->pos_new_env] == '+')
		var->pos_new_env++;
	while (var->i < (var->len_value - 1))
	{
		var->new_tab[var->pos] = new_env[index->j][var->pos_new_env];
		var->i++;
		var->pos++;
		var->pos_new_env++;
	}
	var->pos_tab = var->pos_tab + (*skip);
}

char	*do_replace(char *tab, char **new_env, int skip, t_index index)
{
	for_dollar	var;

	var.pos = 0;
	var.pos_tab = 0;
	var.len_tab = ft_strlen(tab);
	var.new_len = var.len_tab - skip;
	var.len_value = ft_strlen(&new_env[index.j][str_len_env(new_env[index.j])]);
	var.new_tab = malloc (sizeof(char) * (var.new_len + var.len_value));
	while (var.pos < (index.a - 1))
	{
		var.new_tab[var.pos] = tab[var.pos];
		var.pos++;
		var.pos_tab++;
	}
	var.i = 0;
	new_in_old(&var, &index, new_env, &skip);
	while (tab && tab[var.pos_tab])
	{
		var.new_tab[var.pos] = tab[var.pos_tab];
		var.pos++;
		var.pos_tab++;
	}
	var.new_tab[var.pos] = '\0';
	free(tab);
	return (var.new_tab);
}

void	new_in_old_interrogation(for_dollar *var)
{
	var->pos_tab = var->pos_tab + 2;
	while (var->value[var->i])
	{
		var->new_tab[var->pos] = var->value[var->i];
		var->pos++;
		var->i++;
	}
}

char	*replace_interrogation(char *tab, char **new_env, int skip, t_index index)
{
	for_dollar	var;

	var.pos = 0;
	var.pos_tab = 0;
	var.value = ft_itoa(g_exit_code[0]);
	var.len_tab = ft_strlen(var.value);
	var.new_len = var.len_tab - skip;
	var.len_value = ft_strlen(var.value);
	var.new_tab = malloc (sizeof(char) * (var.new_len + var.len_value));
	while (var.pos < (index.a - 1))
	{
		var.new_tab[var.pos] = tab[var.pos];
		var.pos++;
		var.pos_tab++;
	}
	var.i = 0;
	new_in_old_interrogation(&var);
	while (tab && tab[var.pos_tab])
	{
		var.new_tab[var.pos] = tab[var.pos_tab];
		var.pos++;
		var.pos_tab++;
	}
	var.new_tab[var.pos] = '\0';
	free(tab);
	return (var.new_tab);
}

int	research(int skip, int a, char *tab, char **new_env)// -1 veut dire qu'on a trouve
{
	int	len_env;
	int	i;

	i = 0;
	if (skip == 1 && tab[a] == '?')//skip == 1 car le if de la fonction d'avant check les ?
		return (-2);
	while (new_env[i])
	{
		len_env = str_len_env(new_env[i]);
		if ((skip - 1) != len_env || ft_strncmp(new_env[i], &tab[a], (skip - 1)) != 0)
			i++;
		else
			return (i);
	}
	return (-1);
}

char	*found_it(char *tab, char **new_env, t_index *index, int *skip)
{
	// t_index index;
	int	i;


	// index.a = i;
	i = index->a;
	while (tab[i])
	{
		if (tab[i] == '\'' || tab[i] == '"' || tab[i] == ' ' || tab[i] == '-' || tab[i] == '!' || tab[i] == '@' || tab[i] == '#' || tab[i] == '$' || tab[i] == '%' || tab[i] == '^' || tab[i] == '&' || tab[i] == '*' || tab[i] == '(' || tab[i] == ')' || tab[i] == '{' || tab[i] == '}' || tab[i] == '[' || tab[i] == ']' || tab[i] == '|' || tab[i] == ';' || tab[i] == ':' || tab[i] == '<' || tab[i] == '>' || tab[i] == '?' || tab[i] == '/'|| tab[i] == '~' || tab[i] == '\\')
		{
			index->j = research(*skip, index->a, tab, new_env);
			if (index->j != -1)
			{
				if (index->j == -2)
					tab = replace_interrogation(tab, new_env, *skip, (*index));
				else
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
		if (index->j == -2)
			tab = replace_interrogation(tab, new_env, *skip, (*index));
		else
			tab = do_replace(tab, new_env, *skip, (*index));
	}
	return (tab);
}

char	*found_dollar_inquote(char *tab, int *i, char ** new_env, t_index *index)//peut etre pas besoin de renvoyer un char* ou alors il faut envoyer l'adresse de tab
{
	int	skip;

	skip = 0;
	(*i)++;
	while (tab[(*i)] && tab[(*i)] != '"' /*&& tab[(*i)] != '\''*/)
	{
		while (tab[(*i)] == '$' && tab[(*i) + 1] == '$')
			i++;
		while (tab[(*i)] == '$')
		{
			skip++;
			index->a = (*i) + 1;
			//dprintf(2, "index->a = %d\nindex->j =%d\n ", index->a, index->j);
			tab = found_it(tab, new_env, index, &skip);
			//dprintf(2, "index->a = %d\nindex->j = %d", index->a, index->j);
			if (index->j == -1)
				(*i) = skip + (*i);
			skip = 0;
		}
		(*i)++;
	}
	return (tab);
}

char	*one_dollar_or_more(char *tab, int *i, char ** new_env, t_index *index)
{
	int	skip;

	skip = 0;
	while (tab[(*i)] && tab [(*i) + 1] != '\0' && tab[(*i)] == '$' && tab[(*i) + 1] != ' ')
	{
		skip++;
		index->a = (*i) + 1;
		tab = found_it(tab, new_env, index, &skip);
		if (index->j == -1)
		{
			(*i) = -1;
			break ;
		}
		else
		{
			(*i) = -1;
			break ;
		}
		skip = 0;
	}
	return (tab);
}

char	*replace_dollar(char *tab, char **new_env)//peu etre possible de pas renvoyer un char mais il faut dans ce cas envoyer l'adresse de tab
{
	int		i;
	int		skip;
	t_index	index;

	skip = check_dollar(tab);
	i = 0;
	if (skip == 0)
		return (tab);
	skip = 0;
	while (tab && tab[i] != '\0')
	{
		if (tab[i] == '"')
			tab = found_dollar_inquote(tab, &i, new_env, &index);
		if (tab && tab[i] && tab[i] == '\'')//PEUT ETRE qu'il faut un while
		{
			i++;
			while (tab && tab[i] != '\0' && tab[i] != '\'' && tab[i] != '\'')
				i++;
			if (tab && tab[i] && tab[i] == '\'')
				i++;
		}
		while (tab && tab[i] != '\0' && tab[i] == '$' && tab[i + 1] == '$')
					i++;
		tab = one_dollar_or_more(tab, &i, new_env, &index);
		if (i == -1)
			i = 0;
		else
			i++;
	}
	return (tab);
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
