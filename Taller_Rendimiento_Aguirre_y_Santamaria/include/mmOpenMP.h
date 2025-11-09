/*#######################################################################################
#* Pontificia Universidad Javeriana - Facultad de Ingeniería (Sistemas)
#* Materia: Sistemas Operativos
#* Profesor: J. Corredor
#*Tema: Taller de Evaluación de Rendimiento
#* Autores: Juliana Aguirre Ballesteros, Juan Carlos Santamaría Orjuela
#* Archivo:
#*      mmOpenMP.h
#* Propósito del archivo:
#*  - Declarar funciones comunes para todos los programas del taller.
#*  - Centralizar la medición de tiempo, impresión e inicialización de matrices.
#*  - Evitar duplicar prototipos en las versiones Serie, OpenMP, Pthreads y Fork.
#######################################################################################*/

#ifndef MM_OPENMP_H
#define MM_OPENMP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <omp.h>

// esta función marca el inicio del cronómetro 
void InicioMuestra(void);

// esta función calcula e imprime el tiempo transcurrido desde InicioMuestra 
void FinMuestra(void);

// esta función imprime la matriz por consola si D es pequeño
void impMatrix(double *matrix, int D);

// esta función llena A y B con valores aleatorios en rangos acotados
void iniMatrix(double *m1, double *m2, int D);

#endif /* MM_OPENMP_H */
