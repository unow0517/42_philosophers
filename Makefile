# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/09 20:32:15 by yowoo             #+#    #+#              #
#    Updated: 2024/07/10 11:48:16 by yowoo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror

SRCS = main.c utils.c check_input.c init_struct.c

OBJS = $(SRCS:.c=.o)

NAME = philo

HEADERS = philo.h

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS)
	cc $(CFLAGS) $(OBJS) -I $(HEADERS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
