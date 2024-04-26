#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Fonction exécutée par le premier thread
void *thread_func1(void *args) {
    while (1) { // Boucle infinie
        printf("Thread 1: Bonjour !\n"); // Affichage d'un message
        sleep(1); // Pause d'une seconde
    }
    return NULL; // La fonction renvoie NULL à la fin de son exécution
}

// Fonction exécutée par le deuxième thread
void *thread_func2(void *args) {
    while (1) { // Boucle infinie
        printf("Thread 2: Salut !\n"); // Affichage d'un message
        sleep(2); // Pause de deux secondes
    }
    return NULL; // La fonction renvoie NULL à la fin de son exécution
}

// Fonction principale du programme
int main() {
    pthread_t th1, th2; // Déclaration de deux variables de type pthread_t pour stocker les identifiants des threads

    // Création des deux threads et exécution de leurs fonctions respectives
    pthread_create(&th1, NULL, thread_func1, NULL);
    pthread_create(&th2, NULL, thread_func2, NULL);

    // Attente de la fin de chaque thread
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    return 0; // Fin du programme
}

