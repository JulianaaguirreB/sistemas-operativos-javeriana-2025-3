/******************************************************************************
*Pontificia Universidad Javeriana
*Autor: Juliana Aguirre Ballesteros
*Materia: Sistemas Operativos
*Profesor:J.corredor
*Tema: Uso interfaz de creación de hilos PTHREAD
*
*Descripción:
*Programa que permite crear varios hilos según el número indicado por el usuario. 
*Cada hilo muestra su número de tarea por pantalla. 
*Esto demuestra cómo crear y ejecutar varios hilos en paralelo usando pthread.
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <pthread.h>

// Función que ejecutará cada hilo y imprime el número de tarea correspondiente.
static void *funcion(void *arg){
    int tarea = *(int*)arg;             // Guarda el número de tarea recibido como argumento
    printf("Tarea :- %d -\n", tarea);   // Muestra el número de tarea
    return NULL;                        // El hilo termina sin devolver nada
}

int main (int argc, char *argv[]){
    if (argc != 2){                                        // Si no se pasa el número de tareas como argumento
        printf("\t$ ./ejecutable NUM\n");                  // Muestra cómo ejecutar correctamente el programa
        exit(0);                                          
    }

    int N = atoi(argv[1]);                                 // Convierte el argumento a número entero
    int tareas[N];                                         // Arreglo para guardar los números de tarea
    pthread_t hilos[N];                                    // Arreglo para guardar los identificadores de hilos

    for (int i = 0; i < N; i++){                           // Bucle para crear cada hilo
        tareas[i] = i + 1;                                 // Asigna un número de tarea
        pthread_create(&hilos[i], NULL, funcion, &tareas[i]);  // Crea el hilo y le pasa su número de tarea
    }

    for (int i = 0; i < N; i++){                           // Bucle para esperar que todos los hilos terminen
        pthread_join(hilos[i], NULL);                      // Espera la finalización del hilo actual
    }

    return 0;                                           
}
