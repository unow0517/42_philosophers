# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/09 20:32:15 by yowoo             #+#    #+#              #
#    Updated: 2024/07/13 21:59:23 by yowoo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror

SRCS = main.c utils.c check_input.c inits.c thread_routines.c  monitor.c

OBJS = $(SRCS:.c=.o)

NAME = philo

HEADERS = philo.h

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS)
	gcc -pthread $(CFLAGS) $(OBJS) -I $(HEADERS) -o $(NAME) -fstack-protector

#-pthread flag for linux!

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
