/*************************************************************************************************************************************************
*Pontificia Universidad Javeriana
*Autor: Juliana Aguirre Ballesteros
*Materia: Sistemas Operativos
*Profesor: J.corredor
*Tema: Uso de hilos con variable compartida y exclusión mutua (mutex)
*
*Descripción:
*Programa que crea varios hilos usando pthread. 
*Cada hilo muestra su número y su ID. 
*Además, se usa un mutex para controlar el acceso a una variable compartida y evitar conflictos cuando varios hilos la modifican al mismo tiempo.
******************************************************************************************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>

#define NTHREADS 10                                // Cantidad de hilos a crear
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER; // Inicializa el mutex
int counter = 0;                                   // Variable compartida entre los hilos

// Función que ejecutará cada hilo
void *thread_function(void *arg) {
    int i = *(int *)(arg);                                              // Guarda el número del hilo
    printf("Thread number: %d | Thread ID %ld\n", i, pthread_self());   // Muestra el número e ID del hilo
    pthread_mutex_lock(&mutex1);                                        // Bloquea el acceso a la variable compartida
    counter++;                                                          // Incrementa el contador
    pthread_mutex_unlock(&mutex1);                                      // Libera el acceso para otros hilos
}

// Función principal
void main() {
    pthread_t thread_id[NTHREADS];          // Arreglo para los identificadores de los hilos
    int i, j;                               // Variables de control

    for (i = 0; i < NTHREADS; i++) {        // Bucle para crear los hilos
        pthread_create(&thread_id[i], NULL, thread_function, &i); // Crea cada hilo
    }

    printf("Final counter value: %d\n", counter); // Muestra el valor final del contador
}