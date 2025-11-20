#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int main(void)
{
    int fd;
    char *line;

    // Abre un archivo de prueba (crea uno si no existe)
    fd = open("test.txt", O_RDONLY);
    if (fd < 0)
    {
        printf("Error al abrir el archivo\n");
        return (1);
    }

    // Lee líneas una por una
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Línea leída: %s", line);
        free(line);
    }

    close(fd);
    return (0);
}