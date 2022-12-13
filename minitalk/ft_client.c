#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  // Vérifier les arguments de la ligne de commande
  if (argc != 3) {
    printf("Usage : %s <PID du serveur> <message>\n", argv[0]);
    return 1;
  }

  // Récupérer le PID du serveur et la chaîne de caractères à envoyer
  pid_t server_pid = atoi(argv[1]);
  char *msg = argv[2];

  // Envoyer un signal SIGUSR1 au serveur pour l'informer de la connexion
  if (kill(server_pid, SIGUSR1) != 0) {
    perror("Erreur lors de l'envoi du signal SIGUSR1");
    return 1;
  }

  // Attendre la réponse du serveur
  sleep(1);

  // Envoyer la chaîne de caractères au serveur en utilisant un signal SIGUSR2
  union sigval sval;
  sval.sival_ptr = (void*) msg;
  if (kill(server_pid, SIGUSR2) != 0) {
    perror("Erreur lors de l'envoi du signal SIGUSR2");
    return 1;
  }

  // Attendre la fin de la transmission de la chaîne de caractères
  sleep(1);

  return 0;
}

