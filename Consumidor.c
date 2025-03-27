/***************************************************************************************
PONTIFICA UNIVERSIDAD JAVERIANA
Autor: Juan Diego Rojas
Materia: Sistemas Operativos
Profesor: John Corredor
Clase: 2154
Descripcion: Archivo Cliente - Consumidor
Este programa implementa el rol de consumidor en una comunicación entre procesos usando
FIFO (named pipe). El consumidor envía cadenas al productor, recibe la cadena invertida
y la muestra por pantalla. Finaliza cuando se ingresa la palabra "end".
****************************************************************************************/

#include <stdlib.h>     // Funciones generales
#include <stdio.h>      // Entrada/salida estándar
#include <string.h>     // Manejo de cadenas
#include <unistd.h>     // Funciones POSIX: read, write, close
#include <fcntl.h>      // open, O_RDWR
#include <sys/stat.h>   // mkfifo (por si se agrega la creación aquí)
#include <sys/types.h>  // Tipos para llamadas al sistema

#define FIFO_FILE "/tmp/fifo_twoway"  // Ruta del archivo FIFO compartido con el productor

/*############################
CLIENTE
Este programa actúa como consumidor: toma cadenas desde el teclado, las envía al productor,
espera la respuesta invertida y la muestra en pantalla. Si se ingresa "end", termina.
############################*/


int main() {
   int fd;                 // Descriptor de archivo del FIFO
   int end_process;        // Variable para saber si se ingresó "end"
   int stringlen;          // Longitud de la cadena ingresada
   int read_bytes;         // Bytes leídos desde el FIFO
   char readbuf[80];       // Buffer para enviar/recibir la cadena
   char end_str[5];        // Cadena "end" para finalizar el programa

   // Mensaje inicial para el usuario
   printf("FIFO_CLIENT: Send messages, infinitely, to end enter \"end\"\n");

   // Abrir el FIFO en modo lectura/escritura. O_CREAT asegura que se cree si no existe
   fd = open(FIFO_FILE, O_CREAT | O_RDWR);

   // Guardar la palabra de finalización
   strcpy(end_str, "end");

   // Bucle principal de interacción
   while (1) {
      // Solicitar al usuario que ingrese una cadena
      printf("Enter string: ");
      fgets(readbuf, sizeof(readbuf), stdin); // Leer con salto de línea

      // Obtener la longitud real sin el salto de línea final
      stringlen = strlen(readbuf);
      readbuf[stringlen - 1] = '\0'; // Eliminar '\n'

      // Comparar si la cadena es "end"
      end_process = strcmp(readbuf, end_str);

      if (end_process != 0) {
         // Si no es "end", enviar la cadena al productor
         write(fd, readbuf, strlen(readbuf));
         printf("FIFOCLIENT: Sent string: \"%s\" and string length is %d\n", readbuf, (int)strlen(readbuf));

         // Esperar respuesta del productor
         read_bytes = read(fd, readbuf, sizeof(readbuf));
         readbuf[read_bytes] = '\0'; // Terminar correctamente la cadena

         // Mostrar la cadena invertida
         printf("FIFOCLIENT: Received string: \"%s\" and length is %d\n", readbuf, (int)strlen(readbuf));
      } else {
         // Si es "end", también se envía al productor y se termina
         write(fd, readbuf, strlen(readbuf));
         printf("FIFOCLIENT: Sent string: \"%s\" and string length is %d\n", readbuf, (int)strlen(readbuf));
         close(fd); // Cerrar el FIFO
         break;     // Salir del bucle
      }
   }

   return 0; // Fin del programa
}
