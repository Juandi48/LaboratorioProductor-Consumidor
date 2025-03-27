/***************************************************************************************
PONTIFICA UNIVERSIDAD JAVERIANA
Autor: Juan Diego Rojas
Materia: Sistemas Operativos
Profesor: John Corredor
Clase: 2154
Descripcion: Archivo Servidor - Productor
Se aplica el paradigma de productor consumidor, Este programa implementa el rol de
productor en un sistema de comunicación entre procesos usando FIFO (named pipes).
El productor recibe cadenas enviadas por un consumidor,las invierte usando la función
reverse_string, y las retorna al consumidor.
****************************************************************************************/


#include <stdlib.h> // Funciones generales: exit, malloc, etc.
#include <stdio.h> // Entrada y salida estándar: printf, fgets, etc.
#include <string.h> // Manejo de cadenas: strlen, strcpy, strcmp, etc.
#include <unistd.h> // Funciones POSIX: read, write, close, sleep
#include <fcntl.h> // Funciones y constantes de control de archivos: open, O_RDWR
#include <sys/stat.h> // mkfifo y permisos
#include <sys/types.h> // Tipos de datos usados en llamadas del sistema

#define FIFO_FILE "/tmp/fifo_twoway" // Ruta del archivo FIFO (pipe) usado para comunicación
#include "reverse_string.h" //Archivo funcion reverse_string.h

/*#######

SERVIDOR

Este programa actúa como el productor. Espera recibir cadenas desde el FIFO,
las invierte y las reenvía al consumidor.

####*/

void reverse_string(char *);

int main() {
   int fd;  // Descriptor de archivo para el FIFO
   char readbuf[80]; // Buffer para almacenar la cadena recibida
   char end[10]; // Palabra clave para finalizar la comunicación
   int to_end; // Variable para verificar si se recibió la palabra "end"
   int read_bytes; // Cantidad de bytes leídos desde el FIFO

   // Crear el FIFO si no existe. Se asignan permisos 0640 (lectura/escritura para dueño, lectura para grupo).
   /* Create the FIFO if it does not exist */
   mkfifo(FIFO_FILE, S_IFIFO|0640);

   // Copiar la palabra clave "end" a la variable 'end'
   strcpy(end, "end");

   // Abrir el FIFO en modo lectura/escritura
   fd = open(FIFO_FILE, O_RDWR);

   // Bucle principal: esperar cadenas desde el consumidor
   while(1) {
      // Leer datos desde el FIFO y guardar la cantidad de bytes leídos
      read_bytes = read(fd, readbuf, sizeof(readbuf));

      // Agregar terminador nulo para asegurar que la cadena esté bien formada
      readbuf[read_bytes] = '\0';

      // Mostrar en consola la cadena recibida y su longitud
      printf("FIFOSERVER: Received string: \"%s\" and length is %d\n", readbuf, (int)strlen(readbuf));

      // Comparar si se recibió la palabra "end"
      to_end = strcmp(readbuf, end);

      // Si la cadena es "end", cerrar el FIFO y salir del programa
      if (to_end == 0) {
         close(fd);
         break;
      }

      // Invertir la cadena usando reverse_string()
      reverse_string(readbuf);

      // Mostrar la cadena invertida
      printf("FIFOSERVER: Sending Reversed String: \"%s\" and length is %d\n", readbuf, (int) strlen(readbuf));

      // Escribir la cadena invertida de vuelta al FIFO
      write(fd, readbuf, strlen(readbuf));
      /*
      sleep - This is to make sure other process reads this, otherwise this
      process would retrieve the message
      */

      // Esperar 2 segundos para asegurar que el consumidor lea antes de la siguiente vuelta
      sleep(2);
   }

   // Fin del programa
   return 0;
}
