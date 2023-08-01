# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/10 10:08:26 by slampine          #+#    #+#              #
#    Updated: 2023/08/01 10:48:16 by slampine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SOURCES = main.c init.c utils.c monitor.c time_utils.c 
OBJECTS = $(SOURCES:%.c=%.o)
INCLUDE = -lmlx -framework OpenGL -framework AppKit

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJECTS) philo.h
	cc $(CFLAGS) $(OBJECTS) $(INCLUDE) -o $(NAME)

clean:
	rm -f $(OBJECTS)
fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re