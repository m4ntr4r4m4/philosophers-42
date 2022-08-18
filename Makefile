# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/07 13:14:42 by ahammoud          #+#    #+#              #
#    Updated: 2022/08/08 20:57:20 by ahammoud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	./philo.c ./ft_atoi.c ./utils.c

OBJS	=	${SRCS:.c=.o}

.c.o	:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I includes/

NAME	=	 philo

CFLAGS	=	-Wall -Werror -Wextra -g -pthread 


CC	=	gcc


${NAME}	:	${OBJS} 
			${CC}  ${OBJS}  -o ${NAME}

all	:	${NAME}

RM	=	rm -f

clean	:
		${RM} ${OBJS}

fclean	:	clean
			${RM} ${NAME}

re		:	fclean all

.PHONY	:	all clean fclean re
