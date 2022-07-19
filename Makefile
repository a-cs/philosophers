# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acarneir <acarneir@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/06 20:54:08 by acarneir          #+#    #+#              #
#    Updated: 2022/07/18 20:37:23 by acarneir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
FLAGS = -g -Wall -Wextra -Werror

INCLUDE_DIR = ./includes
INCLUDE = $(INCLUDE_DIR)/philosophers.h

OBJ_DIR = ./objs
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

SRC_DIR = ./src
SRC = $(SRC_DIR)/philosophers.c \
		$(SRC_DIR)/actions.c \
		$(SRC_DIR)/watcher.c \
		$(SRC_DIR)/utils/utils.c \
		$(SRC_DIR)/utils/time.c

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) -pthread $(OBJ) -o $(NAME)
	@echo "Compiled!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDE)
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/utils
	@$(CC) -c $(FLAGS) -I$(INCLUDE_DIR) -o $@ $<

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "Deleting EVERYTHING...\n"
	@rm -rf $(NAME)
	@echo "Project cleaned up!"

re: fclean all