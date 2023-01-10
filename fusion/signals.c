#include"minishell.h"

void handle_sig(int sig)//il faut free si exit 
{
	if (sig == SIGINT)//ctrl+c
	{
        rl_on_new_line();
        // rl_on_new_line_with_prompt();devoir defenir un prompte au prealable peut etre pour eviter que le prompt ne s'affiche qu'une fois qu'on a touche a un lettre
        write(1, "\n", 1);
        rl_replace_line("", 0);
        rl_redisplay();
	}
	if (sig == SIGTSTP)//il faudra l'enlever
	{
		exit(0);
	}
}

void setup_signal_handlers(void)
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
  if (signal(SIGTSTP, handle_sig) == SIG_ERR)
  {
    perror("signal failed");
    exit (1);
  }
}