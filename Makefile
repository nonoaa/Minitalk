# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: byahn <byahn@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/01 17:32:32 by byahn             #+#    #+#              #
#    Updated: 2021/08/01 17:32:34 by byahn            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = minitalk
NAME_SERVER = server
NAME_CLIENT = client
SOURCES_SERVER = server.c ft_putnbr.c
SOURCES_CLIENT = client.c ft_itoa.c
OBJECTS_SERVER = $(SOURCES_SERVER:.c=.o)
OBJECTS_CLIENT = $(SOURCES_CLIENT:.c=.o)

all: $(NAME)

$(NAME): $(NAME_SERVER) $(NAME_CLIENT)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

$(NAME_SERVER): $(OBJECTS_SERVER)
	$(CC) $(CFLAGS) -o $(NAME_SERVER) $(OBJECTS_SERVER)

$(NAME_CLIENT): $(OBJECTS_CLIENT)
	$(CC) $(CFLAGS) -o $(NAME_CLIENT) $(OBJECTS_CLIENT)

clean:
	rm -f $(OBJECTS_SERVER)
	rm -f $(OBJECTS_CLIENT)

fclean: clean
	rm -f $(NAME_SERVER)
	rm -f $(NAME_CLIENT)

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus
