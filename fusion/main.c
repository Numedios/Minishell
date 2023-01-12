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
	
	prev = NULL;
	maillon = NULL;
	setup_signal_handlers();
	//new_env = my_env(env);//ne pas oublier de free a la fin le new env
	//while (1)
	//{
		i = 0;
		line = rl_gets();
		if (line == NULL)  // si l'utilisateur appuie sur ctrl-D
		{
			printf("\n");
			exit(0);
		}
		if (parse(line) == 0)
		{
			//line = "cat >a | cat | >a";
			if (!quote_close(line))
			{
				dprintf(2, "Quote non fermer\n");
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
			check_input_output(&(maillons->output));
			pipex(maillons, env);
			ft_print_maillons(maillons);
			//find_maillon_without_cmd(&maillons);
			//ft_print_maillons(maillons);
			//printf("\n\nLen = %d\n\n", ft_strlen_maillons(maillons));
			free_maillons(&maillons);
			ft_free_tab(split_pipe);
		}
	//}
	return (1);
}

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