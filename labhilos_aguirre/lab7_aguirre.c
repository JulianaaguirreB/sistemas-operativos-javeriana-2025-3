/***************************************************************************************************************************************************************
*Pontificia Universidad Javeriana
*Autor: Juliana Aguirre Ballesteros
*Materia: Sistemas Operativos
*Profesor: J.corredor
*Tema: Cálculo de suma de cuadrados con hilos y exclusión mutua
*
*Descripción:
*Programa que crea 20 hilos concurrentes, donde cada uno calcula el cuadrado de un número entero y lo suma a una variable global compartida llamada acumulado.
*El objetivo es demostrar el uso de hilos para realizar tareas en paralelo y cómo sincronizar su ejecución cuando comparten recursos comunes.
*Para evitar errores de concurrencia y garantizar que los resultados sean correctos, se implementa un mecanismo de exclusión mutua utilizando un mutex.
*Al finalizar, el programa muestra el resultado total de la suma de los cuadrados de los primeros 20 números naturales.
**************************************************************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

int acumulado = 0;                                  // Variable global 
pthread_mutex_t bloqueoCC = PTHREAD_MUTEX_INITIALIZER; // Mutex para evitar condición de carrera

// Función que calcula el cuadrado del número recibido y lo suma a acumulado
void *cuadrados(void *x){
    int xi = (intptr_t)x;                           // Se castea el argumento al tipo entero

    pthread_mutex_lock(&bloqueoCC);                 // Bloqueo de la sección crítica
    acumulado += xi * xi;                           // Suma del cuadrado al acumulado
    pthread_mutex_unlock(&bloqueoCC);               // Desbloqueo de la sección crítica

    return NULL;                                    // Fin del hilo
}

// Función principal que crea los hilos y muestra el resultado final
int main(){
    pthread_t WorkersTh[20];                        // Arreglo de 20 hilos

    for(int i = 0; i < 20; i++)                     // Creación de los hilos
        pthread_create(&WorkersTh[i], NULL, &cuadrados, (void *)(intptr_t)(i + 1));

    for(int i = 0; i < 20; i++){                    // Esperar a que cada hilo termine
        void *acumulado;
        pthread_join(WorkersTh[i], &acumulado);
    }

    printf("Valor suma cuadrados = %d \n", (int) acumulado);  // Muestra el resultado final

    return 0;                                       
}
