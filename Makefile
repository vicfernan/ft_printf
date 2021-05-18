# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vifernan <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/08 19:55:57 by vifernan          #+#    #+#              #
#    Updated: 2021/05/18 13:00:05 by vifernan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libftprintf.a

CFLAGS	= -Wall -Wextra -Werror

SRCS	= ft_printf.c \

OBJS	= $(SRCS:.c=.o)

INCLUDES = -I./includes

all: $(NAME)

RED = \033[0;31m
GREEN = \033[0;32m
NO_COLOR = \033[0m

$(NAME): $(OBJS)
	$(MAKE) -C ./libft
	cp libft/libft.a $(NAME)
	gcc -c $(CFLAGS) $(INCLUDES) $(SRCS)
	ar -rcs $(NAME) $(OBJS)
	@echo "$(GREEN)======[COMPILADO]===== $(NO_COLOR)"

clean:
	$(MAKE) clean -C ./libft
	rm -rf $(NAME)
	rm -rf $(OBJS)

fclean:
	$(MAKE) fclean -C ./libft
	rm -rf $(NAME)

re: fclean all

test: all
	gcc $(FLAGS) ft_printf.c $(NAME)
	./a.out | cat -e

.PHONY: all clean fclean re bonus
