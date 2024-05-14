# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: otodd <otodd@student.42london.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/13 17:53:24 by otodd             #+#    #+#              #
#    Updated: 2024/05/14 14:38:04 by otodd            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

YELLOW		=	\033[1;33m
RED			=	\033[1;31m
GREEN		=	\033[1;32m
BLUE		=	\033[1;34m
CYAN		=	\033[1;36m
NC			=	\033[0m
ERASE		=	\033[2K\r

CC 			= 	cc
CFLAGS 		= 	-Wall -Wextra -Werror
NAME		= 	philo
COUNTER 	= 	0
PRETTY 		= 	true

SRC_DIR 	= 	src
OBJ_DIR 	= 	obj
INC_DIR 	= 	include

SRCS		= 	$(SRC_DIR)/ft_utils.c		\
				$(SRC_DIR)/init.c			\
				$(SRC_DIR)/logging.c		\
				$(SRC_DIR)/manage.c			\
				$(SRC_DIR)/run.c			\
				$(SRC_DIR)/utils.c

OBJS 		= 	$(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

HEADERS		= 	-I$(INC_DIR)

all: $(NAME)

dir:
	@if [ ! -d "obj" ]; then \
		mkdir -p obj; \
		if [ "$(PRETTY)" = "true" ]; then \
			printf "$(ERASE)[$(GREEN)PHILO$(NC)]	    Creating obj directory..."; \
		else \
			echo "[$(GREEN)PHILO$(NC)]	    Creating obj directory..."; \
		fi \
	fi

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(HEADERS) $(LIBS) -o $@
	@if [ "$(PRETTY)" = "true" ]; then \
		printf "$(ERASE)[$(BLUE)PHILO$(NC)]	    Building $@... ($(COUNTER) sources compiled)\n"; \
	else \
		echo "[$(BLUE)PHILO$(NC)]	    Building $@..."; \
	fi

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/philo.h | dir
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@
	@if [ "$(PRETTY)" = "true" ]; then \
		printf "$(ERASE)[$(CYAN)PHILO$(NC)]	    Compiling $< --> $@"; \
		$(eval COUNTER = $(shell echo $$(($(COUNTER) + 1)))) \
	else \
		echo "[$(CYAN)PHILO$(NC)]	    Compiling $< --> $@"; \
	fi

clean:
	@rm -rf $(OBJ_DIR)
	@if [ "$(PRETTY)" = "true" ]; then \
		printf "$(ERASE)[$(YELLOW)PHILO$(NC)]	    Cleaning object directory..."; \
	else \
		echo "[$(YELLOW)PHILO$(NC)]	    Cleaning object directory..."; \
	fi
	

fclean: clean
	@rm -rf $(NAME)
	@if [ "$(PRETTY)" = "true" ]; then \
		printf "$(ERASE)[$(RED)PHILO$(NC)]	    Cleaning executable directory..."; \
	else \
		echo "[$(RED)PHILO$(NC)]	    Cleaning executable directory..."; \
	fi

re: fclean all

.PHONY: all clean fclean re
