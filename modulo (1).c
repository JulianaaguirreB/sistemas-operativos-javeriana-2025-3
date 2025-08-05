/************************************************************************************************
nombre: juliana aguirre ballesteros
asignatura: sistemas operativos
docente: j.corredor, PhD
objetivos: puntero en c
fecha: 31 de julio
*********************************************************************************************/

#include "modulo.h"    // Incluir el archivo de cabecera con las declaraciones de funciones
#include <stdio.h>      // Librería para funciones estándar de entrada y salida
#include <stdlib.h>     // Librería para funciones como malloc, rand, etc.
#include <time.h>       // Librería para funciones relacionadas con el tiempo (aunque no se utiliza directamente aquí)

/**
 * Imprime un mensaje de bienvenida y encabezado para el calculador de masa corporal.
 * return Devuelve 0 al finalizar la función.
 */
int printFuncion() {
  printf("***************************************");
  printf("\n Calculador de masa corporal \n");
  printf("*************************************** \n");
  return 0;  // Retorna 0 al finalizar la función
}

/**
 * Calcula el índice de masa corporal (IMC) usando la fórmula: IMC = masa / (altura * altura)
 * para masa La masa corporal en kilogramos.
 * para altura La altura en metros.
 * return El valor calculado del IMC.
 */
float imcFuncion(float masa, float altura) {
  
// La fórmula del IMC es masa / (altura * altura)

  float IMC = masa / (altura * altura);
  return IMC;  // Retorna el valor del IMC calculado
}

/**
 * Imprime una matriz de tamaño NxN.
 * para mA La matriz a imprimir.
 * para N El tamaño de la matriz (N x N).
 */
void impMatrix(float *mA, int N) {
  
// Recorre las filas de la matriz

  for (int i = 0; i < N; i++) {

    // Recorre las columnas de la matriz

    for (int j = 0; j < N; j++) {

      // Imprime el valor en la posición (i, j) de la matriz

      printf(" %f ", mA[i * N + j]);
    }
    printf(" \n");  // Nueva línea al final de cada fila
  }
}

/**
 * Realiza la multiplicación de dos matrices mA y mB y retorna el resultado.
 * para N El tamaño de las matrices (NxN).
 * para mA La primera matriz para multiplicar.
 * para mB La segunda matriz para multiplicar.
 * return Una nueva matriz resultante de la multiplicación de mA y mB.
 */
float *matrixMult(int N, float *mA, float *mB) {
  
// Asigna memoria dinámica para la matriz resultado mC de tamaño N x N

  float *mC = (float *)malloc(N * N * 4);  // Cada float ocupa 4 bytes
  
  // Recorre las filas de la matriz mA

  for (int i = 0; i < N; i++) {

    // Recorre las columnas de la matriz mB

    for (int j = 0; j < N; j++) {

      float suma = 0;  // Variable para almacenar la suma de productos

      // Realiza la multiplicación de matrices

      for (int k = 0; k < N; k++) {
        suma += mA[i * N + k] * mB[k * N + j];  // Producto de A[i][k] y B[k][j]
      }
      mC[i * N + j] = suma;  // Almacena el resultado en la posición (i, j) de la matriz resultante
    }
  }
  
  return mC;  // Retorna la matriz resultante
}

/**
 * Llena las matrices mA y mB de tamaño NxN con valores aleatorios.
 * Los valores generados están en el rango de 0 a 12.1 (multiplicando un valor aleatorio por 0.121).
 * para N El tamaño de las matrices (NxN).
 * para mA La primera matriz a llenar con valores aleatorios.
 * para mB La segunda matriz a llenar con valores aleatorios.
 */
void llenarMatriz(int N, float *mA, float *mB) {
  // Recorre las filas de las matrices
  for (int i = 0; i < N; i++) {
    // Recorre las columnas de las matrices
    for (int j = 0; j < N; j++) {
      
// Asigna un valor aleatorio a las matrices mA y mB
      mA[i * N + j] = rand() % 100 * 0.121;  // Genera un número aleatorio entre 0 y 12.1 para mA
      mB[i * N + j] = rand() % 100 * 0.121;  // Genera un número aleatorio entre 0 y 12.1 para mB
    }
  }
}

