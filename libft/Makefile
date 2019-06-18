# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/07 16:39:25 by ydonse            #+#    #+#              #
#    Updated: 2019/05/13 15:02:58 by malluin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC_PATH = src

SRC_NAME = ft_atoi.c ft_memdel.c ft_strclr.c ft_strncat.c\
ft_bzero.c      ft_memmove.c    ft_strcmp.c     ft_strncmp.c\
ft_isalnum.c    ft_memset.c     ft_strcpy.c     ft_strncpy.c\
ft_isalpha.c    ft_putchar.c    ft_strdel.c     ft_strnequ.c\
ft_isascii.c    ft_putchar_fd.c ft_strdup.c     ft_strnew.c\
ft_isdigit.c    ft_putendl.c    ft_strequ.c     ft_strnstr.c\
ft_isprint.c    ft_putendl_fd.c ft_striter.c    ft_strrchr.c\
ft_itoa.c       ft_putnbr.c     ft_striteri.c   ft_strsplit.c\
ft_memalloc.c   ft_putnbr_fd.c  ft_strjoin.c    ft_strstr.c\
ft_memccpy.c    ft_putstr.c     ft_strlcat.c    ft_strsub.c\
ft_memchr.c     ft_putstr_fd.c  ft_strlen.c     ft_strtrim.c\
ft_memcmp.c     ft_strcat.c     ft_strmap.c     ft_tolower.c\
ft_memcpy.c     ft_strchr.c     ft_strmapi.c    ft_toupper.c\
ft_lstnew.c		ft_lstdelone.c	ft_lstdel.c		ft_lstadd.c\
ft_lstiter.c	ft_lstmap.c		ft_swap.c		ft_sort_integer_table.c\
ft_print_words_tables.c		ft_recursive_power.c	ft_sqrt.c\
ft_strsub_free.c	ft_strdup_free.c	ft_strjoin_free.c get_next_line.c\
ft_sqrt_high.c ft_get_nbr.c ft_free_tab_str.c ft_llitoa.c ft_lutoa.c\
ft_longlen.c ft_abs.c switch_bool.c ft_gnl_utils.c

OBJ_NAME = $(SRC_NAME:.c=.o)

OBJ_PATH = obj

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

HEADER_PATH = includes/

HEADER_NAME = libft.h get_next_line.h

HEADER = $(addprefix $(HEADER_PATH)/,$(HEADER_NAME))

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $@ $^

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(HEADER)
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@gcc  -Wall -Werror -Wextra -I $(HEADER_PATH) -MMD -o $@ -c $<

clean:
	@rm -f $(OBJ) $(OBJ:.o=.d)
	@rmdir $(OBJ_PATH) 2> /dev/null || true

fclean: clean
	@rm -f $(NAME)

re: fclean
	$(MAKE) all

.PHONY: make clean fclean re

-include $(OBJ:.o=.d)
