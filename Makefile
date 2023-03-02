# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/15 16:27:16 by gissao-m          #+#    #+#              #
#    Updated: 2023/03/02 19:15:40 by gissao-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
INCLUDE = -I ./include/
CFLAGS = -pthread -g $(INCLUDE)


RM = rm -rf

PATH_SRC = ./src/

PATH_OBJS = ./objs/

SRC =	$(PATH_SRC)main.c \
		$(PATH_SRC)libft_utils.c \
		$(PATH_SRC)check.c \
		$(PATH_SRC)eat.c \
		$(PATH_SRC)fork.c \
		$(PATH_SRC)free.c \
		$(PATH_SRC)init_struct.c \
		$(PATH_SRC)init_thread.c \
		$(PATH_SRC)mutex.c \
		$(PATH_SRC)time.c \
		$(PATH_SRC)validate_args.c \
		

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