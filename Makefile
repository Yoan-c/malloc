# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ycoutena <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/04 08:44:56 by ycoutena          #+#    #+#              #
#    Updated: 2017/11/24 12:04:32 by ycoutena         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	./src/ft_add_memory.c ./src/ft_create_memory.c ./src/ft_free.c \
			./src/ft_global.c ./src/ft_malloc.c ./src/ft_other.c \
			./src/ft_realloc.c ./src/ft_variable.c ./src/show_alloc_mem.c

ICD		=	./include/malloc.h

LN		=	libft_malloc.so

OBJS	=	$(SRCS:.c=.o)

LIBPRINTF = libftprintf.a

DIROBJ	=	./src/obj

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror -I includes/

RM		=	rm -rf

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif	

NAME	= 	libft_malloc_$(HOSTTYPE).so


all		:	$(NAME)

$(NAME)	:
			@(cd ft_printf/ && $(MAKE))
			@$(CC) $(CFLAGS) -c $(SRCS)
			@$(CC) -o $(NAME) -shared *.o ft_printf/$(LIBPRINTF)
			@mv *.o src
			@mkdir $(DIROBJ)
			@mv ./src/*.o $(DIROBJ)
			@ln -s $(NAME) $(LN)

clean	:
			@$(RM) $(DIROBJ)
			@(cd ft_printf/ && $(MAKE) clean)

fclean	:	clean
			@$(RM) $(NAME)
			@$(RM) $(LN)
			@(cd ft_printf/ && $(MAKE) fclean)

re		:	fclean all

.PHONY: clean fclean re
