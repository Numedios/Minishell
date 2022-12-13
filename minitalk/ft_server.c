#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Liste ou tableau pour enregistrer les PIDs des clients
int clients[1024];
int nb_clients = 0;

// Gestionnaire de signal pour SIGUSR1
void sigusr1_handler(int sig, siginfo_t *info, void *context) {
  // Enregistrer le PID du client
  clients[nb_clients++] = info->si_pid;
}

// Gestionnaire de signal pour SIGUSR2
void sigusr2_handler(int sig, siginfo_t *info, void *context) {
  // Vérifier si le PID du client est enregistré
  for (int i = 0; i < nb_clients; i++) {
    if (clients[i] == info->si_pid) {
      // Lire et afficher la chaîne de caractères envoyée par le client
      char *msg = (char*) info->si_value.sival_ptr;
      printf("Message reçu de %d : %s\n", info->si_pid, msg);
      break;
    }
  }
}

int main() {
  // Afficher le PID du serveur
  printf("PID du serveur : %d\n", getpid());

  // Créer un processus fils pour l'écoute des signaux
  pid_t pid = fork();

  if (pid == 0) {
    // Processus fils

    // Enregistrer les gestionnaires de signaux pour SIGUSR1 et SIGUSR2
    struct sigaction sigusr1_action, sigusr2_action;

    sigusr1_action.sa_sigaction = sigusr1_handler;
    sigusr1_action.sa_flags = SA_SIGINFO;
    sigemptyset(&sigusr1_action.sa_mask);
    sigaction(SIGUSR1, &sigusr1_action, NULL);

    sigusr2_action.sa_sigaction = sigusr2_handler;
    sigusr2_action.sa_flags = SA_SIGINFO;
    sigemptyset(&sigusr2_action.sa_mask);
    sigaction(SIGUSR2, &sigusr2_action, NULL);

    // Attendre la fin du processus
    pause();
  } else {
    // Processus principal

    // Attendre la fin du processus fils
    waitpid(pid, NULL, 0);
  }

  return 0;
}

