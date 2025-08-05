/*****************************************************************************
*                     Pontificia Universidad Javeriana
* ================================*=========================================
*
* Autor: Juliana aguirre ballesteros
* Materia: Sistemas Operativos
* Docente: J. Correrdor. PhD
* Objetivo: Puntero en c
* fecha: 31 de julio

******************************************************************************/


#ifndef _MODULO_H_  // Verifica si la constante _MODULO_H_ no está definida
#define _MODULO_H_  // Define la constante _MODULO_H_ para evitar inclusiones múltiples

#include <stdio.h>  // Incluir la librería estándar para operaciones de entrada/salida
#include <stdlib.h> // Incluir la librería estándar para operaciones como malloc, rand, etc.
#include <time.h>   // Incluir la librería para funciones relacionadas con el tiempo

/* Función que imprime un mensaje de bienvenida al programa.
 Retorna 0 al finalizar la ejecución de la función.*/
int printFuncion();

/*Función que calcula el índice de masa corporal (IMC).
Recibe la masa corporal en kg y la altura en metros.
Devuelve el valor calculado del IMC.*/
float imcFuncion(float masa, float altura);

// Función que imprime una matriz de tamaño NxN.
// Recibe un puntero a la matriz y el tamaño N de la misma.

void impMatrix(float *mA, int N);

/* Función que realiza la multiplicación de dos matrices mA y mB de tamaño NxN.
 Recibe el tamaño N y las dos matrices a multiplicar.
 Devuelve un puntero a la matriz resultante de la multiplicación.*/

float *matrixMult(int N, float *mA, float *mB);

// Función que llena dos matrices mA y mB de tamaño NxN con valores aleatorios.
// Los valores son generados de forma aleatoria con rand() y se asignan a las matrices.
void llenarMatriz(int N, float *mA, float *mB);

#endif  // Fin de la verificación de la constante _MODULO_H_

