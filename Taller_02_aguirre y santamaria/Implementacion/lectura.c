/**************************************************************************************************************************************************************
*Autores: Juliana Aguirre Ballesteros 
*Juan Carlos Santamaria Orjuela
Nombre archivo_lectura.c
*Universidad: Pontificia Universidad Javeriana *
*Materia: Sistemas Operativos 
*Profesor: J.Corredor
*Objetivos: 
*
*    -Implementar una función en C que lea una cantidad específica de números enteros desde un archivo de texto y los cargue en memoria dinámica. 
*    - Aplicar conceptos de manejo de archivos, validación de datos y reserva/liberación de memoria. 
*    -Integrar esta rutina dentro del programa principal del Taller 02,  encargado de gestionar procesos y comunicación entre ellos. 
*
 ********************************************************************************************************************************************************/

//#include "io.h"
#include <stdio.h>
#include <stdlib.h>

int* leer_enteros(const char* ruta, int N) {
    /* Verificar que la cantidad de números sea valida */
    if (N <= 0) return NULL;
    /* Abrir el archivo indicado en modo lectura */
    FILE* f = fopen(ruta, "r");
     /* Si no se logra, retorna NULL. */
    if (!f) 
    return NULL;
/* Reservar memoria dinamica para N */
    int* arr = (int*)malloc(sizeof(int) * N);
    /* solicita un bloque de memoria para que almacene los valores pero si la reserva falla, se libera el archivo y retorna NULL */
    if (!arr) { 
        fclose(f); 
        return NULL; }

   /* Inicializa el contador de elementos leidos  */     
    int leidos = 0;
    /*lee los elementos del archivo*/
    while (leidos < N) {
        /*  Intentar leer un número y lo almacena en el arreglo */
        if (fscanf(f, "%d", &arr[leidos]) != 1) {
            /* Archivo con menos números o dato invalido*/
            free(arr);
            fclose(f);
            return NULL;
        }
        /*incrementa el contador al leer el un numero*/
        leidos++;
    }
/*cierra el archivo despues de terminar la lectura y retorna el puntero al arreglo con los datos que fueron leidos*/
    fclose(f);
    return arr;
}
