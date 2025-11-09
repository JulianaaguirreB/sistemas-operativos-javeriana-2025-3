/*#######################################################################################
#* Pontificia Universidad Javeriana
#* Materia: Sistemas Operativos
#* Profesor: J. Corredor
#*Tema: Taller de Evaluación de Rendimiento
#* Autores: Juliana Aguirre Ballesteros, Juan Carlos Santamaría Orjuela
#* Programa:
#*      Multiplicación de Matrices algoritmo clásico
#* Archivo: mmClasicaSerie.c
#* OBJETIVOS :
#*  - Implementar la multiplicación de matrices cuadradas sin paralelismo (1 solo hilo).
#*  - Usar este programa como línea base para comparar rendimiento con las versiones paralelas.
#*  - Medir el tiempo total en microsegundos usando las funciones de medición comunes.
#*  - Aceptar el tamaño de la matriz (N) desde la línea de comandos.
#*  - Mantener el formato de salida compatible con lanzador.pl (última línea = tiempo).
######################################################################################*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include "mmOpenMP.h"

// esta función realiza la multiplicación clásica de matrices 
// esta función recorre A por filas y B por columnas, acumulando el producto en C
static void mm(const double *A, const double *B, double *C, int N) {
    for (int i = 0; i < N; ++i) {              // este bucle recorre las filas de A
        for (int j = 0; j < N; ++j) {          // este bucle recorre las columnas de B
            double s = 0.0;                    // esta variable acumula el resultado parcial
            for (int k = 0; k < N; ++k)        // este bucle interno realiza el producto punto
                s += A[i*N + k] * B[k*N + j];  // esta línea realiza la multiplicación y suma
            C[i*N + j] = s;                    // esta línea guarda el resultado en C[i][j]
        }
    }
}

int main(int argc, char **argv) {
    // esta sección valida los argumentos de entrada (N)
    if (argc < 2) { 
        fprintf(stderr, "Uso: %s N [hilos_ignorado]\n", argv[0]); 
        return 1; 
    }
    int N = atoi(argv[1]);                     // esta variable guarda el tamaño de la matriz
    if (N <= 0) { 
        fprintf(stderr, "N inválido\n"); 
        return 1; 
    }

    // esta parte reserva memoria dinámica para A, B y C
    double *A = (double*)calloc((size_t)N*N, sizeof(double));
    double *B = (double*)calloc((size_t)N*N, sizeof(double));
    double *C = (double*)calloc((size_t)N*N, sizeof(double));

    // esta validación verifica que la memoria fue asignada correctamente
    if (!A || !B || !C) { 
        fprintf(stderr, "Fallo al reservar memoria\n"); 
        free(A); free(B); free(C); 
        return 1; 
    }

    // esta llamada llena las matrices A y B con valores aleatorios
    iniMatrix(A, B, N);

    // estas llamadas miden el tiempo de ejecución de la multiplicación
    InicioMuestra(); 
    mm(A, B, C, N); 
    FinMuestra();

    // esta sección libera la memoria reservada
    free(A); 
    free(B); 
    free(C);

    return 0;
}
