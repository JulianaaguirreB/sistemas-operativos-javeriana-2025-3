/***************************************************************************************
*                               Pontificia Universidad Javeriana                        
* Autor: Juliana Aguirre Ballesteros                                                    
* Materia: Sistemas Operativos                                        
* Laboratorio: OpenMP                                                                   
* Profesor: J. Corredor                                                                                                                                 
* Descripcion:                                                                          
*   Este programa demuestra el uso de las clausulas private y reduction en OpenMP   
*   para controlar el alcance de las variables dentro de un bucle paralelo.             
*   Se observa como las variables privadas se inicializan por hilo y no comparten valor.
* Objetivo:                                                                                
*   - Observar los efectos del paralelismo sobre las variables locales y globales.      
****************************************************************************************/

#include <omp.h>     
#include <stdio.h>
#include <stdlib.h>

int main() {

    /*  Declaracion de variables */
    int i;
    const int N = 1000;
    int a = 50;
    int b = 0;

    /*  Region paralela con clausulas private */
    #pragma omp parallel for private(i) private(a)
    for (i = 0; i < N; i++) {
        /*Cada hilo tiene su propia copia de a */
        b = a + i;
    }

    /* Mostrar resultados finales */
    printf("a = %d b = %d (Se espera a=50 b=1049)\n", a, b);

    return 0;
}
