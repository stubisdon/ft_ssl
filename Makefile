# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dkotov <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/05 09:06:23 by dkotov            #+#    #+#              #
#    Updated: 2018/09/07 11:07:39 by dkotov           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ft_ssl
COMP		= gcc
RM			= rm -rf
FLAGS		= -Wall -Wextra -Werror
FILES		= srcs/ft_ssl.c\
					srcs/ft_helper.c\
					srcs/ft_cases_new.c\
					srcs/ft_functions.c\
					srcs/ft_sha256.c\
					srcs/ft_md5.c

HEADER	= -I header/ft_ssl.h
LIB			= -L lib/ -lftprintf

$(NAME): $(FILES)
	$(COMP) -o $(NAME) $(FILES) $(LIB) $(HEADER)

all: $(NAME)

clean:
	$(RM) $(NAME)*

fclean: clean

re: fclean $(NAME)

test:
	$(COMP) -o $(NAME) $(FILES) $(LIB) $(HEADER) -g
