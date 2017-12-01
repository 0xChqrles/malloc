# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clanier <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/23 15:18:27 by clanier           #+#    #+#              #
#    Updated: 2017/12/01 17:53:40 by clanier          ###   ########.fr        #
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
SRCS_LIST		=	malloc.c free.c realloc.c show_alloc_mem.c
SRCS			=	$(addprefix $(SRCS_DIR), $(SRCS_LIST))
OBJS_DIR		=	objs/
OBJS_LIST		=	$(patsubst %.c, %.o, $(SRCS_LIST))
OBJS			=	$(addprefix $(OBJS_DIR), $(OBJS_LIST))
OBJS_LIBFT_DIR	=	objs_libft/
OBJS_LIBFT_LIST	=	ft_atoi.o ft_bzero.o ft_call_flags.o ft_call_nbr_flags.o ft_call_str_flags.o \
					ft_check_flags.o ft_extra_flags.o ft_f_flags.o ft_f_lens.o ft_flags.o \
					ft_flags_funcs.o ft_freejoin.o ft_get_flags.o ft_get_size.o ft_h_flags.o \
					ft_h_lens.o ft_hh_flags.o ft_hh_lens.o ft_invalid_flags.o ft_isalnum.o \
					ft_isalpha.o ft_isascii.o ft_isdigit.o ft_isprint.o ft_itoa.o ft_j_flags.o \
					ft_j_lens.o ft_l_flags.o ft_l_lens.o ft_lens.o ft_ll_flags.o ft_ll_lens.o \
					ft_memalloc.o ft_memccpy.o ft_memchr.o ft_memcmp.o ft_memcpy.o ft_memdel.o \
					ft_memmove.o ft_memset.o ft_nbrlen.o ft_nbrset_tab.o ft_nbrtotal_tab.o \
					ft_parse_flags.o ft_pow.o ft_print_flags.o ft_printf.o ft_putchar.o ft_putchar_fd.o \
					ft_putchar_tab.o ft_putendl.o ft_putendl_fd.o ft_putnbr.o ft_putnbr_fd.o \
					ft_putnbr_tab.o ft_putstr.o ft_putstr_fd.o ft_putwchar.o ft_realloc.o ft_sqrt.o \
					ft_str_flags.o ft_str_lens.o ft_strcat.o ft_strcdup.o ft_strchr.o ft_strclr.o \
					ft_strcmp.o ft_strcpy.o ft_strdel.o ft_strdup.o ft_strequ.o ft_striter.o \
					ft_striteri.o ft_strjoin.o ft_strlcat.o ft_strlen.o ft_strmap.o ft_strmapi.o \
					ft_strncat.o ft_strncmp.o ft_strncpy.o ft_strnequ.o ft_strnew.o ft_strnstr.o \
					ft_strrchr.o ft_strsplit.o ft_strstr.o ft_strsub.o ft_strtrim.o ft_tolower.o \
					ft_toupper.o ft_uputnbr.o ft_z_flags.o ft_z_lens.o get_next_line.o ft_abs.o
OBJS_LIBFT		=	$(addprefix $(OBJS_LIBFT_DIR), $(OBJS_LIBFT_LIST))
HEADERS			=	-I./includes -I./libft/includes
LIBFT_DIR		=	libft/
LIBFT_FILE		=	libft.a
LIBFT			=	$(addprefix $(LIBFT_DIR), $(LIBFT_FILE))

all : $(NAME)

.PHONY: all clean

$(NAME) : $(OBJS)
	@make --no-print-directory -C $(LIBFT_DIR)
	@echo "\033[37mLinking...\033[0m"
	@mkdir -p $(OBJS_LIBFT_DIR)
	@cp $(addprefix $(LIBFT_DIR), $(OBJS_LIBFT_LIST)) $(OBJS_LIBFT_DIR)
	@gcc $(OBJS) $(OBJS_LIBFT) -shared -o $(NAME)
	@echo "\033[32mLibrary \033[1;32m$(NAME)\033[1;0m\033[32m created.\033[0m"
	@rm -rf $(LINK)
	@ln -s $(NAME) $(LINK)
	@echo "\033[1;32m$(LINK)\033[0;32m -> \033[1;32m$(NAME)\033[1;0m"

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@
	@echo "\033[34mCompilation of \033[36m$(notdir $<)\033[34m done.\033[0m"

clean :
	@rm -rf $(OBJS_DIR) $(OBJS_LIBFT_DIR)
	@make clean --no-print-directory -C $(LIBFT_DIR)
	@echo "\033[31mObjects files \033[1;31m$(OBJS_LIST)\033[1;0m\033[31m removed.\033[0m"

fclean :
	@rm -rf $(OBJS_DIR) $(OBJS_LIBFT_DIR)
	@make fclean --no-print-directory -C $(LIBFT_DIR)
	@rm -rf $(NAME) $(LINK)
	@echo "\033[31mLink \033[1;31m$(LINK)\033[1;0m\033[31m removed.\033[0m"
	@echo "\033[31mLib \033[1;31m$(NAME)\033[1;0m\033[31m removed.\033[0m"

re : fclean all
