// Directiva de preprocesador para evitar inclusión múltiple del archivo de cabecera
#ifndef GET_NEXT_LINE_H
// Define la macro GET_NEXT_LINE_H si no está definida, para incluir el archivo solo una vez
# define GET_NEXT_LINE_H

// Verifica si BUFFER_SIZE no está definido (permite definirlo externamente)
# ifndef BUFFER_SIZE
// Define BUFFER_SIZE con un valor por defecto de 42 bytes
#  define BUFFER_SIZE 42
# endif

// Prototipo de la función principal get_next_line, que toma un descriptor de archivo y retorna una línea
char	*get_next_line(int fd);

// Fin de la condición de inclusión múltiple
#endif