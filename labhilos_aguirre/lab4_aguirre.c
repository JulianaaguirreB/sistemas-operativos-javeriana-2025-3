/*****************************************************************************************************************************************************
*Pontificia Universidad Javeriana
*Autor: Juliana Aguirre Ballesteros
*Materia: Sistemas Operativos
*Profesor: J.corredor
*Tema: Hilos con API POSIX
*
*Descripción:
*Programa que usa la API POSIX para crear dos hilos que trabajan con un contador compartido. 
*Uno de los hilos se detiene cuando el contador está en un rango específico, mientras que el otro continúa y reanuda el primero usando señales de condición.
*************************************************************************************************************************************************************/

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;       // Mutex para controlar el acceso al contador
pthread_mutex_t condition_mutex = PTHREAD_MUTEX_INITIALIZER;   // Mutex usado junto con la condición
pthread_cond_t condition_cond = PTHREAD_COND_INITIALIZER;      // Variable para sincronizar hilos

int count = 0;                                                 // Contador compartido entre los hilos
#define COUNT_DONE  15                                         // Valor final del contador
#define COUNT_HALT1 4                                          // Límite inferior del rango de pausa
#define COUNT_HALT2 11                                         // Límite superior del rango de pausa

// Función que incrementa el contador, pero se detiene cuando está entre COUNT_HALT1 y COUNT_HALT2
void *count01() {
    for(;;) {                                                  
        pthread_mutex_lock(&condition_mutex);                   // Bloquea el mutex de condición
        while(count >= COUNT_HALT1 && count <= COUNT_HALT2) {   // Si el contador está en el rango, espera
            pthread_cond_wait(&condition_cond, &condition_mutex);
        }
        pthread_mutex_unlock(&condition_mutex);                 // Desbloquea el mutex de condición

        pthread_mutex_lock(&count_mutex);                       // Bloquea el acceso al contador
        count++;                                                // Incrementa el contador
        printf("Counter value functionCount ==> 01 <==: %d\n", count);
        pthread_mutex_unlock(&count_mutex);                     // Libera el acceso

        if(count >= COUNT_DONE) return(NULL);                   // Si llega al valor final, termina el hilo
    }
}

// Función que incrementa el contador y envía señales cuando el otro hilo está detenido
void *count02() {
    for(;;) {
        pthread_mutex_lock(&condition_mutex);                   // Bloquea el mutex de condición
        if(count < COUNT_HALT1 || count > COUNT_HALT2) {        // Si el contador está fuera del rango, envía señal
            pthread_cond_signal(&condition_cond);
        }
        pthread_mutex_unlock(&condition_mutex);                 // Desbloquea el mutex de condición

        pthread_mutex_lock(&count_mutex);                       // Bloquea el contador
        count++;                                                // Incrementa el contador
        printf("Counter value functionCount ==> 02 <==: %d\n", count);
        pthread_mutex_unlock(&count_mutex);                     // Libera el acceso al contador

        if(count >= COUNT_DONE) return(NULL);                   // Si llega al valor final, termina el hilo
    }
}

// Función principal que crea y ejecuta los dos hilos
int main() {
    pthread_t thread1, thread2;                                 // Variables para los identificadores de hilos
    pthread_create(&thread1, NULL, &count01, NULL);             // Crea el primer hilo
    pthread_create(&thread2, NULL, &count02, NULL);             // Crea el segundo hilo
    pthread_join(thread1, NULL);                                // Espera que el hilo 1 termine
    pthread_join(thread2, NULL);                                // Espera que el hilo 2 termine
    exit(0);                                                   
}

#include <pthread.h>
