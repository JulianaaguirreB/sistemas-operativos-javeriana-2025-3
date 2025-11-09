/*#######################################################################################
#* Pontificia Universidad Javeriana
#* Materia: Sistemas Operativos
#* Profesor: J. Corredor
#*Tema: Taller de Evaluación de Rendimiento
#* Autores: Juliana Aguirre Ballesteros, Juan Carlos Santamaría Orjuela
#* Programa:
#*      Utilidades comunes para multiplicación de matrices
#* Archivo: mmOpenMP.c
#* OBJETIVOS :
#*  - Proveer funciones comunes para todos los programas: medir tiempo, imprimir matrices,
#*    y inicializar A y B con valores aleatorios.
#*  - Mantener una salida de tiempo en microsegundos compatible con el lanzador.pl.
#*  - Evitar duplicar código en las versiones Serie, OpenMP, Pthreads y Fork.
#######################################################################################*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "mmOpenMP.h"

struct timeval inicio, fin;

// esta función marca el instante inicial del cronómetro
void InicioMuestra(){
        gettimeofday(&inicio, (void *)0);
}

// esta función calcula e imprime el tiempo transcurrido desde InicioMuestra 
void FinMuestra(){
        gettimeofday(&fin, (void *)0);
        fin.tv_usec -= inicio.tv_usec;
        fin.tv_sec  -= inicio.tv_sec;
        double tiempo = (double) (fin.tv_sec*1000000 + fin.tv_usec);
        printf("%9.0f \n", tiempo);
}

// esta función imprime la matriz por consola solo si D < 9 
void impMatrix(double *matrix, int D){
        if(D < 9){
                printf("\n");
                for(int i=0; i<D*D; i++){
                        if(i%D==0) printf("\n");
                        printf("%.2f ", matrix[i]);
                }
                printf("\n**-----------------------------**\n");
        }
}

// esta función inicializa A y B con valores aleatorios en rangos acotados
// esta función recorre toda la memoria lineal de las matrices 
void iniMatrix(double *m1, double *m2, int D){
        for(int i=0; i<D*D; i++, m1++, m2++){
                *m1 = (double)rand()/RAND_MAX*(5.0-1.0);        // Valores entre 1 y 5
                *m2 = (double)rand()/RAND_MAX*(9.0-2.0);        // Valores entre 2 y 9
        }
}
