/*#################################################################################################
#* 						Pontificia Universidad Javeriana 
#* Materia: Sistemas Operativos
#* Profesor: J. Corredor
#*Tema: Taller de Evaluación de Rendimiento
#* Autores: Juliana Aguirre Ballesteros, Juan Carlos Santamaría Orjuela
#* Programa:
#*      Multiplicación de Matrices algoritmo clásico
#* Archivo: mmClasicaFork.c
#* OBJETIVOS:
#*  - Dividir el cálculo de C = A x B por bloques de filas y ejecutarlo en procesos hijo.
#*  - Medir el tiempo total en microsegundos de la sección paralela usando fork().
#*  - Aceptar N (tamaño de la matriz) y P (número de procesos) desde la línea de comandos.
#*  - Mantener impresión de matrices solo cuando N es pequeño.
#*  - Dejar el formato de salida listo para ser leído por lanzador.pl.
######################################################################################################*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <time.h>
#include "mmOpenMP.h"


// //esta función multiplica las filas [filaI, filaF) de A por B y escribe los resultados en C
// //esta función recorre A por filas y B por columnas usando punteros (stride D)
void multiMatrix(double *mA, double *mB, double *mC, int D, int filaI, int filaF) {
	double Suma, *pA, *pB;
    for (int i = filaI; i < filaF; i++) {           // Filas asignadas a este proceso
        for (int j = 0; j < D; j++) {               // Columnas de B/C
			Suma = 0.0;
			pA = mA+i*D;                            // Inicio de fila i de A
			pB = mB+j;                               // Columna j de B (acceso por stride D)
            for (int k = 0; k < D; k++, pA++, pB+=D) {
				Suma += *pA * *pB;	               // Producto punto fila(i)·columna(j)
            }
			mC[i*D+j] = Suma;                        // Guarda C[i,j]
        }
    }
}

int main(int argc, char *argv[]) {

	// //esta sección valida los argumentos de entrada: N (tamaño) y num_P (procesos)

	if (argc < 3) {
		printf("\n \t\tUse: $./nom_ejecutable Size Hilos \n");
		exit(0);
	}
	int N      = (int) atoi(argv[1]);   // //esta variable guarda el tamaño de la matriz (N x N)
	int num_P  = (int) atoi(argv[2]);   // //esta variable guarda el número de procesos a crear

	// //esta sección reserva memoria contigua para A, B y C (N*N doubles inicializados en 0)

	double *matA = (double *) calloc(N*N, sizeof(double));
	double *matB = (double *) calloc(N*N, sizeof(double));
	double *matC = (double *) calloc(N*N, sizeof(double));

    srand(time(0)); 
    // //esta parte llena A y B con valores aleatorios e imprime si N es pequeño (prueba)
    iniMatrix(matA, matB, N);
    impMatrix(matA, N);
    impMatrix(matB, N);
    
    int rows_per_process = N/num_P;     // //esta variable guarda cuántas filas calcula cada proceso

	InicioMuestra();                    // //esta llamada marca el inicio del cronómetro

    // //este bucle crea num_P procesos, cada hijo calcula un bloque de filas de C

    for (int i = 0; i < num_P; i++) {
        pid_t pid = fork();
        
        if (pid == 0) {                             // Proceso hijo
            int start_row = i * rows_per_process;   // //esta variable es la primera fila del hijo i
            int end_row = (i == num_P - 1) ? N : start_row + rows_per_process; // //esta cubre el residuo
            
			multiMatrix(matA, matB, matC, N, start_row, end_row);  // //esta línea realiza el cálculo
            
			// //esta impresión muestra las filas calculadas por este hijo si N es pequeño
			if(N<9){
           		printf("\nChild PID %d calculated rows %d to %d:\n", getpid(), start_row, end_row-1);
            	for (int r = start_row; r < end_row; r++) {
                	for (int c = 0; c < N; c++) {
                    	printf(" %.2f ", matC[N*r+c]);
                	}
                	printf("\n");
            	}
			}
            exit(0);                                // //este exit termina el proceso hijo
        } else if (pid < 0) {                       // //esta rama maneja error de fork()
            perror("fork failed");
            exit(1);
        }
    }
    
    // //esta sección hace que el proceso padre espere a todos los hijos
    for (int i = 0; i < num_P; i++) {
        wait(NULL);
    }
  	
	FinMuestra();                                   // //esta llamada marca y muestra el tiempo total
 
	// //esta sección libera la memoria reservada
	free(matA);
	free(matB);
	free(matC);

    return 0;
}
