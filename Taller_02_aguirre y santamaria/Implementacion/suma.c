/****************************************************************************************************
*Autores: Juliana Aguirre Ballesteros
*Juan Carlos Santamaría Orjuela
*Nombre archivo: suma.c
*Universidad: Pontificia Universidad Javeriana
*Materia: Sistemas Operativos
*Profesor: J. Corredor
*Objetivos:
*
*   -Implementar funciones que realicen la suma de los elementos de uno o dos arreglos enteros.
*   -Aplicar estructuras de control y paso de parámetros en C.
*   -Reutilizar funciones internas para optimizar el código y evitar duplicación de lógica.
*****************************************************************************************************/
#include "suma.h"

/* Calcula la suma de los elementos de un arreglo */
long suma_array(const int* a, int n) {
    /*inicializa una variable que va acumular en cero */
    long s = 0;
    /* Recorre el arreglo sumando cada elemento */
    for (int i = 0; i < n; ++i) s += a[i];
    /*retorna el valor total acumulado*/
    return s;
}
/*calcula la suma combinada de dos arreglos*/
long suma_doble(const int* a, int n, const int* b, int m) {
    /*llama a la funcion summa_array para cada arreglo y va a retornar el total*/
    return suma_array(a, n) + suma_array(b, m);
}
