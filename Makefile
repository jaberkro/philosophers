# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jaberkro <jaberkro@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/05/23 12:14:46 by jaberkro      #+#    #+#                  #
#    Updated: 2022/05/25 13:46:00 by jaberkro      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = philo
FLAGS = -Wall -Wextra -Werror -g
INC = -I ./include

SRC_DIR = src
BUILD_DIR = obj

SRC = $(SRC_DIR)/main.c $(SRC_DIR)/parsing.c
OBJ = $(subst $(SRC_DIR), $(BUILD_DIR), $(SRC:.c=.o))

# COLORS
PINK	= \x1b[35m
BLUE	= \x1b[34m
YELLOW	= \x1b[33m
GREEN	= \x1b[32m
RED		= \x1b[31m
RESET	= \x1b[0m

all: $(BUILD_DIR) $(NAME)

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	CC $(FLAGS) $(INC) -c $^ -o $@

$(NAME): $(OBJ)
	CC $(FLAGS) $(OBJ) $(INC) -o $(NAME)
	@echo "$(RED)Done $(GREEN)COM$(YELLOW)PI$(BLUE)LING $(PINK)PHILOSOPHERS$(RESET):)"

clean:
	rm -rf $(BUILD_DIR)
	@echo "$(RED)Done $(GREEN)CLEANING$(YELLOW) PHILOSOPHERS$(PINK) :)$(RESET)"

fclean: clean
	rm -f $(NAME)
	@echo "$(RED)Done $(GREEN)FANCY CLEANING$(YELLOW) PHILOSOPHERS$(PINK) :)$(RESET)"

re: fclean all

.PHONY: all clean fclean re
