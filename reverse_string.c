/***************************************************************************************
PONTIFICIA UNIVERSIDAD JAVERIANA
Autor: Juan Diego Rojas
Materia: Sistemas Operativos
Profesor: John Corredor
Clase: 2154
Descripcion: Archivo Funcion reverse_string.c
Este archivo contiene la implementación de la función reverse_string, que invierte el
contenido de una cadena de caracteres. Esta función es utilizada por el archivo productor
(Productores.c) para procesar la cadena recibida desde el consumidor antes de enviarla de
vuelta. Se implementa de forma modular para facilitar la reutilización y mantenimiento.
****************************************************************************************/

#include <string.h>          // Se incluye para usar strlen()
#include "reverse_string.h"  // Se incluye la declaración de la función

// Implementación de la función reverse_string:
// Invierte una cadena de caracteres en el mismo buffer (in-place)
void reverse_string(char *str) {
    int last, first;    // Índices para recorrer la cadena desde ambos extremos
    char temp;          // Variable temporal para realizar el intercambio de caracteres

    // Se obtiene el índice del último carácter válido (antes del '\0')
    last = strlen(str) - 1;

    // Se comienza desde el primer carácter
    first = 0;

    // Intercambiar caracteres hasta llegar al centro
    while (first < last) {
        temp = str[first];     // Guardar el carácter actual
        str[first] = str[last]; // Colocar el carácter del final al inicio
        str[last] = temp;       // Colocar el carácter del inicio al final

        first++;  // Avanzar hacia el centro desde el inicio
        last--;   // Avanzar hacia el centro desde el final
    }
}
