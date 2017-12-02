# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clanier <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/23 15:18:27 by clanier           #+#    #+#              #
#    Updated: 2017/12/02 18:58:04 by clanier          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

LINK			=	libft_malloc.so
NAME			=	$(LINK:.so=$(addprefix _, $(HOSTTYPE)).so)
SHEL			=	/bin/sh
CC				=	gcc
CFLAGS			=	-g -Wall -Wextra -Werror
SRCS_DIR		=	srcs/
SRCS_LIST		=	alloc_mem_funcs.c free.c main.c \
					print_funcs.c show_alloc_mem.c \
					calloc.c init.c malloc.c realloc.c
SRCS			=	$(addprefix $(SRCS_DIR), $(SRCS_LIST))
OBJS_DIR		=	objs/
OBJS_LIST		=	$(patsubst %.c, %.o, $(SRCS_LIST))
OBJS			=	$(addprefix $(OBJS_DIR), $(OBJS_LIST))
HEADERS			=	-I./includes

all : $(NAME)

.PHONY: all clean

$(NAME) : $(OBJS)
	@echo "\033[37mLinking...\033[0m"
	@gcc $(OBJS) -shared -o $(NAME)
	@echo "\033[32mLibrary \033[1;32m$(NAME)\033[1;0m\033[32m created.\033[0m"
	@rm -rf $(LINK)
	@ln -s $(NAME) $(LINK)
	@echo "\033[1;32m$(LINK)\033[0;32m -> \033[1;32m$(NAME)\033[1;0m"

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@
	@echo "\033[34mCompilation of \033[36m$(notdir $<)\033[34m done.\033[0m"

clean :
	@rm -rf $(OBJS_DIR)
	@echo "\033[31mObjects files \033[1;31m$(OBJS_LIST)\033[1;0m\033[31m removed.\033[0m"

fclean :
	@rm -rf $(OBJS_DIR)
	@rm -rf $(NAME) $(LINK)
	@echo "\033[31mLink \033[1;31m$(LINK)\033[1;0m\033[31m removed.\033[0m"
	@echo "\033[31mLib \033[1;31m$(NAME)\033[1;0m\033[31m removed.\033[0m"

re : fclean all
