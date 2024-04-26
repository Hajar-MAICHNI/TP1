#include <stdio.h>     
#include <stdlib.h>   
#include <pthread.h>  
#include <unistd.h>    

#define NUM_TASKS 3    // D�finition du nombre de t�ches

// Structure repr�sentant une t�che p�riodique
typedef struct {
    int id;         // Identifiant de la t�che
    int period;     // P�riode de la t�che en secondes
} PeriodicTask;

// Fonction ex�cut�e par chaque thread repr�sentant une t�che p�riodique
void *taskFunction(void *arg) {
    PeriodicTask *task = (PeriodicTask *)arg; // Conversion de l'argument en pointeur vers une t�che p�riodique

    while (1) { // Boucle infinie pour ex�cuter la t�che p�riodiquement
        sleep(task->period); // Attente pendant la p�riode d�finie de la t�che
        printf("Task %d executed.\n", task->id); // Affichage de l'ex�cution de la t�che avec son identifiant
    }

    return NULL; // La fonction renvoie NULL � la fin de son ex�cution (ceci ne sera jamais atteint ici)
}

int main() {
    int TASK_PERIODS[] = {1, 2, 3}; // P�riodes des t�ches en secondes
    pthread_t threads[NUM_TASKS];    // Tableau pour stocker les identifiants des threads
    PeriodicTask tasks[NUM_TASKS];   // Tableau pour stocker les t�ches p�riodiques
    int i;

    // Cr�ation des threads repr�sentant les t�ches p�riodiques
    for (i = 0; i < NUM_TASKS; ++i) {
        tasks[i].id = i + 1;          // Attribution de l'identifiant � chaque t�che
        tasks[i].period = TASK_PERIODS[i]; // Attribution de la p�riode � chaque t�che
        pthread_create(&threads[i], NULL, taskFunction, (void *)&tasks[i]); // Cr�ation du thread avec la fonction de t�che et les param�tres
    }

    sleep(10); // Attente de 10 secondes pour permettre l'ex�cution des t�ches

    // Annulation des threads et attente de leur terminaison
    for (i = 0; i < NUM_TASKS; ++i) {
        pthread_cancel(threads[i]); // Annulation du thread
        pthread_join(threads[i], NULL); // Attente de la terminaison du thread
    }

    return 0; // Fin du programme
}

