#include "../minishell.h"

void	init(two_pipe *two_pipe)
{
    two_pipe->status = 0;
    two_pipe->i = 0;
    two_pipe->fd_in = -3;
    two_pipe->fd_out = -3;
	if (pipe(two_pipe->pipe_fd) < 0)
	{
		write(2,"pipe_fd\n", 8);
		exit ;
	}
}

/*return 1 si il y a pas de builtin a faire et 0 si il y en a un et finir pipex*/
// gerer les erreurs pour chaque built in a qui on envoie trop d'argument

int	check_if_builtin (char **args, char **env)
{
	int	cmp;
	char *tab;
	int i;
	
	cmp = 0;
	i = 0;
	while (args[cmp])
	{
		if(args[cmp][0] == '-')
			return(1);
		cmp++;
	}
	if (str_cmp(args[0], "cd") == 1 && cmp == 2)
		return(do_cd(args[1]), 0);
	if (str_cmp(args[0], "env") == 1)
		return (do_env(env), 0);
	if (str_cmp(args[0], "pwd") == 1)
		return (do_pwd(), 0);
	if (str_cmp(args[0], "exit") == 1 && cmp < 3)// pas plus d'un argument et si pas d'argument le retour d'exit est 0 en code erreur 
		return (do_exit(args[1]), 0); 
	if (str_cmp(args[0], "unset") == 1)
	{
		while (args[++i])
			do_unset(args[i], env);
		return (0);
	}
	if (str_cmp(args[0], "export") == 1)
	{
		while (args[++i])
			env = do_export(args[i], env);
		return (0);
	}
	return (1);
}

int check_echo (char **args)
{
	int	cmp;
	char *tab;
	int i;
	
	cmp = 0;
	i = 0;
	while (args[cmp])
	{
		while (args[cmp][i])
		{
			if(args[cmp][0] == '-')
			{
				while(args[cmp][i] && args[cmp][i] == 'n')
					i++;
				if (args[cmp][i] == 'e' || args[cmp][i] == 'E')
					return (1);
			}
			i++;
		}
		i = 0;
		cmp++;
	}
	if (str_cmp(args[0], "echo") == 1)//attention a le droit a une seule option
	{
		do_echo(&args[1]);
		return (0);
	}
	return (1);
}


/*
void	write_error(char *argv, t_vare *vare, char *tab)
{
	ft_putstr_fd("bash: ", 2);
	perror(argv);
	if (tab[0] == '1')
		close(vare->fd_in);
	if (tab[1] == '1')
		close(vare->fd_out);
	if (tab[2] == '1')
		close(vare->pipe_fd[1]);
	if (tab[3] == '1')
		close(vare->pipe_fd[0]);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	free_all(vare);
	exit(EXIT_FAILURE);
}

void	write_error_2(char *argv, int i, t_vare *vare)
{
	if (i == 1)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(argv, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	if (i == 2)
	{
		ft_putstr_fd("bash: ", 2);
		perror(argv);
	}
	if (i == 3)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(argv, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	free_all(vare);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	exit(EXIT_FAILURE);
}

int	end_close(t_vare *vare)
{
	if (close(vare->pipe_fd[0]) < 0)
		return (write_error("pipe_fd[0]", vare, "1111"), 1);
	if (close(vare->pipe_fd[1]) < 0)
		return (write_error("pipe_fd[1]", vare, "1111"), 1);
	if (close(vare->fd_in) < 0)
		return (write_error("fd_in", vare, "1111"), 1);
	if (close(vare->fd_out) < 0)
		return (write_error("fd_out", vare, "1111"), 1);
	free_all(vare);
	return (0);
}

*/