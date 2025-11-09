/***************************************************************************************
*                               Pontificia Universidad Javeriana                        
* Autor: Juliana Aguirre Ballesteros                                                    
* Materia: Sistemas Operativos                                        
* Laboratorio: OpenMP                                                                   
* Profesor: J. Corredor                                                                                                                                
* Descripcion:                                                                          
*   Este programa demuestra el uso de las clausulas private en OpenMP                 
*   para controlar el alcance de las variables dentro de una region paralela.           
*   Se observa como cada hilo mantiene sus propias copias de las variables a y b.   
* Objetivo:                                                                             
*   - Mostrar el funcionamiento de la clausula private en OpenMP.                     
*   - Evidenciar la independencia de las variables locales en cada hilo.                
****************************************************************************************/

#include <omp.h>       
#include <stdio.h>
#include <stdlib.h>

int main() {

    /* Declaracion de variables */
    int i;
    const int N = 1000;
    int a = 50;
    int b = 0;

    /* Region paralela con variables privadas */
    #pragma omp parallel for private(i) private(a) private(b)
    for (i = 0; i < N; i++) {
        /* Cada hilo tiene su propia copia de a y b */
        b = a + i;
    }

    /* Mostrar resultados finales */
    printf("a = %d b = %d (Se espera a=50 b = 1049)\n", a, b);

    return 0;
}
