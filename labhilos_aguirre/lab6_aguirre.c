/*****************************************************************************************************************************
*Pontificia Universidad Javeriana
*Autor: Juliana Aguirre Ballesteros
*Materia: Sistemas Operativos
*Profesor: J.corredor
*Tema: Cálculo concurrente de suma de cuadrados con hilos POSIX
*
*Descripción:
*Programa que crea 20 hilos, cada uno calcula el cuadrado de un número del 1 al 20 y los suma en una variable global compartida. 
*Demuestra el uso básico de hilos POSIX y el paso de argumentos a través de punteros.
*******************************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>

int acumulado = 0;    //Variable global para acumular la suma de los cuadrados

//Función que calcula el cuadrado del número recibido
void *cuadrados(void *x){
    int xi = (intptr_t)x;           
    acumulado += xi * xi;           //Se suma el cuadrado del número al acumulado global
    return NULL;                    //El hilo termina su ejecución
}

int main(){
    pthread_t WorkersTh[20];        //Declaración del arreglo de 20 hilos

    for(int i = 0; i < 20; i++)     //Creación de los 20 hilos
        pthread_create(&WorkersTh[i], NULL, &cuadrados, (void *)(intptr_t)(i + 1));

    for(int i = 0; i < 20; i++){    //Esperar a que cada hilo termine
        void *acumulado;
        pthread_join(WorkersTh[i], &acumulado);
    }

    printf("Valor suma cuadrados = %d \n", (int) acumulado);   //Se muestra el resultado final
    return 0;
}
