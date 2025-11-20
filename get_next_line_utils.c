// Incluye el archivo de cabecera que define BUFFER_SIZE y prototipos de funciones
#include "get_next_line.h"
// Incluye la biblioteca estándar para malloc y free
#include <stdlib.h>

// Función que busca la primera ocurrencia de un carácter en una cadena
char	*ft_strchr(const char *s, int c)
{
	// Bucle que recorre la cadena hasta el carácter nulo
	while (*s)
	{
		// Si encuentra el carácter buscado, retorna un puntero a esa posición
		if (*s == (char)c)
			return ((char *)s);
		// Avanza al siguiente carácter
		s++;
	}
	// Si no encuentra el carácter, retorna NULL
	return (NULL);
}

// Función que calcula la longitud de una cadena
size_t	ft_strlen(const char *s)
{
	// Declara una variable para almacenar la longitud
	size_t	len;

	// Inicializa la longitud en 0
	len = 0;
	// Bucle que cuenta caracteres hasta encontrar el nulo
	while (s[len])
		len++;
	// Retorna la longitud calculada
	return (len);
}

// Función que concatena dos cadenas, liberando la primera
char	*ft_strjoin(char *s1, char *s2)
{
	// Declara variables para las longitudes de las cadenas
	size_t	len1;
	size_t	len2;
	// Declara un puntero para el resultado concatenado
	char	*result;
	// Declara un índice para bucles
	size_t	i;

	// Si s1 es NULL, su longitud es 0; de lo contrario, calcula con ft_strlen
	if (!s1)
		len1 = 0;
	else
		len1 = ft_strlen(s1);
	// Calcula la longitud de s2
	len2 = ft_strlen(s2);
	// Asigna memoria para el resultado: longitudes totales + 1 para el nulo
	result = malloc(len1 + len2 + 1);
	// Si la asignación falla, retorna NULL
	if (!result)
		return (NULL);
	// Inicializa el índice para copiar s1
	i = 0;
	// Bucle para copiar s1 al resultado
	while (i < len1)
	{
		result[i] = s1[i];
		i++;
	}
	// Reinicia el índice para copiar s2
	i = 0;
	// Bucle para copiar s2 al resultado después de s1
	while (i < len2)
	{
		result[i + len1] = s2[i];
		i++;
	}
	// Añade el carácter nulo al final
	result[len1 + len2] = '\0';
	// Libera la memoria de s1 ya que no se necesita más
	free(s1);
	// Retorna el resultado concatenado
	return (result);
}

// Función que extrae la línea completa del stash (hasta '\n' o fin)
char	*ft_extract_line(char *stash)
{
	// Declara un puntero para encontrar la posición del '\n'
	char	*newline;
	// Declara una variable para la longitud de la línea
	size_t	len;
	// Declara un puntero para la línea extraída
	char	*line;
	// Declara un índice para el bucle de copia
	size_t	i;

	// Busca la primera ocurrencia de '\n' en stash
	newline = ft_strchr(stash, '\n');
	// Si hay '\n', la longitud es hasta '\n' inclusive; de lo contrario, toda la cadena
	if (newline)
		len = newline - stash + 1;
	else
		len = ft_strlen(stash);
	// Asigna memoria para la línea: longitud + 1 para el nulo
	line = malloc(len + 1);
	// Si la asignación falla, retorna NULL
	if (!line)
		return (NULL);
	// Inicializa el índice para copiar
	i = 0;
	// Bucle para copiar los caracteres de stash a line
	while (i < len)
	{
		line[i] = stash[i];
		i++;
	}
	// Añade el carácter nulo al final de line
	line[len] = '\0';
	// Retorna la línea extraída
	return (line);
}

// Función que recorta el stash para remover la línea ya extraída
char	*ft_trim_stash(char *stash)
{
	// Declara un puntero para encontrar la posición del '\n'
	char	*newline;
	// Declara una variable para la longitud del nuevo stash
	size_t	len;
	// Declara un puntero para el nuevo stash
	char	*new_stash;
	// Declara un índice para el bucle de copia
	size_t	i;

	// Busca la primera ocurrencia de '\n' en stash
	newline = ft_strchr(stash, '\n');
	// Si no hay '\n', significa que stash está vacío o no tiene línea completa, libera y retorna NULL
	if (!newline)
	{
		free(stash);
		return (NULL);
	}
	// Calcula la longitud de la parte restante después del '\n'
	len = ft_strlen(newline + 1);
	// Asigna memoria para el nuevo stash: longitud + 1 para el nulo
	new_stash = malloc(len + 1);
	// Si la asignación falla, retorna NULL
	if (!new_stash)
		return (NULL);
	// Inicializa el índice para copiar
	i = 0;
	// Bucle para copiar los caracteres restantes a new_stash
	while (i < len)
	{
		new_stash[i] = newline[1 + i];
		i++;
	}
	// Añade el carácter nulo al final de new_stash
	new_stash[len] = '\0';
	// Libera la memoria del stash original
	free(stash);
	// Retorna el nuevo stash recortado
	return (new_stash);
}