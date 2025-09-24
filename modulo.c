/**************************************************************************************
 * Fecha: 11/09/2025
 * Autor: juliana aguirre ballesteros
 * Materia: Sistemas Operativos
 * Tema: Concurrencia
 * Objetivo: Hacer una metodología para la implementación de la multiplicación de matrices.
 * La idea principal, es construir paso a paso la implementación para hacer uso de la
 * biblioteca PTHREAD. Se implementa el Algoritmo Clásico de multiplicación de matrices, para
 * matrices cuadradas, es decir, la dimensión de filas es igual a la de columnas.
 * A continuación se describen los paso
 *  - Reserva de memoria
 *      - Creación de punteros para matrices del tipo doble
 *      - Asignación de memoria
 *      - Ingreso de argumentos de entrada (Dimensión matriz, número de hilos)
 *      - Validación argumentos de entrada
 *      - Inicializar las matrices
 *      - Imprimir las matrices
 *      - Función para inicializar las matrices
 *      - Función para imprimir las matrices
 *      - Algoritmo clásico de multiplicación matrices
 *  - Se verifica el resultado
 *      - Función para multiplicación las matrices
 *      - Declaración vector de hilos
 *      - Creación de hilos según tamaño de vector de hilos
 *      - Crear estructura de datos que encapsule los argumentos de entrada de la función MM
 * Implementación de paralelismo: resolución de la multiplicación de matrices
 *  - Se crea el vector de hilos
 *  - Se tiene pendiente la exclusión de los hilos
 *  - Se pasa a globales las matrices
 *  - Encapsular los datos para enviarlos a la función MxM
 *  - Se desencapsulan los datos dentro de la función MxM (descomprimen)
*************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "modulo.h"

// Variables globales para tiempos
struct timeval ini, fin;

//Funcion para medir tiempo inicial
void InicioMuestra(){
	gettimeofday(&ini, (void *)0);
}
//Funcion para medir tiempo final y luego muestra el resultado en microsegundos
void FinMuestra(){
	gettimeofday(&fin, (void *)0);
	fin.tv_usec -= ini.tv_usec;
	fin.tv_sec -= ini.tv_sec;
	double tiempo = (double) (fin.tv_sec*1000000 + fin.tv_usec);
	printf("%9.0f \n", tiempo);
}

//Funcion que inicia la matriz y va a llenar las matrices con valores de prueba
void iniMatriz(int n, double *m1, double *m2){
   	for(int i=0; i<n*n; i++){
	        m1[i] = i*2.3 + 1.3;
	        m2[i] = i*2.3;
	}
};
//Funcion para imprimir la matriz en pantalla
void imprMatrices(int n, double *matriz){
    if(n<9){
        printf("\n#######################################################\n");
   	for(int i=0; i<n*n; i++){
                if(i%n==0) printf("\n");
	        printf(" %f ", matriz[i]);
   }
 printf("\n");
    } else {
        printf("\n#######################################################\n");
    }
};
// Algoritmo de multiplicación de matrices cuadradas
void multiMatrizClasica(double *m1, double *m2, double *m3, int n){
 for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            double sumaTemp, *pA, *pB;
            sumaTemp = 0.0;
            pA = m1 + i*n;
            pB = m2 + j;
            for(int k=0; k<n; k++, pA++, pB+=n){
                sumaTemp += *pA * *pB;
            }
            m3[j+i*n] = sumaTemp;
        }
    }
};
