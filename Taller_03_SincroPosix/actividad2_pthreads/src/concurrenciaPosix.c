/********************************************************************************************
                         Pontificia Universidad Javeriana
Autores: Juliana Aguirre Ballesteros 
         Juan Carlos Santamaria Orjuela
Materia: sistemas operativos
Profesor: j. corredor
Taller 03 Posix Semáforos

Descripcion:
Este programa lee desde un fichero de texto una cantidad de números enteros y calcula
el valor máximo usando hilos POSIX. El usuario indica por línea de comandos
el nombre del fichero y la cantidad de hilos a usar. El vector con los datos se reparte
en varios segmentos, y cada hilo busca el máximo parcial de su segmento. Al final, el
programa reúne los resultados parciales y obtiene el máximo global.

Se controla la memoria reservada y la creación de hilos, y si ocurre algún error se muestra
un mensaje claro y se termina el programa. Este ejemplo sirve para entender cómo repartir
trabajo entre hilos, cómo pasar argumentos a cada hilo y cómo combinar los resultados
después de esperar a que todos terminen.

Objetivos:
- leer datos enteros desde un fichero de forma sencilla.
- repartir un vector en segmentos y asignarlos a varios hilos.
- usar hilos POSIX (pthreads) para buscar máximos parciales en paralelo.
- combinar los resultados parciales para obtener el máximo global.
- manejar errores de lectura, reserva de memoria y creación de hilos.
********************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// estructura que almacena la parte del vector que trabajará cada hilo
struct argHilos{
        int inicio;      // posición inicial del segmento
        int fin;         // posición final del segmento
        int *vector;     // puntero al vector completo de datos
        int maxparcial;  // resultado máximo parcial encontrado por el hilo
};

typedef struct argHilos param_H;

// función que ejecuta cada hilo para buscar el máximo en su rango
void *buscarMax(void *parametro){
        param_H *argumentos = (param_H *)parametro;  // convierte el puntero genérico al tipo de argumentos

        // inicia el máximo parcial con el primer elemento de su segmento
        argumentos->maxparcial = argumentos->vector[argumentos->inicio];

        // recorre el resto de posiciones del segmento buscando el valor mayor
        for (int i = argumentos->inicio + 1; i < argumentos->fin; i++) {
                if (argumentos->vector[i] > argumentos->maxparcial)
                        argumentos->maxparcial = argumentos->vector[i];
        }

        pthread_exit(0);      // termina el hilo explicitamente
        return NULL;          // valor de retorno estándar para función de hilo
}

// función que coordina los hilos para obtener el máximo de todo el vector
int maximoValor(int *vec, int n, int nhilos) {
        // controla casos de entrada inválida o límites simples
        if (n <= 0) return 0;
        if (nhilos < 1) nhilos = 1;
        if (nhilos > n) nhilos = n;

        // reserva memoria para los identificadores de hilos y sus argumentos
        pthread_t *ths = (pthread_t *)malloc(sizeof(pthread_t) * nhilos);
        param_H   *args = (param_H   *)malloc(sizeof(param_H)   * nhilos);
        if (!ths || !args) {
            // si hay problema de memoria, libera lo que se haya reservado y avisa
                free(ths); free(args);
                fprintf(stderr, "Memoria insuficiente\n");
                return 0;
        }

        // calcula el tamaño base de cada segmento y el sobrante
        int base = n / nhilos;
        int rem  = n % nhilos;
        int cursor = 0;       // posición actual en el vector para repartir tramos

        // crea los hilos y asigna a cada uno un rango del vector
        for (int t = 0; t < nhilos; t++) {
                int tam = base + (t < rem ? 1 : 0);  // algunos hilos reciben un elemento extra
                args[t].inicio = cursor;            // inicio del segmento para el hilo t
                args[t].fin    = cursor + tam;      // final del segmento para el hilo t
                args[t].vector = vec;               // referencia al vector completo

                cursor += tam;                      // avanza el cursor para el siguiente hilo

                // crea el hilo que ejecutará la búsqueda del máximo parcial
                if (pthread_create(&ths[t], NULL, buscarMax, (void *)&args[t]) != 0) {

                        // si falla la creación de un hilo, espera los ya creados
                        for (int j = 0; j < t; j++) pthread_join(ths[j], NULL);
                        // calcula un máximo clásico secuencial como respaldo
                        int fallback = vec[0];
                        for (int k = 1; k < n; k++) if (vec[k] > fallback) fallback = vec[k];
                        free(ths); free(args);
                        return fallback;
                }
        }

        // espera a que todos los hilos terminen su trabajo
        for (int t = 0; t < nhilos; t++) pthread_join(ths[t], NULL);

        // toma el máximo parcial del primer hilo como referencia
        int maximo = args[0].maxparcial;
        // compara con los máximos parciales del resto de hilos para sacar el máximo global
        for (int t = 1; t < nhilos; t++)
                if (args[t].maxparcial > maximo) maximo = args[t].maxparcial;

        // libera la memoria usada para hilos y argumentos
        free(ths);
        free(args);
        return maximo;    // devuelve el valor máximo encontrado en todo el vector
}

int main(int argc, char *argv[]) {
        FILE *fichero;         // fichero desde donde se leen los datos
        int n, nhilos, i;      // n: tamaño del vector, nhilos: número de hilos
        int *vec;              // puntero al vector de enteros
        int ret, maximo;       // ret: control de lecturas, maximo: resultado final

        // comprueba que se pasen exactamente 2 argumentos: fichero y número de hilos
        if (argc!=3) {
                fprintf(stderr, "Error en número de argumentos \n");
                exit(-1);
        }

        // intenta abrir el fichero en modo lectura
        fichero = fopen(argv[1], "r");
        if (fichero == NULL) {
                perror("No se puede abrir fichero");  // muestra error si no lo logra
                exit(-2);
        }

        // lee el tamaño del vector desde el fichero
        ret = fscanf(fichero, "%d", &n);
        if (ret !=1) {
                fprintf(stderr, "No se puede leer tamaño\n");
                fclose(fichero);
                exit(-3);
        }

        // convierte el segundo argumento en número de hilos
        nhilos = atoi(argv[2]);
        // reserva memoria para el vector de tamaño n
        vec = (int *)malloc(sizeof(int) * n);
        if (!vec) {
                fclose(fichero);
                fprintf(stderr, "No se pudo reservar memoria para el vector\n");
                exit(-4);
        }

        // lee los n valores del fichero y los guarda en el vector
        for (i=0; i!=n; ++i) {
                ret = fscanf(fichero, "%d", &vec[i]);
                if (ret !=1) {
                        fprintf(stderr, "No se puede leer elemento nro %d\n", i);
                        fclose(fichero);
                        free(vec);
                        exit(-5);
                }
        }

        // llama a la función que usa hilos para buscar el máximo del vector
        maximo = maximoValor(vec, n, nhilos);
        printf("Máximo: %d\n", maximo);     // muestra el máximo encontrado

        // cierra el fichero y libera la memoria del vector
        fclose(fichero);
        free(vec);
        return 0;                        
}
