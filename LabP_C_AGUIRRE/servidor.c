/**************************************************
 * Pontificia universidad javeriana
 * Autor:Juliana aguirre ballesteros
 * Materia:sistemas operativos
 * Tema:implementacion de productor consumidor apartir de pipe Named
 * descripcion:
 * -Archivo que actúa como el servidor dentro de la comunicación mediante un FIFO.
 * - Su función principal es recibir mensajes enviados por otro proceso .
 * - Cuando recibe un texto, lo procesa invirtiendo su contenido y lo devuelve al emisor.
 * - Si el mensaje recibido es la palabra "end", el programa cierra la comunicación y termina.
 * 
 *  Funcionalidades principales:
 * - Creación y apertura de un FIFO en el sistema.
 * - Lectura de cadenas de texto desde otro proceso.
 * - Procesamiento del mensaje recibido.
 * - Envío de la respuesta de vuelta al otro proceso.
 * - Finalización controlada al recibir una señal de cierre .
 ************************************************/


#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_FILE "/tmp/fifo_twoway"

/* Prototipo de función que invierte el contenido de una cadena */
void reverse_string(char *);

int main() {
   int fd;
   char readbuf[80];    /* Arreglo donde se almacenan los datos que llegan del cliente */
   char end[10];        /* Palabra clave que indica cuándo finalizar la comunicación */
   int to_end;
   int read_bytes;

   /* Crea el FIFO , si aún no existe, con permisos de lectura/escritura */
   mkfifo(FIFO_FILE, S_IFIFO|0640);

   /* Copia la palabra "end" para usarla como condición de salida */
   strcpy(end, "end");

   /* Abre el FIFO en modo lectura/escritura para la comunicación */
   fd = open(FIFO_FILE, O_RDWR);

   /* se mantiene leyendo y respondiendo mensajes */
   while(1) {
      /* Intenta leer datos desde el FIFO*/
      read_bytes = (int)read(fd, readbuf, sizeof(readbuf) - 1);

      /* Si la lectura falla, vuelve a intentar */
      if (read_bytes < 0) continue;

      /* Se agrega un carácter nulo al final para marcar el fin de la cadena */
      readbuf[read_bytes] = '\0';

      
      printf("FIFOSERVER: Received string: \"%s\" and length is %d\n", readbuf, read_bytes);

      /* Compara el texto recibido con la palabra "end" */
      to_end = strcmp(readbuf, end);

      /* Si el mensaje es "end", cierra el FIFO y termina la ejecución */
      if (to_end == 0) {
         close(fd);
         break;
      }

      /* Si no es "end", invierte el texto recibido */
      reverse_string(readbuf);

      /* Muestra en pantalla la cadena invertida antes de enviarla de vuelta */
      printf("FIFOSERVER: Sending Reversed String: \"%s\" and length is %d\n", readbuf, (int)strlen(readbuf));

      /* Envía la cadena invertida al cliente a través del FIFO */
      write(fd, readbuf, strlen(readbuf));

      sleep(2);
   }
   return 0;
}

/* Función que invierte los caracteres de una cadena recibida */
void reverse_string(char *str) {
   int last, limit, first;
   char temp;

   /* Calcula la posición del último carácter */
   last = strlen(str) - 1;

   /* Límite hasta la mitad de la cadena */
   limit = last / 2;

   /* Índice inicial */
   first = 0;

   /* Intercambia los caracteres desde los extremos hacia el centro */
   while (first < last) {
      temp = str[first];
      str[first] = str[last];
      str[last] = temp;
      first++;
      last--;
   }
}
