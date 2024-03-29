# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: otodd <otodd@student.42london.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/13 17:53:24 by otodd             #+#    #+#              #
#    Updated: 2024/03/26 17:34:07 by otodd            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

YELLOW=\033[1;33m
RED=\033[1;31m
GREEN=\033[1;32m
BLUE=\033[1;34m
CYAN=\033[1;36m
NC=\033[0m

CC 			= 	cc
CFLAGS 		= 	-Wall -Wextra -Werror -g
NAME		= 	philo

SRC_DIR 	= 	src
OBJ_DIR 	= 	obj
INC_DIR 	= 	include

SRCS		= 	$(SRC_DIR)/init.c		\
				$(SRC_DIR)/logging.c	\
				$(SRC_DIR)/utils.c		\
				$(SRC_DIR)/minift.c		\
				$(SRC_DIR)/routines.c	

OBJS 		= 	$(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

HEADERS		= 	-I$(INC_DIR)

all: $(NAME)

dir:
	@if [ ! -d "obj" ]; then \
		echo "[$(GREEN)PHILO$(NC)]	    Creating obj directory..."; \
		mkdir -p obj; \
	fi

$(NAME): $(OBJS)
	@echo "[$(BLUE)PHILO$(NC)]	    Building $@..."
	@$(CC) $(CFLAGS) $(OBJS) $(HEADERS) $(LIBS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/philo.h | dir
	@echo "[$(CYAN)PHILO$(NC)]	    Compiling $< --> $@"
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@


clean:
	@echo "[$(YELLOW)PHILO$(NC)]	    Cleaning object directory..."
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "[$(RED)PHILO$(NC)]	    Cleaning executable directory..."
	@rm -rf $(NAME)

re: fclean all

norm: check_norminette all

.PHONY: all clean fclean re norm
