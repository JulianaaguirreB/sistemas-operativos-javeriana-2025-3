/*#######################################################################################
#* Pontificia Universidad Javeriana 
#* Materia: Sistemas Operativos
#* Profesor: J. Corredor
#*Tema: Taller de Evaluación de Rendimiento
#* Autores: Juliana Aguirre Ballesteros, Juan Carlos Santamaría Orjuela
#* Programa:
#*      Multiplicación de Matrices algoritmo clásico
#* Archivo: mmClasicaPosix.c
#* OBJETIVOS:
#*  - Calcular C = A x B usando el algoritmo clásico y hilos POSIX.
#*  - Repartir el trabajo por bloques de filas entre los hilos.
#*  - Medir el tiempo total de ejecución en microsegundos.
#*  - Recibir por línea de comandos: tamaño de matriz  y número de hilos.
#*  - Imprimir matrices solo cuando N es pequeño.
######################################################################################*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "mmOpenMP.h"

// esta variable es un mutex general 
pthread_mutex_t MM_mutex;
// estas variables globales apuntan a las matrices A, B y C
double *matrixA, *matrixB, *matrixC;

// esta estructura guarda los parámetros que cada hilo necesita
struct parametros{
	int nH;   // esta variable guarda el número total de hilos
	int idH;  // esta variable guarda el id del hilo (0..nH-1)
	int N;    // esta variable guarda la dimensión de la matriz 
};

// esta función es la tarea de cada hilo: multiplica su bloque de filas y escribe en C
void *multiMatrix(void *variables){
	struct parametros *data = (struct parametros *)variables;  // esta conversión recupera los parámetros
	
	int idH		= data->idH;  // esta variable es el id del hilo
	int nH		= data->nH;   // esta variable es el número total de hilos
	int D		= data->N;    // esta variable es la dimensión de la matriz
	int filaI	= (D/nH)*idH;     // esta variable es la primera fila que procesa el hilo
	int filaF	= (D/nH)*(idH+1); // esta variable es la fila final 
	double Suma, *pA, *pB;        // estas variables soportan el producto punto

    for (int i = filaI; i < filaF; i++){
        for (int j = 0; j < D; j++){
			pA = matrixA + i*D;  // este puntero apunta al inicio de la fila i de A
			pB = matrixB + j;    // este puntero recorre la columna j de B con stride D
			Suma = 0.0;          // esta variable acumula el producto punto
            for (int k = 0; k < D; k++, pA++, pB+=D){
				Suma += *pA * *pB; // esta suma realiza el producto fila·columna
			}
			matrixC[i*D+j] = Suma; // esta asignación guarda el resultado en C[i][j]
		}
	}

	// estas llamadas al mutex dejan una sección protegida vacía (no necesaria, pero inocua)
	pthread_mutex_lock (&MM_mutex);
	pthread_mutex_unlock (&MM_mutex);
	pthread_exit(NULL); // esta llamada finaliza ordenadamente el hilo
}

int main(int argc, char *argv[]){
	// esta sección valida que se ingresen N y número de hilos
	if (argc < 3){
		printf("Ingreso de argumentos \n $./ejecutable tamMatriz numHilos\n");
		exit(0);	
	}
    int N = atoi(argv[1]);        // esta variable guarda el tamaño de la matriz (N x N)
    int n_threads = atoi(argv[2]); // esta variable guarda el número de hilos

    pthread_t p[n_threads];       // este arreglo guarda los identificadores de hilos
    pthread_attr_t atrMM;         // esta variable guarda los atributos de creación de hilos

	// esta sección reserva memoria para A, B y C
	matrixA  = (double *)calloc(N*N, sizeof(double));
	matrixB  = (double *)calloc(N*N, sizeof(double));
	matrixC  = (double *)calloc(N*N, sizeof(double));

	// esta parte inicializa A y B con números aleatorios e imprime si N es pequeño
	iniMatrix(matrixA, matrixB, N);
	impMatrix(matrixA, N);
	impMatrix(matrixB, N);

	// esta llamada marca el inicio del cronómetro
	InicioMuestra();

	// esta parte inicializa el mutex y los atributos de los hilos
	pthread_mutex_init(&MM_mutex, NULL);
	pthread_attr_init(&atrMM);
	pthread_attr_setdetachstate(&atrMM, PTHREAD_CREATE_JOINABLE); // esta opción crea hilos joinables

	// este bucle crea n_threads hilos y asigna su bloque de filas
	for (int j=0; j<n_threads; j++){
		struct parametros *datos = (struct parametros *) malloc(sizeof(struct parametros)); 
		datos->idH = j;            // esta asignación guarda el id del hilo
		datos->nH  = n_threads;    // esta asignación guarda el total de hilos
		datos->N   = N;            // esta asignación guarda la dimensión

        pthread_create(&p[j],&atrMM,multiMatrix,(void *)datos); // esta llamada lanza el hilo
	}

    // este bucle espera (join) a que todos los hilos terminen
    for (int j=0; j<n_threads; j++) pthread_join(p[j],NULL);

	// esta llamada marca y muestra el tiempo total transcurrido
	FinMuestra();

	// esta línea imprime C si N es pequeño 
	impMatrix(matrixC, N);

	// esta sección libera la memoria y destruye recursos
	free(matrixA);
	free(matrixB);
	free(matrixC);

	pthread_attr_destroy(&atrMM);
	pthread_mutex_destroy(&MM_mutex);
	pthread_exit (NULL); // esta llamada finaliza el hilo principal 

	return 0;
}
