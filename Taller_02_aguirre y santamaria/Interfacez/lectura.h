/**************************************************************************************************************************************************************
*Autores: Juliana Aguirre Ballesteros
*Juan Carlos Santamaría Orjuela
*Nombre archivo: lectura.h
*Universidad: Pontificia Universidad Javeriana
*Materia: Sistemas Operativos
*Profesor: J. Corredor
*Objetivos:
*
*   -Declarar la función de lectura utilizada para cargar números enteros desde un archivo de texto.
*   -Definir la estructura básica del encabezado con directivas de inclusión condicional para evitar redefiniciones.
*   -Garantizar una interfaz clara entre los módulos lectura.c y el programa principal del Taller 02.
**************************************************************************************************************************************************************/
#ifndef IO_H
#define IO_H
/*Declaración de la función que lee N enteros desde un archivo */
int* leer_enteros(const char* ruta, int N);
/*Devuelve un puntero a un arreglo dinamico con los valores cargados*/
#endif
