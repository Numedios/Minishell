#include "minishell.h"

extern int	exit_code[2];

//declarer exit_code[2], le deuxieme int servira a gerer les cas dans les enfants
void	handle_sig(int sig)//il faut free si exit
{
	if (sig == SIGINT)//ctrl+c
	{
		if (exit_code[1] == 5)//pour here doc 
		{
			/*
			rajouter exit code dans le here doc
			psk je me dis peut etre que je mettrait en place un exit_code special pour celui la, en mode si exit_code[1]=5, 
			et on mettre cette valeur au debut de la fonction, mon signal fermera tous les pipes, passera l'exit code a 6 
			et on rajoute une condition pour executer pipex qui est que exit_code[1] != 6
			ou que juste dans mon signal quand exit code[1] == 5, on free tout comme ca il se passe rien dans pipex
			*/
		}
		if (exit_code[1] == 2)
		{
			// dprintf(2, "here2\n");
			exit_code[1] = 3;// == 0
			write(1, "\n", 1);
		}
		else
		{
			//dprintf(2, "here\n");
			rl_replace_line("", 0);
			write(1, "\n", 1);
			rl_on_new_line();
			// rl_on_new_line_with_prompt();devoir defenir un prompte au prealable peut etre pour eviter que le prompt ne s'affiche qu'une fois qu'on a touche a un lettre
			rl_redisplay();
			exit_code[0] = 130;//verifier les codes erreurs
		}
	}
	// if (sig == SIGTSTP)//il faudra l'enlever
	// {
	// 	if (exit_code[1] == 2)
	// 	{
	// 		write(2, "Quit (code dumped)\n", 19);
	// 	}
	// 	else
	// 		exit(0);
	// }
}

void	setup_signal_handlers(void)
{
	// Définissez handle_sig() comme le gestionnaire de signal pour SIGINT.
	if (signal(SIGINT, handle_sig) == SIG_ERR)
	{
		perror("signal failed");
		exit (1);
	}
	// Définissez SIG_IGN comme le gestionnaire de signal pour SIGQUIT.
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		perror("signal failed");
		exit (1);
	}
	// Définissez handle_sig() comme le gestionnaire de signal pour SIGTSTP.
	// if (signal(SIGTSTP, handle_sig) == SIG_ERR)
	// {
	// 	perror("signal failed");
	// 	exit (1);
	// }
}

/*
void handle_sigint(int sig, siginfo_t *si, void *ucontext)//il faut free si exit
{
	if (sig == SIGINT)//ctrl+c
	{
		if (si->si_pid != 0)
		{
			exit_code = 130;
			rl_on_new_line();
			write(1, "\n", 1);
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else
		{
			exit_code = 130;
		}
	}
	if (sig == SIGTSTP)
	{
		exit(0);
	}
}

void	handle_sigquit(int sig, siginfo_t *si, void *ucontext)
{
	(void) ucontext;
	if (sig == SIGQUIT)
	{

	}
}

void setup_signal_handlers(void)
{
	struct sigaction sa_sigint;
	struct sigaction sa_sigquit;

	//memset(&sa, 0, sizeof(sa));
	sa_sigint.sa_sigaction = &handle_sigint;
	sa_sigint.sa_flags = SA_SIGINFO;
	sa_sigint.sa_sigaction = &handle_sigint;
	sa_sigint.sa_flags = SA_SIGINFO;
	if (sigaction(SIGINT, &sa_sigint, NULL) == -1)
	{
		perror("signal failed");
		exit (1);
	}

	if (sigaction(SIGQUIT, &sa_sigquit, NULL) == -1)
	{
		perror("signal failed");
		exit (1);
	}
}
*/
