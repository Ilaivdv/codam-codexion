.PHONY: all re clean fclean
.DEFAULT_GOAL: all

CC = cc -Wall -Werror -Wextra
LIB_FLAGS = -lpthread
NAME = codexion
SRC_DIR = src
SRC = main.c

OBJ_DIR = obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

re: fclean all

$(NAME): $(OBJ)
	$(CC) $(LIB_FLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

clean:
	@rm $(SRC:%.c=$(OBJ_DIR)/%.o)

fclean: clean
	@rm $(NAME)
