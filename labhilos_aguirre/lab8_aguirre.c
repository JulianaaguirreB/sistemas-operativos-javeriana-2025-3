/***************************************************************************************************************************************************************
*Pontificia Universidad Javeriana
*Autor: Juliana Aguirre Ballesteros
*Materia: Sistemas Operativos
*Profesor: J.corredor
*Tema: Comunicación entre hilos usando variables de condición y mutex
*
*Descripción:
*Programa que demuestra la sincronización entre hilos mediante el uso de mutex y variables de condición.
*Se crean dos hilos: uno que espera una señal que reportara y otro que cambia un valor y envía la notificación esta notificara.  
*El hilo reportar permanece bloqueado hasta que el hilo *asignar* modifica la variable compartida y envía una señal de aviso.  
*Esto muestra cómo coordinar la ejecución entre hilos para evitar problemas de concurrencia y asegurar que las operaciones se realicen en el orden correcto.
******************************************************************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>   

pthread_cond_t var_cond = PTHREAD_COND_INITIALIZER;   // Variable de condición para sincronizar hilos
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;    // Mutex para proteger el acceso a las variables compartidas
int valor = 100;                                     // Variable compartida entre hilos
bool notificar = false;                              // Bandera para indicar cuándo enviar la señal

// Función que espera una señal antes de continuar
void *reportar(void *nousado){
    pthread_mutex_lock(&mutex);                                 // Bloquea el acceso a las variables compartidas
    printf("Antes de la señal, el valor es: %d\n", valor);      // Muestra el valor inicial antes de la señal

    while(!notificar){                                          // Espera hasta que notificar sea verdadero
        pthread_cond_wait(&var_cond, &mutex);                   // Espera la señal del otro hilo
    }

    printf("Después de la señal, el valor es: %d\n", valor);    // Muestra el valor después de recibir la señal

    pthread_mutex_unlock(&mutex);                               // Libera el mutex
    return NULL;                                                // El hilo termina sin devolver valor
}

// Función que modifica el valor y envía una señal al otro hilo
void *asignar(void *nousado){
    sleep(1);                                                   // Espera un segundo para simular trabajo previo
    pthread_mutex_lock(&mutex);                                 // Bloquea las variables compartidas
    valor = 20;                                                 // Cambia el valor compartido
    notificar = true;                                           // Activa la bandera para notificar al otro hilo
    pthread_cond_signal(&var_cond);                             // Envía la señal a reportar
    pthread_mutex_unlock(&mutex);                               // Libera el mutex
    return NULL;                                                // El hilo termina sin devolver valor
}

// Función principal que crea los hilos y espera su finalización
int main(int argc, char *argv[]){
    pthread_t reporte, asigne;                                  // Identificadores de los hilos

    pthread_create(&reporte, NULL, reportar, NULL);             // Crea el hilo que esperará la señal
    pthread_create(&asigne, NULL, asignar, NULL);               // Crea el hilo que enviará la señal

    void *nousado;                                              // Puntero para recibir valores de salida 
    pthread_join(reporte, &nousado);                            // Espera que reportar termine
    pthread_join(asigne, &nousado);                             // Espera que asignar termine

    return 0;                                                 
}
