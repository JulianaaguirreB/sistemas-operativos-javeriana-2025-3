/********************************************************************************************
                         Pontificia Universidad Javeriana
Autores: Juliana Aguirre Ballesteros 
         Juan Carlos Santamaria Orjuela
Materia: sistemas operativos
Profesor: j. corredor
Taller 03 Posix Semáforos

Descripcion:
Este programa muestra un ejemplo de concurrencia usando hilos POSIX (pthreads) con
un esquema de productor–consumidor dentro del mismo proceso. Se simulan varios
hilos productores que generan líneas de texto y las guardan en un conjunto de
búferes en memoria. Al mismo tiempo, un hilo especial llamado spooler se encarga
de leer esas líneas del búfer y mostrarlas por pantalla.

Para coordinar el acceso al arreglo de búferes se usan un mutex y dos variables
de condición. El mutex protege las variables compartidas para que solo un hilo
las modifique a la vez. Las condiciones permiten que los hilos esperen de forma
bloqueante cuando no hay espacio para escribir o cuando no hay líneas nuevas
para imprimir. Así se evita que los hilos consuman CPU haciendo ciclos vacíos.

Objetivos:
- ilustrar el uso de hilos POSIX en un problema productor–consumidor.
- usar un mutex para proteger secciones críticas con variables compartidas.
- emplear variables de condición para bloquear y despertar hilos al compartir datos.
- manejar un grupo de hilos productores y un hilo spooler que imprime en pantalla.
- practicar la sincronización básica entre hilos dentro de un mismo proceso.
********************************************************************************************/

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>

#ifndef MAX_BUFFERS
#define MAX_BUFFERS 8
#endif

// arreglo de búferes donde cada posición guarda una línea de texto
char buf [MAX_BUFFERS] [100];
// índice donde el siguiente productor escribirá
int buffer_index;
// índice desde donde el spooler leerá la siguiente línea
int buffer_print_index;

// mutex que protege el acceso a los índices, contadores y a los búferes
pthread_mutex_t buf_mutex = PTHREAD_MUTEX_INITIALIZER;
// condición para despertar productores cuando haya espacio disponible
pthread_cond_t buf_cond = PTHREAD_COND_INITIALIZER;
// condición para despertar al spooler cuando haya líneas listas para imprimir
pthread_cond_t spool_cond = PTHREAD_COND_INITIALIZER;
// cuenta cuántos búferes están libres para que los productores escriban
int buffers_available = MAX_BUFFERS;
// cuenta cuántas líneas hay pendientes por imprimir
int lines_to_print = 0;

// función que ejecutan los hilos productores
void *producer (void *arg);
// función que ejecuta el hilo spooler (consumidor de líneas)
void *spooler (void *arg);

int main (int argc, char **argv){
    pthread_t tid_producer [10], tid_spooler;  // arreglo de hilos productores y un hilo spooler
    int i, r;

    buffer_index = buffer_print_index = 0;     // inicializa índices de escritura y lectura

    // crea el hilo spooler que estará esperando líneas para imprimir
    if ((r = pthread_create (&tid_spooler, NULL, spooler, NULL)) != 0) {
        fprintf (stderr, "Error = %d (%s)\n", r, strerror (r)); exit (1);
    }

    int thread_no [10];                        // arreglo para identificar cada hilo productor
    for (i = 0; i < 10; i++) {
        thread_no [i] = i;                    // asigna un id simple al hilo
        // crea cada hilo productor, pasando su id como parámetro
        if ((r = pthread_create (&tid_producer [i], NULL, producer, (void *) &thread_no [i])) != 0) {
            fprintf (stderr, "Error = %d (%s)\n", r, strerror (r)); exit (1);
        }
    }

    // espera a que todos los hilos productores terminen
    for (i = 0; i < 10; i++)
        if ((r = pthread_join (tid_producer [i], NULL)) == -1) {
            fprintf (stderr, "Error = %d (%s)\n", r, strerror (r)); exit (1);
        }
    
    // mientras queden líneas por imprimir, espera un poco
    while (lines_to_print) sleep (1);
    // cuando ya no hay líneas, cancela el hilo spooler
    if ((r = pthread_cancel (tid_spooler)) != 0) {
        fprintf (stderr, "Error = %d (%s)\n", r, strerror (r)); exit (1);
    }

    // no se hace join del spooler para no cambiar el flujo original
    exit (0);
}

void *producer (void *arg){
    int i, r;
    int my_id = *((int *) arg);   // id del hilo productor
    int count = 0;                // contador de mensajes producidos por este hilo

    // cada productor genera 10 líneas de texto
    for (i = 0; i < 10; i++) {

        // entra a la sección crítica protegida con el mutex
        if ((r = pthread_mutex_lock (&buf_mutex)) != 0) {
            fprintf (stderr, "Error = %d (%s)\n", r, strerror (r)); exit (1);
        }
            // mientras no haya búferes libres, espera en la condición
            while (!buffers_available) 
                pthread_cond_wait (&buf_cond, &buf_mutex);

            // guarda la posición actual de escritura y la avanza
            int j = buffer_index;
            buffer_index++;
            if (buffer_index == MAX_BUFFERS)
                buffer_index = 0;     // vuelve al inicio en forma circular
            buffers_available--;      // reduce el número de espacios libres

            // escribe el mensaje en el búfer elegido
            sprintf (buf [j], "Thread %d: %d\n", my_id, ++count);
            lines_to_print++;         // aumenta la cantidad de líneas pendientes

            // avisa al spooler que ya hay una línea lista para imprimir
            pthread_cond_signal (&spool_cond);

        // sale de la sección crítica liberando el mutex
        if ((r = pthread_mutex_unlock (&buf_mutex)) != 0) {
            fprintf (stderr, "Error = %d (%s)\n", r, strerror (r)); exit (1);
        }
    
        sleep (1);                    // pausa para espaciar la producción
    }

    // salida limpia del hilo productor
    return NULL;
}

void *spooler (void *arg){
    int r;

    while (1) {  // lazo infinito, el hilo se cancela desde main
        // entra a la sección crítica para revisar líneas pendientes
        if ((r = pthread_mutex_lock (&buf_mutex)) != 0) {
            fprintf (stderr, "Error = %d (%s)\n", r, strerror (r)); exit (1);
        }
            // si no hay líneas para imprimir, espera en la condición
            while (!lines_to_print) 
                pthread_cond_wait (&spool_cond, &buf_mutex);

            // imprime la línea en la posición actual del búfer
            printf ("%s", buf [buffer_print_index]);
            fflush(stdout); // asegura que la salida se vea inmediatamente
            lines_to_print--;           // reduce el contador de líneas pendientes

            // avanza el índice de impresión de forma circular
            buffer_print_index++;
            if (buffer_print_index == MAX_BUFFERS)
               buffer_print_index = 0;

            // se ha liberado un búfer, así que hay un espacio vacío más
            buffers_available++;
            // despierta a los productores que puedan estar esperando espacio
            pthread_cond_signal (&buf_cond);

        // libera el mutex y sale de la sección crítica
        if ((r = pthread_mutex_unlock (&buf_mutex)) != 0) {
            fprintf (stderr, "Error = %d (%s)\n", r, strerror (r)); exit (1);
        }

    }

    // valor de retorno estándar, aunque no se alcanza por el bucle infinito
    return NULL;
}
