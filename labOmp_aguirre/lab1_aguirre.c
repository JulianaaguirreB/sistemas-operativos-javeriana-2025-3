/***************************************************************************************
*                               Pontificia Universidad Javeriana                        
* Autor: Juliana Aguirre Ballesteros                                                    
* Materia: Sistemas Operativos                                                          
* Laboratorio: OpenMP                                                                   
* Profesor: J. Corredor                                                                    
* Descripción:                                                                  
*   Este programa muestra el funcionamiento básico de OpenMP. Primero consulta el   
*   número máximo de hilos que el sistema puede manejar. Luego crea una región paralela 
*   mediante la directiva #pragma omp parallel, en la cual cada hilo imprime su ID.   
*   Esto permite visualizar el comportamiento concurrente y la distribución de hilos.                                                               
* Objetivo:                                                                             
*   - Introducir el uso de la librería OpenMP para el manejo de paralelismo a nivel     
*     de hilos dentro de un programa en C.                                              
*   - Mostrar el número máximo de hilos que puede usar el sistema operativo.            
*   - Crear una región paralela donde cada hilo imprime su identificador.            
****************************************************************************************/


#include <omp.h> 
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    /*  Obtener el numero maximo de hilos que el sistema puede usar */
    int maxcores = omp_get_max_threads();
    printf("Numero maximo de cores del SO: %d hilos\n", maxcores);

    /* Crear una region paralela con OpenMP */
    #pragma omp parallel
    {
        /* Cada hilo imprime su identificador dentro de la region */
        printf("Hilo ID en región paralela: %d\n", omp_get_thread_num());
    }

    return 0;
}
