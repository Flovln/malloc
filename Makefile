# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fviolin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/23 17:41:56 by fviolin           #+#    #+#              #
#    Updated: 2017/09/12 15:14:14 by fviolin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

SRCS = srcs/malloc.c \
	   srcs/free.c \
	   srcs/realloc.c \
	   srcs/show_alloc_mem.c \
	   srcs/size.c \
	   srcs/blocks_handler.c \
	   srcs/chunks_handler.c

OBJS = $(SRCS:.c=.o)
	FLAGS = -Wall -Wextra -Werror
	LIBS = -L./libft -lft	

$(NAME): $(OBJS)
	make -C ./libft
	gcc $(FLAGS) -shared $(OBJS) $(LIBS) -o $(NAME)
	ln -F -s libft_malloc_$(HOSTTYPE).so libft_malloc.so

all: $(NAME)

clean:
	rm -f $(OBJS)
	make -C ./libft/ clean

fclean:clean
	rm -rf $(NAME)
	rm -rf libft_malloc.so
	rm -rf libft_malloc_$(HOSTTYPE).so
	make fclean -C ./libft

re: fclean all

runtests:
	cp libft_malloc_$(HOSTTYPE).so libftmalloc.a
	gcc -o tests/test0 tests/test0.c -I includes/ -L . -lft_malloc -lft -L./libft/
	gcc -o tests/test1 tests/test1.c -I includes/ -L . -lft_malloc -lft -L./libft/
	gcc -o tests/test2 tests/test2.c -I includes/ -L . -lft_malloc -lft -L./libft/
	gcc -o tests/test3 tests/test3.c -I includes/ -L . -lft_malloc -lft -L./libft/
	gcc -o tests/test3_bis tests/test3_bis.c -I includes/ -L . -lft_malloc -lft -L./libft/
	gcc -o tests/test4 tests/test4.c -I includes/ -L . -lft_malloc -lft -L./libft/
	gcc -o tests/test5 tests/test5.c -I includes/ -L . -lft_malloc -lft -L./libft/
	@echo "-----------------------------------------------"
	/usr/bin/time -l ./tests/test0
	@echo "-----------------------------------------------"
	/usr/bin/time -l ./tests/test1
	@echo "-----------------------------------------------"
	/usr/bin/time -l ./tests/test2
	@echo "-----------------------------------------------"
	./tests/test3
	@echo "-----------------------------------------------"
	./tests/test3_bis
	@echo "-----------------------------------------------"
	./tests/test4
	@echo "-----------------------------------------------"
	./tests/test5
	@echo "-----------------------------------------------"

.PHONY: all clean fclean re
