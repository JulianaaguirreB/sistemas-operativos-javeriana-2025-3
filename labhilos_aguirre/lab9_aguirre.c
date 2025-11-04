/***************************************************************************************************************************************************************
*Pontificia Universidad Javeriana
*Autor: Juliana Aguirre Ballesteros
*Materia: Sistemas Operativos
*Profesor: J.corredor
*Tema: Comunicación entre hilos con variables de condición y mutex
*
*Descripción:
*Este programa demuestra cómo sincronizar la ejecución entre dos hilos mediante el uso de un mutex y una variable de condición. 
*Se crean dos hilos: uno llamado “reportar”, que espera una señal para mostrar el valor de una variable compartida, y otro llamado “asignar”, 
*que modifica dicha variable y envía la señal correspondiente. El uso del mutex garantiza que solo un hilo acceda a la variable compartida a la vez, 
*mientras que la variable de condición permite que el hilo “reportar” permanezca en espera hasta recibir la notificación de “asignar”. 
*De esta forma, se evita la condición de carrera y se logra una coordinación precisa entre los hilos.
******************************************************************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

int valor = 100;                                   // Variable compartida entre los hilos
bool notificar = false;                            // Bandera que indica cuándo enviar la señal

pthread_mutex_t bloqueoCC = PTHREAD_MUTEX_INITIALIZER;   // Mutex para proteger la sección crítica
pthread_cond_t  condCC   = PTHREAD_COND_INITIALIZER;     // Variable de condición para sincronizar hilos

// Función del hilo que espera una señal antes de imprimir el valor
void *reportar(void *nousada){
    pthread_mutex_lock(&bloqueoCC);                      // Bloquea la sección crítica
    while(!notificar)                                   // Espera hasta que la bandera cambie a verdadero
        pthread_cond_wait(&condCC, &bloqueoCC);         // Espera la señal del hilo asignar
    printf("\n\tEl valor es: %d\n", valor);             // Imprime el valor una vez que se ha actualizado
    pthread_mutex_unlock(&bloqueoCC);                   // Libera el mutex
    return NULL;                                        // Termina el hilo sin devolver valor
}

// Función del hilo que modifica el valor y notifica al otro hilo
void *asignar(void *nousada){
    valor = 20;                                         // Modifica la variable compartida
    pthread_mutex_lock(&bloqueoCC);                     // Bloquea la sección crítica
    notificar = true;                                   // Cambia la bandera para indicar la actualización
    pthread_cond_signal(&condCC);                       // Envía la señal al hilo reportar
    pthread_mutex_unlock(&bloqueoCC);                   // Libera el mutex
    return NULL;                                        // Termina el hilo sin devolver valor
}

// Función principal que crea ambos hilos y espera su finalización
int main(){
    pthread_t reporte, asigne;                          // Identificadores de los hilos

    pthread_create(&reporte, NULL, &reportar, NULL);    // Crea el hilo que esperará la señal
    pthread_create(&asigne, NULL, &asignar, NULL);      // Crea el hilo que enviará la señal

    void *nousada;                                      // Variable para la sincronización final
    pthread_join(reporte, &nousada);                    // Espera que el hilo reportar termine
    pthread_join(asigne, &nousada);                     // Espera que el hilo asignar termine

    return 0;                                          
