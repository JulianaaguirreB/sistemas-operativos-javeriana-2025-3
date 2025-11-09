/***************************************************************************************
*                               Pontificia Universidad Javeriana                        
* Autor: Juliana Aguirre Ballesteros                                                    
* Materia: Sistemas Operativos                                                          
* Laboratorio: OpenMP                                                                   
* Profesor: J. Corredor                                                                                                                                 
* Descripcion:                                                                          
*   Este programa calcula la sumatoria de la funcion seno aplicando paralelismo con     
*   OpenMP. 
*   El usuario ingresa la cantidad de hilos y el numero de repeticiones del     
*   ciclo for. 
*   Cada iteracion realiza una sumatoria parcial y el resultado total se     
*   obtiene mediante la clausula reduction.
*   Adicionalmente se mide el tiempo total de ejecucion utilizando la funcion omp_get_wtime().                                 
* Objetivo:                                                                             
*   - Implementar una region paralela que ejecute el calculo de una sumatoria.          
*   - Utilizar la clausula 'reduction' para combinar los resultados parciales.          
*   - Calcular e imprimir el tiempo total de ejecucion segun el numero de hilos.        
****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

/* Funcion que realiza la suma de senos en un rango triangular */
static inline double f_tramo(int i) {
    int start  = i * (i + 1) / 2;
    int finish = start + i;
    double acc = 0.0;
    for (int j = start; j <= finish; ++j) {
        acc += sin((double)j);
    }
    return acc;
}

int main(int argc, char *argv[]) {

    /* Validar argumentos de entrada */
    if (argc != 3) {
        fprintf(stderr, "Uso:\n\t%s numHilos numRepeticiones\n", argv[0]);
        return 1;
    }

    /* Leer numero de hilos y repeticiones */
    int numHilos = atoi(argv[1]);
    long long N  = atoll(argv[2]);

    if (numHilos <= 0 || N <= 0) {
        fprintf(stderr, "Argumentos invalidos: numHilos > 0 y numRepeticiones > 0.\n");
        return 1;
    }

    /* Fijar el numero de hilos a usar */
    omp_set_num_threads(numHilos);

    double sumatoria = 0.0;

    /* Medir tiempo de inicio */
    double t0 = omp_get_wtime();

    /* Region paralela con clausula reduction */
    #pragma omp parallel for reduction(+:sumatoria) schedule(static)
    for (long long i = 0; i < N; ++i) {
        sumatoria += f_tramo((int)i);
    }

    /* Medir tiempo final */
    double t1 = omp_get_wtime();
    double elapsed = t1 - t0;

    /* Mostrar resultados */
    printf("Hilos: %d | Repeticiones: %lld\n", numHilos, N);
    printf("Sumatoria seno: %.6f\n", sumatoria);
    printf("Tiempo total: %.6f s\n", elapsed);

    return 0;
}
