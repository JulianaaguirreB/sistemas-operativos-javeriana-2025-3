/*#######################################################################################
#* Pontificia Universidad Javeriana 
#* Materia: Sistemas Operativos
#* Profesor: J. Corredor
#*Tema: Taller de Evaluación de Rendimiento
#* Autores: Juliana Aguirre Ballesteros, Juan Carlos Santamaría Orjuela
#* Programa:
#*      Multiplicación de Matrices algoritmo clásico
#* Archivo: mmClasicaOpenMP.c
#* OBJETIVOS :
#*  - Implementar la multiplicación clásica de matrices cuadradas utilizando OpenMP.
#*  - Dividir el trabajo entre varios hilos para aprovechar los núcleos del procesador.
#*  - Medir el tiempo de ejecución total en microsegundos para análisis de rendimiento.
#*  - Aceptar parámetros desde la línea de comandos: tamaño de la matriz (N) y hilos (TH).
#*  - Mostrar resultados y matrices solo si el tamaño es pequeño, para fines de prueba.
######################################################################################*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <omp.h>
#include "mmOpenMP.h"

// esta función multiplica matrices A y B y guarda el resultado en C
// esta función usa paralelismo con OpenMP para repartir las filas entre varios hilos
void multiMatrix(double *mA, double *mB, double *mC, int D){
	double Suma, *pA, *pB;
	#pragma omp parallel   // esta directiva crea una región paralela
	{
	#pragma omp for        // esta directiva reparte las iteraciones del bucle entre los hilos
	for(int i=0; i<D; i++){
		for(int j=0; j<D; j++){
			pA = mA+i*D;    // esta variable apunta al inicio de la fila i de A
			pB = mB+j;      // esta variable apunta a la columna j de B
			Suma = 0.0;     // esta variable acumula el resultado del producto punto
			for(int k=0; k<D; k++, pA++, pB+=D){
				Suma += *pA * *pB;  // esta operación realiza el producto fila·columna
			}
			mC[i*D+j] = Suma;       // esta línea guarda el resultado en C[i][j]
		}
	}
	}
}

int main(int argc, char *argv[]){
	// esta sección verifica que se hayan pasado los parámetros requeridos
	if(argc < 3){
		printf("\n Use: $./clasicaOpenMP SIZE Hilos \n\n");
		exit(0);
	}

	int N = atoi(argv[1]);   // esta variable guarda el tamaño de la matriz 
	int TH = atoi(argv[2]);  // esta variable guarda el número de hilos que se usarán

	// esta parte reserva memoria dinámica para las tres matrices A, B y C
	double *matrixA  = (double *)calloc(N*N, sizeof(double));
	double *matrixB  = (double *)calloc(N*N, sizeof(double));
	double *matrixC  = (double *)calloc(N*N, sizeof(double));

	srand(time(NULL));       // esta línea inicializa la semilla de números aleatorios
	omp_set_num_threads(TH); // esta función define el número de hilos que usará OpenMP

	// esta parte inicializa las matrices con valores aleatorios y las imprime si son pequeñas
	iniMatrix(matrixA, matrixB, N);
	impMatrix(matrixA, N);
	impMatrix(matrixB, N);

	// esta parte mide el tiempo de ejecución de la multiplicación
	InicioMuestra();
	multiMatrix(matrixA, matrixB, matrixC, N);
	FinMuestra();

	// esta parte muestra la matriz resultado si el tamaño es pequeño 
	impMatrix(matrixC, N);

	// esta parte libera la memoria asignada dinámicamente
	free(matrixA);
	free(matrixB);
	free(matrixC);
	
	return 0;
}
