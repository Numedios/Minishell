#include "minishell.h"

/* --suppressions=readline_leaks.txt */
int	only_white_space(char *line_read)
{
	int	i;

	i = 0;
	while (line_read[i])
	{
		if (line_read[i] != ' ' )
			return (0);
		i++;
	}
	return (1);
}
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
		{
			if (only_white_space(line_read) == 0)
				add_history(line_read);
		}
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
	garbage->split_pipe = ft_split2(line , "|");
	garbage ->maillons = NULL;
	if (!(garbage->split_pipe))
		return (0);
	while (garbage && garbage->split_pipe[i])
	{
		garbage->split_lst = ft_split_list(garbage->split_pipe[i], WHITE_SPACE);
		if (!(garbage->split_lst))
				break;
		create_split_arg(&garbage->split_lst);
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

void end_quote(t_garbage *garbage)
{
    t_maillons        *tmp;
    t_input_output    *tmp2;
    int i;

    i = 0;
    tmp = NULL;
    tmp2 = NULL;
    if (garbage && garbage-> maillons)
        tmp = garbage->maillons;
    while (garbage && garbage->maillons)
    {
        i = 0;
		if (garbage && garbage-> maillons && garbage->maillons->output)
        	tmp2 = garbage->maillons->output;
		else
			tmp2 = NULL;
        while (garbage && garbage->maillons && (garbage->maillons->args)[i])
        {
            (garbage->maillons->args)[i] = delete_the_quote(((garbage->maillons->args)[i]), 0, 0);
            i++;
        }
        if (garbage && garbage->maillons && garbage->maillons->command)
        	garbage->maillons->command = delete_the_quote(garbage->maillons->command, 0, 0);
        while(garbage && garbage-> maillons && garbage->maillons->output)
        {
            garbage->maillons->output->file_name = delete_the_quote(garbage->maillons->output->file_name, 0, 0);
            garbage->maillons->output = garbage->maillons->output->next;
        }
		if (tmp2)
       		garbage->maillons->output = tmp2;
        garbage->maillons = garbage->maillons->next;
    }
    if (tmp)
        garbage->maillons = tmp;
}

int main(int argc, char **argv, char **env)
{
	char		*line;
	t_garbage	garbage;
	char		**new_env;

	initialize_garbage(&garbage);
	garbage.new_env = my_env(env);
	while (1)
	{
		g_exit_code[1] = 0;
		setup_signal_handlers();
		line = rl_gets();
		if (line && line[0] == '\0')
			g_exit_code[0] = 0;
		if (line == NULL && g_exit_code[1] != 8)
		{
			s_fd("\nexit11\n", 2);
			free_garbage_env_exit(&garbage, 0);
		}
		if (parse(line) == 0)
		{
			garbage.line = delete_dollar(line, garbage.new_env, 0, 0);
			garbage.line = replace_dollar(line, garbage.new_env, 0, 0);
			loop_create_maillons(garbage.line, &garbage);
			cmd_to_path(garbage.maillons, garbage.new_env);
			find_all_heredoc(garbage.maillons);
			//ft_print_maillons(garbage.maillons);
			//printf("*********************\nma");
			end_quote(&garbage);
			//ft_print_maillons(garbage.maillons);
			if (g_exit_code[1] != 7)
			pipex(garbage.maillons, &garbage.new_env, &garbage);
			free_garbage(&garbage);
		}
	}
	free_garbage_and_env(&garbage);
	return (1);
}
