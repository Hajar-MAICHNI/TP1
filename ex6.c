#include <stdio.h>      
#include <stdlib.h>    
#include <pthread.h>   

#define ARRAY_SIZE 10   // Taille du tableau
#define NUM_THREADS 4   // Nombre de threads

int totalSum = 0; // Variable globale pour stocker la somme totale des �l�ments du tableau

// Structure contenant les arguments pour chaque thread
typedef struct {
    int *start;             // Pointeur vers le d�but de la section du tableau
    int *end;               // Pointeur vers la fin de la section du tableau
    pthread_mutex_t *lock; // Pointeur vers le verrou mutex pour la synchronisation
} PartialSumArgs;

// Fonction ex�cut�e par chaque thread pour calculer la somme partielle
void *sum_partial(void *args) {
    PartialSumArgs *partialArgs = (PartialSumArgs *)args; // Conversion de l'argument en pointeur vers PartialSumArgs

    int partialSum = 0; // Variable locale pour stocker la somme partielle

    // Parcours de la section du tableau attribu�e � ce thread
    int *p;
    for (p = partialArgs->start; p < partialArgs->end; p++) {
        partialSum += *p; // Ajout de la valeur de chaque �l�ment � la somme partielle
    }

    // Verrouillage du mutex pour �viter les conflits d'acc�s � la variable globale totalSum
    pthread_mutex_lock(partialArgs->lock);

    totalSum += partialSum; // Ajout de la somme partielle � la somme totale

    // D�verrouillage du mutex apr�s la mise � jour de totalSum
    pthread_mutex_unlock(partialArgs->lock);

    pthread_exit(NULL); // Terminaison du thread
}

int main() {
    int array[ARRAY_SIZE]; // D�claration du tableau d'entiers
    int i;

    // Initialisation du tableau avec des valeurs de 1 � ARRAY_SIZE
    for (i = 0; i < ARRAY_SIZE; ++i) {
        array[i] = i + 1;
    }

    pthread_mutex_t lock; // D�claration du verrou mutex
    pthread_mutex_init(&lock, NULL); // Initialisation du verrou mutex

    pthread_t threads[NUM_THREADS]; // Tableau pour stocker les identifiants des threads
    PartialSumArgs threadArgs[NUM_THREADS]; // Tableau pour stocker les arguments des threads

    int sectionSize = ARRAY_SIZE / NUM_THREADS; // Taille de chaque section du tableau

    // Cr�ation et ex�cution des threads pour calculer les sommes partielles
    for (i = 0; i < NUM_THREADS; ++i) {
        // Attribution des param�tres pour chaque thread
        threadArgs[i].start = (array + i * sectionSize); // D�but de la section du tableau
        threadArgs[i].end = (array + ((i == NUM_THREADS - 1) ? ARRAY_SIZE : (i + 1) * sectionSize)); // Fin de la section du tableau
        threadArgs[i].lock = &lock; // Verrou mutex pour la synchronisation

        // Cr�ation du thread avec les arguments correspondants
        if (pthread_create(&threads[i], NULL, sum_partial, (void *)&threadArgs[i]) != 0) {
            fprintf(stderr, "Erreur lors de la cr�ation du thread %d\n", i); // Affichage d'un message d'erreur en cas d'�chec
            return 1; // Retourne 1 pour indiquer une erreur
        }
    }

    // Attente de la fin de chaque thread
    for (i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    // Affichage de la somme totale calcul�e
    printf("Somme totale : %d\n", totalSum);

    pthread_mutex_destroy(&lock); // Destruction du verrou mutex

    return 0; // Fin du programme
}

