#include <stdio.h>      
#include <stdlib.h>    
#include <pthread.h>   

#define ARRAY_SIZE 10   // Taille du tableau
#define NUM_THREADS 4   // Nombre de threads

int totalSum = 0; // Variable globale pour stocker la somme totale des éléments du tableau

// Structure contenant les arguments pour chaque thread
typedef struct {
    int *start;             // Pointeur vers le début de la section du tableau
    int *end;               // Pointeur vers la fin de la section du tableau
    pthread_mutex_t *lock; // Pointeur vers le verrou mutex pour la synchronisation
} PartialSumArgs;

// Fonction exécutée par chaque thread pour calculer la somme partielle
void *sum_partial(void *args) {
    PartialSumArgs *partialArgs = (PartialSumArgs *)args; // Conversion de l'argument en pointeur vers PartialSumArgs

    int partialSum = 0; // Variable locale pour stocker la somme partielle

    // Parcours de la section du tableau attribuée à ce thread
    int *p;
    for (p = partialArgs->start; p < partialArgs->end; p++) {
        partialSum += *p; // Ajout de la valeur de chaque élément à la somme partielle
    }

    // Verrouillage du mutex pour éviter les conflits d'accès à la variable globale totalSum
    pthread_mutex_lock(partialArgs->lock);

    totalSum += partialSum; // Ajout de la somme partielle à la somme totale

    // Déverrouillage du mutex après la mise à jour de totalSum
    pthread_mutex_unlock(partialArgs->lock);

    pthread_exit(NULL); // Terminaison du thread
}

int main() {
    int array[ARRAY_SIZE]; // Déclaration du tableau d'entiers
    int i;

    // Initialisation du tableau avec des valeurs de 1 à ARRAY_SIZE
    for (i = 0; i < ARRAY_SIZE; ++i) {
        array[i] = i + 1;
    }

    pthread_mutex_t lock; // Déclaration du verrou mutex
    pthread_mutex_init(&lock, NULL); // Initialisation du verrou mutex

    pthread_t threads[NUM_THREADS]; // Tableau pour stocker les identifiants des threads
    PartialSumArgs threadArgs[NUM_THREADS]; // Tableau pour stocker les arguments des threads

    int sectionSize = ARRAY_SIZE / NUM_THREADS; // Taille de chaque section du tableau

    // Création et exécution des threads pour calculer les sommes partielles
    for (i = 0; i < NUM_THREADS; ++i) {
        // Attribution des paramètres pour chaque thread
        threadArgs[i].start = (array + i * sectionSize); // Début de la section du tableau
        threadArgs[i].end = (array + ((i == NUM_THREADS - 1) ? ARRAY_SIZE : (i + 1) * sectionSize)); // Fin de la section du tableau
        threadArgs[i].lock = &lock; // Verrou mutex pour la synchronisation

        // Création du thread avec les arguments correspondants
        if (pthread_create(&threads[i], NULL, sum_partial, (void *)&threadArgs[i]) != 0) {
            fprintf(stderr, "Erreur lors de la création du thread %d\n", i); // Affichage d'un message d'erreur en cas d'échec
            return 1; // Retourne 1 pour indiquer une erreur
        }
    }

    // Attente de la fin de chaque thread
    for (i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    // Affichage de la somme totale calculée
    printf("Somme totale : %d\n", totalSum);

    pthread_mutex_destroy(&lock); // Destruction du verrou mutex

    return 0; // Fin du programme
}

