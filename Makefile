CC = cc
CFLAGS = -g -fsanitize=address #-Wall -Wextra -Werror
VAL = valgrind --leak-check=full --track-origins=yes

SRC = src/main.c src/init.c src/builtin_1.c src/signal.c src/builtin_2.c \
	  src/builtin_utils.c src/utils.c src/env.c src/pipes.c src/redirection.c
OBJ_DIR = obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

LIBFT = libft/libft.a

NAME = minishell

all: $(NAME)

$(LIBFT):
	@make --no-print-directory -C libft

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) -lreadline
	@echo "\033[32mProgram is ready to execute\033[0m"

$(OBJ_DIR)/%.o: %.c
	@mkdir	-p	$(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@rm -rf $(OBJ_DIR)
	@make --no-print-directory fclean -C libft
	@echo "\033[31mProgram Removed\033[0m"

fclean: clean
	@rm -f $(NAME)

re: fclean all

valgrind: $(NAME)
	$(VAL) ./$(NAME)

.PHONY: all clean fclean re valgrind