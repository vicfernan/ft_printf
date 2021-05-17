# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vifernan <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/08 19:55:57 by vifernan          #+#    #+#              #
#    Updated: 2021/05/17 13:02:00 by vifernan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libftprintf.a

CFLAGS	= -Wall -Wextra -Werror

SRCS	= ft_printf.c \

OBJS	= $(SRCS:.c=.o)

INCLUDES = -I./includes

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C ./libft
	cp libft/libft.a $(NAME)
	gcc -c $(CFLAGS) $(INCLUDES) $(SRCS)
	ar -rcs $(NAME) $(OBJS)

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
