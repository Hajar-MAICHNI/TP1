#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Fonction exécutée par le premier thread
void *Tache1(void *arg) {
    int i = 0;
    while (i < 5) { // Boucle d'exécution pour Tache1
        printf("Execution de Tache 1\n"); // Affichage de message
        sleep(1); // Pause d'une seconde
        i++; // Incrémentation du compteur
    }
    return NULL; // La fonction renvoie NULL à la fin de son exécution
}

// Fonction exécutée par le deuxième thread
void *Tache2(void *arg) {
    int j = 0;
    while (j < 3) { // Boucle d'exécution pour Tache2
        printf("Execution de Tache 2\n"); // Affichage de message
        sleep(2); // Pause de deux secondes
        j++; // Incrémentation du compteur
    }
    return NULL; // La fonction renvoie NULL à la fin de son exécution
}

//Test 1
int main(int argc, char *argv[]) {
    pthread_t thread1, thread2; // Déclaration de deux variables de type pthread_t pour stocker les identifiants des threads
    pthread_create(&thread1, NULL, Tache1, NULL); // Création du premier thread exécutant la fonction Tache1
    pthread_create(&thread2, NULL, Tache2, NULL); // Création du deuxième thread exécutant la fonction Tache2
    pthread_join(thread1, NULL); // Attente de la fin du premier thread
    pthread_join(thread2, NULL); // Attente de la fin du deuxième thread
    return EXIT_SUCCESS; // Retourne une valeur de succès à la fin du programme
}

//Test 2
/*int main(int argc, char *argv[]) {
    pthread_t thread1, thread2; // Déclaration de deux variables de type pthread_t pour stocker les identifiants des threads
    pthread_create(&thread1, NULL, Tache1, NULL); // Création du premier thread exécutant la fonction Tache1
    pthread_join(thread1, NULL); // Attente de la fin du premier thread avant de créer le deuxième thread
    pthread_create(&thread2, NULL, Tache2, NULL); // Création du deuxième thread exécutant la fonction Tache2
    pthread_join(thread2, NULL); // Attente de la fin du deuxième thread
    return EXIT_SUCCESS; // Retourne une valeur de succès à la fin du programme
}
*/


