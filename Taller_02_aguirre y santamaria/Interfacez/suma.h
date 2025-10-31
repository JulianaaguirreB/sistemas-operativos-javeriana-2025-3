/**************************************************************************************************************************************************************
*Autores: Juliana Aguirre Ballesteros
*Juan Carlos Santamaría Orjuela
*Nombre archivo: suma.h
*Universidad: Pontificia Universidad Javeriana
*Materia: Sistemas Operativos
*Profesor: J. Corredor
*Objetivos:
*
*    - Declarar las funciones para sumar elementos de uno o dos arreglos enteros.
*    - Proveer una interfaz clara para los módulos que implementan la lógica de suma.
*    - Evitar redefiniciones mediante guardas de inclusión.
*
**************************************************************************************************************************************************************/

#ifndef SUMAS_H
#define SUMAS_H

/* Suma los elementos del arreglo a de tamaño n y retorna el total */
long suma_array(const int* a, int n);

/*  Retorna la suma total combinando los arreglos a (n) y b (m)*/
long suma_doble(const int* a, int n, const int* b, int m);

#endif