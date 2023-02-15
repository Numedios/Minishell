#include "minishell.h"

/* --suppressions=readline_leaks.txt */

/* Read a string, and return a pointer to it.  Returns NULL on EOF. */
char *rl_gets()
{
	/* A static variable for holding the line. */
	static char *line_read = (char *)NULL;
	/* If the buffer has already been allocated, return the memory
	   to the free pool. */
	//if (line_read)
	//{
	//	free(line_read);
		line_read = (char *)NULL;
	//}

	/* Get a line from the user. */
		line_read = readline("Minishell > ");

		/* If the line has any text in it, save it on the history. */
		if (line_read && *line_read)
			add_history(line_read);
		//if (ft_strcmp(line_read, "stop"))
		//	break;

	return (line_read);
}

/*
int main(int argc, char **argv, char **env)
{
	int res;
	char buff[1000];
	char buff2[1000];
	char *line;
	char **tab;
	line = rl_gets();

	tab = ft_split(line, WHITE_SPACE);
	pwd();
	cd(tab);
	pwd();
	//printf("line = %s\n", line);
}
*/

int	g_exit_code[2];

t_maillons *loop_create_maillons(char * line, t_garbage *garbage)
{
	t_maillons		*maillons;
	t_maillons		*maillon;
	t_maillons		*prev;
	int				i;

	i = 0;
	prev = NULL;
	garbage->split_pipe = ft_split(line , "|");
	garbage ->maillons = NULL;
	if (!(garbage->split_pipe))
		return (0);
	while (garbage && garbage->split_pipe[i])
	{
		garbage->split_lst = ft_split_list(garbage->split_pipe[i], WHITE_SPACE);
		if (!(garbage->split_lst))
				break;
		create_split_arg(&garbage-> split_lst);
		maillon = create_maillons(&garbage->split_lst, prev);
		add_end_maillons(&garbage->maillons, maillon);
		prev = maillon;
		ft_free_split_arg(&garbage->split_lst);
		i++;
	}
	ft_free_tab(garbage->split_pipe);
	garbage->split_lst = NULL;
	garbage->split_pipe = NULL;
	return (garbage->maillons);
}

int main(int argc, char **argv, char **env)
{
	char		*line;
	t_garbage	garbage;
	char		**new_env;

	initialize_garbage(&garbage);
	garbage.new_env = my_env(env);//ne pas oublier de free a la fin le new env
	while (1)
	{
		setup_signal_handlers();
		line = rl_gets();
		if (line == NULL)  // si l'utilisateur appuie sur ctrl-D
		{
			free_garbage(&garbage);
			ft_free_tab(garbage.new_env);
			//free(line);
			printf("\n");
			exit(0);
		}
		if (parse(line) == 0)
		{
			garbage.line = delete_dollar(line, garbage.new_env, 0, 0);
			//printf("line after delete= %s\n", line);
			garbage.line = replace_dollar(line, garbage.new_env, 0, 0);
			//printf("line after replace= %s\n", line);
			loop_create_maillons(garbage.line, &garbage);
			cmd_to_path(garbage.maillons, garbage.new_env);
			find_all_heredoc(garbage.maillons);// verifier les leak au niveau de cat << a <b
			printf("exit_code[1] = %d\n", g_exit_code[1]);
			check_inputs_outputs(garbage.maillons);
			//ft_print_garbage(&garbage);
			//ft_print_maillons(garbage.maillons);
			pipex(garbage.maillons, &garbage.new_env, &garbage);
			free_garbage(&garbage);
		}
	}
	free_garbage(&garbage);
	ft_free_tab(garbage.new_env);
	return (1);
}

/*

int main(int argc, char **argv, char **env)
{
	char			*line;
	char			**split_pipe;
	t_split_elem	*split_arg;
	t_maillons		*maillons; // utile pour toi zak faire le parsing dessus
	t_maillons		*maillon;
	t_maillons		*prev;
	int				i;
	char **new_env;
	char *tab;

	prev = NULL;
	maillon = NULL;
	g_exit_code[0] = 0;
	setup_signal_handlers();
	new_env = my_env(env);//ne pas oublier de free a la fin le new env
	while (1)
	{
		i = 0;
		line = rl_gets();
		if (line == NULL)  // si l'utilisateur appuie sur ctrl-D
		{
			write(2, "exit\n", 5);
			ft_free_tab(new_env);
			exit(0);
		}
		line  = replace_dollar(line, new_env);
		line = delete_dollar(line);
		printf("line = %s\n", line);
		if (parse(line) == 0)
		{
			if (!quote_close(line))
			{
				dprintf(2, "Quote non fermer\n");
				ft_free_tab(new_env);
				exit (0);
			}
			split_pipe = ft_split(line , "|"); // gerer le cas ou les pipes se trouve dans des parenthese
			maillons = NULL;
			if (!split_pipe)
				return (0);
			while (split_pipe[i])
			{
				split_arg = ft_split_list(split_pipe[i], WHITE_SPACE);
				if (!split_arg)
					break;
				//ft_print_split_elem(split_arg);
				create_split_arg(&split_arg);
				maillon = create_maillons(&split_arg, prev);
				add_end_maillons(&maillons, maillon);
				prev = maillon;
				ft_free_split_arg(&split_arg);
				i++;
			}
			cmd_to_path(maillons, env);
			check_inputs_outputs(maillons);
			//pipex(maillons, env);
			pipex_2(maillons, new_env);
			//ft_print_maillons(maillons);
			find_maillon_without_cmd(&maillons);
			free_maillons(&maillons);
			ft_free_tab(split_pipe);
		}
	}
	return (1);
}

*/

/*

split_pipe = ft_split(line , "|");
			maillons = NULL;
			if (!split_pipe)
				return (0);
			while (split_pipe[i])
			{
				split_arg = ft_split_list(split_pipe[i], WHITE_SPACE);
				if (!split_arg)
					break;
				create_split_arg(&split_arg);
				maillon = create_maillons(&split_arg, prev);
				add_end_maillons(&maillons, maillon);
				prev = maillon;
				ft_free_split_arg(&split_arg);
				i++;
			}



*/

// cat > A > B < sadsadas < 48787 > C

// in1 cat cat out3
//  dev/stdin ls >> a
// out5 echo "bonjour" -> pipe
// in3 cat out6
//  in3 pwd cat out6

/*
*
*
* si
*
*
*/
/*
int main(int argc, char **argv, char **env)
{
	char			**line;
	char	**word;

	word = ft_split("bonjours aurevoir", " ");
	line = word;
	//ft_free_tab(line);
	printf("line = %p // word = %p\n", line[0], word[0]);
	//free(word);
	printf("line = %p // word = %p\n", line[1], word[1]);
}*/



// asas<"SAs<>SA<><A S><"asas
// > in >> in2 cat -e < out <out2 << out3 -l

/*
t_maillons *loop_create_maillons(char * line)
{
	t_maillons		*maillons;
	t_maillons		*maillon;
	t_maillons		*prev;
	char			**split_pipe;
	t_split_elem	*split_arg;
	int				i;

	i = 0;
	prev = NULL;
	split_pipe = ft_split(line , "|");
	maillons = NULL;
	if (!split_pipe)
		return (0);
	while (split_pipe[i])
	{
		split_arg = ft_split_list(split_pipe[i], WHITE_SPACE);
		if (!split_arg)
				break;
		create_split_arg(&split_arg);
		maillon = create_maillons(&split_arg, prev);
		add_end_maillons(&maillons, maillon);
		prev = maillon;
		ft_free_split_arg(&split_arg);
		i++;
	}
	ft_free_tab(split_pipe);
	return (maillons);
}


int main(int argc, char **argv, char **env)
{
	char			*line;
	t_maillons		*maillons;
	char **new_env;

	setup_signal_handlers();
	//new_env = my_env(env);//ne pas oublier de free a la fin le new env
	//while (1)
	//{
		line = rl_gets();
		if (line == NULL)  // si l'utilisateur appuie sur ctrl-D
		{
			ft_free_tab(new_env);
			printf("\n");
			exit(0);
		}
		if (parse(line) == 0)
		{
			maillons = loop_create_maillons(line);
			ft_print_maillons(maillons);
			cmd_to_path(maillons, env);
			find_all_heredoc(maillons);
			check_inputs_outputs(maillons);
			pipex(maillons, env);
			free_maillons(&maillons);
		}
	//}
	//ft_free_tab(new_env);
	return (1);
}*/
