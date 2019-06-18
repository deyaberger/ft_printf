# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/30 19:03:50 by ncoursol          #+#    #+#              #
#    Updated: 2019/06/18 16:25:05 by ncoursol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NO_COLOR = \033[0m
COMP_COLOR = \033[33m
BIN_COLOR = \033[32m
BIN2_COLOR = \033[36m
PROG_COLOR = \033[35m

NAME = libftprintf.a
CC = gcc
FLAGS = -Wall -Wextra -Werror

LIB_DIR = ./libft

SOURCES = ft_format_csp.c\
ft_format_di.c\
ft_nan_inf.c\
ft_print_float.c\
ft_format_f.c\
ft_format_u.c\
ft_format_xx.c\
ft_check_add.c\
ft_check_char.c\
ft_convert.c\
ft_printf.c\
ft_ltoa.c\
ft_ftoa.c\
ft_utoa.c\
ft_dtoh.c\
ft_format_pct.c\
ft_format_b.c\
ft_format_o.c\
ft_color.c\
ft_float.c\
ft_mult2.c\

OBJ = $(SOURCES:.c=.o)

INCLUDE = ft_printf.h

.PHONY: all clean fclean re norme

$(NAME): $(OBJ)
	(cd $(LIB_DIR) && $(MAKE))
	cp libft/libft.a ./$(NAME)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)
	@echo "$(COMP_COLOR)   --- Compiled ! ---  $(NO_COLOR)"

all: $(NAME)

norme: fclean
	norminette $(SRC)

clean:
	rm -rf $(OBJ)
	(cd $(LIB_DIR) && $(MAKE) $@)
	@echo "$(BIN2_COLOR)   --- Binary   deleted ---        $(NO_COLOR)"

fclean: clean
	rm -rf $(NAME)
	rm -rf $(LIB_SRC)
	(cd $(LIB_DIR) && $(MAKE) $@)
	@echo "$(PROG_COLOR)   --- Program  deleted ---        $(NO_COLOR)"

re: fclean all
