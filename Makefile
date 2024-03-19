# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: otodd <otodd@student.42london.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/13 17:53:24 by otodd             #+#    #+#              #
#    Updated: 2024/03/19 12:02:56 by otodd            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

YELLOW=\033[1;33m
RED=\033[1;31m
GREEN=\033[1;32m
BLUE=\033[0;34m
NC=\033[0m

CC 		= cc
CFLAGS 	= -Wall -Wextra -Werror -g
NAME	= philo

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

SRCS	= 	$(SRC_DIR)/init.c		\
			$(SRC_DIR)/logging.c	\
			$(SRC_DIR)/utils.c		\
			$(SRC_DIR)/minift.c		

OBJS 	= 	$(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

HEADERS	= -I$(INC_DIR)

all: $(NAME)

dir:
	@if [ ! -d "obj" ]; then \
		echo "[$(GREEN)PHILO$(NC)]	    Creating obj directory..."; \
		mkdir -p obj; \
	fi

check_norminette:
	@echo "[$(BLUE)PHILO$(NC)]	    Checking for errors with Norminette..."
	@if [ $$(pip list | grep "norminette" | wc -l) -gt 1 ]; then \
		echo "[$(RED)PHILO$(NC)]	    Norminette is not installed. Please install Norminette."; \
		exit 1; \
	else \
		if [ $$(norminette src include | grep "Error:" | wc -l) -gt 0 ]; then \
			echo "[$(RED)PHILO$(NC)]	    Norminette found errors."; \
			exit 1; \
		else \
			echo "[$(GREEN)PHILO$(NC)]	    Norminette found no errors."; \
		fi; \
	fi

$(NAME): $(OBJS)
	@echo "[$(GREEN)PHILO$(NC)]	    Building $@..."
	@$(CC) $(CFLAGS) $(OBJS) $(HEADERS) $(LIBS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/philo.h | dir
	@echo "[$(GREEN)PHILO$(NC)]	    Compiling $< --> $@"
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@


clean:
	@echo "[$(YELLOW)PHILO$(NC)]	    Cleaning object files..."
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "[$(YELLOW)PHILO$(NC)]	    Cleaning executable file..."
	@rm -rf $(NAME)

re: fclean all

norm: check_norminette all

.PHONY: all clean fclean re norm
