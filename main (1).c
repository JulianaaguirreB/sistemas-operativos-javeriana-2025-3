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
/* Incluir el archivo de cabecera para las funciones definidas en modulo. 
Incluir la librería estándar para funciones de entrada/salida
Incluir la librería estándar para funciones de asignación de memoria, conversión de cadenas
Incluir la librería para la manipulación de tiempo (aunque no parece ser usada directamente aquí)
*/
#include "modulo.h"
#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

int main(int argc, char *argv[]) {
 // Verifica si el número de argumentos es menor que 4 (incluyendo el nombre del ejecutable). Si es así, imprime un mensaje de uso y termina el programa. 
 if (argc < 4) {
    printf("$./ejecutable valor1 valor2 valor3\n");
    exit(0);
  }


  /*Convierte los valores de los argumentos a tipos adecuados:
  altura: convertida a float
  masacorporal: convertida a float
  N: tamaño de la matriz, convertido a entero*/

  float altura = (float)atof(argv[1]);
  float masacorporal = (float)atof(argv[2]);
  int N = (int)atof(argv[3]);

  printFuncion();

// Calcula el índice de masa corporal (IMC) usando la fórmula: IMC = masa / altura^2

  float valorIMC = imcFuncion(masacorporal, altura);

// Imprime el valor del IMC calculado

  printf("El indice de masa corporal es %f\n", valorIMC);
  printf("*********************************************\n\n\n");
  printf("*********************************************\n");
  printf("                    Matriz                  *\n");
  printf("*********************************************\n");

// Asigna memoria dinámicamente para dos matrices de tamaño N x N
// Se multiplica N * N por 4 porque un 'float' típicamente ocupa 4 bytes

  float *m1 = (float *)malloc(N * N * 4);
  float *m2 = (float *)malloc(N * N * 4);
  
  // Llamar a la función llenarMatriz que llena las matrices m1 y m2 con valores
llenarMatriz(N, m1, m2);

// Imprimir las matrices m1 y m2
  impMatrix(m1, N);
  impMatrix(m2, N);

// Realizar la multiplicación de las matrices m1 y m2, y almacenar el resultado en mC

  float *mC = matrixMult(N, m1, m2);

// Imprimir la matriz resultante mC
  impMatrix(mC, N);

// Liberar la memoria previamente asignada para las matrices m1, m2 y mC
  free(m1);
  free(m2);
  free(mC);
//aqui termina el programa exitosamente :D
  return 0;
}
