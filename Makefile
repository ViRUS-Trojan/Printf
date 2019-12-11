# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/11 19:24:17 by vdelsie           #+#    #+#              #
#    Updated: 2019/12/11 19:24:23 by vdelsie          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RM = /bin/rm -f

NAME = libftprintf.a
SRCS_DIR = ./
FILES = ft_printf parse_prespecifiers parse_specifier int_handlers\
uint_handlers double_handlers str_char_handlers special_handlers\
hard_double_handlers printf_gen_utils printf_double_utils printf_utf_utils\
printf_int_utils
CFILES = $(patsubst %, $(SRCS_DIR)%.c, $(FILES))
OFILES = $(patsubst %, %.o, $(FILES))
INCLUDES = ./includes
CFLAGS = -Wall -Wextra -Werror -O2

#libft
LFT = ./libft/
LFT_FILES = ft_isdigit ft_bzero ft_memset ft_isascii ft_strlen
LFT_CFILES = $(patsubst %, $(LFT)%.c, $(LFT_FILES))
LFT_OFILES = $(patsubst %, %.o, $(LFT_FILES))
LFT_LIB = $(addprefix $(LFT), ft.a)
LFT_INC = -I $(LFT)includes/


.PHONY: all clean fclean re

all : $(LFT_LIB) $(NAME)

$(LFT_LIB):
	make -C $(LFT)

$(OFILES) :
	gcc $(CFLAGS) -c -I $(INCLUDES) $(LFT_INC) $(LFT_CFILES) $(CFILES)

$(NAME) : $(OFILES)
	ar rc $(NAME) $(OFILES) $(LFT_OFILES)
	ranlib $(NAME)

clean :
	make -C $(LFT) clean
	$(RM) $(OFILES)
	$(RM) $(LFT_OFILES)

fclean : clean
	make -C $(LFT) fclean
	$(RM) $(NAME)

re : fclean all
