# Get Next Line (get_next_line)

## Descripción General

El proyecto `get_next_line` es una función en C que permite leer líneas de texto de un descriptor de archivo (file descriptor) de manera eficiente. Esta función es comúnmente utilizada en proyectos de programación de bajo nivel, como en la escuela 42, para aprender conceptos avanzados de manejo de memoria, buffers y lectura de archivos.

La función principal `get_next_line(int fd)` devuelve la siguiente línea de texto del archivo especificado por el descriptor `fd`, incluyendo el carácter de nueva línea (`\n`) si existe. Si se llega al final del archivo, retorna `NULL`.

## Conceptos Clave

### 1. Descriptores de Archivo (File Descriptors)
- En sistemas Unix-like, los descriptores de archivo son enteros que representan archivos abiertos, sockets, pipes, etc.
- `0` es stdin, `1` es stdout, `2` es stderr.
- La función `read()` se usa para leer datos de estos descriptores.

### 2. Buffer y Lectura Eficiente
- `BUFFER_SIZE` define cuántos bytes se leen en cada llamada a `read()`.
- Leer byte por byte sería ineficiente; usar un buffer mejora el rendimiento.
- El buffer debe ser lo suficientemente grande para manejar líneas largas.

### 3. Static Variables (Variables Estáticas)
- La variable `static char *s_stash` en `get_next_line` persiste entre llamadas a la función.
- Esto permite almacenar datos leídos que no forman una línea completa aún.

### 4. Manejo de Memoria
- Todas las asignaciones de memoria (`malloc`) deben liberarse (`free`) para evitar leaks.
- La función debe manejar errores de memoria correctamente.

### 5. Funciones Auxiliares
- `ft_strchr`: Busca un carácter en una cadena.
- `ft_strlen`: Calcula la longitud de una cadena.
- `ft_strjoin`: Concatena dos cadenas, liberando la primera.
- `ft_extract_line`: Extrae la línea completa del stash.
- `ft_trim_stash`: Recorta el stash para remover la línea ya extraída.

## Cómo Funciona Paso a Paso

### Función Principal: `get_next_line(int fd)`

1. **Validación Inicial**:
   - Verifica que `fd` sea válido (>= 0) y `BUFFER_SIZE > 0`.
   - Si no, retorna `NULL`.

2. **Lectura y Unión**:
   - Llama a `read_and_join(fd, s_stash)` para leer datos adicionales si es necesario.
   - Esta función lee en bloques de `BUFFER_SIZE` hasta encontrar un `\n` o EOF.

3. **Extracción y Limpieza**:
   - Llama a `extract_and_clean(&s_stash)` para obtener la línea y actualizar el stash.
   - Retorna la línea obtenida.

### Función `read_and_join(int fd, char *stash)`

- Asigna un buffer temporal.
- En un bucle, lee datos mientras no haya `\n` en stash y se sigan leyendo bytes.
- Une los datos leídos al stash existente.
- Maneja errores de lectura y memoria.

### Función `extract_and_clean(char **stash)`

- Extrae la línea completa usando `ft_extract_line`.
- Recorta el stash usando `ft_trim_stash`.
- Retorna la línea.

## Funciones Auxiliares Detalladas

### `ft_strchr(const char *s, int c)`
- Recorre la cadena `s` buscando el carácter `c`.
- Retorna un puntero al carácter encontrado o `NULL`.

### `ft_strlen(const char *s)`
- Cuenta caracteres hasta el `\0`.
- Retorna la longitud.

### `ft_strjoin(char *s1, char *s2)`
- Calcula longitudes de `s1` y `s2`.
- Asigna memoria para la nueva cadena.
- Copia `s1` y `s2`, añade `\0`.
- Libera `s1`.
- Retorna la nueva cadena.

### `ft_extract_line(char *stash)`
- Encuentra la posición del `\n` o fin de cadena.
- Asigna memoria para la línea.
- Copia los caracteres hasta el `\n` (incluyéndolo).
- Retorna la línea.

### `ft_trim_stash(char *stash)`
- Encuentra el `\n`.
- Si no hay, libera stash y retorna `NULL`.
- Calcula la longitud restante.
- Asigna memoria para el nuevo stash.
- Copia los datos después del `\n`.
- Libera el stash original.
- Retorna el nuevo stash.

## Compilación y Uso

### Compilación
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c -o get_next_line
```

### Uso Básico
```c
#include "get_next_line.h"
#include <fcntl.h>

int main() {
    int fd = open("archivo.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL) {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return 0;
}
```

## Debugging con GDB

Para depurar el código:

1. Compila con `-g`:
   ```bash
   cc -g -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o debug_program
   ```

2. Ejecuta gdb:
   ```bash
   gdb ./debug_program
   ```

3. Comandos útiles en gdb:
   - `break get_next_line` : Pone un breakpoint en la función.
   - `run` : Ejecuta el programa.
   - `next` : Avanza línea por línea.
   - `step` : Entra en funciones.
   - `print variable` : Muestra el valor de una variable.
   - `watch stash` : Monitorea cambios en stash.

## Consideraciones Especiales

- **Múltiples Descriptores**: La variable static `s_stash` es compartida, pero en implementaciones avanzadas se usa un array para múltiples fd.
- **BUFFER_SIZE**: Debe ser > 0. Valores pequeños causan más llamadas a `read()`, valores grandes usan más memoria.
- **Errores**: Manejar `read()` fallos, memoria insuficiente.
- **Norminette**: En 42, el código debe seguir reglas estrictas de estilo.

## Explicación para Expertos

Este proyecto enseña:
- **Gestión de Buffers**: Cómo leer eficientemente sin desperdiciar memoria.
- **Persistencia de Estado**: Uso de static para mantener estado entre llamadas.
- **Manejo de Errores**: Robustez ante fallos de sistema.
- **Algoritmos de Cadenas**: Implementación manual de funciones de string.

Para explicarlo a alguien con conocimientos:
- Enfatiza cómo el stash actúa como un buffer acumulativo.
- Discute trade-offs de BUFFER_SIZE.
- Muestra cómo evita leer más allá de lo necesario.
- Compara con `getline()` de stdio.h, pero más bajo nivel.

Este proyecto es fundamental para entender I/O en C y diseño de APIs eficientes.