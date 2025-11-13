/**********************************************************************************************
*               Pontificia Universidad Javeriana
* Autor: Juliana Aguirre Ballesteros
* Materia: Sistemas Operativos
* Profesor: J. Corredor
* Laboratorio: Sistemas de Ficheros
* Descripción: Programa en C que lee y muestra el contenido 
*              de un archivo llamado readme.txt.
* lee su contenido línea por línea y lo muestra en pantalla.
* Sirve para practicar cómo manejar archivos cómo se  abren, se leen y se cierran correctamente. 
* También ayuda a entender cómo detectar errores si el archivo no existe.
************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

int main(){
    char *filename = "readme.txt";//nombre del archivo que se va a leer
printf("\n ============================== \n");
printf("\n Lectura del fichero readme.txt \n");
printf("\n ===============================\n");
//abre el archivo en modo lectura
    FILE *fp = fopen(filename, "r");

  // Si no se puede abrir el archivo se  va a mostrar un error
    if (fp == NULL){
        printf("Error: could not open file %s", filename);
        return 1;//termina el programa
    }

    //Lectura de línea por línea, máximo 256 bytes   
const unsigned MAX_LENGTH = 256;
    char buffer[MAX_LENGTH];
// Lee el archivo línea por línea hasta llegar al final
    while (fgets(buffer, MAX_LENGTH, fp))
        printf("%s", buffer);

    // Cerrar el fichero despues de leerlo
    fclose(fp);

    return 0;
}

// Conclusiones:
// Este programa permitió practicar cómo abrir y leer archivos en C.
// Se aprendió a usar fopen(), fgets() y fclose() correctamente.
// También se entendió cómo mostrar el contenido de un archivo línea por línea.
// Fue útil para aprender a manejar errores si el archivo no se encuentra.
// Ayuda a comprender el funcionamiento básico de la lectura de archivos en sistemas operativos.
