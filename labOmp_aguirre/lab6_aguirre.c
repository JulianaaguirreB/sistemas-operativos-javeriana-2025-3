/***************************************************************************************
*                               Pontificia Universidad Javeriana                        
* Autor: Juliana Aguirre Ballesteros                                                    
* Materia: Sistemas Operativos                                                          
* Laboratorio: OpenMP                                                                   
* Profesor: J. Corredor                                                                                                                                
* Descripcion:                                                                          
*   Este programa calcula la sumatoria de la funcion seno utilizando paralelismo         
*   con OpenMP. 
*   El usuario ingresa el numero de hilos y la cantidad de repeticiones.     
*   Se usa una clausula reduction para acumular los resultados parciales de cada hilo  
*   y se mide el tiempo total de ejecucion en microsegundos.                            
* Objetivo:                                                                             
*   - Implementar la suma paralela de una funcion matematica usando OpenMP.                            
*   - Medir el tiempo total de ejecucion del proceso completo.                           
****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <sys/time.h>

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

/* Variables para medir tiempo */
struct timeval inicio, fin;

/* Funcion que marca el inicio de la medicion */
void InicioMuestra() {
    gettimeofday(&inicio, (void *)0);
}

/* Funcion que marca el fin de la medicion y calcula la duracion */
void FinMuestra() {
    gettimeofday(&fin, (void *)0);
    fin.tv_usec  -= inicio.tv_usec;
    fin.tv_sec   -= inicio.tv_sec;
    double tiempo = (double)(fin.tv_sec * 1000000 + fin.tv_usec);
    printf("%9.0f microSeg\n", tiempo);
}

/* Funcion de trabajo: suma de senos en un rango dependiente de i */
double f(int i) {
    int j;
    int start = i * (i + 1) / 2;
    int finish = start + i;
    double return_val = 0;
    for (j = start; j < finish; j++)
        return_val += sin(j);
    return return_val;
}

int main(int argc, char *argv[]) {

    /* Validar los argumentos de entrada */
    if (argc != 3) {
        printf("Error:\n\tUso correcto: ./ejecutable NumHilos NumRep\n");
        exit(0);
    }

    /* Leer numero de hilos y repeticiones */
    int numHilos = atoi(argv[1]);
    int numRep   = atoi(argv[2]);
    double sum = 0;
    int i;

    /* Fijar el numero de hilos */
    omp_set_num_threads(numHilos);

    /* Iniciar la medicion del tiempo */
    InicioMuestra();

    /* Region paralela con clausula reduction */
    #pragma omp parallel
    {
        #pragma omp master
        {
            printf("Numero de Hilos: %d\n", numHilos);
        }

        #pragma omp for reduction(+:sum)
        for (i = 0; i <= numRep; i++) {
            sum += f(i);
        }
    }

    /* Finalizar la medicion del tiempo */
    FinMuestra();

    /* Mostrar la sumatoria resultante */
    printf("La sumatoria es: %.2f\n", sum);

    return 0;
}
