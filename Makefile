NAME = get_next_line
CC = cc
CFLAGS = -Wall -Wextra -Werror -D BUFFER_SIZE=42
SRCS = get_next_line.c get_next_line_utils.c

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

clean:
	rm -f $(NAME)

fclean: clean
	rm -f $(NAME)

re: fclean all