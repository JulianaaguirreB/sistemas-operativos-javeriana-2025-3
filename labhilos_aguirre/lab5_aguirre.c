/******************************************************************
*Pontificia Universidad Javeriana
*Autor: Juliana Aguirre Ballesteros
*Materia: Sistemas Operativos
*Profesor: J.corredor
*Tema: Creación y control de hilos con mutex
*
*Descripción:
*Programa que crea tres hilos que simulan trabajos diferentes. 
*Cada hilo incrementa un contador global de forma segura usando un mutex.
*Muestra cuándo inicia y termina su trabajo, y realiza un bucle largo para simular una tarea pesada.
*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h> 

pthread_t tid[3];               // Arreglo con identificadores de los tres hilos
int counter;                    // Variable global compartida
pthread_mutex_t lock;           // Mutex para proteger el acceso a counter

// Función que ejecutará cada hilo y incrementa el contador
void *compute(void *arg)
{
    unsigned long i = 0;                             // Variable para el bucle 

    pthread_mutex_lock(&lock);                        // Bloquea el acceso al contador
    counter += 1;                                     // Incrementa el contador global
    printf("\nJob %d has started\n", counter);        
    pthread_mutex_unlock(&lock);                      // Libera el acceso al contador

    for(i = 0; i < 0xFFFFFFFF; i++);                  // Simula una tarea pesada

    printf("\nJob %d has finished\n", counter);       
    return NULL;                                      // El hilo termina sin devolver nada
}

// Función principal que crea los tres hilos y espera que terminen
int main(void)
{
    int i = 0;                                        // Contador de hilos
    int error;                                        //verificar errores

    while(i < 3)                                      // Bucle para crear los hilos
    {
        error = pthread_create(&(tid[i]), NULL, &compute, NULL); // Crea un hilo
        if (error != 0)                                            // Verifica si hubo error
            printf("\nThread can't be created: [%s]", strerror(error)); 
        i++;
    }

    pthread_join(tid[0], NULL);                       // Espera que el hilo 1 termine
    pthread_join(tid[1], NULL);                       // Espera que el hilo 2 termine
    pthread_join(tid[2], NULL);                       // Espera que el hilo 3 termine

    pthread_mutex_destroy(&lock);                     // Libera el mutex al finalizar

    return 0;                                         
}
