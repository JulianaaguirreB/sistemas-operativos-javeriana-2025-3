/********************************************************************************************
                         Pontificia Universidad Javeriana
Autores: Juliana Aguirre Ballesteros 
         Juan Carlos Santamaria Orjuela
Materia: sistemas operativos
Profesor: j. corredor
Taller 03 Posix Semáforos

Descripción:
Este archivo define todos los recursos compartidos necesarios para la Actividad 1
usando memoria compartida y semáforos POSIX. Aquí se encuentran
los nombres de los semáforos, el nombre del segmento de memoria compartida y la estructura
del búfer circular que ambos procesos utilizan para comunicarse.

Objetivos:
- definir los nombres de los semáforos y la memoria compartida.
- declarar el tamaño del búfer circular para almacenar los datos.
- incluir las librerías necesarias para memoria compartida y semáforos POSIX.
********************************************************************************************/

#ifndef SHARED_H
#define SHARED_H

#define _POSIX_C_SOURCE 200809L


#include <stdio.h>     
#include <stdlib.h>    
#include <unistd.h>     
#include <fcntl.h>      
#include <sys/mman.h>   
#include <sys/stat.h>   
#include <semaphore.h>  
#include <errno.h>     
#include <string.h>     
#include <time.h>      

// nombre del segmento de memoria compartida, este nombre se usa para crear y abrir el área compartida
#define SHM_NAME   "/memoria_compartida"

// SEM_VACIO controla cuántos espacios libres quedan
#define SEM_VACIO  "/vacio"

// SEM_LLENO controla cuántos elementos hay en el búfer listos para consumir
#define SEM_LLENO  "/lleno"

// tamaño del búfer circular donde el productor escribe y el consumidor lee
#define BUFFER     10

// número total de ítems que podrían usarse 
#define N_ITEMS 20

// estructura compartida entre productor y consumidor
// contiene: búfer con datos, índice de entrada y de salida
typedef struct {
    int bus[BUFFER];   // almacena los elementos producidos
    int entrada;       // posición donde el productor insertará el siguiente dato
    int salida;        // posición donde el consumidor leerá el siguiente dato
} compartir_datos;

#endif /* SHARED_H */
