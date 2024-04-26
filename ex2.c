#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *func(void *arg) {
	char *msg = (char *) arg;// Conversion de l'argument en chaîne de caractères
	printf("Message = %s\n", msg);// Affichage du message
	return NULL;
}

int main(int argc, char *argv[]) {
	pthread_t t;// Déclaration d'une variable de type pthread_t pour stocker l'identifiant du thread
	char *msg = "Hello World!";
	if (pthread_create(&t, NULL, func, msg) != 0) { //Pour crée le thread
		
		return EXIT_FAILURE;
	}
	if(pthread_join(t, NULL) !=0){ // Attente de la fin du thread
        
        EXIT_FAILURE;
    }
	return EXIT_SUCCESS;
}
