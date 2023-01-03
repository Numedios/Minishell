#include "minishell.h"

/* --suppressions=readline_leaks.txt */

/* Read a string, and return a pointer to it.  Returns NULL on EOF. */
char *rl_gets()
{
	/* A static variable for holding the line. */
	static char *line_read = (char *)NULL;
	/* If the buffer has already been allocated, return the memory
	   to the free pool. */
	if (line_read)
	{
		free(line_read);
		line_read = (char *)NULL;
	}

	/* Get a line from the user. */
		line_read = readline("Minishell> ");

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
	int				i;
	char **new_env;
	
	setup_signal_handlers();
	new_env = my_env(env);//ne pas oublier de free a la fin le new env
	while (1)
	{
		i = 0;
		line = rl_gets();
		if (line == NULL)  // si l'utilisateur appuie sur ctrl-D
		{
			printf("\n");
			exit(0);
		}
		if (parse(line) == 0)
		{
			//line = "12>30\"ab<cd\"abbb>e>f";
			if (!quote_close(line))
			{
				dprintf(2, "Quote non fermer\n");
				exit (0);
			}
			split_pipe = ft_split(line , "|");
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
				ft_print_split_elem(split_arg);
				ft_print_split_elem(split_arg);
				add_end_maillons(&maillons, create_maillons(&split_arg));
				// ft_print_maillons(maillons);
				//ft_free_split_arg(&split_arg);
				printf("\n***********************\n\n");
				ft_free_split_arg(&split_arg);
				i++;
			}
			free_maillons(&maillons);
			ft_free_tab(split_pipe);
		}
	}
	return (1);
}

/*
int main(int argc, char **argv, char **env)
{
	char			*line;
	char	*word;

	line = rl_gets();
	word = create_word_and_quote2(line, "<>"); // utiliser la version 2 plutot que la version 1ft_lo
	printf("word = %s\n", word);
}*/



// asas<"SAs<>SA<><A S><"asas
// > in >> in2 cat -e < out <out2 << out3 -l