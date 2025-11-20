// Incluye el archivo de cabecera personalizado que define BUFFER_SIZE y la función get_next_line
#include "get_next_line.h"
// Incluye la biblioteca estándar para funciones como malloc y free
#include <stdlib.h>

// Función estática que lee del descriptor de archivo y une los datos al stash hasta encontrar un salto de línea o EOF
static char	*read_and_join(int fd, char *stash)
{
	// Declara un puntero para el buffer temporal donde se almacenarán los datos leídos
	char	*buffer;
	// Declara una variable para almacenar el número de bytes leídos en cada iteración
	int		bytes_read;

	// Asigna memoria para el buffer con tamaño BUFFER_SIZE + 1 para el carácter nulo
	buffer = malloc(BUFFER_SIZE + 1);
	// Si la asignación falla, retorna NULL
	if (!buffer)
		return (NULL);
	// Inicializa bytes_read en 1 para entrar al bucle
	bytes_read = 1;
	// Bucle que continúa mientras no se encuentre un '\n' en stash y se sigan leyendo bytes
	while (!ft_strchr(stash, '\n') && bytes_read > 0)
	{
		// Lee hasta BUFFER_SIZE bytes del descriptor de archivo fd al buffer
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		// Si ocurre un error en la lectura (bytes_read < 0), libera memoria y retorna NULL
		if (bytes_read < 0)
		{
			free(buffer);
			free(stash);
			return (NULL);
		}
		// Añade el carácter nulo al final del buffer para formar una cadena válida
		buffer[bytes_read] = '\0';
		// Une el contenido del buffer al stash existente, liberando el stash anterior
		stash = ft_strjoin(stash, buffer);
		// Si la unión falla, libera el buffer y retorna NULL
		if (!stash)
		{
			free(buffer);
			return (NULL);
		}
	}
	// Libera el buffer temporal ya que no se necesita más
	free(buffer);
	// Retorna el stash actualizado con los nuevos datos
	return (stash);
}

// Función estática que extrae la línea del stash y limpia el stash restante
static char	*extract_and_clean(char **stash)
{
	// Declara un puntero para la línea que se extraerá
	char	*line;

	// Extrae la línea completa (hasta '\n' o fin) del stash
	line = ft_extract_line(*stash);
	// Actualiza el stash para que contenga solo los datos restantes después de la línea
	*stash = ft_trim_stash(*stash);
	// Retorna la línea extraída
	return (line);
}

// Función principal que obtiene la siguiente línea del descriptor de archivo
char	*get_next_line(int fd)
{
	// Declara una variable estática para almacenar el stash entre llamadas (persiste entre invocaciones)
	static char	*s_stash;
	// Declara un puntero para la línea que se retornará
	char		*line;

	// Verifica si el descriptor de archivo es inválido o BUFFER_SIZE es menor o igual a 0, retorna NULL si es así
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	// Llama a read_and_join para leer y unir datos al stash
	s_stash = read_and_join(fd, s_stash);
	// Si read_and_join falla, retorna NULL
	if (!s_stash)
		return (NULL);
	// Extrae la línea y limpia el stash
	line = extract_and_clean(&s_stash);
	// Retorna la línea obtenida
	return (line);
}