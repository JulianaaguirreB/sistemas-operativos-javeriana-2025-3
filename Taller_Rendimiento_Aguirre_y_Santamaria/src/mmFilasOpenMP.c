/*#######################################################################################
#* Pontificia Universidad Javeriana - Facultad de Ingeniería (Sistemas)
#* Materia: Sistemas Operativos
#* Profesor: J. Corredor
#*Tema: Taller de Evaluación de Rendimiento
#* Autores: Juliana Aguirre Ballesteros, Juan Carlos Santamaría Orjuela
#* Programa:
#*      Multiplicación de Matrices algoritmo matriz Transpuesta
#* Archivo: mmFilasOpenMP.c
#* OBJETIVOS:
#*  - Multiplicar matrices usando la transpuesta de B filas x filas para mejorar cache.
#*  - Repartir el trabajo entre hilos con OpenMP para acelerar el cálculo.
#*  - Medir el tiempo total en microsegundos con las funciones comunes.
#*  - Recibir N (tamaño) y TH (hilos) por línea de comandos.
#*  - Imprimir matrices solo si el tamaño es pequeño.
#######################################################################################*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <omp.h>
#include "mmOpenMP.h"

// esta función multiplica matrices usando B como transpuesta lógica (filas x filas)
// esta función recorre A por filas y B^T por filas para acceso secuencial de memoria
void multiMatrixTrans(double *mA, double *mB, double *mC, int D){
	double Suma, *pA, *pB;

	#pragma omp parallel                 // esta directiva inicia una región paralela
	{
	#pragma omp for                     // esta directiva reparte las iteraciones del bucle externo
	for(int i = 0; i < D; i++){         // este bucle recorre las filas de A
		for(int j = 0; j < D; j++){     // este bucle recorre las filas de B transpuesta (columnas de B)
			pA = mA + i*D;              // este puntero apunta al inicio de la fila i de A
			pB = mB + j*D;              // este puntero apunta al inicio de la “fila j” de B^T (columna j de B)
			Suma = 0.0;                 // esta variable acumula el producto punto
			for(int k = 0; k < D; k++, pA++, pB++){
				Suma += *pA * *pB;      // esta operación realiza el producto fila(A) · fila(B^T)
			}
			mC[i*D + j] = Suma;         // esta línea guarda el resultado en C[i][j]
		}
	}
	}
}

int main(int argc, char *argv[]){
	// esta sección valida que se pasen N (tamaño) y TH (hilos)
	if(argc < 3){
		printf("\n Use: $./clasicaOpenMP SIZE Hilos \n\n");
		exit(0);
	}

	int N = atoi(argv[1]);  // esta variable guarda el tamaño de la matriz (N x N)
	int TH = atoi(argv[2]); // esta variable guarda la cantidad de hilos a usar

	// esta sección reserva memoria dinámica para A, B y C
	double *matrixA = (double *)calloc(N*N, sizeof(double));
	double *matrixB = (double *)calloc(N*N, sizeof(double));
	double *matrixC = (double *)calloc(N*N, sizeof(double));

	srand(time(NULL));       // esta llamada inicializa la semilla de aleatoriedad
	omp_set_num_threads(TH); // esta función fija el número de hilos de OpenMP

	iniMatrix(matrixA, matrixB, N); // esta llamada llena A y B con valores aleatorios

	// estas líneas imprimen A y B si N es pequeño 
	impMatrix(matrixA, N);
	impMatrix(matrixB, N);

	// estas llamadas miden el tiempo de la multiplicación por filas x filas
	InicioMuestra();
	multiMatrixTrans(matrixA, matrixB, matrixC, N);
	FinMuestra();

	// esta línea imprime C si N es pequeño 
	impMatrix(matrixC, N);

	// esta sección libera toda la memoria asignada
	free(matrixA);
	free(matrixB);
	free(matrixC);

	return 0;
}
