# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/09 14:29:49 by jjesberg          #+#    #+#              #
#    Updated: 2023/02/13 21:22:37 by jjesberg         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosophers

SRC =	src/main.c \
		src/error.c \
		src/utils.c \
		src/time.c \
		src/philo.c \
		src/init.c \
		src/routine.c \
		src/forks.c

OBJ = $(SRC:.c=.o)

CC = gcc

FLAGS = -Wall -Wextra -pthread -g -fsanitize=thread -Werror

all: $(NAME)

%.o:%.c
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $@

clean:
	rm -rf $(OBJ)

fclean:
	rm -rf $(NAME)
	rm -rf src/*.o

re: fclean all