/***************************************************************************************
PONTIFICIA UNIVERSIDAD JAVERIANA
Autor: Juan Diego Rojas
Materia: Sistemas Operativos
Profesor: John Corredor
Clase: 2154
Descripcion: Archivo reverse_string.h
Este archivo contiene la declaración de la función reverse_string utilizada para invertir
cadenas de caracteres. Se utiliza en el archivo productor para procesar las cadenas
recibidas desde el consumidor. Este archivo funciona como un encabezado externo que
permite modularizar el código fuente.
****************************************************************************************/

#ifndef REVERSE_STRING_H   // Verifica si REVERSE_STRING_H no ha sido definido aún
#define REVERSE_STRING_H   // Define REVERSE_STRING_H para evitar inclusiones múltiples

// Declaración de la función reverse_string:
// Recibe un puntero a una cadena de caracteres y la invierte en el mismo lugar (in-place).
void reverse_string(char *str);

#endif // REVERSE_STRING_H  // Fin de la directiva de inclusión condicional
