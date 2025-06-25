# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Auto Generated                                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: AUTO                                    #+#    #+#              #
#    Updated: AUTO                                    ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TMPDIR := $(CURDIR)
export TMPDIR
SRCS = philo_bonus.c ft_atoi.c routine_bonus.c process_bonus.c actions_bonus.c
OBJS = $(SRCS:.c=.o)

NAME = philo_bonus

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re