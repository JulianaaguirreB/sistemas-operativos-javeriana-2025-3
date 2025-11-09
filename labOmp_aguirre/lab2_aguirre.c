/***************************************************************************************
*                               Pontificia Universidad Javeriana                        
* Autor: Juliana Aguirre Ballesteros                                                    
* Materia: Sistemas Operativos                                                          
* Laboratorio: OpenMP                                                                   
* Profesor: J. Corredor                                                                                                                                
* Descripción:                                                                          
*   Este programa muestra como fijar manualmente el numero de hilos que usara           
*   una region paralela en OpenMP. Recibe el número de hilos por argumento,             
*   consulta la cantidad máxima de cores disponibles en el sistema.
* Objetivo:                                                                             
*   - Utilizar la directiva omp_set_num_threads() para establecer el número de hilos.  
*   - Mostrar el número maximo de hilos soportados por el sistema operativo.            
*   - Crear una region paralela donde cada hilo identifique su ejecucion.               
****************************************************************************************/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    /*  Validar que se reciba el numero de hilos como argumento */
    if (argc != 2) {
        printf("Error:\n\tUso correcto: ./ejecutable numHilos\n");
        exit(0);
    }

    /* Convertir el argumento a entero*/
    int numHilos = atoi(argv[1]);

    /* Consultar el numero máximo de hilos soportados por el sistema  */
    int maxcores = omp_get_max_threads();
    printf("Numero maximo de cores del SO: %d\n", maxcores);

    /*  Fijar el numero de hilos deseado por el usuario*/
    omp_set_num_threads(numHilos);
    printf("Numero de hilos fijados: %d\n", numHilos);

    /*  Crear una region paralela ejecutada por los hilos configurados  */
    #pragma omp parallel
    {
        /* Cada hilo imprime su identificador dentro de la region */
        printf("Hilo ID en región paralela: %d\n", omp_get_thread_num());
    }

    return 0;
}
