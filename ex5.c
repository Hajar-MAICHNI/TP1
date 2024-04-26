#include <stdio.h>     
#include <stdlib.h>   
#include <pthread.h>  
#include <unistd.h>    

#define NUM_TASKS 3    // Définition du nombre de tâches

// Structure représentant une tâche périodique
typedef struct {
    int id;         // Identifiant de la tâche
    int period;     // Période de la tâche en secondes
} PeriodicTask;

// Fonction exécutée par chaque thread représentant une tâche périodique
void *taskFunction(void *arg) {
    PeriodicTask *task = (PeriodicTask *)arg; // Conversion de l'argument en pointeur vers une tâche périodique

    while (1) { // Boucle infinie pour exécuter la tâche périodiquement
        sleep(task->period); // Attente pendant la période définie de la tâche
        printf("Task %d executed.\n", task->id); // Affichage de l'exécution de la tâche avec son identifiant
    }

    return NULL; // La fonction renvoie NULL à la fin de son exécution (ceci ne sera jamais atteint ici)
}

int main() {
    int TASK_PERIODS[] = {1, 2, 3}; // Périodes des tâches en secondes
    pthread_t threads[NUM_TASKS];    // Tableau pour stocker les identifiants des threads
    PeriodicTask tasks[NUM_TASKS];   // Tableau pour stocker les tâches périodiques
    int i;

    // Création des threads représentant les tâches périodiques
    for (i = 0; i < NUM_TASKS; ++i) {
        tasks[i].id = i + 1;          // Attribution de l'identifiant à chaque tâche
        tasks[i].period = TASK_PERIODS[i]; // Attribution de la période à chaque tâche
        pthread_create(&threads[i], NULL, taskFunction, (void *)&tasks[i]); // Création du thread avec la fonction de tâche et les paramètres
    }

    sleep(10); // Attente de 10 secondes pour permettre l'exécution des tâches

    // Annulation des threads et attente de leur terminaison
    for (i = 0; i < NUM_TASKS; ++i) {
        pthread_cancel(threads[i]); // Annulation du thread
        pthread_join(threads[i], NULL); // Attente de la terminaison du thread
    }

    return 0; // Fin du programme
}

