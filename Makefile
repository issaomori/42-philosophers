# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/15 16:27:16 by gissao-m          #+#    #+#              #
#    Updated: 2022/12/28 18:15:32 by gissao-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
INCLUDE = -I ./include/
CFLAGS = -pthread -g $(INCLUDE)


RM = rm -rf

PATH_SRC = ./src/
PATH_MAIN = $(PATH_SRC)main/

PATH_OBJS = ./objs/

SRC =	$(PATH_MAIN)main.c \
		$(PATH_MAIN)libft_utils.c \
		$(PATH_MAIN)validate_args.c \
		

OBJS = $(patsubst $(PATH_SRC)%.c, $(PATH_OBJS)%.o, $(SRC))

all: $(NAME)

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS)  $(OBJS) -o $(NAME)

$(PATH_OBJS)%.o:	$(PATH_SRC)%.c
	@mkdir -p $(PATH_OBJS)
	@mkdir -p $(PATH_OBJS)main/
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) ./objs

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all $(PATH_OBJS) clean fclean re