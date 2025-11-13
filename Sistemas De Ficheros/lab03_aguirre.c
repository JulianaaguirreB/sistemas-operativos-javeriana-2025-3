/*******************************************************************
*              Pontificia Universidad Javeriana
* Autor: Juliana Aguirre Ballesteros
* Materia: Sistemas Operativos
* Profesor: J. Corredor
* Descripción:
* Este programa pide al usuario escribir el nombre de un directorio
* y muestra información sobre todos los archivos que hay dentro.
* Muestra si los archivos pueden ser leídos por el dueño,
* si son archivos normales o carpetas,
* y también revisa cuáles fueron modificados en los últimos 10 días.
* Además, enseña la fecha exacta de la última modificación de cada uno.
* Sirve para practicar el manejo de directorios.
********************************************************************/


#include <stdio.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

// programa que muestra informacion de los archivos de un directorio
int main() {
    int er;
    char nomdir[100], nomfich[100], resp[30];
    struct stat atr;
    DIR *d;
    struct dirent *rd1;
    time_t fecha;

 // pide el nombre del directorio
    printf("Nombre directorio\n");
    fgets(nomdir, sizeof(nomdir), stdin);
     // quita el salto de línea al final del nombre
    nomdir[strlen(nomdir) - 1] = '\0';
// guarda la fecha actual
    fecha = time(&fecha);
 // intenta abrir el directorio
    if ((d = opendir(nomdir)) == NULL) {
        printf("No existe ese directorio\n");
        return -1;
    } else {
// lee cada archivo o carpeta dentro del directorio
        while ((rd1 = readdir(d)) != NULL) {
            if ((strcmp(rd1->d_name, ".") != 0) && (strcmp(rd1->d_name, "..") != 0)) {
                  // crea la ruta completa del archivo
		strcpy(nomfich, nomdir);
                strcat(nomfich, "/");
                strcat(nomfich, rd1->d_name);
// muestra el nombre del archivo
                printf("\n fichero: %s\n", nomfich);
                
// obtiene los atributos del archivo
		er = stat(nomfich, &atr);
                printf("\n modo: %3o\n", atr.st_mode);
// verifica si el propietario tiene permiso de lectura
                if ((atr.st_mode & 0400) != 0)
                    printf("\n permiso R para propietario\n");
                else
                    printf("\n No permiso R para propietario\n");
// verifica si es un directorio
                if (S_ISDIR(atr.st_mode))
                    printf("\n Es un directorio\n");
                if (S_ISREG(atr.st_mode)) {
                    /* ficheros modificados en los últimos 10 días */
                    if ((fecha - 10 * 24 * 60 * 60) < atr.st_mtime) {
                        printf("\n FICHERO: %s, fecha acceso %s, en sgdos %ld\n",
                               rd1->d_name,
                               ctime(&atr.st_mtime),
                               atr.st_mtime);
                    }
                }
            }
        } /* while */
        closedir(d);
    }
    return 0;
} /* main */
