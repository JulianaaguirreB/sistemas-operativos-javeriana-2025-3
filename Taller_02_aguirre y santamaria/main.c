/**************************************************************************************************************************************************************
*Autores: Juliana Aguirre Ballesteros
*Juan Carlos Santamaría Orjuela
*Nombre archivo: main.c
*Universidad: Pontificia Universidad Javeriana
*Materia: Sistemas Operativos
*Profesor: J. Corredor
*Objetivos:
*
*    - Recibir parámetros por consola y validar su formato.
*    - Leer N1 y N2 enteros desde archivos de texto a memoria dinámica (usar lectura.c / lectura.h).
*    - Crear procesos con fork(): sumaA (nieto), sumaTotal (hijo1) y sumaB (hijo2).
*    - Comunicar resultados al proceso padre mediante un único pipe, etiquetando cada suma.
*    - Imprimir en el padre las tres sumas A, B y Total y liberar recursos.
*
**************************************************************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "lectura.h"
#include "suma.h"

int main(int argc, char* argv[]) {
    /* Validar número de argumentos esperados */
    if (argc != 5) {
        fprintf(stderr, "Uso: %s N1 archivo00 N2 archivo01\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Convertir N1 y N2 a enteros y tomar rutas de archivos*/
    int N1 = atoi(argv[1]), N2 = atoi(argv[3]);
    const char* archivo00 = argv[2];
    const char* archivo01 = argv[4];

    /*  Verificar que N1 y N2 sean tamaños válidos  */
    if (N1 <= 0 || N2 <= 0) {
        fprintf(stderr, "Error: N1 y N2 deben ser > 0.\n");
        return EXIT_FAILURE;
    }

    /*  Leer arreglos usando el módulo lectura */
    int* A = leer_enteros(archivo00, N1);
    if (!A) {
        fprintf(stderr, "Error leyendo %s (formato o cantidad N1=%d inválidos)\n", archivo00, N1);
        return EXIT_FAILURE;
    }

    int* B = leer_enteros(archivo01, N2);
    if (!B) {
        fprintf(stderr, "Error leyendo %s (formato o cantidad N2=%d inválidos)\n", archivo01, N2);
        free(A);
        return EXIT_FAILURE;
    }

    /*  Crear pipe único para que los hijos/nieto envíen resultados al padre  */
    int p[2];
    if (pipe(p) == -1) {
        perror("pipe");
        free(A);
        free(B);
        return EXIT_FAILURE;
    }

    /* fork del Hijo 1   */
    pid_t c1 = fork();
    if (c1 < 0) {
        perror("fork hijo1");
        free(A);
        free(B);
        return EXIT_FAILURE;
    }

    if (c1 == 0) {
        /* Proceso Hijo 1: solo escribe en el pipe */
        close(p[0]); /* no lee del pipe */
        FILE* out = fdopen(p[1], "w");
        if (!out) {
            perror("fdopen hijo1");
            close(p[1]);
            free(A);
            free(B);
            _exit(EXIT_FAILURE);
        }

        /* Crear Nieto: calcular suma A y reportarla */
        pid_t gc = fork();
        if (gc < 0) {
            perror("fork nieto");
            fclose(out);
            free(A);
            free(B);
            _exit(EXIT_FAILURE);
        }

        if (gc == 0) {
            /* NIETO: calcula suma de A y la envía etiquetada 'A' usando suma_array() */
            long sumaA = suma_array(A, N1);
            fprintf(out, "A %ld\n", sumaA);
            fflush(out);
            fclose(out);
            free(A); free(B);
            _exit(0);
        } else {
            /* HIJO 1: calcula suma total (A+B) y la envía etiquetada 'T' usando suma_doble() */
            long sumaT = suma_doble(A, N1, B, N2);
            fprintf(out, "T %ld\n", sumaT);
            fflush(out);
            (void)waitpid(gc, NULL, 0);
            fclose(out);
            free(A); free(B);
            _exit(0);
        }
    }

    /*  fork del Hijo 2 que calcula sumaB */
    pid_t c2 = fork();
    if (c2 < 0) {
        perror("fork hijo2");
        free(A);
        free(B);
        return EXIT_FAILURE;
    }

    if (c2 == 0) {
        /*  Proceso Hijo 2: solo escribe al pipe */
        close(p[0]); /* no lee */
        FILE* out = fdopen(p[1], "w");
        if (!out) {
            perror("fdopen hijo2");
            close(p[1]);
            free(A);
            free(B);
            _exit(EXIT_FAILURE);
        }
        /* Calcular suma de B y enviarla etiquetada 'B' usando suma_array() */
        long sumaB = suma_array(B, N2);
        fprintf(out, "B %ld\n", sumaB);
        fflush(out);
        fclose(out);
        free(A); free(B);
        _exit(0);
    }

    /*  PADRE: cierra escritura y se queda solo leyendo del pipe  */
    close(p[1]); /* solo lee */
    FILE* in = fdopen(p[0], "r");
    if (!in) {
        perror("fdopen padre");
        close(p[0]);
        free(A);
        free(B);
        return EXIT_FAILURE;
    }

    /* Variables para recibir resultados A, B y T*/
    long rA = 0, rB = 0, rT = 0;
    int recibidos = 0;

    /* Leer exactamente 3 líneas etiquetadas desde el pipe*/
    while (recibidos < 3) {
        char t;
        long v;
        if (fscanf(in, " %c %ld", &t, &v) != 2) break;
        if (t == 'A')      rA = v;
        else if (t == 'B') rB = v;
        else if (t == 'T') rT = v;
        recibidos++;
    }
    /*Cerrar stream de lectura del pipe  */
    fclose(in);

    /* Esperar finalización de Hijo 1 y Hijo 2 */
    (void)waitpid(c1, NULL, 0);
    (void)waitpid(c2, NULL, 0);

    /*Imprimir resultados finales en el padre */
    printf("sumaA=%ld\n", rA);
    printf("sumaB=%ld\n", rB);
    printf("sumaTotal=%ld\n", rT);

    /*  Liberar memoria dinámica de A y B (en el padre por claridad; en hijos ya se liberó) */
    free(A); free(B);
    return 0;
}