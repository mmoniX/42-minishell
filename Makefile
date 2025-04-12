CC = cc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address
VAL = valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all

SRC = src/builtin_1.c src/builtin_2.c src/builtin_utils.c src/env_define.c \
	  src/execution.c src/main.c src/pipes.c src/redirection.c src/signal.c \
	  src/utils_1.c src/utils_2.c src/check.c
OBJ_DIR = obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

LIBFT = libft/libft.a

NAME = minishell

all: $(NAME)

$(LIBFT):
	@echo "\033[34m🔄 Loading....\033[0m"
	@make --no-print-directory -C libft

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) -lreadline
	@echo "\033[32m🚀 Program is ready to execute\033[0m"

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