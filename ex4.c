#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Fonction ex�cut�e par le premier thread
void *thread_func1(void *args) {
    while (1) { // Boucle infinie
        printf("Thread 1: Bonjour !\n"); // Affichage d'un message
        sleep(1); // Pause d'une seconde
    }
    return NULL; // La fonction renvoie NULL � la fin de son ex�cution
}

// Fonction ex�cut�e par le deuxi�me thread
void *thread_func2(void *args) {
    while (1) { // Boucle infinie
        printf("Thread 2: Salut !\n"); // Affichage d'un message
        sleep(2); // Pause de deux secondes
    }
    return NULL; // La fonction renvoie NULL � la fin de son ex�cution
}

// Fonction principale du programme
int main() {
    pthread_t th1, th2; // D�claration de deux variables de type pthread_t pour stocker les identifiants des threads

    // Cr�ation des deux threads et ex�cution de leurs fonctions respectives
    pthread_create(&th1, NULL, thread_func1, NULL);
    pthread_create(&th2, NULL, thread_func2, NULL);

    // Attente de la fin de chaque thread
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    return 0; // Fin du programme
}

