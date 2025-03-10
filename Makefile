CC = cc

CFLAGS = -g

SRC = src/main.c

OBJ = $(SRC:.c=.o)

NAME = minishell

all: $(NAME)

$(NAME): $(OBJ) 
	$(CC) $(CFLAGS) -o $@ $(OBJ) -lreadline

clean:
	@rm -f $(OBJ)


fclean: clean
	@rm -f $(NAME)
	@echo "Removing $(NAME)"

re: fclean all
