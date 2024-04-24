# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: otodd <otodd@student.42london.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/13 17:53:24 by otodd             #+#    #+#              #
#    Updated: 2024/04/24 17:51:34 by otodd            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

YELLOW	=	\033[1;33m
RED		=	\033[1;31m
GREEN	=	\033[1;32m
BLUE	=	\033[1;34m
CYAN	=	\033[1;36m
NC		=	\033[0m

all:
	@$(MAKE) -s -C philo
	@$(MAKE) -s -C philo_bonus


clean:
	@echo "[$(YELLOW)PHILO$(NC)]	    Cleaning object directory..."
	@$(MAKE) -s -C philo clean
	@$(MAKE) -s -C philo_bonus clean

fclean: clean
	@echo "[$(RED)PHILO$(NC)]	    Cleaning executable directory..."
	@$(MAKE) -s -C philo fclean
	@$(MAKE) -s -C philo_bonus fclean

re: fclean all

.PHONY: all clean fclean re
