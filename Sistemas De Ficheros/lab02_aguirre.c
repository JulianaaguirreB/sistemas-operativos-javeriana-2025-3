/**********************************************************************************************************
*               Pontificia Universidad Javeriana
* Autor: Juliana Aguirre Ballesteros
* Materia: Sistemas Operativos
* Profesor: J. Corredor
* Laboratorio: Sistemas De Ficheros
* Descripción:
* Este programa en C le pide al usuario el nombre de un 
* directorio y revisa si existe. 
* Si el directorio es válido, muestra los nombres de los archivos que hay dentro y el tamaño de cada uno. 
* obtener información de los archivos con stat() y cómo manejar errores cuando un directorio no existe.
***********************************************************************************************************/

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int main(){
    DIR *d;// Puntero para abrir el directorio
    char nomdir[90], nomfich[90];//cadenas para guardar nombre del directorio  y archivo
    struct stat datos;// Estructura para guardar información de cada archivo
    struct dirent *direc;// Estructura para leer las entradas del directorio

    printf ("Introduzca el Nombre de un Directorio: ");
    fgets (nomdir,sizeof(nomdir),stdin);// Leemos la entrada del usuario
    nomdir[strlen(nomdir)-1]='\0'; /*Eliminamos el \n del Nombre del Fichero*/
 // Intentamos abrir el directorio con opendir()    
if ((d=opendir(nomdir))==NULL){
        printf ("El directorio no existe\n");
        return -1;
    }
 // Leemos cada elemento dentro del directorio
    while ((direc=readdir(d)) !=NULL) {
         strcpy(nomfich, nomdir);      // Copiamos el nombre del directorio en nomfich
        strcat(nomfich, "/");         // Agregamos una barra para unir con el archivo
        strcat(nomfich, direc->d_name); // Agregamos el nombre del archivo actual

        stat (nomfich, &datos);
// Verificamos si es un archivo regular
        if (S_ISREG(datos.st_mode))
 // Mostramos el nombre del archivo y su tamaño
            printf ("Nombre: %s\t Tamaño: %ld\n", direc->d_name, datos.st_size);
    }/*Fin del While*/
    closedir(d);
}

