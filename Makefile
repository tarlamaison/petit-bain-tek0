NAME := D21

CC := gcc

SRC = main.c		\
		game.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -W -g

%.o:%.c
	$(CC) -o $@ -c $< $(CFLAGS)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re