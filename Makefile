.PHONY: all re clean fclean help
.DEFAULT_GOAL: all

CC = cc -Wall -Werror -Wextra
LIB_FLAGS = -lpthread
NAME = codexion
SRC_DIR = src
SRC = main.c args.c

OBJ_DIR = obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

re: fclean all

help:
	@echo "Arguments needed to run the program are as follows:"
	@echo "(All times given are in milliseconds)\n"
	@echo "number_of_coders	- The number of coders and available dongles"
	@echo "time_to_burnout		- The time a coder has to compile again after last compilation"
	@echo "time_to_compile		- The time it takes to compile"
	@echo "time_to_debug		- The time it takes to debug"
	@echo "time_to_refactor	- The time it takes to refactor"
	@echo "number_of_compiles_required - Number of compiles each coders has to reach until the program ends"
	@echo "dongle_cooldown		- The cooldown a dongle has before it can be used again"
	@echo "scheduler		- The scheduler used to decide coder priority, value can be only 'fifo' or 'edf'\n"

$(NAME): $(OBJ)
	$(CC) $(LIB_FLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

clean:
	-@rm $(SRC:%.c=$(OBJ_DIR)/%.o)

fclean: clean
	-@rm $(NAME)
