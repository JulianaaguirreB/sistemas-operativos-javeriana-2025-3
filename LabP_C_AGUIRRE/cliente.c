/********************************************************************************************************************
 * Pontificia Universidad Javeriana
 * Autor: Juliana Aguirre Ballesteros
 * Materia: Sistemas Operativos
 * Tema: Implementación de Productor–Consumidor a partir de Pipe Named
 * 
 * Descripción:
 * - Archivo que cumple el rol de cliente dentro de la comunicación establecida mediante un FIFO.
 * - Su propósito es permitir que el usuario envíe mensajes al servidor para su procesamiento.
 * - Después de enviar un mensaje, el cliente espera recibir la respuesta generada por el servidor.
 * - Cuando el usuario introduce la palabra “end”, el cliente informa al servidor y finaliza la ejecución.
 * 
 * Funcionalidades principales:
 * - Apertura o creación del archivo FIFO para establecer la comunicación.
 * - Lectura de texto ingresado por el usuario desde la consola.
 * - Envío del mensaje al proceso servidor a través del FIFO.
 * - Recepción de la respuesta enviada por el servidor.
 * - Visualización en pantalla de los mensajes enviados y recibidos.
 * 
 *****************************************************************************************************************/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_FILE "/tmp/fifo_twoway"

int main() {
   int fd;
   int end_process;       /* Variable que determina si se debe finalizar el programa */
   int stringlen;         /* Longitud del texto ingresado por el usuario */
   int read_bytes;        /* Número de bytes recibidos desde el FIFO */
   char readbuf[80];      /* Espacio donde se almacenan mensajes enviados y recibidos */
   char end_str[5];       /* Palabra que indica el final del proceso */

   /* Mensaje inicial para el usuario indicando cómo salir del programa */
   printf("FIFO_CLIENT: Send messages, infinitely, to end enter \"end\"\n");

   /* Abre el FIFO con permisos de lectura/escritura */
   fd = open(FIFO_FILE, O_CREAT | O_RDWR, 0640);
   strcpy(end_str, "end");

   /* envía mensajes continuamente hasta recibir orden de terminar */
   while (1) {
      printf("Enter string: ");

      /* Captura una línea escrita por el usuario desde la entrada estándar */
      fgets(readbuf, sizeof(readbuf), stdin);

      /* Calcula el número de caracteres ingresados */
      stringlen = strlen(readbuf);
      readbuf[stringlen - 1] = '\0';

      /* Compara lo ingresado con la palabra "end" para saber si debe detenerse */
      end_process = strcmp(readbuf, end_str);

      /* Si el texto NO es "end", continúa la comunicación */
      if (end_process != 0) {
         /* Envía la cadena ingresada al proceso servidor a través del FIFO */
         write(fd, readbuf, strlen(readbuf));
         printf("FIFOCLIENT: Sent string: \"%s\" and string length is %d\n", readbuf, (int)strlen(readbuf));

         /* Espera la respuesta del servidor (cadena invertida) */
         read_bytes = (int)read(fd, readbuf, sizeof(readbuf) - 1);

         /* Si ocurre un error al leer, vuelve a intentar */
         if (read_bytes < 0) continue;

         /* Agrega un terminador nulo al final del texto recibido */
         readbuf[read_bytes] = '\0';

         /* Muestra en pantalla la respuesta recibida desde el servidor */
         printf("FIFOCLIENT: Received string: \"%s\" and length is %d\n", readbuf, read_bytes);
      } else  {
         /* Si el usuario escribió "end", envía esa palabra al servidor */
         write(fd, readbuf, strlen(readbuf));
         printf("FIFOCLIENT: Sent string: \"%s\" and string length is %d\n", readbuf, (int)strlen(readbuf));

         /* Cierra el descriptor del FIFO y termina la ejecución del cliente */
         close(fd);
         break;
      }
   }
  return 0;
}
