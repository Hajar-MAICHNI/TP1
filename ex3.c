#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Fonction ex�cut�e par le premier thread
void *Tache1(void *arg) {
    int i = 0;
    while (i < 5) { // Boucle d'ex�cution pour Tache1
        printf("Execution de Tache 1\n"); // Affichage de message
        sleep(1); // Pause d'une seconde
        i++; // Incr�mentation du compteur
    }
    return NULL; // La fonction renvoie NULL � la fin de son ex�cution
}

// Fonction ex�cut�e par le deuxi�me thread
void *Tache2(void *arg) {
    int j = 0;
    while (j < 3) { // Boucle d'ex�cution pour Tache2
        printf("Execution de Tache 2\n"); // Affichage de message
        sleep(2); // Pause de deux secondes
        j++; // Incr�mentation du compteur
    }
    return NULL; // La fonction renvoie NULL � la fin de son ex�cution
}

//Test 1
int main(int argc, char *argv[]) {
    pthread_t thread1, thread2; // D�claration de deux variables de type pthread_t pour stocker les identifiants des threads
    pthread_create(&thread1, NULL, Tache1, NULL); // Cr�ation du premier thread ex�cutant la fonction Tache1
    pthread_create(&thread2, NULL, Tache2, NULL); // Cr�ation du deuxi�me thread ex�cutant la fonction Tache2
    pthread_join(thread1, NULL); // Attente de la fin du premier thread
    pthread_join(thread2, NULL); // Attente de la fin du deuxi�me thread
    return EXIT_SUCCESS; // Retourne une valeur de succ�s � la fin du programme
}

//Test 2
/*int main(int argc, char *argv[]) {
    pthread_t thread1, thread2; // D�claration de deux variables de type pthread_t pour stocker les identifiants des threads
    pthread_create(&thread1, NULL, Tache1, NULL); // Cr�ation du premier thread ex�cutant la fonction Tache1
    pthread_join(thread1, NULL); // Attente de la fin du premier thread avant de cr�er le deuxi�me thread
    pthread_create(&thread2, NULL, Tache2, NULL); // Cr�ation du deuxi�me thread ex�cutant la fonction Tache2
    pthread_join(thread2, NULL); // Attente de la fin du deuxi�me thread
    return EXIT_SUCCESS; // Retourne une valeur de succ�s � la fin du programme
}
*/


