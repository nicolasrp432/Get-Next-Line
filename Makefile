# Nombre del ejecutable principal
NAME = get_next_line
# Compilador a usar
CC = cc
# Flags de compilación: warnings, errores, define BUFFER_SIZE, y debug symbols
CFLAGS = -Wall -Wextra -Werror -D BUFFER_SIZE=42 -g
# Archivos fuente principales
SRCS = get_next_line.c get_next_line_utils.c
# Archivo fuente del programa de prueba
MAIN = main.c

# Regla por defecto: compila el ejecutable principal
all: $(NAME)

# Regla para compilar el ejecutable principal a partir de los fuentes
$(NAME): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

# Regla para compilar el programa de prueba incluyendo main.c
test: $(SRCS) $(MAIN)
	$(CC) $(CFLAGS) $(SRCS) $(MAIN) -o test_program

# Regla para limpiar archivos objeto y ejecutables temporales
clean:
	rm -f $(NAME) test_program

# Regla para limpieza completa (igual a clean en este caso)
fclean: clean
	rm -f $(NAME) test_program

# Regla para recompilar todo desde cero
re: fclean all