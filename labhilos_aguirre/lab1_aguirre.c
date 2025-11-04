/*************************************************************************************************************************************************
*Nombre: Juliana Aguirre Ballesteros
*Materia: Sistemas Operativos
*Universidad: Pontificia Universidad Javeriana
*Profesor: J.corredor
*
*Objetivo:
*Implementar un programa que use hilos para ejecutar funciones de manera concurrente,mostrando cómo dos hilos pueden correr al mismo tiempo.
*
*Funcionalidad:
*El programa crea dos hilos independientes.  
*Cada hilo imprime un mensaje distinto ("Thread 1" y "Thread 2").  
*Después, el programa principal espera a que ambos hilos terminen.
*Finalmente, muestra el resultado de la creación de los hilos.
*************************************************************************************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>

//Esta función será ejecutada por cada hilo y recibe un puntero que contiene un mensaje y lo imprime
//ptr,Apunta al mensaje que el hilo debe imprimir
void *print_message_function(void *ptr) {
    char *message; //// Variable para guardar el mensaje recibido
   message = (char *) ptr;         // Convertimos el puntero a tipo char
    printf("%s \n", message);       // Imprimimos el mensaje en pantalla
    return NULL;                    // El hilo no devuelve ningún valor
}

// Crea dos hilos que ejecutan la función print_message_function y luego espera que ambos terminen antes de finalizar el programa
int main() {
    pthread_t thread1, thread2;
    char *message1 = "Thread 1";
    char *message2 = "Thread 2";
    int iret1, iret2;

//Crear los dos hilos y asignarles la función que ejecutarán pthread_create()
    iret1 = pthread_create(&thread1, NULL, print_message_function, (void*) message1);
    iret2 = pthread_create(&thread2, NULL, print_message_function, (void*) message2);

    //Esperar a que ambos hilos terminen,esto evita que el programa principal finalice antes de que los hilos impriman sus mensajes
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
// Mostrar en pantalla el valor que devuelve la creación de cada hilo
    printf("Thread 1 returns: %d\n", iret1);
    printf("Thread 2 returns: %d\n", iret2);

    exit(0);
}
